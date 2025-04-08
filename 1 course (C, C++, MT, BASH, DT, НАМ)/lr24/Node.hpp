#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED
#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    string value;
    Node(string val);
};

#endif// NODE_HPP_INCLUDED