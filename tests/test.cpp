#include "list.h"
#include "map.h"

#include <cassert>
#include <iostream>

void TestListInsertsCorrectlyWhenEmpty()
{
    List<int> list;
    list.Insert(10);
    assert(list.Size() == 1);
    assert(list[0] == 10);
}

void TestListInsertsResizesCorrectlyWhenFull()
{
    List<int> list;
    for (size_t i = 0; i < list.Capacity(); i++)
        list.Insert(i);
    assert(list.Size() == list.Capacity());
    const auto old_capacity = list.Capacity();
    list.Insert(100);
    assert(list.Capacity() > old_capacity);
    assert(list.Size() == old_capacity + 1);
}

void TestListFindWorkWhenElementExists()
{
    List<int> list;
    list.Insert(10);
    list.Insert(20);
    list.Insert(30);
    auto it = list.Find(20);
    assert(it != list.end());
    assert(*it == 20);
}

void TestListFindReturnsEndIteratorWhenElementDoesNotExist()
{
    List<int> list;
    list.Insert(10);
    list.Insert(20);
    list.Insert(30);
    auto it = list.Find(40);
    assert(it == list.end());
}

void TestListOperatorBracketWorksWithinBounds()
{
    List<int> list;
    list.Insert(10);
    list.Insert(20);
    assert(list[0] == 10);
    assert(list[1] == 20);
}

void TestListOperatorBracketThrowsOutOfBound()
{
    List<int> list;
    list.Insert(10);
    bool exception_thrown = false;
    try
    {
        list[1];
    }
    catch (const std::out_of_range &)
    {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void TestListDeleteWorksWithinBounds()
{
    List<int> list;
    list.Insert(10);
    list.Insert(20);
    list.Insert(30);
    list.Delete(1);
    assert(list.Size() == 2);
    assert(list[0] == 10);
    assert(list[1] == 30);
}

void TestListDeleteThrowsOutOfBound()
{
    List<int> list;
    bool exception_thrown = false;
    try
    {
        list.Delete(0);
    }
    catch (const std::out_of_range &)
    {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void TestMapInsertsWhenEmpty()
{
    Map<int, std::string> map;
    map.Insert(1, "one");
    assert(map.Size() == 1);
    assert(*(map.Find(1)) == "one");
}

void TestMapInsertRehashesCorrectlyWhenLoadFactorExceeded()
{
    Map<int, std::string> map;
    map.Insert(1, "one");
    map.Insert(2, "two");
    assert(map.Size() == 2);
    map.Insert(3, "three");
    assert(map.Size() == 3);
    assert(*(map.Find(1)) == "one");
    assert(*(map.Find(2)) == "two");
    assert(*(map.Find(3)) == "three");
}

void TestMapFindWorksWhenKeyExists()
{
    Map<int, std::string> map;
    map.Insert(1, "one");
    assert(*(map.Find(1)) == "one");
}

void TestMapFindReturnsNullptrWhenKeyDoesNotExist()
{
    Map<int, std::string> map;
    map.Insert(1, "one");
    assert(map.Find(2) == nullptr);
}

void TestMapDeleteDoesNothingOnNonExistentKey()
{
    Map<int, std::string> map;
    map.Insert(1, "one");
    map.Delete(2);
    assert(map.Size() == 1);
}

void TestMapDeleteKeyRemovesValueWhenKeyExists()
{
    Map<int, std::string> map;
    map.Insert(1, "one");
    map.Delete(1);
    assert(map.Size() == 0);
}

int main()
{

    TestListInsertsCorrectlyWhenEmpty();
    TestListInsertsResizesCorrectlyWhenFull();
    TestListFindWorkWhenElementExists();
    TestListFindReturnsEndIteratorWhenElementDoesNotExist();
    TestListOperatorBracketWorksWithinBounds();
    TestListOperatorBracketThrowsOutOfBound();
    TestListDeleteWorksWithinBounds();
    TestListDeleteThrowsOutOfBound();
    
    TestMapInsertsWhenEmpty();
    TestMapInsertRehashesCorrectlyWhenLoadFactorExceeded();
    TestMapFindWorksWhenKeyExists();
    TestMapFindReturnsNullptrWhenKeyDoesNotExist();
    TestMapDeleteDoesNothingOnNonExistentKey();
    TestMapDeleteKeyRemovesValueWhenKeyExists();

    std::cout << "All Tests Passed" << std::endl;
    return 0;
}