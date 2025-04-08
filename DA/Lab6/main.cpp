#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void make_array(vector<vector<long long>> &array, int n, int m)
{
    for (int i = n - 2; i >= 0; --i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (j == 0)
            {
                array[i][j] += min(array[i + 1][j], array[i + 1][j + 1]);
            }
            else if (j == m - 1)
            {
                array[i][j] += min(array[i + 1][j - 1], array[i + 1][j]);
            }
            else
            {
                array[i][j] += min({array[i + 1][j - 1], array[i + 1][j], array[i + 1][j + 1]});
            }
        }
    }
}

void find_path(const vector<vector<long long>> &array, int n, int m, int start_col)
{
    int j = start_col;
    for (int i = 0; i < n - 1; ++i)
    {
        cout << "(" << i + 1 << "," << j + 1 << ") ";
        if (j == 0)
        {
            long long x = min(array[i + 1][j], array[i + 1][j + 1]);
            if (x == array[i + 1][j + 1])
            {
                j++;
            }
        }
        else if (j == m - 1)
        {
            long long x = min(array[i + 1][j - 1], array[i + 1][j]);
            if (x == array[i + 1][j - 1])
            {
                j--;
            }
        }
        else
        {
            long long x = min({array[i + 1][j - 1], array[i + 1][j], array[i + 1][j + 1]});
            if (x == array[i + 1][j - 1])
            {
                j--;
            }
            else if (x == array[i + 1][j + 1])
            {
                j++;
            }
        }
    }
    cout << "(" << n << "," << j + 1 << ")\n";
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> data(n, vector<long long>(m));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> data[i][j];
        }
    }

    make_array(data, n, m);

    long long minimum = data[0][0];
    int start_col = 0;
    for (int i = 1; i < m; ++i)
    {
        if (data[0][i] <= minimum)
        {
            minimum = data[0][i];
            start_col = i;
        }
    }

    cout << minimum << "\n";

    find_path(data, n, m, start_col);

    return 0;
}
