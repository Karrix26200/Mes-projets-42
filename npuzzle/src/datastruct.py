from utils import *
import time

class MapTree():
    def __init__(self, val, arr):
        # Val est egal au int de la map
        self.val = val
        # Arr est la suite de l'arbre sauf si c'est la fin, alors = Node
        self.arr = arr

class Node():
    def __init__(self, nmap, step, score, voidpos):
        self.nmap = nmap
        self.voidpos = voidpos
        self.h_score = score
        self.best_step = step
        self.nboor = []

    def try_add_nboor(self, test_nboor):
        if not test_nboor in self.nboor:
            self.nboor.append(test_nboor)

class Stats():
    def __init__(self):
        self.clone_found = 0
        self.clone_useless = 0
        self.clone_better = 0
        self.new_found = 0
        self.start_time = time.time()

    def get_elapsed_time(self):
        return int(time.time() - self.start_time)