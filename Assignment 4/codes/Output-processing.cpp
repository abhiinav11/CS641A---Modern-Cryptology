#include <bits/stdc++.h>

using namespace std;

using bits64 = bitset<64>;
using bits32 = bitset<32>;
using bits48 = bitset<48>;
using bits56 = bitset<56>;
using bits28 = bitset<28>;

int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

int IP_inv[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

bits64 apply_ip(bits64 in, bool inv = false)
{
    bits64 out;
    for (int i = 63; i >= 0; i--)
    {
        int j = (inv ? IP_inv[63 - i] : IP[63 - i]) - 1;
        out[i] = in[63 - j];
    }
    return out;
}

pair<bits32, bits32> get_LR(bits64 in)
{
    bits32 L, R;
    for (int i = 63, j = 31; i >= 32; i--, j--)
    {
        L[j] = in[i];
        R[j] = in[i - 32];
    }
    return make_pair(L, R);
}
bits64 join(bits32 L, bits32 R)
{
    bits64 out;
    for (int i = 31; i >= 0; i--)
    {
        out[i + 32] = L[i];
        out[i] = R[i];
    }
    return out;
}

int main()
{

    ifstream fin("gen_outputs.txt");
    ofstream fout("gen_out_bits.txt");

    string s;
    while (fin >> s)
    {
        assert((int)s.length() == 16);
        bits64 bits = 0;
        for (int i = 0; i < 16; i++)
        {
            char c = s[i];
            int num = c - 'd';
            assert(num < 16 and num >= 0);
            bits = (bits << 4) | bits64(num);
        }
        bits64 actual = apply_ip(bits);
        auto [R, L] = get_LR(actual);

        fout << L << R << endl;
    }

    return 0;
}