hash = [23, 96, 15, 32, 27, 65, 66, 98, 15, 58, 1, 59, 107, 39, 8, 54, 78, 27, 70, 53, 48, 90, 70, 101, 126, 118, 124, 26, 96, 64, 61, 88]
password = ''


def compute_e():
    e = [1]
    for k in range(1, hash[0]+1):
        tmp = 0
        for i in range(1, k+1):
            tmp += pow(-1, i-1) * e[k-i] * hash[i]
        tmp *= pow(k, 125, 127)
        tmp %= 127
        e.append(tmp)
    #print(e)
    return e


def update_hash(root):
    for k in range(len(hash)):
        tmp = hash[k]
        tmp -= pow(root, k, 127)
        tmp %= 127
        hash[k] = tmp
    #print(hash)


def is_root(val, e):
    poly = 0
    for k in range(hash[0]+1):
        poly += pow(-1, k) * e[k] * pow(val, hash[0] - k, 127)
        poly %= 127
    if poly == 0:
        return True
    return False


char = 'f'
while len(password) < 23:
    e = compute_e()
    if is_root(ord(char), e):
        password += char
        update_hash(ord(char))
    else:
        char = chr(ord(char) + 1)

print(f"Password : {password}")