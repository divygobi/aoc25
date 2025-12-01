// /Users/divygobiraj/Projects/aoc25/main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

int main() {
    int fres = 0;
    int res = 0;

    std::ofstream outfile("output.txt");
    outfile << '\n';    
    std::ifstream infile("input_day1.txt");
    //std::ifstream infile("input_day1_test.txt");
    if (!infile) {
        std::cerr << "Failed to open input_day1.txt\n";
    } else {
        std::string line;
        std::vector<int> turns;
        int dial = 50;
        while (std::getline(infile, line)) {
            // handle each line (example: print)
            // skip leading whitespace
            size_t p = 0;
            while (p < line.size() && (line[p] == ' ' || line[p] == '\t' || line[p] == '\r' || line[p] == '\n')){
                ++p;
            } 
            if (p >= line.size()){
                continue;
            } 

            char dir = line[p];
            // value starts immediately after dir (no space)
            size_t q = p + 1;
            while (q < line.size() && std::isspace(static_cast<unsigned char>(line[q]))) ++q;

            int value = 0;
            try {
                size_t consumed = 0;
                value = std::stoi(line.substr(q), &consumed);
                if (consumed == 0) throw std::invalid_argument("no digits");
            } catch (const std::exception&) {
                std::cerr << "Failed to parse integer after direction on line: " << line << '\n';
                continue;
            }

            int prev_dial = dial;
            res += value / 100;
            value = value % 100;
            if (dir == 'R')
            {   
                dial = (dial + value) % 100;
            } 
            else if (dir == 'L') {
                dial = (dial - value + 100) % 100;
            } 
            else {
                continue;
            }

            if (dial == 0){
                fres += 1;
                res += 1;
            }
            else if (dir == 'L' && prev_dial < dial){
                if (prev_dial != 0) {
                    res += 1;
                }
            }
            else if (dir == 'R' && prev_dial > dial){
                res += 1;
            }
            
            outfile << line << '\n';
            outfile << dial << '\n';
            outfile << res << '\n';
            outfile << fres << '\n';
            outfile << "----\n";       
         }

    }

    std::cout << "Result: " << res << '\n';
    std::cout << "Fres: " << fres << '\n';
    outfile.close();
    return 0;
}