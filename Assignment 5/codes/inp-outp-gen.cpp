#include <bits/stdc++.h>
#include "functions.cpp"

using namespace std;

void gen_inp()
{
    ofstream fout("gen-inp.txt");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 128; j++)
        {
            for (int r = 0; r < 8; r++)
            {
                if (r != i)
                    fout << "ff";
                else
                {
                    fout << char('f' + (j >> 4));
                    fout << char('f' + (j & 15));
                }
            }
            fout << endl;
        }
    }
}

void gen_outp()
{
    ifstream fin("gen-inp.txt");
    ofstream fout("commands2.txt");

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

    system("ssh students@172.27.26.188 < commands2.txt > out");
    system("grep --no-group-separator -A 1 \"Slowly, a new text starts appearing on the screen. It reads ...\" out | grep --no-group-separator -v \"Slowly, a new text starts appearing on the screen. It reads ...\" | tr -d \"\\t\" > gen-outp.txt");
    system("rm -rf out commands2.txt");
}

int main() 
{
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

    gen_inp();
    gen_outp();
	
	return 0 ;
}