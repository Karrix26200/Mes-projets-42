# What is n-puzzle ?
This is a 15-puzzle game like but the target grid is snail.

# How I solve it ?
You can choose 3 algoeithms to resolve n-puzzle.
A*: Use step + heuristic function * constant_factor to choose a node in the graph -> f(n) = g(n) + h(n) * c
GBFS: Use only heuristic function to choose a node in the graph -> f(n) = h(n)
UCS: Use only step to choose a node in the graph -> f(n) = g(n)

f(n) = Evaluation function
g(n) = Step of node in the graph
h(n) = Heuristic score of node in the graph

# How get score of node in graph ?
For get a node score, we sum all node elem score.
For get an elem score, we choose one of these heuristics functions:
1. Manhattan distance -> return abs(node_elem.x - target_elem.x) + abs(node_elem.y - target_elem.y)
2. Euclidian distance -> return √( (node_elem.x - target_elem.x)² + (node_elem.y - target_elem.y)² )
3. Binary -> return !(node_elem.x == target_elem.x && node_elem.y == target_elem.y)

# Why use a constant factor "c" ?
This is usefull for configure A* objective.
The greater the "c", the faster is the algorithm for found a solution.
The lower the "c", the better is the solution (in step)

If "c" is negative the algorithm will test all node wich is the more farest from the target and end with the best nodes (it's useless lol)

# How to run it
```
usage: main.py [-h] [-sa SEARCH_ALGORITHM] [-hr HEURISTIC]
               [-hcf HEURISTIC_CONSTANT_FACTOR]

optional arguments:
  -h, --help            show this help message and exit
  -sa SEARCH_ALGORITHM, --search_algorithm SEARCH_ALGORITHM
                        Search algorithm to use (A*, GBFS, UCS)
  -hr HEURISTIC, --heuristic HEURISTIC
                        Heuristic function to use (Manhattan, Euclidian,
                        Binary)
  -hcf HEURISTIC_CONSTANT_FACTOR, --heuristic_constant_factor HEURISTIC_CONSTANT_FACTOR
                        Heuristic constant factor to use (default = 4),
                        usefull only for A*
                        
Exemple:
./res_npuzzle-gen.py 4 -s | ./main.py -sa A* -hr Manhattan -hcf 5
./res_npuzzle-gen.py 4 -s | ./main.py -sa GBFS -hr Euclidian
./res_npuzzle-gen.py 4 -s | ./main.py -sa UCS
```

# What does it look like
![Exemple](https://raw.githubusercontent.com/tdautreme/My_projects_at_42/master/npuzzle/img/output_screen.png)
