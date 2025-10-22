#include "parser.h"

#include <fstream>

namespace parser
{

    List<Map<std::string, std::string>> ReadCsv(const std::string &file)
    {
        List<Map<std::string, std::string>> data;
        std::ifstream infile(file);

        if (!infile.is_open())
            throw std::runtime_error("Could not open file: " + file);

        std::string line;
        std::getline(infile, line);
        auto header = SplitLine(line, ',');

        while (std::getline(infile, line))
        {
            auto row = SplitLine(line, header, ',');
            data.Insert(row);
        }

        infile.close();

        return data;
    }

    std::string StripLine(const std::string &str)
    {
        const std::string whitespace = " \t\n\r\f\v";
        size_t start = str.find_first_not_of(whitespace);

        if (start == std::string::npos)
            return "";

        size_t end = str.find_last_not_of(whitespace);

        return str.substr(start, end - start + 1);
    }

    List<std::string> SplitLine(const std::string &line, char delimiter)
    {
        std::string field;
        List<std::string> row;
        bool in_quotes = false;

        const auto stripped_line = StripLine(line);

        for (char c : stripped_line)
        {
            if (c == '"')
            {
                in_quotes = !in_quotes;
            }
            else if (c == delimiter && !in_quotes)
            {
                row.Insert(StripLine(field));
                field.clear();
            }
            else
            {
                field += c;
            }
        }

        row.Insert(StripLine(field));
        return row;
    }

    Map<std::string, std::string> SplitLine(const std::string &line, const List<std::string> &header, char delimiter)
    {
        Map<std::string, std::string> row;
        auto fields = SplitLine(line, delimiter);

        for (size_t i = 0; i < header.size() && i < fields.size(); ++i)
        {
            row.Insert(header[i], fields[i]);
        }

        return row;
    }
}