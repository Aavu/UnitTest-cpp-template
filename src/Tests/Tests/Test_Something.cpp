#include "UnitTest++.h"
//#include <iostream>

SUITE(Something) {
    TEST(hello)
    {
//        std::cout << "hello\n";
        CHECK_EQUAL(1, 1);
    }

    TEST(hello2)
    {
//        std::cout << "hello2\n";
        CHECK_EQUAL(1, 0);
    }
}