#include <iostream>
#include <fstream>
#include <chrono>
#include <map>


int main()
{

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::map<std::string, unsigned long long> dict;

    std::ifstream in("test.txt");
    std::ofstream out("output.txt");

    int n = 100000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        std::string key;
        in >> key;
        unsigned long long value;
        in >> value;
        dict.insert({key, value});
        out << "OK" << "\n";
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diference = end - start;
    std::cout << "Time taken for inserting of " << n << " elems in std::map: " << diference.count() << " seconds" << std::endl;

    auto start1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        std::string key;
        in >> key;
        out << dict.count(key) << "\n";
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diference1 = end1 - start1;
    std::cout << "Time taken for checking of " << n << " elems in std::map: " << diference1.count() << " seconds" << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++)
    {
        std::string key;
        in >> key;
        dict.erase(key);
        out << "OK" << "\n";
    }

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diference2 = end2 - start2;
    std::cout << "Time taken for removing of " << n << " elems in std::map: " << diference2.count() << " seconds" << std::endl;

    return 0;
}