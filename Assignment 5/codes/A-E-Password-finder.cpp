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
	
	vector<int> E(8);
    vector<vector<int>> A(8, vector<int>(8));

    for (int i = 1; i < 8; i++)
    {
        for (auto [a_11, e_1] : Adj[i - 1])
        {
            for (auto [a_22, e_2] : Adj[i])
            {
                for (int value = 0; value < 128; value++)
                {
                    bool OK = 1;
                    for (int j = 1; j < 128; j++)
                    {
                        string s = inp[i - 1][j];
                        bits7 foo = power(add(mult(value, power(mult(a_11, power(j, e_1)), e_1)), mult(a_22, power(mult(value, power(j, e_1)), e_2))), e_2);
                        bits7 go = convt(s[2 * i], s[2 * i + 1]);
                        OK &= (foo == go);
                    }
                    if (OK)
                    {
                        A[i - 1][i - 1] = a_11;
                        A[i][i] = a_22;
                        E[i - 1] = e_1;
                        E[i] = e_2;
                        A[i][i - 1] = value;
                    }
                }
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = i - 2; j >= 0; j--)
        {
            for (int value = 0; value < 128; value++)
            {
                A[i][j] = value;
                bool OK = 1;
                for (int x = 1; x < 128; x++)
                {
                    bits7 foo = 0;
                    for (int k = j; k <= i; k++)
                    {
                        foo = add(foo, mult(A[i][k], power(mult(A[k][j], power(x, E[j])), E[k])));
                    }
                    foo = power(foo, E[i]);
                    bits7 go = convt(inp[j][x][2 * i], inp[j][x][2 * i + 1]);
                    OK &= (foo == go);
                }
                if (OK)
                {
                    break;
                }
            }
        }
    }
	cout << endl;
	cout << "Matrix A : " << endl;
	cout << endl;
	
	for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(j!=7) cout << A[i][j] << " ";
	    else cout << A[i][j] << endl;
        }
    }

	cout << "\nE : [";
    for (int i = 0; i < 8;i++){
        cout << E[i] << " ]\n"[i == 7];
    }
	
	cout << endl;
	cout << endl;
	cout << "Password : ";
	
	string password = "gsiiipillogpftijmomkfqmrfqmmmhfk";
    for (int i = 0; i < 2; i++)
    {
        bits7 out[8];
        for (int j = 16 * i; j < 16 * i + 16; j += 2)
        {
            out[(j - 16 * i) / 2] = convt(password[j], password[j + 1]);
        }
        bits7 x[8];
        for (int r = 0; r < 8; r++)
        {
            for (int value = 0; value < 128; value++)
            {
                bits7 xx[8];
                for (int k = 0; k < 8; k++)
                    xx[k] = x[k];
                x[r] = value;
                for (int _ = 0; _ < 2; _++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        x[j] = power(x[j], E[j]);
                    }
                    bits7 y[8];
                    for (int j = 0; j < 8; j++)
                    {
                        y[j] = 0;
                        for (int k = 0; k < 8; k++)
                        {
                            y[j] = add(y[j], mult(A[j][k], x[k]));
                        }
                    }
                    for (int j = 0; j < 8; j++)
                    {
                        x[j] = y[j];
                    }
                }
                for (int j = 0; j < 8; j++)
                {
                    x[j] = power(x[j], E[j]);
                }
                bool ok = 1;
                for (int j = 0; j <= r; j++)
                {
                    ok &= (x[j] == out[j]);
                }
                for (int j = 0; j < 8; j++)
                {
                    x[j] = xx[j];
                }
                if (ok)
                {
                    x[r] = value;
                    break;
                }
            }
            cout << char(x[r].to_ullong());
        }
    }
	cout << endl;
	
	return 0 ;
}