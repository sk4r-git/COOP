#on part d'un gros tableau de bytes qui doit representer la heap 

from pwn import *

#io = process("v2_s")
target = ELF("v2_s")
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")

#to change during the exploit
libc_base = 0x7f7fffffffff
code_base = 0x555555555555
heap_base = 0x565555555555


# getters setters dans le tableau
def get_64(tab, i):
    s = 0
    s += tab[i + 7] << 56
    s += tab[i + 6] << 48
    s += tab[i + 5] << 40
    s += tab[i + 4] << 32
    s += tab[i + 3] << 24
    s += tab[i + 2] << 16
    s += tab[i + 1] << 8
    s += tab[i] 
    return s

def get_32(tab, i):
    s = 0
    s += tab[i + 3] << 24
    s += tab[i + 2] << 16
    s += tab[i + 1] << 8
    s += tab[i]
    return s

def get_16(tab, i):
    s = 0
    s += tab[i + 1] << 8
    s += tab[i]
    return s

def get_8(tab, i):
    s = 0
    s += tab[i]
    return s

def set_64(tab, i, n):
    tab[i] = n % 0x100 
    n >>= 8
    tab[i + 1] = n % 0x100 
    n >>= 8
    tab[i + 2] = n % 0x100 
    n >>= 8
    tab[i + 3] = n % 0x100 
    n >>= 8
    tab[i + 4] = n % 0x100 
    n >>= 8
    tab[i + 5] = n % 0x100 
    n >>= 8
    tab[i + 6] = n % 0x100 
    n >>= 8
    tab[i + 7] = n % 0x100 
    return tab

def set_32(tab, i, n):
    tab[i] = n % 0x100 
    n >>= 8
    tab[i + 1] = n % 0x100 
    n >>= 8
    tab[i + 2] = n % 0x100 
    n >>= 8
    tab[i + 3] = n % 0x100 
    return tab

def set_16(tab, i, n):
    tab[i] = n % 0x100 
    n >>= 8
    tab[i + 1] = n % 0x100 
    return tab

def set_8(tab, i, n):
    tab[i] = n % 0x100 
    return tab

# getters des symbols
def get_libc(symbol):
    add = next(libc.search(symbol))
    add += libc_base
    return add

def get_code(symbol):
    add = next(target.search(symbol))
    add += code_base
    return add

#print de toutes les manières possibles
def hex_print(tab):
    print("[", end="")
    for i in range(len(tab)-1):
        print(hex(tab[i]), end="")
        print(", ", end="")
    print (hex(tab[len(tab) - 1]), end="")
    print("]")

def hex_print_64(tab):
    print("[", end="")
    for i in range(0, len(tab)-1, 8):
        to_print = get_64(tab, i)
        print(hex(to_print), end="")
        print(", ", end="")
    to_print = get_64(tab, len(tab) - 8)
    print (hex(to_print), end="")
    print("]")

# traductions des vf gadgets en 'effets sur la heap'
def exam_update_abs(tab, i):
    sA = get_64(tab, i+8)
    sB = get_64(tab, i+16)
    sC = get_64(tab, i+24)
    tab = set_64(tab, i+40, sA + sB)
    tab = set_64(tab, i+48, sA + sC)
    return tab

def ss_set(tab, i):
    puts_ad = get_libc(b'puts')
    tab = set_64(tab, i+24, puts_ad)
    tab = set_64(tab, i+8, puts_ad)
    return tab


test1 = []
for i in range(4000):
    test1.append(0)



hex_print_64(test1)
test1 = exam_update_abs(test1, 0)
test1 = ss_set(test1, 48)
print()
hex_print_64(test1)