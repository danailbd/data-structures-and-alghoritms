#include "MLList.h"
#include "../utils/tests-framework.h"

void TestLListCommonOps() {
    MLList<int> list;
    list.push(1);
    list.push(3);
    list.push(6);

    UnitTests::AssertEq<int>(1, list.getAt(0));
    UnitTests::AssertEq<int>(3, list.getAt(1));
    UnitTests::AssertEq<int>(6, list.getAt(2));

    UnitTests::AssertEq<bool>(true, list.insertAt(5, 2));
    UnitTests::AssertEq<int>(4, list.size());
    UnitTests::AssertEq<int>(5, list.getAt(2));
    UnitTests::AssertEq<int>(6, list.getAt(3));

    // insert at begining
    UnitTests::AssertEq<bool>(true, list.insertAt(2, 0));
    UnitTests::AssertEq<int>(5, list.size());
    UnitTests::AssertEq<int>(2, list.getAt(0));
    UnitTests::AssertEq<int>(1, list.getAt(1));

    
    // test out of bounds
    UnitTests::AssertEq<bool>(false, list.insertAt(2, 6));

    // insert in last place
    UnitTests::AssertEq<bool>(true, list.updateAt(7, 4));
    UnitTests::AssertEq<int>(7, list.getAt(4));

    UnitTests::AssertEq<bool>(true, list.removeAt(1));
    UnitTests::AssertEq<int>(4, list.size());
    UnitTests::AssertEq<int>(3, list.getAt(1));

    UnitTests::AssertEq<bool>(true, list.removeAt(0));
    UnitTests::AssertEq<int>(3, list.size());
    UnitTests::AssertEq<int>(3, list.getAt(0));
}

void TestLListHeadOps() {
    MLList<int> list;
    list.unshift(1);
    UnitTests::AssertEq<int>(1, list.head());
    UnitTests::AssertEq<int>(1, list.shift());

    list.unshift(2);
    list.unshift(3);
    list.unshift(4);

    UnitTests::AssertEq<int>(4, list.head());
    UnitTests::AssertEq<int>(2, list.tail());
    UnitTests::AssertEq<int>(4, list.shift());
    UnitTests::AssertEq<int>(3, list.head());
    UnitTests::AssertEq<int>(3, list.shift());
    UnitTests::AssertEq<int>(2, list.head());
    UnitTests::AssertEq<int>(2, list.shift());
}

void TestLListTailOps() {
    MLList<int> list;
    list.push(1);
    UnitTests::AssertEq<int>(1, list.tail());
    UnitTests::AssertEq<int>(1, list.pop());

    list.push(2);
    list.push(4);
    list.push(1);
    UnitTests::AssertEq<int>(1, list.tail());
    UnitTests::AssertEq<int>(1, list.pop());
    UnitTests::AssertEq<int>(4, list.tail());
    UnitTests::AssertEq<int>(4, list.pop());
    UnitTests::AssertEq<int>(2, list.pop());
}

void TestLListBaseOps() {
    MLList<int> list;

    UnitTests::AssertEq<int>(0, list.size());
    UnitTests::AssertEq<int>(-1, list.find(5));

    list.push(2);
    list.push(1);
    list.push(5);
    list.push(3);

    UnitTests::AssertEq<int>(0, list.find(2));
    
    UnitTests::AssertEq<int>(4, list.size());
    UnitTests::AssertEq<int>(2, list.find(5));

    list.push(3);
    UnitTests::AssertEq<int>(5, list.size());
    UnitTests::AssertEq<int>(3, list.find(3));

    UnitTests::AssertEq<int>(-1, list.find(7));
}



void TestLList() {
    TestLListTailOps();
    TestLListBaseOps();
    TestLListHeadOps();
    TestLListCommonOps();
    // TestLListPrint();
    UnitTests::PrintTestsResult();
}

int main() {
    TestLList();

    return 0;
}
