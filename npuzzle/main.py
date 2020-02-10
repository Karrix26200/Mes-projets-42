#!/usr/bin/env python3

# Extern import
import sys
sys.path.insert(1, './src')

# Intern import (utils)
from utils import *
from datastruct import *

# Intern import (algo)
from param_parsing import *
from file_parsing import *
from target_node import *
from score import *
from solve import *
from print_result import *

'''
g(n) aussi depend de "c" car si c'est c qui change, la proportion change aussi
A* BFS = f(n) = g(n) + h(n) * c
    * solution plus ou moins bonne (depend de c)
    * plus ou moins rapide (depend de c) 
GBFS = f(n) = h(n)
    - trouve pas forcement la meilleur solution
    + rapide
UCS = f(n) = g(n)
    + trouve la meilleur solution en terme de step
    - max lent

g(x) est le facteur optimal, c'est plus lent mais ca donne des meilleurs resultats
h(x) est le facteur de rapidité mais dans le cas d'un GBFS, le resultat est aleatoire
'''

if __name__ == "__main__":
    clear_screen()
    # Param parsing
    constant_factor, step_is_score, heuristic_is_score = parse_param()

    # File parsing
    size, first_nmap, first_voidpos = parse_file()
    print_success("Map parsed successfully")
    print('\n'.join(get_res_list(first_nmap)) + '\n')

    # Target elem and target pos
    target_nmap, target_pos_list = get_target_nmap(size)
    print_success("Target generated successfully")
    print('\n'.join(get_res_list(target_nmap)))

    # Check if solvable
    if not is_solvable(first_nmap, size, first_voidpos):
        exit_error("Map is not solvable")

    # Creating first elem
    first_score = get_h_score_first(first_nmap, size, target_nmap, target_pos_list)
    if first_score == -1:
        exit_error("map already solved")

    # Reference first elem and target in database
    first_elem = reference_in_bdd(None, first_nmap, first_voidpos)
    first_elem.h_score = first_score
    first_elem.best_step = 0

    target_elem = reference_in_bdd(None, target_nmap, target_pos_list[0])
    target_elem.best_step = -1

    # Start solving
    print('')
    solve(first_elem, size, target_pos_list, step_is_score, heuristic_is_score, constant_factor)