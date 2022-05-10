a, A1 = 429, 431955503618234519808008749742
b, A2 = 1973, 176325509039323911968355873643
c, A3 = 7596, 98486971404861992487294722613
p = 455470209427676832372575348833

g1 = (A2 * pow(A1,p-2,p)) % p # g^1973 * g^(-429) = g^1544
g2 = (A3 * pow(A2,p-2,p)) % p # g^7576 * g^(-1973) = g^5623
x = 1544 # 1973 - 429
y = 5623 # 7596 - 1973

while (x != 1): # when x == 1, we have found 'g' (modified Extended Euclidean Algorithm)
    z = y//x # to what power should g1 be raised
    r = g1
    g1 = pow(g1,z,p) # g1 ^ z mod p
    g1 = (g2 * pow(g1,p-2,p)) % p # g2 * g1^(-1)
    g2 = r
    t = x # storing x for replacing with y
    x = y-z*x # updating power for next loop
    y = t # assigning y to previous value of x
print(g1)

g_429 = pow(g1,429,p) # g^429
g_429_inv = pow(g_429,p-2,p) # g^(-429)
password = (A1 * g_429_inv) % p # multiplying g^(-429) on both sides to get password
print(password)