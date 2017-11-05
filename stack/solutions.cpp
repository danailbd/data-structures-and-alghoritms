
#include <iostream>
#include <stack>

using std::cout;
using std::cerr;
using std::endl;

namespace UTests {
    int tests_counter = 0;
    int failed_tests_counter = 0;

    template <typename T>
    void AssertEq(T expected, T value) {
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
}


// -----


bool IsOp(int key) {
    return key < 0;
}

bool IsDigit(char key) {
    return key > '0' && key < '9';
}

int Calc(int& arg1, int& arg2, char op) {
    switch(op) {
        case '+':
            return arg1 + arg2;
        case '-':
            return arg1 - arg2;
        case '*':
            return arg1 * arg2;
        case '/':
            return arg1 / arg2;
        default:
            cout << "Unvalid operation: " << op << std::endl;
    }
    return -1;
}

// Keeps the result positive
int CalcRestricted(int& arg1, int& arg2, char op) {
    int result;
    switch(op) {
        // special case
        case '-':
            result = arg1 - arg2;
            return result < 0 ? 0 : result;
        // else, behave like a normal calculate
        default:
            return Calc(arg1, arg2, op);
    }
}

// Left to right approach - restricted
/*
 * !N.B.
 * This solution is only aplicable under these restrictions for the input and result:
 * - valid expression is passed
 * - we don't support negative result
 * - arguments are **single digits** (positive)
 */
int CalcPNLtoRS(const char* rawExpr) {
    std::stack<int> keys;
    
    char key;
    int arg1, arg2, op;
    for (int i=0 ; rawExpr[i]; i++) {
        key = rawExpr[i];
        if (IsDigit(key)) {
            arg2 = key - '0'; // convert to normal int
            // process as much opration as posible
            while (!keys.empty() && !IsOp(keys.top())) {
                arg1 = keys.top(); keys.pop(); 
                op = -keys.top(); keys.pop(); // the ascii code of the operation
                arg2 = CalcRestricted(arg1, arg2, op);
            }
            keys.push(arg2);
        } else {
            // ensure oparator key is unique 
            keys.push(-key);
        }
    }

    // The only key standing...
    return keys.top();
}


int CalcPNLtoR(char const * rawExpr) {
    std::stack<char> ops;
    std::stack<int> args;
    
    char key;
    int arg1, arg2, op;
    bool pending = false; // previous item was digit
    for (int i=0 ; rawExpr[i]; i++) {
        key = rawExpr[i];
        if (IsDigit(key)) {
            arg2 = key - '0'; // convert to normal int
            if (pending) {
                while(!args.empty()) {
                    op = ops.top(); ops.pop();
                    arg1 = args.top(); args.pop();
                    arg2 = Calc(arg1, arg2, op);
                }
            }
            pending = true;
            args.push(arg2);
        } else {
            ops.push(key);
            pending = false;
        }
    }

    return args.top();
}

void TestCalcPNLtoR(int (*CaclPN) (const char*)) {
    UTests::AssertEq(3, CaclPN("+21"));
    UTests::AssertEq(20, CaclPN("*+234"));
    UTests::AssertEq(29, CaclPN("-*+++2341+211"));
    UTests::AssertEq(5, CaclPN("-*24/62"));
    UTests::AssertEq(8, CaclPN("+-*/22316"));
    // check test failure
    UTests::AssertEq(-1, CaclPN("-23"));
}

int main () {
    TestCalcPNLtoR(CalcPNLtoRS);
    TestCalcPNLtoR(CalcPNLtoR);

    return 0;
}
