#ifndef LIST_H
#define LIST_H

#include <bits/stdc++.h>
#include "node.h"

struct List {
    Node* head;
    Node* tail;
    int size;

    List();

    void push_back(double val);

    void push_front(double val);

    void insert(int i, double val);

    Node* get_node(int i);

    Node* operator[](int i);

    bool is_empty();

    Node* pop_back();

    Node* pop_front();

    void print();

    Node* pop_at_index(int i);

    int find(double val);

    void remove(double val);
    
    void clear_if_in(double val);
};

#endif
