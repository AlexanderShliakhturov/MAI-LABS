#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <bits/stdc++.h>
using namespace std;

class LinkedList {
public:
    struct Node {
        int data;
        Node* next;
        Node(int data) : data(data), next(NULL) {}
    };

    Node* head;
    LinkedList();
    void insert(int data, int pos);
    void remove(int pos);
    void print();
    void merge_sort();

private:
    Node* merge_sort_rec(Node* node);
    Node* merge(Node* first, Node* second);
};

#endif