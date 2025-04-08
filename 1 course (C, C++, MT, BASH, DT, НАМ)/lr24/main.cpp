#include<bits/stdc++.h>
#include "Node.hpp"

using namespace std;

int is_operator(char c) {
    return c == '-' or c == '+' or c == '*' or c == '/' or c == '(' or c == ')' or c == '^' or c == '_'; 
}

int is_num(string elem) {
    return elem.size() >= 2 or isdigit(elem[0]) or isalpha(elem[0]);
}

queue<string> get_revers_polish_notation(string input) {
    queue<string> out;
    queue<string> in;
    stack<string> operators;
    string num;
    int in_num = 0;
    int was_operator = 0;
    
    // Создаем входную очередь
    for (int i = 0; i < (int) input.size(); i ++) { 

        // Если открывающаяся скобка, то значит может быть унарный минус
        if (input[i] == '(') {
            was_operator = 0;
        }
        
        // Первая цифра числа
        if (in_num == 0 and (isdigit(input[i]) or isalpha(input[i]))) {
            in_num = 1;
            num += input[i];
            continue;
        }

        // В этом случае у нас унарный минус перед выражением. Чтобы отличать его от обычного минуса, заменим его на _
        if (in_num == 0 and was_operator == 0 and input[i] == '-') {
            in.push("_");
            was_operator = 1;
            continue;
        }

        // Не первая цифра числа, продолжаем уже существующее
        if (in_num and (isdigit(input[i]) or isalpha(input[i]))) {
            num += input[i];
            continue;
        }
        // Если это оператор, добавляем его
        if (is_operator(input[i])) {
            if (num.size()) {
                in.push(num);
                in_num = 0;
                num = "";
            }
            in.push(string(1, input[i]));
            continue;
        }
    }

    if (num.size()) {
        in.push(num);
    }

    map<string, int> priority = {
        {"-", 1},
        {"+", 1},
        {"*", 2},
        {"/", 2},
        {"_", 2},
        {"^", 3}
    };

    // Создаем выходную очередь
    while (!in.empty()) {
        string elem = in.front();
        in.pop();

        if (is_num(elem)) {
            out.push(elem);
        } else {

            if (operators.empty() or elem == "(") {
                operators.push(elem);
                continue;
            }

            if (elem == ")") {

                while (operators.top() != "(") {
                    out.push(operators.top());
                    operators.pop();
                }

                operators.pop();
                continue;
            }


            while ((operators.size() and priority[elem] <= priority[operators.top()]) ) {
                // Возведение правоасициативная операция, она единственная. Поэтому, если встречаем несколько их подряд, то перекидывать их в выходную очередь не нужно.
                if (elem == "^" and operators.top() == "^") {
                    break;
                }
                out.push(operators.top());
                operators.pop();
            }

            operators.push(elem);
        }
    }
    while (operators.size()) {
        out.push(operators.top());
        operators.pop();
    }
    return out;
}

Node* get_tree(queue<string> polish_notation) {
    stack<Node*> nodes;
    while (!polish_notation.empty()) {
        string elem = polish_notation.front();
        polish_notation.pop();

        //Унарный минус
        if (elem == "_") {
            Node* el_left = nodes.top();
            nodes.pop();
            Node* uno_minus_elem = new Node(elem);
            uno_minus_elem->value = "-";
            uno_minus_elem->right = el_left;
            nodes.push(uno_minus_elem);
            continue;
        }

        // Обычное число
        if (is_num(elem)) {
            Node* new_node = new Node(elem);
            nodes.push(new_node);
        // Иначе, бинарный оператор
        } else {
            Node* el_right = nodes.top();
            nodes.pop();
            Node* el_left = nodes.top();
            nodes.pop();
            Node* new_node = new Node(elem);
            new_node->left = el_left;
            new_node->right = el_right;
            nodes.push(new_node);
        }
    }
    return nodes.top();
}
void print_tree(Node* node, int tab) {
    if (node == nullptr) return;
    print_tree(node->right, tab + 1);
    for (int i = 0; i < tab; i ++) {
        cout << '\t';
    }
    cout << node->value << endl;
    print_tree(node->left, tab + 1);
}

