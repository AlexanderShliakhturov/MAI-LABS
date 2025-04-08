#include <bits/stdc++.h>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    
    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }

    //~Node() {
    //    //cout << "DESTROYED " << this->value << endl;    
    //}
};

struct BinaryTree {
    Node* root;
    BinaryTree() {
        root = nullptr;
    }
    
    void insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
        }
        else {
            Node* obj = root;
            while(true) {
                if (value == obj->value) return;
                if (value < obj->value) {
                    if (obj->left == nullptr) {
                        obj->left = new Node(value);
                        return;
                    }
                    else {
                        obj = obj->left;
                    } 
                }
                if (value > obj->value) {
                    if (obj->right == nullptr) {
                        obj->right = new Node(value);
                        return;
                    }
                    else {
                        obj = obj->right;
                    } 
                }
            }
        }
    }
    
    void get_depth(int n, int &mx, Node* obj) {
        mx = max(mx, n);
        if (obj == nullptr) {
            obj = root;
        }
        if (obj->left != nullptr) {
            get_depth(n + 1, mx, obj->left);
        }
        if (obj->right != nullptr) {
            get_depth(n + 1, mx, obj->right);
        }
    }
 
    int exist_node(int val, Node* obj) {
        if (root == nullptr) return 0;
        if (obj->value == val) return 1;


        if (val < obj->value) {

            if (obj->left != nullptr) {
                return exist_node(val, obj->left);
            }
            return 0;

        }
            
        else {
            if (obj->right != nullptr) {
                return exist_node(val, obj->right);
            }
            return 0;
        }
    }

    void show(Node* root, int tabs) {
        if (root == nullptr) return;
        show(root->right, tabs + 1);
        for (int _ = 0; _ < tabs; _ ++) {
            cout << '\t';
        }
        cout << root->value << endl;
        show(root->left, tabs + 1);
    }

    void remove(int val) {

        if (this->exist_node(val, this->root) == 0) return; 

        Node* obj = root;
        int k = -1;
        int levels = 1;
        this->get_depth(1, levels, nullptr);

        // Checking exsisting of obj
        if (obj) {
            
            // If deleting root
            if (obj->value == val) {

                if (obj->left == nullptr && obj->right == nullptr) {
                    delete root;
                    root = nullptr;
                    return;
                }

                // 1 child
                if (obj->left != nullptr && obj->right == nullptr) {
                    root = obj->left;
                    delete obj;
                    return;
                    
                }

                // 1 child
                if (obj->left == nullptr && obj->right != nullptr) {
                    root = obj->right;
                    delete obj;
                    return;
                }

                //2 child
                if (obj->left != nullptr && obj->right != nullptr) {

                    root = obj->right;

                    Node* left_node;
                    left_node = root;

                    while(true) {
                        if (left_node->left != nullptr) {
                            left_node = left_node->left;
                        }
                        else {
                            break;
                        }
                    }

                    left_node->left = obj->left;
                    delete obj;
                    return;
                }
            }

            while (true) {

                if (val < obj->value) {
                    if (val == obj->left->value) {
                        k = 1;
                        break;
                    }
                    obj = obj->left;
                    continue;
                }

                if (val > obj->value) {
                    if (val == obj->right->value) {
                        k = 2;
                        break;
                    }
                    obj = obj->right;
                    continue;
                }

            }

            if (k == 1) {

                // No child
                if (obj->left->left == nullptr && obj->left->right == nullptr) {
                    delete obj->left;
                    obj->left = nullptr;
                    return;
                }

                // 1 child
                if (obj->left->left != nullptr && obj->left->right == nullptr) {
                    Node* temp;
                    temp = obj->left;
                    obj->left = obj->left->left;
                    delete temp;
                    return;
                    
                }

                // 1 child
                if (obj->left->left == nullptr && obj->left->right != nullptr) {
                    Node* temp;
                    temp = obj->left;
                    obj->left = obj->left->right;
                    delete temp;
                    return;
                }

                // 2 child
                if (obj->left->left != nullptr && obj->left->right != nullptr) {
                    Node* temp;
                    temp = obj->left;
                    obj->left = obj->left->right;

                    Node* left_node;
                    left_node = obj->left;

                    while(true) {
                        if (left_node->left != nullptr) {
                            left_node = left_node->left;
                        }
                        else {
                            break;
                        }
                    }

                    left_node->left = temp->left;
                    delete temp;
                    return;
                }
            }

            if (k == 2) {

                // No child
                if (obj->right->left == nullptr && obj->right->right == nullptr) {
                    delete obj->right;
                    obj->right = nullptr;
                    return;
                }

                // 1 child
                if (obj->right->left != nullptr && obj->right->right == nullptr) {
                    Node* temp;
                    temp = obj->right;
                    obj->right = obj->right->left;
                    delete temp;
                    return;
                }

                // 1 child
                if (obj->right->left == nullptr && obj->right->right != nullptr) {
                    Node* temp;
                    temp = obj->right;
                    obj->right = obj->right->right;
                    delete temp;
                    return;
                }

                // 2 child
                if (obj->right->left != nullptr && obj->right->right != nullptr) {
                    Node* temp;
                    temp = obj->right;
                    obj->right = obj->right->right;

                    Node* left_node;
                    left_node = obj->right;

                    while(true) {
                        if (left_node->left != nullptr) {
                            left_node = left_node->left;
                        }
                        else {
                            break;
                        }
                    }

                    left_node->left = temp->left;
                    delete temp;
                    return;
                }
            }
        }     
    }

    int check_B(Node* root) {

        if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr)) {
            return 0;
        }

        if (root->right != nullptr) {
            if (check_B(root->right) == 0) {
                return 0;
            }
        }

        if (root->left != nullptr) {
            if (check_B(root->left) == 0) {
                return 0;
            }
        }
        return 1;
    }
};

