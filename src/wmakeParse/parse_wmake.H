#ifndef MIKENO_SRC_PARSE_WMAKE_H
#define MIKENO_SRC_PARSE_WMAKE_H

#include <string>
#include <string_view>
#include <map>
#include <vector>


namespace Foam::wmakeParse {

  [[nodiscard]] std::string_view trim(std::string_view sv)noexcept;

  std::vector<std::string> parse_wmake_file(std::string file_content,std::map<std::string,std::string>& parent_dict);

}

#endif