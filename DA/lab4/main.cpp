#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

std::vector<int> z_func(const std::string& s) {
    int l = 0, r = 0, n = s.size();
    std::vector<int> z(n, 0);
    z[0] = n;

    for (int i = 1; i < n; ++i) {
        // Случай 1) i больше чем правая граница.
        if (i >= r) {
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
            l = i;
            r = i + z[i];

        // 2) i внутри левой и правой границ
        } else {
            // Подслучай 2.1) значение ранее вычисленной z-функции меньше чем путь от i до r
            if (i + z[i - l] < r) {
                z[i] = z[i - l];
            
            // Подслучай 2.2) значение ранее вычисленной z-функции больше или равно чем путь от i до r
            } else {
                z[i] = r - i;
                while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
                l = i;
                r = i + z[i];
                
            }
        }
    }
    return z;
}



int main() {

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    std::string text;
    std::string pattern = "mynameisalexander"; 
    in >> text;
    // std::cin >> pattern;
    std::vector<int> positions;

    auto start = std::chrono::high_resolution_clock::now();
    
    std::string all = pattern + "$" + text;
    std::vector<int> Z = z_func(all);
  
    int patternlen = pattern.length();
    int textlen = text.length();
    
    for (int i = 0; i < textlen; ++i) {
        if (Z[patternlen + 1 + i] == patternlen) {
            // out << i << std::endl;
            positions.push_back(i);
        }
    }       

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diference = end - start;
    std::cout << "Time taken for finding all patterns in 10^8 elems: " << diference.count() << " seconds" << std::endl;

    for (auto pos : positions)
    {
        out << pos << std::endl;
    }

     for (auto pos : positions)
    {
        std::cout << pos << std::endl;
    }

    return 0;
}  