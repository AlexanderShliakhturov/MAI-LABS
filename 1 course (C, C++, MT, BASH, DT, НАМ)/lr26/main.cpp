#include "Node.h"
#include <bits/stdc++.h>
using namespace std;
#include "LinkedList.h"
#include "Node.h"

int main() {
    void menu();
    cout << "mklist - создать список" << endl;
    cout << "q - выход" << endl;
    cout << "insert <value> <position> - добавить элемент value на позицию position" << endl;
    cout << "printlist - вывести список" << endl;
    cout << "mergesort - отсортировать слиянием" << endl;
    cout << "remove <position> - удалить элемент на позиции position" << endl << endl;
    string s;
    LinkedList list;
    int value;
    int position;
    int list_exist = 0;
    while(true) {

        cin >> s;
        
        // Создание списка
        if (list_exist == 0 && s == "mklist") {
            list_exist = 1;
            cout << "Список создан" << endl;
            continue;
        }
        if (list_exist && s == "mklist") {
            cout << "Список уже создан" << endl;
            continue;
        }

        // Добавление значения
        if (list_exist && s == "insert") {
            cin >> value;
            cin >> position;
            list.insert(value, position); 
            cout << "Добавлен элемент " << value << " на позицию " << position  << endl;
            continue;}

        if (list_exist == 0 && s == "insert"){
            cout << "Список не создан"  << endl;
            continue;
            }

        // Удаление элемена
        if (list_exist && s == "remove") {
            cin >> position;
            list.remove(position); 
            cout << "Удален элемент на позиции " << position  << endl;
            continue;}

        if (list_exist == 0 && s == "remove"){
            cout << "Список не создан"  << endl;
            continue;
            }
        
         // Вывод списка
        if (list_exist == 1  && s == "printlist"){
            cout << "Список: ";
            list.print();
            continue;
            }

        // if (list_exist == 0  && s == "printlist"){ 
        //     cout << "Список не создан"  << endl;
        //     continue;
        //     }
         
         // Сортировка списка
        if (list_exist == 1  && s == "mergesort"){ 
            list.merge_sort();
            cout << "Список отсортирован " << endl;
            continue;
            }
        if (list_exist == 0 && s == "mergesort"){ 
            cout << "Список не создан" << endl;
            continue;
            }
            
         // Пользователь захотел выйти
        if (s == "q") {
            break;
        }

    }
}