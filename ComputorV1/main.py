import sys
import math

class Instruction:
    def __init__(self, val, powl):
        self.val = val
        self.powl = powl

class Expression:
    def __init__(self, instructions):
        self.instructions = instructions
        self.degree = self.get_polynomial_degree()

    def reduce_form(self):
        new_instructions = []
        for powl in range(self.degree + 1):
            val = 0
            for instruction in self.instructions:
                if instruction.powl == powl:
                    val += instruction.val
            new_instructions.append(Instruction(val, powl))
        self.instructions = new_instructions
        return self.instructions

    def get_polynomial_degree(self):
        max_powl = -1
        for instruction in self.instructions:
            if max_powl == -1 or max_powl < instruction.powl:
                max_powl = instruction.powl
        return max_powl

    def debug(self):
        for instruction in self.instructions:
            print(instruction.val, "* X^", instruction.powl)
        print("")

    def solve(self):
        self.reduce_form()
        if self.degree == 0:
            res = "All real are solutions for degree 0"
        elif self.degree == 1:
            res = self.solve_degree_1()
        elif self.degree == 2:
            res = self.solve_degree_2()
        else:
            res = "The polynomial degree is stricly greater than 2, I can't solve"
        self.print_res(res)

    def encode_form(self):
        estr = ""
        first_turn = True
        for instruction in self.instructions:
            if first_turn:
                first_turn = False
                estr += str(instruction.val) + " * X^" + str(instruction.powl)
            else:
                sign = "+" if instruction.val >= 0 else "-"
                val = str(abs(instruction.val))
                estr += " " + sign + " " + val + " * X^" + str(instruction.powl)
        return estr + " = 0"

    def print_res(self, res):
        res_str = "Reduced form: " + self.encode_form() + "\n"
        res_str += "Polynomial degree: " + str(self.degree) + "\n"
        res_str += res
        print(res_str)

    def solve_degree_1(self):
        a = self.instructions[1].val
        if a == 0:
            exit_error("a can't be equal to 0")
        b = self.instructions[0].val
        res = "The solution is:\n"
        res += str(float(b) * -1 / a)
        return res

    def solve_degree_2(self):
        a = self.instructions[2].val
        if a == 0:
            exit_error("a can't be equal to 0")
        b = self.instructions[1].val
        c = self.instructions[0].val
        delta = (b ** 2) - (4 * a * c)
        res = ""
        if delta < 0:
            res = "Discriminant is strictly equal, no solution"
        elif delta == 0:
            x0 = -1 * (float(b / (2 * a))
            res = "Discriminant is strictly equal, the only solution is:\n"
            res += str(x0)
        else:
            x1 = (b * -1 - math.sqrt(delta)) / (2 * a)
            x2 = (b * -1 + math.sqrt(delta)) / (2 * a)
            res = "Discriminant is strictly positive, the two solutions are:\n"
            res += str(x1) + "\n"
            res += str(x2)
        return res    
    
def exit_error(err):
    print(err)
    exit(1)

def format_val(val):
    return float(val) if "." in val else int(val) 

def format_powl( powl):
    return format_val(powl[2:])

def init_member(iarr, idx):
    sign_factor = 1
    if iarr[idx] == "-":
        sign_factor = -1
        idx += 1
    elif iarr[idx] == "+":
        idx += 1
    return sign_factor, idx

def main_solver(istr):
    # Parsing
    iarr = istr.split(" ")

    # Set up first sign factor
    idx = 0
    sign_factor, idx = init_member(iarr, idx)

    instructions = []
    left_or_right = 1

    # Start parsing loop
    while True:
        # Get A
        curr_val = iarr[idx]
        idx += 2

        # Get powl
        curr_powl = iarr[idx]
        idx += 1

        # Create instruction and put it in good member
        curr_instruction = Instruction(format_val(curr_val) * sign_factor * left_or_right, format_powl(curr_powl))
        instructions.append(curr_instruction)

        # Verif is end
        if idx >= len(iarr):
            break

        # Parse new + - =
        if iarr[idx] == "=":
            left_or_right = -1
            idx += 1
            sign_factor, idx = init_member(iarr, idx)
        else:
            sign_factor = 1 if iarr[idx] == "+" else -1
            idx += 1

    Expression(instructions).solve()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        exit_error("Error")

    istr = sys.argv[1]
    # D2 2solution
    # istr = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
    # D2 1solution
    istr = "1.125 * X^0 - 3 * X^1 + 2 * X^2 = 0"
    # D2 0solution
    # istr = "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
    
    # D1
    # istr = "5 * X^0 + 4 * X^1 = 4 * X^0"
    # D0
    # istr = "42 * X^0 = 42 * X^0"
    # D3
    # istr = "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"
    main_solver(istr)

'''
    Premier degree gerer error
    Gerer 42 * X0 = 42 * X0 -> 0*X0
'''