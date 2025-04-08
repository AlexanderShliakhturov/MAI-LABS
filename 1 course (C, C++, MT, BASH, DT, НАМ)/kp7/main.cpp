#include "matrix.hpp"

void print_inner(Matrix& matrix) {
    int i = 1;
    while ( !(matrix.line[i].first == 0 and matrix.line[i].second.string_number == 0) ) {
        if (matrix.line[i].second.string_number == -1) {
            cout << matrix.line[i].first << " " << matrix.line[i].second << endl;
        } else {
            cout << matrix.line[i].first << " " << matrix.line[i].second.string_number << endl;
        }
        i ++;
    }
    cout << "0 0" << endl;
}

void print_normal(Matrix& matrix, int M, int N) {
    int last_ind = 1;
    int good_line = -1;
    int good_column = -1;
    bool end = false;


    for (int i = 1; i <= M; i++) {        

        if (matrix.line[last_ind].first == 0) {
            good_line = matrix.line[last_ind].second.string_number;
            last_ind ++;
        }

        for (int j = 1; j <= M; j++) {


            if (matrix.line[last_ind].first == 0 and matrix.line[last_ind].second.string_number == 0) {
                end = true;
            }


            if (matrix.line[last_ind].first > 0 and matrix.line[last_ind].second.string_number == -1) {
                good_column = matrix.line[last_ind].first;
            }

            if (good_line == i and good_column == j and !end) {
                cout << matrix.line[last_ind].second;
                last_ind ++;
                
            } else {
                cout << setiosflags(ios::left) << setw(21) << "0";;
            }
        }
        cout << endl;
    }
}

pair< int, ComplexNumber > get_max_value(Matrix& matrix) {
    ComplexNumber maximum(0, 0);
    int i = 1;
    int column = -1;
    while ( !(matrix.line[i].first == 0 and matrix.line[i].second.string_number == 0) ) {
        i ++;
        if (matrix.line[i].first > 0) {
            maximum = max(maximum, matrix.line[i].second);
            if (!(matrix.line[i].second < maximum)) {
                maximum = matrix.line[i].second;
                column = matrix.line[i].first;
            }
        } 
    }
    return {column, maximum};
}

void task(Matrix& matrix, int size) {
    pair< int, ComplexNumber > result = get_max_value(matrix);
    ComplexNumber max_elem = result.second;
    int last_column = result.first;

    if (last_column == -1) {
        cout << "В таблице минимальный элемент равен нулю" << endl;
        return; 
    }


    for (int i = size - 1; i > 0; i --) {

        if (matrix.line[i].second == max_elem and last_column != matrix.line[i].first) {
            last_column = matrix.line[i].first;
            break;
        }

    }

    int i = 1;
    while ( !(matrix.line[i].first == 0 and matrix.line[i].second.string_number == 0) ) {
        if (matrix.line[i].first == last_column) {
            matrix.line[i].second /= max_elem;
        }
        i ++;
    }
}

int main() {
    int M, N;
    string val;
    cin >> M >> N;
    Matrix matrix(M, N);
    int last_index = 1;
    int this_line_has_number = 0;

    for (int i = 1; i <= M; i++) {

        
        this_line_has_number = 0;
        for (int j = 1; j <= N; j ++) {
            cin >> val;
            if (val == "0") {
                continue;
            }

            if (this_line_has_number == 0) {
                matrix.line[last_index].second.set_string_number(i);
                last_index ++;
                this_line_has_number = 1;
            }
            

            double real, imagine;
            string tmp = "";
            int k = 0;
            for (; k < (int) val.size(); k++) {
                if (val[k] == '+') {
                    k++;
                    break;
                }
                tmp += val[k];
            }
            real = stod(tmp);
            tmp = "";
            for (; k < (int) val.size(); k++) {
                if (val[k] == 'i') {
                    break;
                }
                tmp += val[k];
            }
            imagine = stod(tmp);

            matrix.line[last_index].first = j;
            matrix.line[last_index].second.real = real;
            matrix.line[last_index].second.imagine = imagine;
            last_index ++;
        }
    }
    matrix.line[last_index].second.string_number = 0;

    cout << "Внутренне представление матрицы до преобразования: " << endl << endl;
    print_inner(matrix);

    cout << endl <<  "Обычный вид матрицы до преобразования: " << endl << endl;
    print_normal(matrix, M, N);

    task(matrix, last_index);

    cout << endl << "Внутренне представление матрицы после преобразования: " << endl << endl;
    print_inner(matrix);

    cout << endl << "Обычный вид матрицы после преобразования: " << endl << endl;
    print_normal(matrix, M, N);
}