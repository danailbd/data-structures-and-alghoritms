#pragma once

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

static int tests_counter = 0;
static int failed_tests_counter = 0;

class UnitTests {
    public:
        template <typename T>
        static void AssertEq(T expected, T value) {
            tests_counter++;
            if (expected != value) {
                cerr << "FAIL: Values mismatch!" << "\n-- expected: " << expected << "\n---- actual: " << value << endl; 
                failed_tests_counter++;
            } else {
                cout << "." << endl;
            }
        }
        void PrintTestsResult() {
            if (failed_tests_counter)
                cout << "Failure: ";
            else
                cout << "Success: ";
            cout << tests_counter-failed_tests_counter << "|" << tests_counter << " tests." << endl;
        }
};

