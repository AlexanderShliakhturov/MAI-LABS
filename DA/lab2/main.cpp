#include <iostream>
#include <fstream>

using namespace std;

void str_tolower(std::string& str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
}

struct Node {
    std::pair<std::string, unsigned long long> data;
    Node *left;
    Node *right;
    int priority;
    // int value;
    Node(std::string key, unsigned long long value) {data.first = key, data.second = value; left = right = nullptr; priority = ::rand() % 100000;}

};

class BST {

    Node *root;


    void removeTree(Node *p) {
        if (p == nullptr) return;

        removeTree(p->left);
        removeTree(p->right);

        delete p;
    }

    // pair<Node*, Node*> split_sofia(Node* t, std::string k) {
    //     if (t == nullptr) return pair<Node*, Node*>(nullptr, nullptr);

    //     if (k <= t->data.first) {
    //         auto splitted = split_sofia(t->left, k);
    //         auto t1 = splitted.first;
    //         auto t2 = splitted.second;

    //         t->left = t2;

    //         return pair<Node*, Node*>(t1, t);
    //     }

    //     auto splitted = split_sofia(t->right, k);
    //     auto t1 = splitted.first;
    //     auto t2 = splitted.second;

    //     t->right = t1;

    //     return pair<Node*, Node*>(t, t2);
    // }


    static void split_test(Node *n, std::string key, Node *&a, Node *&b) {
        if(!n) {
            a = b = nullptr;
            return;
        }
        if( (n->data).first < key){
            split_test(n->right, key, n->right, b);
            a = n;
        } else {
            split_test(n->left, key, a, n->left);
            b = n;
        }
    }

    static void split_test_equal(Node *n, std::string key, Node *&a, Node *&b) {
        if(!n) {
            a = b = nullptr;
            return;
        }
        if( (n->data).first <= key){
            split_test_equal(n->right, key, n->right, b);
            a = n;
        } else {
            split_test_equal(n->left, key, a, n->left);
            b = n;
        }
    }

    Node* merge(Node *t1, Node *t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;

        if (t1->priority >= t2->priority) {
            t1->right = merge(t1->right, t2);
            return t1;
        }

        t2->left = merge(t1, t2->left);
        return t2;
    }


    Node* find(Node *p, std::string k) {
        while (p) {
            if (k < (p->data).first) p = p->left;
            else if (k > (p->data).first) p = p->right;
            else return p;
        }
        return nullptr;
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        removeTree(root);
    }

    void printHelper(Node* node, int count = 0) {

        if(node == nullptr) {

            cout<<"Дерево пустое"<<endl;

            return;
        }

        if(node->right != nullptr) {

            printHelper(node->right, 1 + count);
        }

        string s(count * 4, ' ');

        cout<<s<<(node->data).first<<" "<<(node->data).second<<" "<<node->priority<<endl;

        if(node->left!= nullptr) {

            printHelper(node->left, 1 + count);
        }
    }

    void print(){
        printHelper(root);
        std::cout << std::endl;
    }

    void errase(std::string key) {
        Node *less, *equal, *greater;
        split_test(root, key, less, greater);
        split_test_equal(greater, key, equal, greater);
        delete equal;
        root = merge(less, greater);
    }

    void insert_test(std::pair<std::string, unsigned long long> k) {
        Node *less, *greater;
        split_test(root, k.first, less, greater);
        root = merge(merge(less, new Node(k.first, k.second)), greater);
    }

    Node* search_test(std::string key) {
        Node *less, *equal, *greater;
        split_test(root, key, less, greater);
        split_test_equal(greater, key, equal, greater);
        Node *result = equal;
        root = merge(merge(less, equal), greater);
        return  result;
    }

    Node* search_sofia(std::string k) {
        return find(root, k);
    }

    // void insert_sofia(std::pair<std::string, unsigned long long> k) {
    //     auto splitted = split_sofia\(root, k.first);
    //     auto t1 = splitted.first;
    //     auto t2 = splitted.second;

    //     t1 = merge(t1, new Node(k.first, k.second));
    //     root = merge(t1, t2);
    // }

};

int main() {

    // std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    BST tree;
    std::string s;

    std::ifstream in("test.txt");
    std::ofstream out("output.txt");


    while (in >> s)
    {
        if (s.empty())
        {
            continue;
        }
        if (s == "+") {
            std::string key;
            in >> key;
            unsigned long long value;
            in >> value;
            str_tolower(key);
            if (tree.search_sofia(key) == nullptr) {
                tree.insert_test({key, value});
                out << "OK" << std:: endl;
                // tree.print();
            }
            else {
                out << "Exist" << "\n";
                // tree.print();
                continue;
            }
        }
        else if (s == "-") {
            std::string key;
            in >> key;
            str_tolower(key);
            if (tree.search_sofia(key) != nullptr) {
                tree.errase(key);
                out << "OK"<< "\n";
                // tree.print();
            }
            else {
                out << "NoSuchWord" << "\n";
                // tree.print();
            }

        }
        else {
            str_tolower(s);
            if (tree.search_sofia(s) == nullptr) {
                out << "NoSuchWord" << "\n";
                // tree.print();
            }
            else {
                out << "OK: " << tree.search_sofia(s)->data.second  << "\n";
                // tree.print();
            }
        }
    }

    return 0;
}
