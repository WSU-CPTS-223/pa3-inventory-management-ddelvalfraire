#if !defined(PARSER_H)
#define PARSER_H

#include "list.h"
#include "map.h"

#include <string>

namespace parser
{
    List<Map<std::string, std::string>> ReadCsv(const std::string &line);
    std::string StripLine(const std::string &str);
    Map<std::string, std::string> SplitLine(const std::string &line, const List<std::string> &header, char delimiter);
    List<std::string> SplitLine(const std::string &line, char delimiter);
}

#endif // PARSER_H
