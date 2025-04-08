#include <bits/stdc++.h>
#include <fstream>
#include <chrono>

using namespace std;
//максимальная мощность возможного алфавита, из символов которого состоит текст
const int POWER_ALPH  = 256;
//символ, который лексикографически меньше всех элементов алфавита, это символ с кодом 96
char lowerSymbol = '`';


//сам класс суффиксного массива
struct SuffixArray {
    //текст, на основе которого строится суфф массив
    string text;
    //вектор с индексами, который после алгоритма построения суфф массива по факту сам и станет суфф массивом
    vector<int> indexes;
    //вектор с классами эквивалентности
    vector<int> EC;
    //количество символов, которое мы добавили к тексту, чтобы добить его до ближайшей степени двойки
    int numberOfAdded = 1;
    //это поле просто для удобства, так как почти во всех методах ниже я буду использовать размер текста
    int textSize = 0;
    // шаг - это тоже вещь, которая нужна для алгоритма, сначала он равен 1, потом 2, потом 4, потом 8, 16, 32, 64 и тд, то есть это сепень двойк
    int step = 1;
    //конструктор суфф массива, который принимает текст, на основе которого мы будем его строить и в конец текста дописывает синдинел
    SuffixArray (string& text) : text(std::move(text + '`')) {
       //вспомогательный метод, которы дополняет текст до ближайшей степени двойки
        completeDegree();
        // метод, который непосредственно строит суфф массив, в нём реализована вся логика алгоритма построения
        build();
        //вспомогательный метод, который после построения суфф массива удаляем все символы, которые мы добавили в текст в методе `completeDegree`
        removeUnnecessary();
    }
    //вспомогательный метод, который после построения суфф массива удаляем все символы, которые мы добавили в текст в методе `completeDegree`
    void removeUnnecessary() {
        vector<int> ind;
        for(size_t i = numberOfAdded; i < indexes.size(); ++i) {
            ind.emplace_back(indexes[i]);
        }
        string t;
        for(int i = 0; i < (textSize - numberOfAdded); ++i) {
            t.push_back(text[i]);
        }
        swap(ind, indexes);
        swap(text, t);
        textSize = text.size();
    }
    //вспомогательный метод, которы дополняет текст до ближайшей степени двойки
    void completeDegree() {
        int degree = 0;
        while(text.size() > std::pow(2, degree)) {
           ++degree;
        }
        int c = text.size();
        for(int i = 0; i < (std::pow(2, degree) - c); ++i) {
            text.push_back(lowerSymbol); ++numberOfAdded;
        }
        textSize = text.size();
    }
    bool start() {
        //вектор, который нужен для сортировки подсчетом символов в тексте
        vector<int> helper(POWER_ALPH, 0);
        //вектор индексов
        vector<int> ind(textSize, 0);
        //вектор класса эквивалентности
        vector<int> ec(textSize, 0);

        //--------------------
        for(char c : text) {
            ++helper[c - lowerSymbol];
        }
        for(int i = 1; i < POWER_ALPH; ++i) {
            helper[i] += helper[i-1];
        }

        for(int i = textSize - 1; i >= 0; --i) {
            ind[--helper[text[i] - lowerSymbol]] = i;
        }


        ec[ind[0]] = 0; bool flag = true;
        for(int i = 1; i < textSize; ++i) {
            if(text[ind[i]] == text[ind[i-1]]) {
                ec[ind[i]] = ec[ind[i-1]]; flag = false;
            } else {
                ec[ind[i]] = ec[ind[i-1]] + 1;
            }
        }
        swap(ind, indexes);
        swap(ec, EC);
        return flag;
    }

