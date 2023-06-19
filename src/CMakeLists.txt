add_executable (CMakeTarget "Array.h" "Vector.h" "LinkedList.h" "Stack.h" "Queue.h" "BinaryTree.h" "HashTable.h" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()
