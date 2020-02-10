import sys
from utils import *
import math

def he_fnc_manhattan(current_pos, target_pos):
    return abs(current_pos.x - target_pos.x) + abs(current_pos.y - target_pos.y)  

def he_fnc_euclidian(current_pos, target_pos):
    return math.sqrt(pow(current_pos.x - target_pos.x, 2) + pow(current_pos.y - target_pos.y, 2))

def he_fnc_binary(current_pos, target_pos):
    return 0 if current_pos.x == target_pos.x and current_pos.y == target_pos.y else 1

heuristic_fnc = None
heuristic_fnc_list = {
    "Manhattan": he_fnc_manhattan,
    "Euclidian": he_fnc_euclidian,
    "Binary": he_fnc_binary
}

step_is_score = False
heuristic_is_score = False

def set_eval_fnc(search_algorithm, heuristic):
    global heuristic_is_score
    global heuristic_fnc
    global step_is_score

    if search_algorithm in ["A*", "UCS"]:
        step_is_score = True
    if heuristic != None and search_algorithm != "UCS":
        heuristic_is_score = True
        heuristic_fnc = heuristic_fnc_list[heuristic]    
    return step_is_score, heuristic_is_score


def get_score_of_elem(nmap, cur_pos, target_pos_list):
    index = nmap[cur_pos.y][cur_pos.x]
    tar_pos = target_pos_list[index]
    return heuristic_fnc(cur_pos, tar_pos)

def use_heuristic(elem, new_nmap, new_voidpos, target_pos_list):
    vpos1_dist = get_score_of_elem(elem.nmap, elem.voidpos, target_pos_list)
    vpos2_dist = get_score_of_elem(new_nmap, new_voidpos, target_pos_list)
    vpos_res = vpos1_dist - vpos2_dist

    tpos1_dist = get_score_of_elem(elem.nmap, new_voidpos, target_pos_list)
    tpos2_dist = get_score_of_elem(new_nmap, elem.voidpos, target_pos_list)
    tpos_res = tpos1_dist - tpos2_dist

    return elem.h_score - (vpos_res + tpos_res)

def get_h_score_opti(elem, new_nmap, new_voidpos, target_pos_list):
    return use_heuristic(elem, new_nmap, new_voidpos, target_pos_list) if heuristic_is_score else 0

def get_h_score_first(nmap, size, target_nmap, target_pos_list):
    if not heuristic_is_score:
        return 0

    heuristics_score = 0

    cur_pos = V2(0, 0)
    elem_arrived = 0

    for y in range(len(nmap)):
        for x in range(len(nmap[y])):
            if nmap[y][x] == target_nmap[y][x]:
                elem_arrived += 1
            if heuristic_is_score:
                cur_pos.y = y
                cur_pos.x = x
                heuristics_score += get_score_of_elem(nmap, cur_pos, target_pos_list)

    if elem_arrived == size * size:
        return -1

    return heuristics_score