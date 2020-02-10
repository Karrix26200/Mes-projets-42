from score import *
from datastruct import *
from cursor import *
from print_result import *

nmap_tree = []
stats = Stats()
queue = []

time_between_info_print = 1
last_time_info = 0

time_between_result_frame = 0.25

def result_found(end_child):
    cur_child = end_child
    end_array = []
    while cur_child.best_step != 0:
        end_array.append(cur_child)
        best_nboor = None
        for nboor in cur_child.nboor:
            if best_nboor == None or nboor.best_step < best_nboor.best_step:
                best_nboor = nboor
        cur_child = best_nboor
    end_array.append(cur_child)
    end_array.reverse()
    total_step = 0
    for elem in end_array:
        print_result(elem.nmap, total_step, end_child.best_step, total_step > 0)
        total_step += 1
        time.sleep(time_between_result_frame)
    exit(0)

def update_chained_step(elem):
    for i in range(len(elem.nboor)):
        if elem.nboor[i] != elem and elem.nboor[i].best_step > elem.best_step + 1:
            elem.nboor[i].best_step = elem.best_step + 1
            update_chained_step(elem.nboor[i])

def add_nboor_to(elem, child):
    if not child in elem.nboor:
        elem.nboor.append(child)
    if not elem in child.nboor:
        child.nboor.append(elem)

def ref_child_add(elem, new_nmap, new_voidpos):
    if elem != None:        
        new_step = elem.best_step + 1
        new_score = get_h_score_opti(elem, new_nmap, new_voidpos, target_pos_list)
    else:
        new_step = 0
        new_score = 0

    new_elem = Node(new_nmap, new_step, new_score, new_voidpos)
    
    if elem != None:
        add_nboor_to(elem, new_elem)
    return new_elem


def reference_in_bdd(elem, nmap, new_voidpos):
    global nmap_tree
    global queue

    nmap_tree_cur = nmap_tree
    nmap_tree_last = None
    
    for line in nmap:
        for char in line:
            found = False
            for i in range(len(nmap_tree_cur)):
                if nmap_tree_cur[i].val == char:
                    if not isinstance(nmap_tree_cur[i].arr, list): # IF IS ELEM (Clone or result ?)
                        cur_elem = nmap_tree_cur[i].arr
                        if cur_elem.best_step != -1: # End 2: It's clone
                            stats.clone_found += 1
                            if elem.best_step + 1 < cur_elem.best_step: # End 2.5: Clone but better path
                                stats.clone_better += 1
                                cur_elem.best_step = elem.best_step + 1
                                add_nboor_to(cur_elem, elem)
                                update_chained_step(cur_elem)
                            else:
                                stats.clone_useless += 1
                            return None
                        # End 3: End found
                        cur_elem.best_step = elem.best_step + 1
                        add_nboor_to(cur_elem, elem)
                        print_info(cur_elem, len(queue))
                        result_found(cur_elem)

                    found = True
                    nmap_tree_cur = nmap_tree_cur[i].arr
                    break
            if not found:
                nmap_tree_cur.append(MapTree(char, []))
                nmap_tree_last = nmap_tree_cur
                nmap_tree_cur = nmap_tree_cur[-1].arr
    
    if not found: # End 1: Elem not found, let's create it
        stats.new_found += 1
        nmap_tree_last[-1].arr = ref_child_add(elem, nmap, new_voidpos)
        return nmap_tree_last[-1].arr

def get_new_nmap(elem, new_y, new_x):
    new_nmap = [row[:] for row in elem.nmap]

    old = new_nmap[new_y][new_x]
    new_nmap[new_y][new_x] = 0
    new_nmap[elem.voidpos.y][elem.voidpos.x] = old
    return new_nmap

def create_child_for(elem, target_y, target_x):
    new_y = elem.voidpos.y + target_y
    new_x = elem.voidpos.x + target_x
    if new_x < 0 or new_y < 0 or new_x >= size or new_y >= size:
        return None
    
    new_voidpos = V2(new_y, new_x)
    new_nmap = get_new_nmap(elem, new_y, new_x)
    return reference_in_bdd(elem, new_nmap, new_voidpos)

