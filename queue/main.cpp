#include <iostream>

#include "queue.cpp"

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
            cerr << "FAIL(" << tests_counter << "): Values mismatch!" << "\n-- expected: " << expected << "\n---- actual: " << value << endl; 
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


void testQueue()
{
    CQueue<int> test_q(3);
    int res;

    UTests::AssertEq<bool>(true, test_q.empty());

    test_q.push(1);
    test_q.head(res);
    UTests::AssertEq(1, res);
    UTests::AssertEq<int>(1, test_q.length());
    UTests::AssertEq<bool>(false, test_q.full());
    UTests::AssertEq<bool>(false, test_q.empty());

    test_q.push(2);
    test_q.head(res);
    UTests::AssertEq(1, res);
    UTests::AssertEq<int>(2, test_q.length());
    UTests::AssertEq<bool>(false, test_q.full());
    UTests::AssertEq<bool>(false, test_q.empty());

    test_q.push(3);
    test_q.head(res);
    UTests::AssertEq(1, res);
    UTests::AssertEq<int>(3, test_q.length());
    UTests::AssertEq<bool>(true, test_q.full());

    test_q.push(6);
    // cout msg; currently not testable
    
    test_q.pop(res);
    UTests::AssertEq(1, res);
    test_q.head(res);
    UTests::AssertEq(2, res);
    UTests::AssertEq<int>(2, test_q.length());
    UTests::AssertEq<bool>(false, test_q.full());

    test_q.push(4);
    test_q.head(res);
    UTests::AssertEq(2, res);
    UTests::AssertEq<int>(3, test_q.length());
    UTests::AssertEq<bool>(true, test_q.full());

    test_q.pop(res);
    UTests::AssertEq(2, res);
    test_q.pop(res);
    UTests::AssertEq(3, res);
    test_q.pop(res);
    UTests::AssertEq(4, res);

    UTests::AssertEq<bool>(true, test_q.empty());
    UTests::AssertEq<bool>(false, test_q.full());

    test_q.push(5);
    test_q.head(res);
    UTests::AssertEq(5, res);
    UTests::AssertEq<int>(1, test_q.length());
    UTests::AssertEq<bool>(false, test_q.full());
    UTests::AssertEq<bool>(false, test_q.empty());
}

int main () {
    testQueue();
}
