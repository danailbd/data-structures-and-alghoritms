#pragma once

#include <iostream>
#include <sstream>

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
                cerr << "FAIL(" << tests_counter << "): Values mismatch!" << "\n-- expected: " << expected << "\n---- actual: " << value << endl; 
                failed_tests_counter++;
            } else {
                cout << "." << endl;
            }
        }


        // Fun with streams
        template <typename T>
        static void AssertCout(const char * expected,
                    void (*func) (int*, int),
                    T* argument,
                    int size) {

                std::ostringstream oss;
                // redirect std out to a custom buffer
                std::streambuf* p_cout_streambuf = std::cout.rdbuf();
                std::cout.rdbuf(oss.rdbuf());

                func(argument, size);

                std::cout.rdbuf(p_cout_streambuf); // restore stream

                // compare the couted string
                AssertEq(std::string(expected), oss.str());
            }


        static void PrintTestsResult() {
            if (failed_tests_counter)
                cout << "Failure: ";
            else
                cout << "Success: ";
            cout << tests_counter-failed_tests_counter << "|" << tests_counter << " tests." << endl;
        }
};

