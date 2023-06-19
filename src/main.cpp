#include<iostream>
#include<cassert>

#include"Array.h"
#include"Vector.h"
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
#include"BinaryTree.h"
#include"HashTable.h"

void ArrayTests()
{
    // Create an instance of Array
    Array<int, 5> array;

    // Test the Size() function
    assert(array.Size() == 5);

    // Test the Empty() function
    assert(!array.Empty());

    // Test the operator[] function
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;
    assert(array[0] == 1);
    assert(array[1] == 2);
    assert(array[2] == 3);
    assert(array[3] == 4);
    assert(array[4] == 5);

    // Test the iterator functionality
    Array<int, 5>::Iterator it = array.begin();
    assert(it != array.end());

    // Test the operator* function of the iterator
    assert(*it == 1);

    // Test the ++ operator of the iterator
    ++it;
    assert(it != array.end());
    assert(*it == 2);

    // Test the ++ operator (post-increment) of the iterator
    Array<int, 5>::Iterator postIncIt = it++;
    assert(postIncIt != array.end());
    assert(*postIncIt == 2);
    assert(it != array.end());
    assert(*it == 3);

    // Test the equality and inequality operators of the iterator
    assert(postIncIt != it);
    assert(postIncIt != array.begin());

    // Test the rbegin() and rend() functions
    Array<int, 5>::ReverseIterator rit = array.rbegin();
    assert(rit != array.rend());
    assert(*rit == 5);

    // Test the ++ operator of the reverse iterator
    ++rit;
    assert(rit != array.rend());
    assert(*rit == 4);

    // Test the -- operator (post-decrement) of the reverse iterator
    Array<int, 5>::ReverseIterator postDecRit = rit--;
    assert(postDecRit != array.rend());
    assert(*postDecRit == 4);
    assert(rit != array.rend());
    assert(*rit == 3);
 
    // Test the equality and inequality operators of the reverse iterator
    ++postDecRit;
    assert(postDecRit == rit);
    assert(postDecRit != array.rbegin());

    // Test the Fill() function
    array.Fill(0);
    for (size_t i = 0; i < array.Size(); ++i) {
        assert(array[i] == 0);
    }

    // Test the Swap() function
    Array<int, 5> otherArray;
    otherArray.Fill(10);
    array.Swap(otherArray);
    for (size_t i = 0; i < array.Size(); ++i) {
        assert(array[i] == 10);
    }
    for (size_t i = 0; i < otherArray.Size(); ++i) {
        assert(otherArray[i] == 0);
    }

    // All tests passed
    std::cout << "All Array tests passed!\n";
}
void VectorTests()
{
    // Create an instance of Vector
    Vector<int> vector;

    // Test the Empty() function
    assert(vector.Empty());

    // Test the Size() function
    assert(vector.Size() == 0);

    // Test the Capacity() function
    assert(vector.Capacity() == 1);

    // Test the PushBack() function
    vector.PushBack(1);
    vector.PushBack(2);
    vector.PushBack(3);
    assert(vector.Size() == 3);
    assert(vector.Capacity() == 4);
    assert(vector[0] == 1);
    assert(vector[1] == 2);
    assert(vector[2] == 3);

    // Test the EmplaceBack() function
    vector.EmplaceBack(4);
    vector.EmplaceBack(5);
    assert(vector.Size() == 5);
    assert(vector.Capacity() == 8);
    assert(vector[3] == 4);
    assert(vector[4] == 5);

    // Test the PopBack() function
    vector.PopBack();
    assert(vector.Size() == 4);
    assert(vector[3] == 4);
    // Test the operator[] function
    vector[0] = 10;
    vector[1] = 20;
    vector[2] = 30;
    vector[3] = 40;
    assert(vector[0] == 10);
    assert(vector[1] == 20);
    assert(vector[2] == 30);
    assert(vector[3] == 40);

    // Test the iterators
    Vector<int>::Iterator it = vector.begin();
    assert(it != vector.end());
    assert(*it == 10);

    ++it;
    assert(it != vector.end());
    assert(*it == 20);

    Vector<int>::Iterator postIncIt = it++;
    assert(postIncIt != vector.end());
    assert(*postIncIt == 20);
    assert(it != vector.end());
    assert(*it == 30);
    ++postIncIt;
    assert(postIncIt == it);

    Vector<int>::ReverseIterator rit = vector.rbegin();
    assert(rit != vector.rend());
    assert(*rit == 40);

    ++rit;
    assert(rit != vector.rend());
    assert(*rit == 30);

    Vector<int>::ReverseIterator postDecRit = rit--;
    assert(postDecRit != vector.rend());
    assert(*postDecRit == 30);
    assert(rit != vector.rend());
    assert(*rit == 20);
    ++postDecRit;
    assert(postDecRit == rit);

    // Test the Copy Constructor
    Vector<int> copyVector(vector);
    assert(copyVector == vector);

    // Test the Move Constructor
    Vector<int> moveVector(std::move(vector));
    assert(moveVector.Size() == 4);
    assert(moveVector[0] == 10);
    assert(moveVector[1] == 20);
    assert(moveVector[2] == 30);
    assert(moveVector[3] == 40);

    // Test the Copy Assignment Operator
    Vector<int> copyAssignVector;
    copyAssignVector = copyVector;
    assert(copyAssignVector == copyVector);

    // Test the Move Assignment Operator
    Vector<int> moveAssignVector;
    moveAssignVector = std::move(moveVector);
    assert(moveAssignVector.Size() == 4);
    assert(moveAssignVector[0] == 10);
    assert(moveAssignVector[1] == 20);
    assert(moveAssignVector[2] == 30);
    assert(moveAssignVector[3] == 40);

    // All tests passed
    std::cout << "All Vector tests passed!\n";
}
void LinkedListTests()
{
    // Create an instance of LinkedList
    LinkedList<int> linkedList;

    // Test the Empty() function
    assert(linkedList.Empty());

    // Test the Size() function
    assert(linkedList.Size() == 0);

    // Test the PushBack() function
    linkedList.PushBack(1);
    linkedList.PushBack(2);
    linkedList.PushBack(3);
    assert(linkedList.Size() == 3);
    assert(linkedList.Front() == 1);
    assert(linkedList.Back() == 3);

    // Test the PushFront() function
    linkedList.PushFront(0);
    assert(linkedList.Size() == 4);
    assert(linkedList.Front() == 0);
    assert(linkedList.Back() == 3);

    // Test the EmplaceBack() function
    linkedList.EmplaceBack(4);
    linkedList.EmplaceBack(5);
    assert(linkedList.Size() == 6);
    assert(linkedList.Back() == 5);

    // Test the EmplaceFront() function
    linkedList.EmplaceFront(-1);
    linkedList.EmplaceFront(-2);
    assert(linkedList.Size() == 8);
    assert(linkedList.Front() == -2);

    // Test the PopBack() function
    linkedList.PopBack();
    assert(linkedList.Size() == 7);
    assert(linkedList.Back() == 4);

    // Test the PopFront() function
    linkedList.PopFront();
    assert(linkedList.Size() == 6);
    assert(linkedList.Front() == -1);

    // Test the Clear() function
    linkedList.Clear();
    assert(linkedList.Empty());
    assert(linkedList.Size() == 0);

    // Test the Swap() function
    LinkedList<int> otherList;
    otherList.PushBack(10);
    otherList.PushBack(20);

    linkedList.Swap(otherList);
    assert(linkedList.Size() == 2);
    assert(linkedList.Front() == 10);
    assert(linkedList.Back() == 20);
    assert(otherList.Size() == 0);
    assert(otherList.Empty());

    // Test the operator== function
    LinkedList<int> list1;
    list1.PushBack(1);
    list1.PushBack(2);
    list1.PushBack(3);

    LinkedList<int> list2;
    list2.PushBack(1);
    list2.PushBack(2);
    list2.PushBack(3);

    assert(list1 == list2);

    // Test the operator!= function
    LinkedList<int> list3;
    list3.PushBack(4);
    list3.PushBack(5);

    assert(list1 != list3);

    // Test the iterators
    LinkedList<int>::Iterator it = linkedList.begin();
    assert(it != linkedList.end());
    assert(*it == 10);

    ++it;
    assert(it != linkedList.end());
    assert(*it == 20);

    LinkedList<int>::Iterator postIncIt = it++;
    assert(postIncIt != linkedList.end());
    assert(*postIncIt == 20);
    assert(it == linkedList.end());

    assert(postIncIt != it);

    LinkedList<int>::ConstIterator cit = linkedList.cbegin();
    assert(cit != linkedList.cend());
    assert(*cit == 10);

    ++cit;
    assert(cit != linkedList.cend());
    assert(*cit == 20);

    LinkedList<int>::ReverseIterator rit = linkedList.rbegin();
    assert(rit != linkedList.rend());
    assert(*rit == 20);

    ++rit;
    assert(rit != linkedList.rend());
    assert(*rit == 10);

    std::cout << "All LinkedList tests passed!\n";
}
void StackTests()
{
    // Create an instance of Stack
    Stack<int> stack;

    // Test the Empty() function
    assert(stack.Empty());

    // Test the Size() function
    assert(stack.Size() == 0);

    // Test the Push() function
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    assert(stack.Size() == 3);
    assert(stack.Top() == 3);

    // Test the Pop() function
    stack.Pop();
    assert(stack.Size() == 2);
    assert(stack.Top() == 2);

    // Test the Find() function
    assert(stack.Find(2));
    assert(!stack.Find(3));

    // Test the Swap() function
    Stack<int> otherStack;
    otherStack.Push(10);
    otherStack.Push(20);

    stack.Swap(otherStack);
    assert(stack.Size() == 2);
    assert(stack.Top() == 20);
    assert(otherStack.Size() == 2);
    assert(otherStack.Top() == 2);

    // Test the iterators
    Stack<int>::Iterator it = stack.begin();
    assert(it != stack.end());
    assert(*it == 10);
    ++it;
    assert(*it == 20);
    --it;
    assert(*it == 10);

    std::cout << "All Stack tests passed!\n";
}
void QueueTests()
{
    // Create an instance of Queue
    Queue<int> queue;

    // Test the Empty() function
    assert(queue.Empty());

    // Test the Size() function
    assert(queue.Size() == 0);

    // Test the Push() function
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    assert(queue.Size() == 3);
    assert(queue.Front() == 1);
    assert(queue.Back() == 3);

    // Test the Pop() function
    queue.Pop();
    assert(queue.Size() == 2);
    assert(queue.Front() == 2);
    assert(queue.Back() == 3);

    // Test the Swap() function
    Queue<int> otherQueue;
    otherQueue.Push(10);
    otherQueue.Push(20);

    queue.Swap(otherQueue);
    assert(queue.Size() == 2);
    assert(queue.Front() == 10);
    assert(queue.Back() == 20);
    assert(otherQueue.Size() == 2);
    assert(otherQueue.Front() == 2);

    // Test the Find() function
    assert(queue.Find(10));
    assert(queue.Find(20));
    assert(!queue.Find(2));

    // Test the iterators
    Queue<int>::Iterator it = queue.begin();
    assert(it != queue.end());
    assert(*it == 10);

    ++it;
    assert(it != queue.end());
    assert(*it == 20);

    std::cout << "All Queue tests passed!\n";
}
void TreeTests()
{
    // Create a binary tree with some values
    BinaryTree<int> binaryTree;
    binaryTree.Insert(20);
    binaryTree.Insert(10);
    binaryTree.Insert(30);
    binaryTree.Insert(5);
    binaryTree.Insert(15);
    binaryTree.Insert(25);
    binaryTree.Insert(35);

    // Test Find
    assert(binaryTree.Find(20) == true);
    assert(binaryTree.Find(10) == true);
    assert(binaryTree.Find(30) == true);
    assert(binaryTree.Find(5) == true);
    assert(binaryTree.Find(15) == true);
    assert(binaryTree.Find(25) == true);
    assert(binaryTree.Find(35) == true);
    assert(binaryTree.Find(100) == false);

    // Test Iterators
    BinaryTree<int>::Iterator it;
    it = binaryTree.begin();
    assert(*it == 5);
    ++it;
    assert(*it == 10);
    ++it;
    assert(*it == 15);
    ++it;
    assert(*it == 20);
    ++it;
    assert(*it == 25);

    BinaryTree<int>::ReverseIterator rit;
    rit = binaryTree.rbegin();
    assert(*rit == 35);
    ++rit;
    assert(*rit == 30);
    ++rit;
    assert(*rit == 25);
    ++rit;
    assert(*rit == 20);
    ++rit;
    assert(*rit == 15);

    // Test Delete
    binaryTree.Delete(20);
    assert(binaryTree.Find(20) == false);
    assert(binaryTree.Size() == 6);

    binaryTree.Delete(10);
    assert(binaryTree.Find(10) == false);
    assert(binaryTree.Size() == 5);

    binaryTree.Delete(30);
    assert(binaryTree.Find(30) == false);
    assert(binaryTree.Size() == 4);

    binaryTree.Delete(5);
    assert(binaryTree.Find(5) == false);
    assert(binaryTree.Size() == 3);

    binaryTree.Delete(15);
    assert(binaryTree.Find(15) == false);
    assert(binaryTree.Size() == 2);

    binaryTree.Delete(25);
    assert(binaryTree.Find(25) == false);
    assert(binaryTree.Size() == 1);

    binaryTree.Delete(35);
    assert(binaryTree.Find(35) == false);
    assert(binaryTree.Size() == 0);
    assert(binaryTree.IsEmpty() == true);

    // Test Copy Constructor and Assignment Operator
    BinaryTree<int> OtherBinaryTree;
    OtherBinaryTree.Insert(10);
    OtherBinaryTree.Insert(5);
    OtherBinaryTree.Insert(15);

    BinaryTree<int> CopyBinaryTree(OtherBinaryTree);
    assert(CopyBinaryTree == OtherBinaryTree);

    binaryTree = CopyBinaryTree;
    assert(binaryTree == CopyBinaryTree);

    // Test Move Constructor and Assignment Operator
    BinaryTree<int> MoveBinaryTree(std::move(OtherBinaryTree));
    assert(OtherBinaryTree.IsEmpty() == true);
    assert(MoveBinaryTree.Find(15) == true);
    assert(MoveBinaryTree.Find(5) == true);
    assert(MoveBinaryTree.Find(10) == true);

    BinaryTree<int> AssigmentMoveBinaryTree;
    AssigmentMoveBinaryTree.Insert(40);
    AssigmentMoveBinaryTree.Insert(50);

    OtherBinaryTree = std::move(AssigmentMoveBinaryTree);
    assert(AssigmentMoveBinaryTree.IsEmpty() == true);
    assert(OtherBinaryTree.Find(40) == true);
    assert(OtherBinaryTree.Find(50) == true);

    std::cout << "All BinaryTree tests passed!\n";
}
void HashTableTests()
{
    // Test constructor and Size()
    HashTable<int, std::string> hashTable(10);
    assert(hashTable.Size() == 10);

    // Test IsEmpty() on empty hash table
    assert(hashTable.IsEmpty());

    // Test Insert() and operator[]
    hashTable.Insert(1, "One");
    hashTable.Insert(2, "Two");
    assert(!hashTable.IsEmpty());
    assert(hashTable[1] == "One");
    assert(hashTable[2] == "Two");

    // Test Insert() with existing key
    hashTable.Insert(2, "New Two");
    assert(hashTable[2] == "New Two");

    // Test Iterator
    auto it = hashTable.begin();
    assert(it != hashTable.end());
    assert(it.Key() == 1);
    assert(it.Value() == "One");

    ++it;
    assert(it != hashTable.end());
    assert(it.Key() == 2);
    assert(it.Value() == "New Two");

    // Test Copy constructor and operator=
    HashTable<int, std::string> copyTable(hashTable);
    assert(copyTable.Size() == hashTable.Size());
    assert(copyTable[1] == "One");
    assert(copyTable[2] == "New Two");

    HashTable<int, std::string> assignedTable;
    assignedTable = hashTable;
    assert(assignedTable.Size() == hashTable.Size());
    assert(assignedTable[1] == "One");
    assert(assignedTable[2] == "New Two");

    // Test Clear() and IsEmpty()
    hashTable.Clear();
    assert(hashTable.IsEmpty());

    // Test move constructor and operator=
    HashTable<int, std::string> movedTable(std::move(copyTable));
    assert(movedTable.Size() == hashTable.Size());
    assert(movedTable[1] == "One");
    assert(movedTable[2] == "New Two");

    HashTable<int, std::string> moveAssignedTable;
    moveAssignedTable = std::move(assignedTable);
    assert(moveAssignedTable.Size() == hashTable.Size());
    assert(moveAssignedTable[1] == "One");
    assert(moveAssignedTable[2] == "New Two");

    std::cout << "All HashTable tests passed!" << std::endl;
}

int main()
{
    ArrayTests();
    VectorTests();
    LinkedListTests();
    StackTests();
    QueueTests();
    TreeTests();
    HashTableTests();

    return 0;
}
