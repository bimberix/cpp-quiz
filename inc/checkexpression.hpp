#pragma once

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <map>
#include <cstdlib>
#include "common.hpp"

#define CHECK_EXPRESSION(EXPR, X, A, B, C, disp_x, disp_a, disp_b, disp_c, check_x, check_a, check_b, check_c) \
[]()->std::pair<int, int> \
{ \
    int score = 0; \
    auto x = X; \
    auto a = A; \
    auto b = B; \
    auto c = C; \
    \
    std::cout << "What is the result?" << std::endl; \
    \
    std::cout << "```" << std::endl; \
    if (disp_x) std::cout << type_name(x) << " x = " << double(x) << ";" << std::endl; \
    if (disp_a) std::cout << type_name(a) << " a = " << double(a) << ";" << std::endl; \
    if (disp_b) std::cout << type_name(b) << " b = " << double(b) << ";" << std::endl; \
    if (disp_c) std::cout << type_name(c) << " c = " << double(c) << ";" << std::endl; \
    \
    std::cout << STR(EXPR) << std::endl << "```" << std::endl; \
    EXPR \
    \
    if (check_x) score += check_result("x", x); \
    if (check_a) score += check_result("a", a); \
    if (check_b) score += check_result("b", b); \
    if (check_c) score += check_result("c", c); \
    return std::make_pair<int, int>(check_x + check_a + check_b + check_c, std::forward<int>(score)); \
}
