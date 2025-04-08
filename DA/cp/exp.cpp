#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#include <algorithm>
#include <fstream>

using namespace std;
const int POWER_ALPH  = 256;



bool start() {
        //вектор, который нужен для сортировки подсчетом символов в тексте
        vector<int> helper(POWER_ALPH, 0);
        //вектор индексов
        vector<int> ind(textSize, 0);
        //вектор класса эквивалентности
        vector<int> ec(textSize, 0);

        //--------------------
        //в этих циклах я заполняю вектор helper, чтобы потом использовать его в сортировке подсчетом индексов
        for(char c : text) {
            ++helper[c - lowerSymbol];
        }
        // префикс сумма
        for(int i = 1; i < POWER_ALPH; ++i) {
            helper[i] += helper[i-1];
        }
        //---------

       // заполняю вектор индексов, они будут посорчены по первому символу
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