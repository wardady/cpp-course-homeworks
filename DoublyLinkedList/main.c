#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

#define test_array_size 5

int main() {
    List my_list_1 = {0, 0};
    List *lst = &my_list_1;

    printf("Creating list from double value 10.4\n");
    create_from_value(lst, 10.4);
    to_string(lst);
    delete_list(lst);
    printf("\n");

    printf("Creating list from array {1.0, 5.0, 4.0, 3.0, 2.0}\n");
    List my_list_2 = {0, 0};
    lst = &my_list_2;
    double arr[test_array_size] = {1.0, 5.0, 4.0, 3.0, 2.0};
    create_from_array(lst, arr, test_array_size);
    to_string(lst);
    printf("\n");

    printf("Copying list to empty list\n");
    List my_list_copy = {0, 0};
    List *lst_to = &my_list_copy;
    copy(lst, lst_to);
    to_string(lst_to);
    printf("Copy list to nonempty list (must be 1):\t%d\n",copy(lst,lst_to));
    delete_list(lst_to);
    printf("\n");

    printf("Pushing 10 to front...;\npushing node with value 20 to front...;\npushing node with value 20 to back...;\npushing 14.4 to back...\n\n");
    pushfront(lst, 10);
    Node *test = (Node *) malloc(sizeof(Node));
    test->value = 20;
    pushfront_node(lst, test);
    Node *test2 = (Node *) malloc(sizeof(Node));
    test2->value = 20;
    pushback_node(lst, test2);
    pushback(lst, 14.4);
    to_string(lst);
    printf("\n");

    printf("Inserting node with value 20 to position 1...;\n");
    Node *test3 = (Node *) malloc(sizeof(Node));
    test3->value = 20;
    insert_node(lst, test3, 1);
    insert(lst, 10.4, 2);
    to_string(lst);
    printf("\n");

    printf("Popping from front...; popping from back...;\n");
    pop_front(lst);
    pop_back(lst);
    to_string(lst);
    printf("\n Removing at index 1...; removing by value 4...\n");
    remove_at(lst, 1);
    remove_by_value(lst, 4,0.0000001);
    to_string(lst);

    Node *first = get_by_index(lst, 0);
    printf("value of 0th element: %f\n", first->value);
    first = get_by_value(lst, 3,0.0000001);
    printf("Node value got when searching for node with value 3: %f\n", first->value);
    sort_list(lst, greater);
    to_string(lst);
    sort_list(lst, less);
    to_string(lst);

    return 0;
}