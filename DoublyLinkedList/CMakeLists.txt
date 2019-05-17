cmake_minimum_required(VERSION 3.14)
project(DoublyLinkedList C)

set(CMAKE_C_STANDARD 99)

add_library(DoublyLinkedList STATIC llist.h library.c)
add_executable(DoublyLinkedListTest main.c)
target_link_libraries(DoublyLinkedListTest DoublyLinkedList)