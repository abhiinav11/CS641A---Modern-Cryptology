#include <bits/stdc++.h>
using namespace std;

// This code will be used to analyze the encoding

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random_gen(int a, int b)
{
    uniform_int_distribution<int> uid(a, b);
    return uid(rng);
}

void get_inp()
{
    ofstream fout("test-inp.txt");

    int L = 1000;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int k = random_gen(0, 7);
            fout << char('f' + k);
            k = random_gen(0, 15);
            fout << char('f' + k);
        }
        fout << endl;
    }
}

void get_outp()
{
    ifstream fin("test-inp.txt");
    ofstream fout("commands.txt");

    fout << "Cryptophilic" << endl;
    fout << "team3" << endl;
    fout << 5 << endl;

    fout << "go" << endl;
    fout << "wave" << endl;
    fout << "dive" << endl;
    fout << "go" << endl;
    fout << "read" << endl;

    string s;
    while (fin >> s)
    {
        fout << s << endl;
        fout << 'c' << endl;
    }

    fout << "back" << endl;
    fout << "exit" << endl;

    fout.close();
    fin.close();

    system("ssh students@172.27.26.188 < commands.txt > out");
    system("grep --no-group-separator -A 1 \"Slowly, a new text starts appearing on the screen. It reads ...\" out | grep --no-group-separator -v \"Slowly, a new text starts appearing on the screen. It reads ...\" | tr -d \"\\t\" > test-outp.txt");
    system("rm -rf out commands.txt");
}

void analyze_enc()
{
    ifstream fin("test-outp.txt");
    vector<int> count(26);

    string s;
    fin >> s;
    while (fin >> s)
    {
        for (char c : s)
            count[c - 'a']++;
    }

    for (int i = 0; i < 26; i++)
    {
        cout << char('a' + i) << ' ' << count[i] << endl;
    }
    cout << endl;
}

int main()
{
    get_inp();
    get_outp();
    analyze_enc();

    return 0;
}
