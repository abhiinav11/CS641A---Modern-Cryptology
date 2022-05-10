#include <bits/stdc++.h>
#include "functions.cpp"

// Using the fact that A is lower triangular matrix

using namespace std;

int main() 
{
	ifstream fin("gen-outp.txt");
    vector<pair<int, int>> Adj[8];

    string inp[8][128];

    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 128; j++)
            fin >> inp[i][j];
        for (int value = 0; value < 128; value++)
        {
            for (int e = 1; e <= 126; e++)
            {
                bool OK = 1;
                for (int j = 1; j < 128; j++)
                {
                    string s = inp[i][j];
                    bits7 result = convt(s[2 * i], s[2 * i + 1]);
                    bits7 expec = mult(value, power(j, e));
                    expec = mult(value, power(expec, e));
                    expec = power(expec, e);
                    OK &= (result == expec);
                    if (!OK)
                        break;
                }
                if (OK)
                    Adj[i].push_back({value, e});
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        cout << "For i = " << i + 1 << ": ";
        for (auto [a, e] : Adj[i])
        {
            cout << "(" << a << ", " << e << ") ; ";
        }
        cout << endl;
    }
	
	return 0 ;
}