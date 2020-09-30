import math

def math_count(mylist):
    a = 0
    for i in mylist:
        a += 1
    return a

def math_mean(mylist):
    total = 0
    for i in mylist:
        total += i
    return total / math_count(mylist)

def math_min(mylist):
    best = None
    for i in mylist:
        if best is None or i < best:
            best = i
    return best

def math_max(mylist):
    best = None
    for i in mylist:
        if best is None or i > best:
            best = i
    return best

def math_percentile(mylist, percent):
    return sorted(mylist)[int(math_count(mylist) * percent)]

'''
C'est la racine carré de la moyenne de la somme des distances des nombres par rapport à la moyenne
En gros c'est la moyenne des distances de la moyenne
'''
def math_std(mylist, mean=None):
    total = 0
    if mean is None:
        mean = math_mean(mylist)
    for nbr in mylist:
        total += (nbr - mean)**2
    return math.sqrt(total / math_count(mylist))

def math_min_max_scaling(mylist, v_min=None, v_max=None):
    if v_min is None:
        v_min = math_min(mylist)
    if v_max is None:
        v_max = math_max(mylist)
    vrange = v_max - v_min
    for i in range(len(mylist)):
        mylist[i] = (mylist[i] - v_min) / vrange
    return mylist, v_min, v_max

def math_standardize(mylist, v_min = None, v_max = None, n_mean = None, std = None):
    if type(mylist) is not list:
        mylist = [mylist]
    n_mylist, v_min, v_max = math_min_max_scaling(mylist, v_min, v_max)
    if n_mean is None:
        n_mean = math_mean(n_mylist)
    if std is None:
        std = math_std(n_mylist, n_mean)
    for i in range(len(n_mylist)):
        n_mylist[i] = (n_mylist[i] - n_mean) / std
    return n_mylist, v_min, v_max, n_mean, std