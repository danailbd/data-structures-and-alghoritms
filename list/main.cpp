#include "LList.h"
#include "../utils/tests-framework.h"


void TestLListTailOps() {
    LList<int> list;
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
    LList<int> list;

    UnitTests::AssertEq<int>(0, list.size());
    UnitTests::AssertEq<int>(-1, list.find(5));

    list.push(2);
    list.push(1);
    list.push(5);
    list.push(3);
    
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
    // TestLListHeadOps();
    // TestLListCommonOps();
}

int main() {
    TestLList();

    return 0;
}
