#include "list.h"

List::List() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

    void List::push_back(double val) {
        // Случай 1, пустой список
        size ++;
        if (head == nullptr) {
            head = new Node(val);
            tail = head;
            return;
        }
        // Случай 2, список состоит из одного элемента (в этом случае конец и начало равны)
        if (head == tail) {
            head->next = new Node(val);
            tail = head->next;
            return;
        }
        // Случай 3, список состоит более чем из одного элемента
        tail->next = new Node(val);
        tail = tail->next;
    }

    void List::push_front(double val) {
        size ++;
        // Случай 1, пустой список
        if (head == nullptr) {
            head = new Node(val);
            tail = head;
            return;
        }
        // Случай 2, список состоит из одного элемента (в этом случае конец и начало равны)
        if (head == tail) {
            head = new Node(val);
            head->next = tail;
            return;
        }
        // Случай 3, список состоит более чем из одного элемента
        Node* tmp = head;
        head = new Node(val);
        head->next = tmp;
    }

    // Вставка (добавление) нового элемента по его значению на индекс следующий за индексом i
    void List::insert(int i, double val) {
        Node* left = get_node(i);
        if (left == nullptr) return;
        Node* right = get_node(i + 1);
        if (right == nullptr) {
            push_back(val);
            return;
        }
        left->next = new Node(val);
        left->next->next = right;
        size ++;
    }

    Node* List::get_node(int i) {
        if (i < 0 or i >= size) return nullptr;
        Node* node = head;
        while (i != 0) {
            node = node->next;
            i --;
        }
        return node;
    }

    Node* List::operator[](int i) {
        return get_node(i);
    }

    bool List::is_empty() {
        return size == 0;
    }

    Node* List::pop_back() {
        // Случай 1, пустой список
        if (this->is_empty()) {
            return nullptr;
        }
        // Случай 2, список состоит из одного элемента (в этом случае конец и начало равны)
        if (head == tail) {
            size --;
            Node* tmp = head;
            delete head;
            head = nullptr;
            tail = nullptr;
            return tmp;
        }
        // Случай 3, список состоит более чем из одного элемента
        size --;
        Node* tmp = tail;
        delete tail;
        Node* new_tail = get_node(size - 1);
        new_tail->next = nullptr;
        tail = new_tail;
        return tmp;
    }

    Node* List::pop_front() {
        // Случай 1, пустой список
        if (this->is_empty()) {
            return nullptr;
        }
        // Случай 2, список состоит из одного элемента (в этом случае конец и начало равны)
        if (head == tail) {
            size --;
            Node* tmp = head;
            delete head;
            head = nullptr;
            tail = nullptr;
            return tmp;
        }
        // Случай 3, список состоит более чем из одного элемента
        size --;
        Node* old_front = head;
        head = old_front->next;
        return old_front;
    }

    void List::print() {
        Node* node = head;
        while (node != nullptr ) {
            cout << node->val << " ";
            node = node->next;
        }
        cout << endl << endl;
    }

    Node* List::pop_at_index(int i) {
        if (i < 0 or i >= size) return nullptr;
        if (i == 0) return pop_front();
        if (i == size - 1) return pop_back();
        Node* left = get_node(i - 1);
        Node* right = get_node(i + 1);
        left->next = right;
        Node* curr = get_node(i);
        size --;
        return curr;
    }

    int List::find(double val) {
        Node* node = head;
        int k = 0;
        if (node == nullptr) return -1;
        while (node->val != val) {
            if (node == nullptr) return -1;
            node = node->next;
            if (node == nullptr) return -1;
            k ++;
        }
        return k;
    }

    void List::remove(double val) {
        int i = find(val);
        if (i != -1) {
            pop_at_index(i);
        }
    }
    
    void List::clear_if_in(double val) {
    	if (find(val) != -1) {
    		while(size != 0) {
    			pop_back();
    		}
    	}
    }