def create_childs(elem): # Return childs if not clone
    childs = []

    child = create_child_for(elem, 1, 0)
    if child != None: childs.append(child)

    child = create_child_for(elem, -1, 0)
    if child != None: childs.append(child)

    child = create_child_for(elem, 0, 1)
    if child != None: childs.append(child)

    child = create_child_for(elem, 0, -1)
    if child != None: childs.append(child)

    return childs


def get_score(elem):
    global heuristic_is_score
    global step_is_score
    return (elem.h_score * constant_factor if heuristic_is_score else 0) + (elem.best_step if step_is_score else 0)

def insert_childs(childs, queue):
    queue.extend(childs)
    queue = sorted(queue, key=lambda elem: get_score(elem))
    return queue

def best_step_elem(queue):
    fscore = get_score(queue[0])
    best_step = queue[0].best_step
    best_idx = 0
    for i in range(len(queue)):
        if get_score(queue[i]) != fscore:
            break
        if queue[i].best_step < best_step:
            best_step = queue[i].best_step
            best_idx = i
    return best_idx
            
def set_global(g_size, g_target_pos_list, g_step_is_score, g_heuristic_is_score, g_constant_factor):
    global size
    global target_pos_list
    global step_is_score
    global heuristic_is_score
    global formula
    global constant_factor

    size = g_size
    target_pos_list = g_target_pos_list
    step_is_score = g_step_is_score
    heuristic_is_score = g_heuristic_is_score
    constant_factor = g_constant_factor

    formula = c_green("f(n)") + " = "
    if step_is_score:
        formula += c_yel("g(n)") + (" + " if heuristic_is_score else "")
    if heuristic_is_score:
        formula += c_blue("h(x)") + " * " + c_red("c")

def print_info(elem, queue_length):
    global constant_factor
    str_list = []
    str_list.append("Current best node:")
    str_list.append("   Total score " + formula + " = " + c_green(get_score(elem)))
    str_list.append("       Step score = " + c_yel(elem.best_step))
    str_list.append("       Heuristic score  = " + c_blue(elem.h_score))
    str_list.append("       Constant factor = " + c_red(constant_factor))
    str_list.append("")
    str_list.append("Complexity statistics:")
    str_list.append("   Complexity in time (Tested nodes) = " + c_yel(stats.clone_found + stats.new_found))
    str_list.append("   Complexity in size (Queue length + Tree length) = " + c_blue(queue_length + stats.new_found))
    str_list.append("")
    str_list.append("More statistics:")
    str_list.append("   Clone found = " + c_blue(stats.clone_found))
    str_list.append("       Useless clone = " + c_red(stats.clone_useless))
    str_list.append("       Better clone = " + c_green(stats.clone_better))
    str_list.append("   New found = " + c_green(stats.new_found))
    str_list.append("   Second elapsed = " + c_yel(stats.get_elapsed_time()))
    if elem.best_step == 0:
        print('\n'.join(str_list))
    else:
        print_list_from_bottom(str_list)

def can_i_print_verbose(elem, queue_length):
    global last_time_info
    global time_between_info_print
    
    if last_time_info < time.time() - time_between_info_print:
        last_time_info = time.time()
        print_info(elem, queue_length)


def solve(begin, g_size, g_target_pos_list, g_step_is_score, g_heuristic_is_score, g_constant_factor):
    global queue
    set_global(g_size, g_target_pos_list, g_step_is_score, g_heuristic_is_score, g_constant_factor)

    # Queue est une liste de node du graph trié du potentiellement meilleur définit par l'algo de recherche
    # La on insert le premier node dans la queue sachant que c'est cette fonction qui trie
    queue = insert_childs([begin], queue)
    while True:        
        # La on recupere tous les nodes qui ont exactement le meme meilleur resultat et on recupere l'index de celui qui a le moins de step pour un meilleur resultat
        idx = best_step_elem(queue)
        # On recupere le node avec l'indice
        elem = queue[idx]
        # Affichage graphique
        can_i_print_verbose(elem, len(queue))
        # La on déploit les nodes (4 max, 1 par coté), et, si c'est pas des nodes deja vue (clone), on les recuperes
        # Si le child target est trouvé, le programme se termine
        childs = create_childs(elem)
        # On supprime le node parent des childs puisqu'on vient de le traiter
        del queue[idx]
        # Et on injecte les childs qu'on vient de découvrir dans la queue
        queue = insert_childs(childs, queue)
