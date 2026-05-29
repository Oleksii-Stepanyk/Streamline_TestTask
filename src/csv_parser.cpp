#include "csv_parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string CSVParser::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\"");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r\"");
    return str.substr(first, (last - first + 1));
}

std::vector<ParsedRow> CSVParser::parseCSVFile(const std::string& filename) {
    std::vector<ParsedRow> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "CRITICAL ERROR: Could not open " << filename << "\n";
        return data;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        ParsedRow row;
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, row.itemName, ',');

        std::getline(ss, token, ',');
        try {
            row.quantity = std::stoi(token);
        } catch (...) {
            row.quantity = 0;
        }

        std::string catsStr;
        std::getline(ss, catsStr);

        catsStr = trim(catsStr);

        std::stringstream catSS(catsStr);
        std::string catToken;
        while (std::getline(catSS, catToken, ',')) {
            row.categories.push_back(trim(catToken));
        }

        data.push_back(row);
    }
    return data;
}