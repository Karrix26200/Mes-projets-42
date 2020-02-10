import shutil

def cursor_move (y, x):
    print("\033[%d;%dH" % (y, x))

def print_list_from_bottom(lst):
    collumns, rows = shutil.get_terminal_size((80, 20))
    start_y = rows - len(lst) - 1
    for line in lst:
        cursor_move(start_y, 0)
        print(' ' * collumns)
        cursor_move(start_y, 0)
        print(line)
        start_y += 1
    