import datetime
import shutil

class V2():
    def __init__(self, y, x):
        self.y = y
        self.x = x

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    BACK_OKBLUE = '\033[104m'
    OKGREEN = '\033[92m'
    BACK_OKGREEN = '\033[102m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    UNDERLINE_STOP = '\033[24m'

def c_datetime():
    now = datetime.datetime.now()
    return str(now.year) + "/" + str(now.month).zfill(2) + "/" + str(now.day).zfill(2) + " - " + str(now.hour).zfill(2) + ":" + str(now.minute).zfill(2) + ":" + str(now.second).zfill(2)

def print_global(message, color = ""):
    nowtime = c_datetime()
    print(bcolors.OKBLUE + '[' + nowtime + '] ' + bcolors.ENDC + color + str(message) + bcolors.ENDC)

def print_success(message): print_global(message, bcolors.OKGREEN)
def print_warning(message): print_global(message, bcolors.WARNING)
def print_error(message): print_global(message, bcolors.FAIL)

def exit_error(message):
    print_error(message)
    exit(1)

def print_2D(array):
    print('\n'.join([''.join(['{:4}'.format(item) for item in row]) 
      for row in array]))

def print_V2(array):
    strr = ""
    for a in array:
        strr += str(a.y) + ":" + str(a.x) + ", "
    print(strr)

def clear_screen():
    collumns, rows = shutil.get_terminal_size((80, 20))
    print ("\n" * rows)

def c_udln(message):
    return bcolors.UNDERLINE + str(message) + bcolors.UNDERLINE_STOP

def c_green(message):
    return bcolors.OKGREEN + str(message) + bcolors.ENDC

def c_red(message):
    return bcolors.FAIL + str(message) + bcolors.ENDC

def c_blue(message):
    return bcolors.OKBLUE + str(message) + bcolors.ENDC

def c_yel(message):
    return bcolors.WARNING + str(message) + bcolors.ENDC