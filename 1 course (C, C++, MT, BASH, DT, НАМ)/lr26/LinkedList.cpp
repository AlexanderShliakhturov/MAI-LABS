#include <bits/stdc++.h>
using namespace std;

#include "LinkedList.h"
#include "Node.h"

LinkedList::LinkedList() {
    head = nullptr;
}

void LinkedList::insert(int data, int pos) {
    Node* new_node = new Node(data);
    if (head == NULL) {
        // если список пустой, добавляем элемент в начало
        head = new_node;
    }
    else if (pos == 0) {
        // если позиция равна 0, добавляем элемент в начало
        new_node->next = head;
        head = new_node;
    }
    else {
        // ищем элемент, предшествующий позиции вставки
        Node* prev = head;
        for (int i = 0; i < pos - 1 && prev->next != NULL; i++) {
            prev = prev->next;
        }
        // если позиция больше длины списка, добавляем элемент в конец
        if (prev->next == NULL) {
            prev->next = new_node;
        }
        else {
            // вставляем элемент между prev и prev->next
            new_node->next = prev->next;
            prev->next = new_node;
        }
    }
    }

void LinkedList::remove(int pos) {
    // проверяем, что список не пустой
    if (head == NULL) {
        return;
    }

    Node* to_delete;

    if (pos == 0) {
        // если удаляем первый элемент, просто обновляем указатель на голову списка
        to_delete = head;
        head = head->next;
    }
    else {
        // ищем элемент, предшествующий позиции удаления
        Node* prev = head;
        for (int i = 0; i < pos - 1 && prev->next != NULL; i++) {
            prev = prev->next;
        }
        // проверяем, что позиция не превышает размер списка
        if (prev->next == NULL) {
            return;
        }
        // удаляем элемент
        to_delete = prev->next;
        prev->next = to_delete->next;
    }

    // освобождаем память, выделенную для удаляемого элемента
    delete to_delete;
}

void LinkedList::print() {
     Node* curr = head;
        while (curr != NULL) {
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }

void LinkedList::merge_sort() {
    head = merge_sort_rec(head);
}

LinkedList::Node* LinkedList::merge_sort_rec(Node* node)  {
   if (node == NULL || node->next == NULL) {
            return node;
        }

        // разделяем список на две части
        Node* fast = node->next;
        Node* slow = node;
        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        Node* second_half = slow->next;
        slow->next = NULL;

        // сортируем каждую часть рекурсивно
        Node* first_half_sorted = merge_sort_rec(node);
        Node* second_half_sorted = merge_sort_rec(second_half);

        // объединяем две отсортированные части
        Node* merged_list = merge(first_half_sorted, second_half_sorted);
        return merged_list;
    }

LinkedList::Node* LinkedList::merge(Node* first, Node* second) {
    if (first == NULL) {
            return second;
        }
        if (second == NULL) {
            return first;
        }

        if (first->data < second->data) {
            first->next = merge(first->next, second);
            return first;
        }
        else {
            second->next = merge(first, second->next);
            return second;
        }
    }