//
// Created by hermann on 16.05.19.
//

#ifndef LINKEDLIST_LLIST_H
#define LINKEDLIST_LLIST_H

#include <stdio.h>

typedef struct Node {
    double value;
    struct Node *next;
    struct Node *previous;
} Node;
typedef struct {
    Node *head;
    Node *tail;
} List;

int create_from_value(List *list, double val);

int create_from_array(List *list, double *arr, size_t size);

int copy(List *from, List *to);

void to_string(List *list);

int pushfront_node(List *list, Node *val);

int pushback_node(List *list, Node *val);

int insert_node(List *list, Node *val, size_t index);

int pop_front(List *list);

int pop_back(List *list);

int remove_at(List *list, size_t index);

int remove_by_value(List *list, double value, double precision);

Node *get_by_index(List *list, size_t index);

Node *get_by_value(List *list, double value, double precision);

void delete_list(List *list);

int pushfront(List *list, double value);

int pushback(List *list, double value);

int insert(List *list, double value, size_t index);

int greater(Node *lhs, Node *rhs);

int less(Node *lhs, Node *rhs);

void sort_list(List *list, int (*comparator)(Node *, Node *));

#endif //LINKEDLIST_LLIST_H
