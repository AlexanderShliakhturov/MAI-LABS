#include "list.h"

void procedure(Node* node) {
    if (node == nullptr) return;
    while (node->next != nullptr) {
        if (node->val > node->next->val) {
            swap(node->val, node->next->val);
        }
        node = node->next;
    }
}

void bubble_sort(List l) {
    for (int _ = 0 ; _ < l.size; _ ++) {
        procedure(l.head);
    }
}

void help() 
{
    cout << "Для управления списком введите одну из следующих комманд: " << endl;
    cout << "help - Вызов меню помощи" << endl;
    cout << "quit - Выход из программы" << endl;
    //cout << "push_back <value> - добавить значение в конец" << endl;
    cout << "push_front <value> - добавить значение в начало" << endl;
    cout << "insert <index> <value> - добавить значение после определенного индекса" << endl;
    cout << "get_value <index> - получить значение по индексу" << endl;
    cout << "size - узнать размер списка" << endl;
    //cout << "pop_back - удалить последний элемент" << endl;
    //cout << "pop_front - удалить первый элемент" << endl;
    cout << "pop <index> - удалить элементы на определенном индексе" << endl;
    //cout << "remove <value> - удалить элемент по значению " << endl;
    //cout << "bubble_sort - выполнить сортировку пузырьком" << endl;
    cout << "print - вывести список" << endl;
    cout << "clear_if <value> - очистить список, если есть элемент с таким значением" << endl;
    cout << "clear_all - очистить список" << endl << endl << endl;
}

void menu()
{
    help();
    string action;
    List list;
    double val;
    int ind;
    while (true) {
        cin >> action;
        if (action == "help") {
            help();
            continue;
        }

        if (action == "quit") {
            return;
        }

        if (action == "push_back") {
            cin >> val;
            list.push_back(val);
            continue;
        }

        if (action == "push_front") {
            cin >> val;
            list.push_front(val);
            continue;
        }

        if (action == "insert") {
            cin >> ind >> val;
            if (ind < 0 or ind >= list.size) {
                cout << "Указан неверный индекс" << endl << endl;
            } else {
                list.insert(ind, val);
            }
            continue;
        }

        if (action == "get_value") {
            cin >> ind >> val;
            if (ind < 0 or ind >= list.size) {
                cout << "Указан неверный индекс" << endl << endl;
            } else {
                cout << list.get_node(ind)->val << endl << endl;
            }
            continue;
        }

        if (action == "size") {
            cout << list.size << endl << endl;
            continue;
        }

        if (action == "pop_back") {
            list.pop_back();
            continue;
        }

        if (action == "pop_front") {
            list.pop_front();
            continue;
        }

        if (action == "pop") {
            cin >> ind;
            if (ind < 0 or ind >= list.size) {
                cout << "Указан неверный индекс" << endl << endl;
            } else {
                list.pop_at_index(ind);
            }
            continue;
        }

        if (action == "remove") {
            cin >> val;
            if (list.find(val) == -1) {
                cout << "Указанного значения не существует в списке" << endl << endl;
            } else {
                list.remove(val);
            }
            continue;
        }

        if (action == "bubble_sort") {
            bubble_sort(list);
            continue;
        }

        if (action == "print") {
            list.print();
            continue;
        }

        if (action == "clear_if") {
            cin >> val;
            list.clear_if_in(val);
            continue;
        }

        if (action == "clear_all") {
            while (list.size) {
                list.pop_back();
            }
            continue;
        }

        cout << "Вы ввели неверное действие. Программа завершена" << endl << endl;
        break;
    }
}


int main()
{
    menu();
}
