//
// Created by joseph on 2025/11/15.
//

#include <ranges>
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <optional>
#include <exception>
#include <cstdlib>
#include <format>

#ifndef WIN32
#include <unistd.h>
#endif
#include "parse_wmake.H"

#include <boost/regex.hpp>

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

//  std::optional<size_t> first_quote_location(std::string_view line) {
//    size_t quote_counter=0;
//    for(size_t idx=0;idx<line.size();idx++) {
//      const char ch=line[idx];
//      if(ch=='\'' or ch=='\"') {
//        quote_counter++;
//      }
//      if(ch=='=') {
//        if(quote_counter>0) { // = after quote, not a variable statement
//          return std::nullopt;
//        }
//        return idx;
//      }
//    }
//    return std::nullopt;
//  }

  std::string evaluate_string(const std::string &input,
                              const std::map<std::string,std::string>& vars,
                              const wmake_parse_option&option) {
    namespace rules=boost::regex_constants;

    auto match_replace_with_re=[&vars,&option](const std::string&raw,const boost::regex &pattern) {
      std::string ret;
      ret.reserve(raw.size());
      boost::sregex_iterator end;
      auto prev_loc=raw.begin();
      for(auto it=boost::sregex_iterator{raw.begin(),raw.end(),pattern};it not_eq end;++it) {
        // Location of $
        const auto loc=it->operator[](0).begin();
        assert(loc>=prev_loc);
        // Copy string before $
        ret+= std::string_view{prev_loc,loc};
        // Update prev_loc to next character of )
        prev_loc=it->operator[](0).end();

        const std::string var_name{loc+2,it->operator[](0).end()-1};
        auto value_it=vars.find(var_name);
        const char* value = nullptr;
        if(value_it==vars.end()) { // non-existence variable
          switch (option.when_undefined_reference) {
            case undefined_reference_behavior::empty_string:
              value="";
              break;
            case undefined_reference_behavior::throw_exception:
              throw std::runtime_error{std::format("Undefined reference to variable \"{}\"",var_name)};
          }
        } else{
          value=value_it->second.c_str();
        }
        assert(value not_eq nullptr);
        // Append value of expression
        ret+=value;
      }
      // Append rest part
      ret+=std::string_view{prev_loc,raw.end()};
      return ret;
    };

    const boost::regex reg_bracket{R"(\$\(\w+\))"};
    std::string ret;
    ret=match_replace_with_re(input,reg_bracket);
    if(option.parse_brace_expression and ret.contains('}')) {
      const boost::regex reg_brace{R"(\$\{\w+\})"};
      ret=match_replace_with_re(ret,reg_brace);
    }
    return ret;
  }

  std::vector<std::string> parse_wmake_file(std::string_view text, std::map<std::string,std::string>& parent_dict,
                                            const wmake_parse_option&option) {
    std::vector<std::string> files;
    auto lines = filter_file_lines(text);
    const boost::regex file_pattern{R"(^\s*([\w\/\.]+)\s*$)"};
    const boost::regex single_variable_pattern{R"((\w+)\s*=\s*([\w/]+))"};
    const boost::regex multi_variable_pattern{R"((\w+)\s*=\s*([\S\s]+?)\s*$)"};
    for(std::string & line: lines) {
      if(line.contains('$')) {
        line= evaluate_string(line,parent_dict,option);
      }
      boost::smatch match;
      if(boost::regex_search(line,match,file_pattern)) {
        std::string filename=match[1].str();
        files.emplace_back(filename);
        continue;
      }
      match=boost::smatch{};
      if(boost::regex_search(line,match,single_variable_pattern)) {
        std::string var_name{match[1]};
        std::string var_value{match[2]};

        parent_dict.emplace(var_name,var_value);
        continue;
      }
      match=boost::smatch{};
      if(boost::regex_search(line,match,multi_variable_pattern)) {
        std::string var_name{match[1]};
        std::string var_value{match[2]};

        parent_dict.emplace(var_name,var_value);
        continue;
      }
      throw std::runtime_error{std::format("Expression is neither filename nor variable: \"{}\"",line)};
    }
    return files;
  }

  [[maybe_unused]] std::map<std::string,std::string> get_environment_variables() noexcept {
    std::map<std::string,std::string> vars;

    for(size_t idx=0;;idx++) {
      const char* expression_c_str=environ[idx];
      if(expression_c_str== nullptr) {
        break;
      }
      std::string_view expression{expression_c_str};
      if(expression.empty()) {
        break;
      }
      const size_t eq_loc=expression.find_first_of('=');
      std::string var_name, value;
      if(eq_loc==std::string_view::npos) {
        value="";
        var_name=expression;
      }else {
        var_name=expression.substr(0,eq_loc);
        value=expression.substr(eq_loc+1,std::string_view ::npos);
      }

      vars.emplace(var_name,value);
    }

    return vars;
  }
}
