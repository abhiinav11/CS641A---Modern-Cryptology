def coppersmith(poly, modulus, beta, mm, tt, XX):
    
    dd = poly.degree()
    nn = dd * mm + tt

    polyZ = poly.change_ring(ZZ)
    x = polyZ.parent().gen()

    # compute the polynomials
    gg = []
    for ii in range(mm):
        for jj in range(dd):
            gg.append((x * XX)**jj * modulus**(mm - ii) * polyZ(x * XX)**ii)
    for ii in range(tt):
        gg.append((x * XX)**ii * polyZ(x * XX)**mm)

    # construct the lattice B
    BB = Matrix(ZZ, nn)

    for ii in range(nn):
        for jj in range(ii+1):
            BB[ii, jj] = gg[ii][jj]

    # LLL algorithm
    BB = BB.LLL()

    # transform shortest vector in the polynomial
    new_poly = 0
    for ii in range(nn):
        new_poly += x**ii * BB[0, ii] / XX**ii

    # factor polynomial
    possible_roots = new_poly.roots()
    
    # test roots
    roots = []
    for root in possible_roots:
        if root[0].is_integer():
            result = polyZ(ZZ(root[0]))
            if gcd(modulus, result) >= modulus^beta:
                roots.append(ZZ(root[0]))

    return roots

#RSA parameters given in the final window
e = 5
N = 84364443735725034864402554533826279174703893439763343343863260342756678609216895093779263028809246505955647572176682669445270008816481771701417554768871285020442403001649254405058303439906229201909599348669565697534331652019516409514800265887388539283381053937433496994442146419682027649079704982600857517093
C = 105426173168126061170093885614354470624494488749910697994176430527345639240318192017922875824873215503356935865081463349044100998022540123663471728053438523002630164119597236285455020717065407679108886724000823081927257944679621965245890218519919623471547332646512280232788220540094538823473219746567541532

padding = "Cryptophilic: This door has RSA encryption with exponent 5 and the password is "

#maximum length
message_length = 200

ZmodN = Zmod(N);

binary_padding = ''.join(['{0:08b}'.format(ord(x)) for x in padding])

for LENGTH in range(0, message_length+1, 4):          # size of the root

    # Problem to equation (default)
    P.<M> = PolynomialRing(Zmod(N) ,implementation='NTL')
    poly = ((int(binary_padding, 2)<<LENGTH) + M)^e - C
    dd = poly.degree()

    beta = 1                                
    epsilon = beta / 7                      
    mm = ceil(beta**2 / (dd * epsilon))     
    tt = floor(dd * mm * ((1/beta) - 1))    
    XX = ceil(N**((beta**2/dd) - epsilon))  

    roots = coppersmith(poly, N, beta, mm, tt, XX)

    if roots:
        m = roots[0]
        print("m is : ", m)
        m_binary = format(m,'b').zfill(LENGTH)
        message = ""
        for i in range(0, len(m_binary)//8):
            s = 8*i
            e = s + 8
            num_bin = m_binary[s:e]
            d = int(num_bin, base=2)
            message += chr(d)
        print("Size of m is : ", LENGTH)
        print("Password is : ", message, sep = '')
        break
        
    elif LENGTH == message_length:
        print("No Solution")