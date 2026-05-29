#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include <vector>

struct ParsedRow {
    std::string itemName;
    int quantity;
    std::vector<std::string> categories;
};

class CSVParser {
public:
    static std::string trim(const std::string& str);
    static std::vector<ParsedRow> parseCSVFile(const std::string& filename);
};

#endif
