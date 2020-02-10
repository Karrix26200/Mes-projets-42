import argparse
from utils import *
from score import *

search_algorithm_list = ["A*", "GBFS", "UCS"]
heuristic_list = ["Manhattan", "Euclidian", "Binary"]
conf = {}

def parse_param():
    parser = argparse.ArgumentParser()
    parser.add_argument("-sa", "--search_algorithm", help="Search algorithm to use (" + ', '.join(search_algorithm_list) + ")", type=str)
    parser.add_argument("-hr", "--heuristic", help="Heuristic function to use (" + ', '.join(heuristic_list) + ")", type=str)
    parser.add_argument("-hcf", "--heuristic_constant_factor", help="Heuristic constant factor to use (default = 4), usefull only for A*", type=float)
    args = parser.parse_args()
    error_msg = ""
    if args.search_algorithm == None or not args.search_algorithm in search_algorithm_list:
        error_msg += "-sa or --search_algorithm parameter is required or not valid. Use it like this:\n"
        for sa in search_algorithm_list: error_msg += "  ./main.py -sa " + sa + "\n" 
    elif args.search_algorithm != "UCS" and (args.heuristic == None or not args.heuristic in heuristic_list):
        error_msg += "-hr or --heuristic parameter is required for A* or GBFS or is not valid. Use it like this:\n"
        for hr in heuristic_list: error_msg += "  ./main.py -sa " + args.search_algorithm + " -hr " + hr + "\n" 

    if args.heuristic_constant_factor != None:
        constant_factor = args.heuristic_constant_factor
    else:
        constant_factor = 4

    if error_msg != "":
        exit_error(error_msg)

    step_is_score, heuristic_is_score = set_eval_fnc(args.search_algorithm, args.heuristic)
    return constant_factor, step_is_score, heuristic_is_score
    