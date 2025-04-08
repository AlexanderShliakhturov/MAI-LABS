#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include <chrono>

using namespace std;

class SuffixArray {
public:
    string text;        
    int textSize;       
    vector<int> indexes; 
    vector<int> EC;    
    int step;          
    static const int POWER_ALPH = 256; 
    static const char lowerSymbol = 0; 

    SuffixArray(const string& str) {
        text = str + "$"; 
        textSize = text.size();
        indexes.resize(textSize);
        EC.resize(textSize);
        step = 1;
        build();
    }

private:
    bool start() {
        vector<int> helper(POWER_ALPH, 0);
        vector<int> ind(textSize, 0);
        vector<int> ec(textSize, 0);

        for (char c : text) {
            ++helper[c - lowerSymbol];
        }
        for (int i = 1; i < POWER_ALPH; ++i) {
            helper[i] += helper[i - 1];
        }

        for (int i = textSize - 1; i >= 0; --i) {
            ind[--helper[text[i] - lowerSymbol]] = i;
        }

        ec[ind[0]] = 0;
        bool flag = true;
        for (int i = 1; i < textSize; ++i) {
            if (text[ind[i]] == text[ind[i - 1]]) {
                ec[ind[i]] = ec[ind[i - 1]];
                flag = false;
            } else {
                ec[ind[i]] = ec[ind[i - 1]] + 1;
            }
        }

        swap(ind, indexes);
        swap(ec, EC);
        return flag;
    }

    void build() {
        if (start())
            return;

        while (step < textSize) {
            vector<int> ind(textSize, 0);
            vector<int> ec(textSize, 0);

            for (int i = 0; i < textSize; ++i) {
                ind[i] = (indexes[i] - step + textSize) % textSize;
            }
            for (int i = 0; i < textSize; ++i) {
                ec[i] = EC[ind[i]];
            }

            vector<int> helper(textSize, 0);
            for (int i = 0; i < textSize; ++i) {
                ++helper[ec[i]];
            }
            for (int i = 1; i < textSize; ++i) {
                helper[i] += helper[i - 1];
            }

            vector<int> indHelper(textSize, 0);
            for (int i = textSize - 1; i >= 0; --i) {
                indHelper[--helper[ec[i]]] = ind[i];
            }

            vector<pair<int, int>> ecDoubleHelper(textSize, {0, 0});
            for (int i = 0; i < textSize; ++i) {
                ecDoubleHelper[i].first = EC[indHelper[i]];
                ecDoubleHelper[i].second = EC[(indHelper[i] + step) % textSize];
            }

            EC[indHelper[0]] = 0;
            bool flag = true;
            for (int i = 1; i < textSize; ++i) {
                if (ecDoubleHelper[i] == ecDoubleHelper[i - 1]) {
                    EC[indHelper[i]] = EC[indHelper[i - 1]];
                    flag = false;
                } else {
                    EC[indHelper[i]] = EC[indHelper[i - 1]] + 1;
                }
            }
            swap(indHelper, indexes);
            step *= 2;
            if (flag)
                return;
        }
    }
};

string BWT(const string& input) {
    SuffixArray suffixArray(input);
    const vector<int>& suffixIndexes = suffixArray.indexes;
    string bwtResult;

    for (int i = 0; i < suffixArray.textSize; ++i) {
        int suffixPos = suffixIndexes[i];
        bwtResult += (suffixPos == 0) ? suffixArray.text[suffixArray.textSize - 1]
                                      : suffixArray.text[suffixPos - 1];
    }

    return bwtResult;
}


vector<int> MTF(const string &text)
{
    vector<char> symbols(27);
    for (int i = 0; i < 26; ++i)
        symbols[i + 1] = 'a' + i;
    symbols[0] = '$';

    vector<int> result;
    for (char c : text)
    {
        auto it = find(symbols.begin(), symbols.end(), c);
        int index = distance(symbols.begin(), it);
        result.push_back(index);
        symbols.erase(it);
        symbols.insert(symbols.begin(), c);
    }
    return result;
}

vector<pair<int, int>> RLE(const vector<int> &codes)
{
    vector<pair<int, int>> result;
    int count = 1;
    for (size_t i = 1; i <= codes.size(); ++i)
    {
        if (i < codes.size() && codes[i] == codes[i - 1])
        {
            ++count;
        }
        else
        {
            result.emplace_back(count, codes[i - 1]);
            count = 1;
        }
    }
    return result;
}

vector<int> decodeRLE(const vector<pair<int, int>> &rle)
{
    vector<int> result;
    for (const auto &[count, value] : rle)
    {
        result.insert(result.end(), count, value);
    }
    return result;
}

string decodeMTF(const vector<int> &codes)
{
    vector<char> symbols(27);
    for (int i = 0; i < 26; ++i)
        symbols[i + 1] = 'a' + i;
    symbols[0] = '$';

    string result;
    for (int index : codes)
    {
        char c = symbols[index];
        result += c;
        symbols.erase(symbols.begin() + index);
        symbols.insert(symbols.begin(), c);
    }
    return result;
}

string inverseBWT(const string &bwt)
{
    size_t n = bwt.size();
    vector<pair<char, size_t>> table;
    for (size_t i = 0; i < n; ++i)
    {
        table.emplace_back(bwt[i], i);
    }
    sort(table.begin(), table.end());

    string result;
    size_t index = 0;
    for (size_t i = 0; i < n; ++i)
    {
        result += table[index].first;
        index = table[index].second;
    }

    if (!result.empty())
    {
        result = result.substr(1);
    }
    return result;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    auto start = std::chrono::high_resolution_clock::now();

    string command;
    input >> command;
    if (command == "compress")
    {
        string text;
        input >> text;

        string bwtResult = BWT(text);

        vector<int> mtfResult;
        mtfResult.reserve(bwtResult.size());
        mtfResult = MTF(bwtResult);

        vector<pair<int, int>> rleResult = RLE(mtfResult);

        for (const auto &[count, value] : rleResult)
        {
            output << count << " " << value << '\n';
        }
    }
    else if (command == "decompress")
    {
        vector<pair<int, int>> rle;

        int count, value;
        size_t totalElements = 0;

        while (input >> count >> value)
        {
            rle.emplace_back(count, value);
            totalElements += count;
        }

        vector<int> mtfCodes;
        mtfCodes.reserve(totalElements);

        mtfCodes = decodeRLE(rle);

        string bwtResult = decodeMTF(mtfCodes);
        string text = inverseBWT(bwtResult);

        output << text << '\n';
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diference = end - start;
    std::cout << "Time taken for lenght 1000: " << diference.count() << " seconds" << std::endl;

    return 0;
}