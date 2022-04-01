#include "IntegerString.hpp"

#include <algorithm>
#include <iostream>
#include <string>

#define _XSTR(s) _STR(s)
#define _STR(s) #s

#define CHECK_FN(fn, a, b, test)                     \
    {                                                \
        std::cout << _XSTR(fn) << "(" << (a) << ","; \
        std::cout << (b) << ") = " << (test);        \
        if (fn((a), (b)) == test)                    \
            std::cout << " ok";                      \
        else                                         \
            std::cout << " FAILED";                  \
        std::cout << std::endl;                      \
    }

#define CHECK_DIV(a, b, qt, rt)                            \
    {                                                      \
        std::cout << "div(" << (a) << ",";                 \
        std::cout << (b) << ") = " << (qt) << "," << (rt); \
        std::string q, r;                                  \
        q = div((a), (b), (r));                            \
        if (q == (qt) && r == (rt))                        \
            std::cout << " ok";                            \
        else                                               \
            std::cout << " FAILED";                        \
        std::cout << std::endl;                            \
    }

using namespace integerstring;
int main() {
    CHECK_FN(eq, "12", "12", true);
    CHECK_FN(eq, "0", "0", true);

    CHECK_FN(le, "12", "20", true);
    CHECK_FN(le, "20", "12", false);
    CHECK_FN(le, "1", "20", true);
    CHECK_FN(le, "20", "1", false);
    CHECK_FN(le, "2", "10", true);
    CHECK_FN(le, "10", "2", false);
    CHECK_FN(le, "12", "13", true);
    CHECK_FN(le, "13", "12", false);
    CHECK_FN(le, "12", "12", true);

    CHECK_FN(ge, "12", "20", false);
    CHECK_FN(ge, "20", "12", true);
    CHECK_FN(ge, "1", "20", false);
    CHECK_FN(ge, "20", "1", true);
    CHECK_FN(ge, "2", "10", false);
    CHECK_FN(ge, "10", "2", true);
    CHECK_FN(ge, "12", "13", false);
    CHECK_FN(ge, "13", "12", true);
    CHECK_FN(ge, "12", "12", true);

    CHECK_FN(lt, "12", "20", true);
    CHECK_FN(lt, "20", "12", false);
    CHECK_FN(lt, "1", "20", true);
    CHECK_FN(lt, "20", "1", false);
    CHECK_FN(lt, "2", "10", true);
    CHECK_FN(lt, "10", "2", false);
    CHECK_FN(lt, "12", "13", true);
    CHECK_FN(lt, "13", "12", false);
    CHECK_FN(lt, "12", "12", false);

    CHECK_FN(gt, "12", "20", false);
    CHECK_FN(gt, "20", "12", true);
    CHECK_FN(gt, "1", "20", false);
    CHECK_FN(gt, "20", "1", true);
    CHECK_FN(gt, "2", "10", false);
    CHECK_FN(gt, "10", "2", true);
    CHECK_FN(gt, "12", "13", false);
    CHECK_FN(gt, "13", "12", true);
    CHECK_FN(gt, "12", "12", false);

    CHECK_FN(add, "2", "3", "5");
    CHECK_FN(add, "8", "7", "15");
    CHECK_FN(add, "123", "432", "555");
    CHECK_FN(add, "999", "1", "1000");
    CHECK_FN(add, "9990", "10", "10000");
    CHECK_FN(add, "9899", "201", "10100");
    CHECK_FN(add, "10000400000", "600000", "10001000000");
    CHECK_FN(add, "432", "123", "555");
    CHECK_FN(add, "1", "999", "1000");
    CHECK_FN(add, "10", "9990", "10000");
    CHECK_FN(add, "201", "9899", "10100");
    CHECK_FN(add, "600000", "10000400000", "10001000000");

    CHECK_FN(sub, "3", "2", "1");
    CHECK_FN(sub, "15", "3", "12");
    CHECK_FN(sub, "12", "9", "3");
    CHECK_FN(sub, "100", "2", "98");
    CHECK_FN(sub, "10000", "9999", "1");
    CHECK_FN(sub, "10000", "1", "9999");
    CHECK_FN(sub, "10000", "1000", "9000");
    CHECK_FN(sub, "10000", "10000", "0");
    CHECK_FN(sub, "1", "1", "0");
    CHECK_FN(sub, "0", "0", "0");
    CHECK_FN(sub, "271590", "12345", "259245");

    CHECK_FN(mul, "2", "3", "6");
    CHECK_FN(mul, "6", "7", "42");
    CHECK_FN(mul, "16", "117", "1872");
    CHECK_FN(mul, "12345", "22", "271590");
    CHECK_FN(mul, "22", "12345", "271590");

    CHECK_DIV("0", "5", "0", "0");
    CHECK_DIV("4", "5", "0", "4");
    CHECK_DIV("8", "2", "4", "0");
    CHECK_DIV("271590", "12345", "22", "0");
    CHECK_DIV("1872", "16", "117", "0");
    CHECK_DIV("20", "10", "2", "0");
    CHECK_DIV("29", "10", "2", "9");
    CHECK_DIV("191893687078", "155433", "1234574", "146536");
    return 0;
}
