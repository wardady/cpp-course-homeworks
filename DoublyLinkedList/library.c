#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

void to_string(List *list) {
    Node *current = list->head;
    while (current) {
        printf("%f\t", current->value);
        current = current->next;
    }
    printf("\n");
}

int pushfront_node(List *list, Node *val) {
    if (!list || !val) {
        return 1;
    }
    if (!list->head) {
        val->next = 0;
        list->tail = val;
    } else {
        val->next = list->head;
        list->head->previous = val;
    }
    val->previous = 0;
    list->head = val;
    return 0;
}

int pushback_node(List *list, Node *val) {
    if (!list || !val) {
        return 1;
    }
    if (!list->tail) {
        val->previous = 0;
        list->head = val;
    } else {
        val->previous = list->tail;
        list->tail->next = val;
    }
    val->next = 0;
    list->tail = val;
    return 0;
}

Node *get_by_index(List *list, size_t index) {
    if (!list || !list->head) {
        return NULL;
    }
    Node *current = list->head;
    for (size_t i = 0; i < index; ++i) {
        if (!current->next) {
            return NULL;
        }
        current = current->next;
    }
    return current;
}

int insert_node(List *list, Node *val, size_t index) {
    if (!list || !val) {
        return 1;
    }

    Node *current = list->head;
    for (size_t i = 0; i < index; ++i) {
        if (!current->next) {
            return 1;
        }
        current = current->next;
    }

    if (current == list->tail) {
        val->previous = list->tail;
        list->tail->next = val;
        list->tail = val;
    } else {
        val->previous = current->previous;
        val->next = current;
        current->previous = val;
        if (val->previous) {
            val->previous->next = val;
        } else {
            list->head = val;
        }
    }
    return 0;
}

int pop_front(List *list) {
    if (!list || !list->head) {
        return 1;
    }
    Node *temp = list->head;
    list->head->next->previous = 0;
    list->head = list->head->next;
    free(temp);
    return 0;
}

int pop_back(List *list) {
    if (!list || !list->tail) {
        return 1;
    }
    Node *temp = list->tail;
    list->tail->previous->next = 0;
    list->tail = list->tail->previous;
    free(temp);
    return 0;
}

int remove_at(List *list, size_t index) {
    if (!list || !list->head) {
        return 1;
    }
    Node *current = get_by_index(list, index);
    if (!current) {
        return 2;
    }

    if (current == list->head) {
        list->head = current->next;
    } else {
        current->previous->next = current->next;
    }
    if (current == list->tail) {
        list->tail = current->previous;
    } else {
        current->next->previous = current->previous;
    }
    free(current);
    return 0;
}

int remove_by_value(List *list, double value) {
    if (!list || !list->head) {
        return 1;
    }
    Node *current = list->head;
    do {
        if (current->value == value) {
            if (current == list->head) {
                list->head = current->next;
            } else {
                current->previous->next = current->next;
            }
            if (current == list->tail) {
                list->tail = current->previous;
            } else {
                current->next->previous = current->previous;
            }
            free(current);
            return 0;
        }
        current = current->next;
    } while (current);
    return 2;
}

Node *get_by_value(List *list, double value) {
    if (!list || !list->head) {
        return NULL;
    }
    Node *current = list->head;
    while (current) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void delete_list(List *list) {
    if (!list || !list->head) {
        return;
    }
    Node *temp = list->head;
    while (temp->next) {
        temp = temp->next;
        free(temp->previous);
    }
    free(temp);
}

int pushfront(List *list, double value) {
    if (!list) {
        return 1;
    }
    Node *val = (Node *) malloc(sizeof(Node));
    val->value = value;
    int response = pushfront_node(list, val);
    if (response) {
        free(val);
    }
    return response;
}

int pushback(List *list, double value) {
    if (!list) {
        return 1;
    }
    Node *val = (Node *) malloc(sizeof(Node));
    val->value = value;
    int response = pushback_node(list, val);
    if (response) {
        free(val);
    }
    return response;
}

int insert(List *list, double value, size_t index) {
    if (!list) {
        return 1;
    }
    Node *val = (Node *) malloc(sizeof(Node));
    val->value = value;
    int response = insert_node(list, val, index);
    if (response) {
        free(val);
    }
    return response;
}

int greater(Node *lhs, Node *rhs) {
    return lhs->value > rhs->value;
}

int less(Node *lhs, Node *rhs) {
    return lhs->value < rhs->value;
}

void sort_list(List *list, int (*comparator)(Node *, Node *)) {
    if (!list || !list->head) {
        return;
    }
    Node *current = list->head->next;
    Node *last, *step;
    while (current) {
        step = current->next;
        last = current->previous;
        last->next = step;
        if (last->next)
            last->next->previous = last;
        while (last && comparator(last, current)) {
            last = last->previous;
        }
        if (last) {
            current->previous = last;
            current->next = last->next;
            last->next = current;
            if (current->next) {
                current->next->previous = current;
            }
        } else {
            pushfront_node(list, current);
        }
        current = step;
    }

}

int create_from_value(List *list, double val) {
    if (!list || list->head) {
        return 1;
    }
    Node *new = (Node *) malloc(sizeof(Node));
    new->value = val;
    list->head = new;
    list->tail = new;
    return 0;
}

int create_from_array(List *list, double *arr, size_t size) {
    if (!list || list->head) {
        return 1;
    }
    create_from_value(list, arr[0]);
    to_string(list);
    int response;
    Node *current = list->head;
    for (size_t i = 1; i < size; ++i) {
        Node *new = (Node *) malloc(sizeof(Node));
        new->value = arr[i];
        response = pushback_node(list, new);
        if (response) {
            return response;
        }
    }
    return 0;
}

int copy(List *from, List *to) {
    if (!from || !to || to->head || !from->head) {
        return 1;
    }
    int response;
    Node *current = from->head;
    while (current) {
        response = pushback(to, current->value);
        if (response) {
            return response;
        }
        current = current->next;
    }
    return 0;
}