void get_infix(Node* node) {
    if (node == nullptr) return;
    if (node->value.size() == 1 and is_operator((node->value)[0])) {
        cout << "(";
    }
    get_infix(node->left);
    cout << node->value;
    get_infix(node->right);
    if ((node->left != nullptr and node->right != nullptr) or (node->left == nullptr and node->right != nullptr and node->value == "-")) {
        cout << ")";
    }
}

int bin_pow(int x, int y) {
    int z = 1;
    while (y) {
        if (y & 1) z *= x;
        y = y >> 1;
        x *= x;
    }
    return z;
}

string calc_value(string el1, string el2, string oper) {
    int res;
    int is_negative = 0;
    if (oper == "+") {
        res = stoi(el1) + stoi(el2);
    }
    if (oper == "-") {
        res = stoi(el1) - stoi(el2);
    }
    if (oper == "*") {
        res = stoi(el1) * stoi(el2);
    }
    if (oper == "/") {
        res = stoi(el1) / stoi(el2);
    }
    if (oper == "^") {
        res = bin_pow(stoi(el1), stoi(el2));
    }
    
    string result = "";
    if (res < 0) {
        is_negative = 1;
        res *= -1;
    }
    while (res > 0) {
        string digit;
        if (res % 10 == 0) digit = "0";
        if (res % 10 == 1) digit = "1";
        if (res % 10 == 2) digit = "2";
        if (res % 10 == 3) digit = "3";
        if (res % 10 == 4) digit = "4";
        if (res % 10 == 5) digit = "5";
        if (res % 10 == 6) digit = "6";
        if (res % 10 == 7) digit = "7";
        if (res % 10 == 8) digit = "8";
        if (res % 10 == 9) digit = "9";
        result += digit;
        res = floor(res / 10);
    }
    if (is_negative) result += "-";
    reverse(result.begin(), result.end());
    if (result.empty()) {
        result = "0";
    }
    return result;
}

bool is_var(string var) {
    for (char letter : var) {
        if (!( ('a' <= letter and letter <= 'z') or  ('A' <= letter and letter <= 'Z') )) {
            return false;
        }
    }
    return true;
}

void task(Node* node) {
    if (is_num(node->left->value) and is_var(node->right->value)) {
        int add = stoi(node->left->value);
        string var = node->right->value;
        if (add == 1) {
            node->value = node->right->value;
            node->left = nullptr;
            node->right = nullptr;
            return;
        }
        
        node->value = "+";
        while (add > 2) {
            node->right = new Node(var);
            node->left = new Node("+");
            
            add --;
            node = node->left;
        }
        node->left = new Node(var);
        
        node->right = new Node(var);
    }

    if (is_num(node->right->value) and is_var(node->left->value)) {
        int add = stoi(node->right->value);
        string var = node->left->value;
        if (add == 1) {
            node->value = node->left->value;
            node->right = nullptr;
            node->left = nullptr;
            return;
        }
        
        node->value = "+";
        while (add > 2) {
            node->left = new Node(var);
            node->right = new Node("+");
            
            add --;
            node = node->right;
        }
        node->right = new Node(var);
        
        node->left = new Node(var);
    }
    
}


void search_multiply(Node* node) {
    if (node == nullptr) return;
    search_multiply(node->left);
    search_multiply(node->right);
    if (node->value == "*" and node->left != nullptr and node->right != nullptr) {
        task(node);
    }
}

void del_nodes(Node* node) {
    if (node == nullptr) {
        return;
    }
    del_nodes(node->left);
    del_nodes(node->right);
    delete node;
}

int main() {
    string input;
    string tmp;
    while(cin >> tmp) {
        input += tmp;
    }
    
    queue<string> polish = get_revers_polish_notation(input);
    Node* root = get_tree(polish);
    cout << "Дерево выражения до преобразования" << endl << endl;
    print_tree(root, 0);
    cout << "Инфиксная запись до преобразования" << endl << endl;
    get_infix(root);
    search_multiply(root);
    cout << endl;
    cout << "Дерево выражения после преобразования" << endl << endl;
    print_tree(root, 0);
    cout << "Инфиксная запись после преобразования" << endl << endl;
    get_infix(root);
    cout << endl;

    del_nodes(root);
}