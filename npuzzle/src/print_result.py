from cursor import *
from utils import *

color_range = 150
color_padding = (255 - color_range)

def get_max_number_len(nmap):
    biggest = 0
    for line in nmap:
        for char in line:
            test_len = len(str(char))
            if test_len > biggest:
                biggest = test_len
    return biggest

def get_color_escape(r, g, b, background=False):
    return '\033[{};2;{};{};{}m'.format(48 if background else 38, r, g, b)

def get_color(nbr, max_nbr):
    clr = int(color_range / max_nbr * nbr) + color_padding
    return get_color_escape(clr, 0, 0, True)

def get_res_list(nmap):
    str_list = []
    max_number_len = get_max_number_len(nmap)
    format_str = '{:' + str(max_number_len) + '}'
    color_max = pow(len(nmap), 2) 
    for line in nmap:
        line_str = ""
        for char in line:
            if char == 0:
                line_str += bcolors.BACK_OKGREEN + format_str.format(" ") + " " + bcolors.ENDC
            else:
                line_str += get_color(char, color_max) + format_str.format(char) + " " + bcolors.ENDC 
        str_list.append(line_str)
    return str_list

def print_result(nmap, step, max_step, flush = True):
    str_list = get_res_list(nmap)

    str_list.append("Step: " + c_blue(step) + " / " + c_green(max_step))
    if flush:
        print_list_from_bottom(str_list)
    else:
        print('\n'.join(str_list))