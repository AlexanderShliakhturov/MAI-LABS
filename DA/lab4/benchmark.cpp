#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <chrono>

std::vector<int> findall(std::string text, std::string pattern)
{
    std::vector<int> positions;
    int pos = text.find(pattern);

    while (pos != std::string::npos)
    {
        positions.push_back(pos);
        pos = text.find(pattern, pos + 1);
    }


    return positions;
}

int main()
{

    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string text;

    in >> text;
    // std::cout << text << std::endl;

    std::string pattern = "mynameisalexander";


    auto start = std::chrono::high_resolution_clock::now();


    std::vector<int> positions = findall(text, pattern);

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