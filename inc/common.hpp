#pragma once

#include <iostream>
#include <sstream>
#include <map>

#define STR(X) #X

auto get_answer()
{
    unsigned long long answer;
    
    std::string str;
    std::cin >> str;
    
    auto stream = std::stringstream(str);
    
    if (std::string::npos != str.find("x") || std::string::npos != str.find("X"))
    {
        stream >> std::hex >> answer;
    }
    else
    {
        stream >> std::dec >> answer;
    }
    
    return answer;
}

int check_result(std::string name, auto value)
{
    std::cout << name << " = ";
    auto score = value == get_answer() ? 1 : 0;
    std::cout << (score ? "That's correct! " : "Wrong answer! ") << name << " = " << value << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return score;
}

std::string type_name(auto type)
{
    static std::map<std::string, std::string> type_map;
    static bool init = false;
    
    std::string short_name = typeid(type).name();
    
    if (!init)
    {
        init = true;
        type_map.insert(std::make_pair("h", "std::uint8_t"));
        type_map.insert(std::make_pair("a", "std::int8_t"));
        type_map.insert(std::make_pair("c", "char"));
        type_map.insert(std::make_pair("s", "std::int16_t"));
        type_map.insert(std::make_pair("t", "std::uint16_t"));
        type_map.insert(std::make_pair("i", "int"));
        type_map.insert(std::make_pair("f", "float"));
        type_map.insert(std::make_pair("d", "double"));
        type_map.insert(std::make_pair("j", "unsigned int"));
        type_map.insert(std::make_pair("y", "unsigned long long"));
        type_map.insert(std::make_pair("m", "unsigned long"));
    }

    auto iter = type_map.find(short_name);
    if(iter != type_map.end())
    {
        return iter->second;
    }
    
    return short_name;
}
