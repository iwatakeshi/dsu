#include <string>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <iostream>
#include "colors.h"

extern "C" {
    void grep(const char * target, char * pattern, int flag, int linenum);
}

void grep(const char * target, char * pattern, int flag, int linenum) {
    std::string 
        s_target = target,
        s_pattern = pattern,
        c_pattern = red(pattern),
        line, result = "";
    std::istringstream iss(s_target);
    while(std::getline(iss, line)) {
        std::string temp = line;
        result = "";
        size_t start_pos = 0;

        while((start_pos = temp.find(s_pattern, start_pos)) != std::string::npos) {
            temp.replace(start_pos, s_pattern.length(), c_pattern);
            start_pos += c_pattern.length(); 
        }
        if(line.compare(temp) != 0) {
            std::string s_linenum = std::to_string(linenum);
            std::string c_linenum = green((char *)s_linenum.c_str());
            std::string s_colon = ":";
            std::string c_colon = blue((char *)s_colon.c_str());
            if(flag == 0) { result.append(temp); }
            else if (flag == 1) { result.append(c_linenum + c_colon + temp); }
        }
    }
    if(!std::isspace(result[0]) && result[0] != 0) {
        printf("%s\n", result.c_str());
    }
}