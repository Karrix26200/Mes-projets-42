from utils import *
from datastruct import *
from score import *

def parse_file():
    need_size = True
    size = False
    nmap = []
    for line in sys.stdin:
        if line[0] == "#": pass
        elif need_size:
            try:
                size = int(line)
                need_size = False
            except:
                exit_error("mapsize must be a number")
        else:
            line = ' '.join(line.split())
            nmap.append(line.split(' '))
    if size <= 2:
        exit_error("map size must be greater than 2")
    
    nmap, first_voidpos = verify_nmap(size, nmap)
    return size, nmap, first_voidpos


def verify_nmap(size, nmap):
    valid_test = [False] * (size * size)
    first_voidpos = None

    if len(nmap) != size:
        exit_error("nmap size is not correct")
    for y in range(len(nmap)):
        if len(nmap[y]) != size:
            exit_error("nmap size is not correct")
        for x in range(len(nmap[y])):
            try:
                nmap[y][x] = int(nmap[y][x])
            except:
                exit_error("map element must be number")
            if nmap[y][x] < 0 or nmap[y][x] >= len(valid_test):
                exit_error("number must be between 0 and size^2")
            elif valid_test[nmap[y][x]] == True:
                exit_error("number already exist")
            valid_test[nmap[y][x]] = True

            if nmap[y][x] == 0:
                first_voidpos = V2(y, x)

    return nmap, first_voidpos

'''
Pour verifier si un Jeu est solvable, on applique les regles de:
https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
Mais ca ne suffit pas car on fonctionne avec un snail.
Ducoup j'ai mis sur papier toutes les size où l'algo ne fonctionne pas et j'ai trouvé un pattern d'inversion
La repartition des solvables est celle-ci pour chaque size:

IDX_PACK = 0
    need_reverse 3
    work 4
    need_reverse 5 6

IDX_PACK = 1
    work 7
    need_reverse 8
    work 9 10

IDX_PACK = 2
    need_reverse 11
    work 12
    need_reverse 13 14
etc ...

Donc on utilise d'abord % 4 pour verifier si = 1, ou = autre (0, 2, 3)
Puis on divise en pack de 4 et on applique la parité de l'indice du pack
'''

def is_solvable(nmap, size, first_voidpos):
    parity = is_solvable_ctr(nmap, size, first_voidpos)

    tst_s = size - 3
    # On check si c'est == 1 donc si c'est au "milieu" du pack de 4, sinon False
    first_bool = tst_s % 4 == 1

    # On recuperer la parité de l'indice du pack de 4
    # pour inverser le first bool si besoin
    second_bool = int(tst_s / 4) % 2 == 0

    if second_bool:
        first_bool = not first_bool

    # On inverse la parité par rapport a tout ce qu'on a fait
    if first_bool:
        parity = not parity

    return parity

def is_solvable_ctr(nmap, size, first_voidpos):
    nmap_1D = []
    for line in nmap:
        nmap_1D += line
    nmap_inv_count = get_inv_count(nmap_1D, size)
    if size % 2 != 0 and nmap_inv_count % 2 == 0:
        return True
    elif size % 2 == 0:
        pos_from_bottom = size - first_voidpos.y
        return pos_from_bottom % 2 != nmap_inv_count % 2
    return False

def get_inv_count(nmap_1D, size):
    size_2 = size * size
    inv_count = 0
    for y in range(size_2 - 1):
        for x in range(y + 1, size_2):
            if nmap_1D[x] != 0 and nmap_1D[y] != 0 and nmap_1D[y] > nmap_1D[x]:
                inv_count += 1
    return inv_count