#include <iostream>

#include <queue>

using std::cout;
using std::cerr;
using std::endl;


/**********************************************************************
*                        Tests framework def                         *
**********************************************************************/


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

/**********************************************************************
*                      End Tests framework def                       *
**********************************************************************/


/***********
*  Utils  *
***********/

template<class T>
std::queue<T> ArrayToQueue(T* arr, int size) {
    std::queue<T> q;
    for(int i=0; i < size; i++)
        q.push(arr[i]);
    return q;
}

/***************
*  End Utils  *
***************/





bool isQueueMonotonous(std::queue<int>& q) {
    int current = q.front(),
        next;
    q.pop();
    short reverser =
        current > q.front()?
        1 : // normal comparison
        -1; // reversed comparison

    for (int i=0; i < q.size(); i++) {
        next = q.front() * reverser;
        q.pop();
        q.push(next * reverser);

        if (current < next) {
            return false;
        }
        current = next;
    }

    return true;
}



void TestIsQueueMonotonous()
{
    int arr_asc[5] = {1, 2, 3, 4, 5};
    std::queue<int> q_asc(ArrayToQueue(arr_asc, 5));
    UTests::AssertEq<bool>(true, isQueueMonotonous(q_asc));

    int arr_desc[4] = {5, 4, 3, 2};
    std::queue<int> q_desc(ArrayToQueue(arr_desc, 4));
    UTests::AssertEq<bool>(true, isQueueMonotonous(q_desc));

    int arr_broken[5] = {5, 4, 3, 2, 6};
    std::queue<int> q_br(ArrayToQueue(arr_broken, 5));
    UTests::AssertEq<bool>(false, isQueueMonotonous(q_br));
}


int main() {
    TestIsQueueMonotonous();

    return 0;
}
