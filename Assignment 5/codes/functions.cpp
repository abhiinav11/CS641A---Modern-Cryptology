#include <bits/stdc++.h>
using namespace std;

using bits7 = bitset<7>;
using bits13 = bitset<13>;

#define endl '\n'

bits13 mod = bits13("10000011");

bits7 add(bits7 x, bits7 y)
{
    x ^= y;
    return x;
}

bits7 rem(bits13 x)
{
    for (int i = 12; i >= 7; i--)
    {
        if (x[i] != 0)
        {
            x ^= (mod << (i - 7));
        }
    }

    for (int i = 12; i >= 7; i--)
    {
        assert(x[i] == 0);
    }

    bits7 answer;
    for (int i = 0; i < 7; i++)
        answer[i] = x[i];

    return answer;
}

bits7 mult(bits7 x, bits7 y)
{
    bits13 result;
    result.reset();
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (x[i] == 1 and y[j] == 1)
                result[i + j] = result[i + j] ^ 1;
        }
    }
    return rem(result);
}

bits7 power(bits7 a, int n)
{
    bits7 result = 1;
    while (n)
    {
        if (n & 1)
            result = mult(result, a);
        n >>= 1;
        a = mult(a, a);
    }
    return result;
}

bits7 convt(char a, char b)
{
    int foo = ((a - 'f') << 4) + (b - 'f');
    assert(foo < 128);
    bits7 result = foo;
    return result;
}