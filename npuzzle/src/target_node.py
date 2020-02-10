from datastruct import *
from utils import *

def set_target_info(target_nmap, target_pos, y, x, cnt):
    target_nmap[y][x] = cnt
    target_pos[cnt].y = y
    target_pos[cnt].x = x

def get_target_nmap(size):
    target_nmap = [[0 for x in range(size)] for y in range(size)]
    target_pos = [V2(0, 0) for i in range(size * size)]

    x = 0
    y = 0
    cnt = 1
    cnt_bu = -1
    while cnt != cnt_bu:
        cnt_bu = cnt
        while x < size - 1 and target_nmap[y][x + 1] == 0:
            set_target_info(target_nmap, target_pos, y, x, cnt)
            cnt += 1
            x += 1
        while y < size - 1 and target_nmap[y + 1][x] == 0:
            set_target_info(target_nmap, target_pos, y, x, cnt)
            cnt += 1
            y += 1
        while x > 0 and target_nmap[y][x - 1] == 0:
            set_target_info(target_nmap, target_pos, y, x, cnt)
            cnt += 1
            x -= 1
        while y > 0 and target_nmap[y - 1][x] == 0:
            set_target_info(target_nmap, target_pos, y, x, cnt)
            cnt += 1
            y -= 1
    target_pos[0].y = y
    target_pos[0].x = x
    return target_nmap, target_pos