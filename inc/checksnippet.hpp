#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "common.hpp"



#define CHECK_SNIPPET(SNIPPET) \
[]()->std::pair<int, int> \
{ \
    std::cout << "What\'s the value of \'result\' variable?" << std::endl; \
    std::string s(STR((SNIPPET))); \
    s.erase(0, 1); \
    s.erase(s.length() - 1, 1); \
    std::string::size_type pos; \
    pos = 0; \
    while(std::string::npos != (pos = s.find(";", pos))){ \
        s.replace(pos, 1, ";\n"); \
        pos+=2; \
    } \
    pos = 0; \
    while(std::string::npos != (pos = s.find("{", pos))){ \
        s.replace(pos, 1, "{\n"); \
        pos+=2; \
    } \
    std::cout << "```" << std::endl << s << "```" << std::endl; \
    { \
        try { \
            SNIPPET \
            return std::make_pair<int, int>(1, check_result("result", result)); \
        } \
        catch (...) { \
            std::cin.get(); \
            std::cout << "Exception occurred!" << std::endl; \
        } \
    } \
    return std::make_pair<int,int>(0, 0); \
} 
