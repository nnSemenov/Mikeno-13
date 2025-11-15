//
// Created by joseph on 2025/11/15.
//

#include <ranges>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <optional>
#include <exception>
#include <format>
//#include <boost/algorithm/string.hpp>

#include "parse_wmake.H"

namespace Foam::wmakeParse {

  std::string_view trim(std::string_view sv) noexcept {
    std::string_view empty=" \t\n\r\f\v";
    const size_t idx_beg=sv.find_first_not_of(empty);
    const size_t idx_end=sv.find_last_not_of(empty);
    if(idx_beg==std::string_view::npos) {
      assert(idx_end==std::string_view::npos);
      return {};
    }
    if(idx_end<idx_beg) {
      return {};
    }
    return {sv.data()+idx_beg,sv.data()+idx_end+1};
  }

  std::vector<std::string> filter_file_lines(std::string_view text) noexcept {
    std::vector<std::string> ret;
    std::string new_line;
    for(const auto & seg: text | std::views::split('\n')) {
      std::string_view raw_line{seg};
      std::string_view line= trim(raw_line);
      const bool is_empty_line = line.empty() or line.starts_with('#');

      if(line.ends_with('\\')) {
        if(not is_empty_line)
          new_line+=line.substr(0,line.length()-1);
        continue;
      }

      if(not is_empty_line)
        new_line+=line;

      auto trim_new_line=trim(new_line);
      if(not trim_new_line.empty()) {
        ret.emplace_back(trim_new_line);
      }
      new_line.clear();
    }


    auto trim_new_line=trim(new_line);
    if(not trim_new_line.empty()) {
      ret.emplace_back(trim_new_line);
    }
    return ret;
  }

  std::optional<size_t> first_quote_location(std::string_view line) {
    size_t quote_counter=0;
    for(size_t idx=0;idx<line.size();idx++) {
      const char ch=line[idx];
      if(ch=='\'' or ch=='\"') {
        quote_counter++;
      }
      if(ch=='=') {
        if(quote_counter>0) { // = after quote, not a variable statement
          return std::nullopt;
        }
        return idx;
      }
    }
    return std::nullopt;
  }

  std::string evaluate_string(std::string_view raw,
                              const std::map<std::string,std::string>& vars,
                              const wmake_parse_option&option) {
    std::string ret;
    for(const auto & seg_: raw | std::views::split('$')) {
      std::string_view seg{seg_};
      if(seg.empty()) {
        continue;
//        throw std::runtime_error{std::format("Found invalid expression: \"{}\"",raw)};
      }

      char bracket=0;
      char reverse_bracket=0;
      if(seg[0]=='(') {
        bracket=seg[0];
        reverse_bracket=')';
      }
      if(seg[0]=='{') {
        bracket=seg[0];
        reverse_bracket='}';
      }

      if(bracket==0) {
        ret+='$';
        ret+=seg;
        continue;
      }

      const size_t reverse_bracket_loc=seg.find_first_of(reverse_bracket);
      if(reverse_bracket_loc==std::string_view::npos) {
        throw std::runtime_error{std::format("Found incomplete evaluate expression: \"${}\"",raw)};
      }

      const std::string var_name{seg.data()+1,seg.data()+reverse_bracket_loc};
      auto it = vars.find(var_name);
      const char* value = nullptr;
      if(it==vars.end()) { // non-existence variable
        switch (option.when_nonexist_variable) {
          case reference_nonexist_variable_behavior::empty_string:
            value="";
            break;
          case reference_nonexist_variable_behavior::throw_exception:
            throw std::runtime_error{std::format("Undefined reference to variable \"{}\"",var_name)};
        }
      } else{
        value=it->second.c_str();
      }
      assert(value not_eq nullptr);

      ret+=value;
      std::string_view reset_part{seg.begin()+reverse_bracket_loc+1,seg.end()};
      ret += reset_part;
    }

    return ret;
  }

  std::vector<std::string> parse_wmake_file(std::string text, std::map<std::string,std::string>& parent_dict,
                                            const wmake_parse_option&option) {
    std::vector<std::string> files;
    auto lines = filter_file_lines(text);
    for(std::string & line: lines) {
      if(line.contains('$')) {
        line= evaluate_string(line,parent_dict,option);
      }

      const auto quote_loc_opt= first_quote_location(line);
      if(not quote_loc_opt) { // not a variable statement
        files.emplace_back(line);
        continue;
      }

      const size_t quote_loc=quote_loc_opt.value();
      std::string_view var_name_raw{line.data(),quote_loc};
      std::string_view var_name = trim(var_name_raw);

      std::string_view var_value_raw{line.begin()+ptrdiff_t(quote_loc+1),line.end()};
      std::string_view var_value= trim(var_value_raw);

      parent_dict.emplace(var_name,var_value);
    }
    return files;
  }
}