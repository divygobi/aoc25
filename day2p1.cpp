#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>
#include <cctype>

//Ids are given as a inclusive, hyphenated range
//All on one line, comma separated
//Example: 123-456,789-1011,1213-1415

//Two invalid product ids
//Repeated parts of the id, eg 1414 and 1313 in the range 1213-1415, 
//<123><123>
int main() {
    std::ifstream inputFile("input_day2.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    if (!std::getline(inputFile, line))
    {
        std::cerr << "Error reading line from file." << std::endl;
        return 1;
    }

    //sum of all invalid product ids
    int64_t res1 = 0;

    std::vector<std::pair<int64_t, int64_t>> ranges;

    size_t pos = 0;
    while (pos < line.length()) {
        size_t dash_pos = line.find('-', pos);
        size_t comma_pos = line.find(',', pos);
        
        if (dash_pos == std::string::npos) break;
        
        int64_t start = std::stoll(line.substr(pos, dash_pos - pos));
        
        size_t end_pos = (comma_pos == std::string::npos) ? line.length() : comma_pos;
        int64_t end = std::stoll(line.substr(dash_pos + 1, end_pos - dash_pos - 1));
        
        ranges.push_back({start, end});
        
        if (comma_pos == std::string::npos) break;
        pos = comma_pos + 1;
    }

    for (const auto& range : ranges) {
        int64_t start = range.first;
        int64_t end = range.second;

        for (int64_t id = start; id <= end; ++id) {
            std::string id_str = std::to_string(id);
            bool is_invalid = false ;
            
            if (id_str.length() % 2 == 0) {
                size_t half_len = id_str.length() / 2;
                for (size_t i = 0; i < half_len; ++i) {
                    if (id_str[i] != id_str[i + half_len]) {
                        is_invalid = false;
                        break;
                    }
                    is_invalid = true;
                }
            }
            

            if (is_invalid) {
                res1 += id;
            }
        }
    }
    std::cout << "Sum of invalid product IDs: " << res1 << std::endl;
    return 0;
}