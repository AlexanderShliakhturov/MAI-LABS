#include "line.hpp"



ComplexNumber string_to_complex(string value) {
    ComplexNumber number;
    string temp = "";
    int i = 0;

    for (; i < (int) value.size(); i ++) {
        if (value[i] == '+') {
            i ++;
            break;
        }
        temp += value[i];
    }
    number.real = stold(temp);
    temp = "";
    for (; i < (int) value.size(); i ++) {
        if (value[i] == 'i') {
            break;
        }
        temp += value[i];
    }
    number.imagine = stold(temp);
    return number;
}

void read_table(vector<Line>& table) {
    ComplexNumber key;
    string string_key;
    string data;
    cout << "Введите число элементов в таблице: ";
    int n;
    cin >> n;
    cout << endl;
    for (int i = 0; i < n; i ++) {
        cin >> string_key;
        key = string_to_complex(string_key);
        getline(cin, data);
        Line line = Line(key, data);
        table.push_back(line);
    }
}

vector<Line> sort_table(vector<Line>& table) {
    int counter[table.size()];
    for (int i = 0; i < (int) table.size(); i ++) {counter[i] = 0;}

    for (int i = 0; i < (int) table.size(); i ++) {
        for (int j = i + 1; j < (int) table.size(); j ++) {
            if (table[i].key < table[j].key) {
                counter[j] ++;
            } else {
                counter[i] ++;
            }
        }
    }

    vector<Line> new_table(table.size());
    for (int i = 0; i < (int) table.size(); i ++) {
        new_table[counter[i]] = table[i];
    }
    return new_table;
}

vector<Line> reverse(vector<Line>& table) {
    int counter[table.size()];
    for (int i = 0; i < (int) table.size(); i ++) {counter[i] = 0;}

    for (int i = 0; i < (int) table.size(); i ++) {
        for (int j = i + 1; j < (int) table.size(); j ++) {
            if (table[i].key < table[j].key) {
                counter[i] ++;
            } else {
                counter[j] ++;
            }
        }
    }

    vector<Line> new_table(table.size());
    for (int i = 0; i < (int) table.size(); i ++) {
        new_table[counter[i]] = table[i];
    }
    return new_table;
}

vector<Line> random(vector<Line>& table) {
    int counter[table.size()];
    int busy_index[table.size()];

    for (int i = 0; i < (int) table.size(); i ++) {counter[i] = 0;}
    for (int i = 0; i < (int) table.size(); i ++) {
        int random = rand() % table.size();
        while (busy_index[random] == 1) {
            random = rand() % table.size();
        }
        counter[i] = random;
        busy_index[random] = 1;
    }

    vector<Line> new_table(table.size());
    for (int i = 0; i < (int) table.size(); i ++) {
        new_table[counter[i]] = table[i];
    }
    return new_table;
}

void print_table(vector<Line>& table) {
    for (int i = 0; i < (int) table.size(); i++) {
        cout << table[i].key << table[i].data << endl;
    }
    cout << endl << endl;
}

string binary_search(vector<Line>& table, ComplexNumber& key, int high, int low) {
    while (low <= high) {
        int mid = (int) ((low + high) / 2);
        if (table[mid].key == key) {
            return table[mid].data;
        }
        if (table[mid].key < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return "Заданного елемента нет в таблице\n";
}

string binary_search(vector<Line>& table) {
    cout << "Введите число: \n";
    string value;
    cin >> value;
    ComplexNumber key = string_to_complex(value);
    int n = (int) table.size();
    vector<Line> sorted_table = sort_table(table);
    return binary_search(sorted_table, key, n - 1, 0);
}

void help() {
    cout << "help - описание команд" << endl;
    cout << "quit - выход из программы" << endl;
    cout << "make - инициализировать таблицу" << endl;
    cout << "sort - отсортировать по возрастанию ключа" << endl;
    cout << "reverse - отсортировать по убыванию ключа" << endl;
    cout << "random - перемешать элементы таблицы в случайном порядке" << endl;
    cout << "binary_search - выполнить бинарный поиск строки по ключу" << endl;
}

void menu() {
    help();
    cout << endl;
    string input;
    vector<Line> table;
    while (true) {
        cin >> input;

        if (input == "help") {
            help();
            cout << endl;
            continue;
        }

        if (input == "quit") {
            break;
        }

        if (input == "make") {
            read_table(table);
            cout << endl;
            continue;
        }

        if (input == "sort") {
            print_table(table);
            table = sort_table(table);
            print_table(table);
            cout << endl;
            continue;
        }

        if (input == "reverse") {
            print_table(table);
            table = reverse(table);
            print_table(table);
            cout << endl;
            continue;
        }

        if (input == "random") {
            print_table(table);
            table = random(table);
            print_table(table);
            cout << endl;
            continue;
        }

        if (input == "binary_search") {
            cout << binary_search(table) << endl;
            cout << endl;
            continue;
        }

        cout << "Введена неверная команда" << endl;
        return;
    }
}

int main() {
    menu();
}