int str_validate(string s) {
    int key = 1;

    for (char i : s) {  
        if (('0' > i || i > '9') && i != '-') {
            key = 0;
            break;
        }
    }
    return key;
}


void menu() {
    cout << "h - справка" << endl;
    cout << "q - выход" << endl;
    cout << "mktree - создание дерева" << endl;
    cout << "insert <> - добавление элемента" << endl;
    cout << "remove <> - удаление элемента" << endl;
    cout << "Btree - проверка, является ли дерево B-деревом" << endl;
    cout << "show - вывод" << endl << endl; 
    string s;
    BinaryTree bt;
    string value;
    int tree_exists = 0;
    int val;
    const vector<string> CORRECT_INPUT = {"h", "q", "mktree", "insert", "remove", "depth", "show"};
    const int CNT_CORRECT_INPUTS = CORRECT_INPUT.size();
    

    while(true) {

        cin >> s;

        // Пользователь захотел выйти
        if (s == "q") {
            break;
        }

        if (s == "h" ) {
            cout << "h - справка" << endl;
            cout << "q - выход" << endl;
            cout << "mktree - создание дерева" << endl;
            cout << "insert <> - добавление элемента" << endl;
            cout << "remove <> - удаление элемента" << endl;
            cout << "Btree - проверка, является ли дерево B-деревом" << endl;
            cout << "show - вывод" << endl << endl;
            continue;
        }

        // Создание дерева
        if (tree_exists == 0 && s == "mktree") {
            tree_exists = 1;
            cout << "Дерево создано" << endl;
            continue;
        }
        if (tree_exists && s == "mktree") {
            cout << "Дерево уже создано" << endl;
            continue;
        }


        // Добавление значения
        if (tree_exists && s == "insert") {
            cin >> value;
            
            if (str_validate(value)) {
                val = stoi(value);
            }
            else {
                cout << "Введено не число" << endl;
                continue;
            }

            if (bt.exist_node(val, bt.root) == 1) {
                cout << "Вершина " << val <<  " уже в дереве" << endl;
                continue;
            }

            bt.insert(val);
            cout << "Добавлено значение " << val << endl;
            continue;
        }
        if (tree_exists == 0 && s == "insert") {
            cin >> value;
            cout << "Дерева не существует, не возможно добавить элемент" << endl;
            continue;
        }

        // Удаление вершины
        if (tree_exists && s == "remove") {
            cin >> value;
            if (str_validate(value)) {
                val = stoi(value);
            }
            else {
                cout << "Введено не число" << endl;
                continue;
            }

            if (bt.exist_node(val, bt.root) == 0) {
                cout << "Вершины " << val <<  " не существует" << endl;
                continue;
            }

            bt.remove(val);
            cout << "Удалена вершина со значением  " << val << endl;
            if (bt.root == nullptr) {
                tree_exists = 0;
                cout << "Дерево удалено" << endl;
            }
            continue;
        }
        if (tree_exists == 0 && s == "remove") {
            cin >> value;
            cout << "Дерева не существует, невозможно удалить вершину" << endl;
            continue;
        }

        if (tree_exists && s == "show") {
            bt.show(bt.root, 0);
            continue;
        }
        if (tree_exists == 0 && s == "show") {
            cout << "Дерева не существует" << endl;
            continue;
        }

        if (tree_exists && s == "Btree") {
            if (bt.check_B(bt.root)) {
                cout << "Это дерево является B-деревом" << endl;
            }
            else {
                cout << "Это дерево является не B-деревом" << endl;
            }
            continue;
        }

        if (tree_exists == 0 && s == "Btree") {
            cout << "Дерева не существует" << endl;
            continue;
        }

        cout << "Ошибка, неверная команда!!!" << endl;
        break;
        
    }

    
}

int main() {
    menu();
}