    // метод, который непосредственно строит суфф массив, в нём реализована вся логика алгоритма построения
    void build() {
        if(start()) //проделываю первую иттерацию, возможно на этом этапе уже будет построен суфф массив, если это так, то делаю return, это возможно только когда текст состоит из попарно различных символов
            return;
        while(step < textSize) {
            vector<int> ind(textSize, 0);
            vector<int> ec(textSize, 0);

            //обновляем индексы
            for(int i = 0; i < textSize; ++i) {
                ind[i] = (indexes[i] - step + textSize) % textSize;
            }
            //обновляем классы эквивалентности
            for(int i = 0; i < textSize; ++i) {
                ec[i] = EC[ind[i]];
            }

            // начинаем сортировку подсчетом
            // формируем массив подсчетов и префикс сумму
            vector<int> helper(textSize, 0);
            for(int i = 0; i < textSize; ++i) {
                ++helper[ec[i]];
            }
            for(int i = 1; i < textSize; ++i) {
                helper[i] += helper[i-1];
            }

            //заполняем массив правильных идексов, отсорченных по классам эквивалентности
            vector<int> indHelper(textSize, 0);
            for(int i = textSize - 1; i >= 0; --i){
                indHelper[--helper[ec[i]]] = ind[i];
            }

            //проставляем новые классы эквивалентности, состоящие из двух чисел
            vector<pair<int, int>> ecDoubleHelper(textSize, {0, 0});
            for(int i = 0; i < textSize; ++i) {
                ecDoubleHelper[i].first = EC[indHelper[i]];
                ecDoubleHelper[i].second = EC[(indHelper[i] + step) % textSize];
            }

            //Проставляем новые одиночные индексы
            EC[indHelper[0]] = 0; bool flag = true;
            for(int i = 1; i < textSize; ++i) {
                if(ecDoubleHelper[i] == ecDoubleHelper[i-1]) {
                    EC[indHelper[i]] = EC[indHelper[i-1]]; flag = false;
                } else {
                    EC[indHelper[i]] = EC[indHelper[i-1]] + 1;
                }
            }
            swap(indHelper, indexes);
            step *= 2;
            if(flag)
                return;
        }
    }

    //вспомогательный метод, который сравнивает на равенство паттерн и подстроку текста
    bool equal(const string& pattern, int x) {
        for(int i = 0; i < pattern.size(); ++i) {
            if(x + i > textSize - 1) return false;
            if(pattern[i] != text[x + i]) {
                return false;
            }
        }
        return true;
    }
    //вспомогательный метод, который проверяет, больше ли паттерн подстроки текста
    bool more(const string& pattern, int x) {
        for(int i = 0; i < pattern.size(); ++i) {
            if(x + i > textSize - 1) {
                return true;
            }
            if(pattern[i] == text[x + i]) continue;
            if(pattern[i] > text[x + i]) {
                return true;
            }
            return false;
        }
        return false;
    }
    //вспомогательный метод, который проверяет, меньше ли паттерн подстроки текста
    bool less(const string& pattern, int x) {
        return !(equal(pattern, x) || more(pattern, x));
    }
    //сам бинарный поиск
    int lowerBound(const string& pattern) {
        vector<int> ans;
        int l = 0, r = indexes.size() - 1;
        if(less(pattern, indexes[l]) || more(pattern, indexes[r])) {
            return -1;//паттерна нет в тексте
        }
        if(equal(pattern, indexes[l])) return l;//если первый же элемент в суфф массиве равен паттерну, то это и есть lower_bound
        int m;
        while(r - l > 1) {
            m = (r + l) / 2;
            if(more(pattern, indexes[m])) {
                l = m;
            } else {
                r = m;
            }
        }
        if(equal(pattern, indexes[r])) {
            return r;
        } else {
            return -1;
        }
    }
};


int main() {

    std::ifstream pat("patterns.txt");
    std::ofstream tex("text.txt");

    //считываю текст
    string text;
    tex<<text;

    auto start = std::chrono::high_resolution_clock::now();


    //строю суфф массив по тексту
    SuffixArray suffixArray(text);
   //на этом месте в коде суфф массив уже построено, идем дальше

    string pattern;
    int iteration = 0;
    //считываю паттерны в цикле
    while(pat>>pattern) {
        ++iteration;
        //запускаю бинарный поиск паттерна в суфф массиве, который возвращает самый первый индекс из суфф массива, в который входит паттерн, если такого нет, возвращает -1
        int l = suffixArray.lowerBound(pattern);
        if(l == -1) continue;
        set<int> ans;

        //бегу по суфф массиву и ищу последнее вхождение паттерна в суфф массив
        for(; l < suffixArray.textSize; ++l) {
            if(!suffixArray.equal(pattern, suffixArray.indexes[l])) break;
            ans.insert(suffixArray.indexes[l]);
        }
        cout<<iteration<<": ";
        //вывожу ответ для каждого паттерна
        for(auto iter = ans.begin(); iter != ans.end(); ++iter) {
            auto copy = iter;
            if(++copy == ans.end()) {
                cout<<*iter + 1;
                continue;
            }
            cout<<*iter + 1<<", ";
        }
        cout<<endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diference = end - start;
    std::cout << "Time taken for lenght 10000000: " << diference.count() << " seconds" << std::endl;
}