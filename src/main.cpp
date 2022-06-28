#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "checkexpression.hpp"
#include "checksnippet.hpp"
#include "common.hpp"

int main ()
{
    std::vector<std::pair<int, int>(*)()> expressions{};
    
    expressions.emplace_back(CHECK_EXPRESSION(
            x = a - b;
            ,
            std::uint8_t(0), std::int8_t(0), 1, 0,
            1, 1, 1, 0,
            1, 0, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = sizeof(a) / sizeof(b);
            ,
            0U, int(15), char(3), 0,
            1, 1, 1, 0,
            1, 0, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = a + b++ + --c;
            ,
            4, 1, 2, 3,
            1, 1, 1, 1,
            1, 0, 1, 1)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x *= a + b * c;
            ,
            2, 1, 2, 3,
            1, 1, 1, 1,
            1, 0, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = a + b / c;
            ,
            0, 2.5f, 2, 3,
            1, 1, 1, 1,
            1, 0, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = (a - b) * c;
            ,
            0, double(1.1), 2, 1,
            1, 1, 1, 1,
            1, 0, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = a << b++ >> c--;
            ,
            0u, 8, 1, 1,
            1, 1, 1, 1,
            1, 0, 1, 1)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = (~a + b) * c;
            ,
            0u, 0ULL, 2U, 10UL,
            1, 1, 1, 1,
            1, 1, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = (a ^ a) + (b ^ b) + (c ^ c);
            ,
            0, 123, 321, 746,
            1, 1, 1, 1,
            1, 0, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            a^=b; b^=a; a^=b;
            ,
            0, 111, 222, 0,
            0, 1, 1, 0,
            0, 1, 1, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = c ? a | (2 << b) : a & ~(1 << b);
            ,
            0, 6, 1, 0,
            1, 1, 1, 1,
            1, 1, 0, 0)
    );

    expressions.emplace_back(
        CHECK_EXPRESSION (
            x = a / b; c = a % b;
            ,
            0, 15, 6, 0,
            1, 1, 1, 1,
            1, 0, 0, 1)
    );

#define SNIPPET1 \
int a = 4;\
int* p_a = &a;\
auto result = p_a;\
std::cout << std::endl << "address of a = " << &a << std::endl;

#define SNIPPET2 \
int b = 4;\
int& a = b;\
a = ++b;\
a += 4;\
b -= 1;\
auto result = b;

#define SNIPPET3 \
int&& a = 6;\
int&& b = std::forward<int>(a);\
a = ++b;\
a += 4;\
b -= 1;\
auto result = b;

#define SNIPPET4 \
\
int a[] = {1,2,3,4,5,6,7,8,9,0};\
auto result = *(a + 4);

#define SNIPPET5 \
int a[] = {1,2,3,4,5,6,7,8,9,0};\
auto p_a = (char*)(a+1);\
auto result = *(p_a + 4);

#define SNIPPET6 \
union {\
 struct {\
  unsigned a : 16;\
  unsigned b : 16;\
 } s;\
std::uint32_t i;\
} u;\
std::cout << std::endl << "address of u.s = " << &u.s << std::endl;\
auto result = &u.i;

#define SNIPPET7 \
auto result = 0;\
for (std::int8_t i=0; i++; i<128)\
    result = i;\

#define SNIPPET8 \
auto result = 0; \
throw "Exception!";\

    expressions.emplace_back(CHECK_SNIPPET(SNIPPET1));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET2));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET3));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET4));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET5));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET6));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET7));
    expressions.emplace_back(CHECK_SNIPPET(SNIPPET8));

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::shuffle(expressions.begin(), expressions.end(), gen);

    std::pair<int, int> score = {0,0};

    for(auto& expr : expressions){
        std::system("clear");
        auto points = expr();
        score.first += points.first;
        score.second += points.second;
        std::cout << score.second << "/" << score.first << std::endl; 
        std::cout << points.second << "/" << points.first << std::endl; 
        std::cout << "Press any key to continue ..." << std::endl;
        std::cin.get();
    }

    std::cout << score.second << "/" << score.first << std::endl; 
    std::cin.get();

    std::system("clear");
    return 0;
}
