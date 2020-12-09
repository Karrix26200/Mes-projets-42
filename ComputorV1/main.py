#!/usr/bin/env python3

import sys
import math

class Instruction:
    def __init__(self, val, powl):
        self.val = val
        if type(powl) is float:
            exit_error("pow must be int")
        self.powl = powl

class Expression:
    def __init__(self, instructions):
        self.instructions = instructions
        self._degree = None

    @property
    def degree(self):
        if self._degree is None:
            self._degree = self.get_polynomial_degree()
        return self._degree

    def reduce_form(self):
        new_instructions = []
        tmp_degree = self.get_polynomial_degree()
        for powl in range(tmp_degree + 1):
            val = 0
            for instruction in self.instructions:
                if instruction.powl == powl:
                    val = round(val + instruction.val, 5)
            new_instructions.append(Instruction(val, powl))
        # Remove instruction with 0 * pow
        new_instructions[:] = [x for x in new_instructions if x.val != 0]
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
        if self.degree == -1:
            self._degree = 0
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
        if estr == "":
            estr = "0x"
        return estr + " = 0"

    def print_res(self, res):
        res_str = "Reduced form: " + self.encode_form() + "\n"
        res_str += "Polynomial degree: " + str(self.degree) + "\n"
        res_str += res
        print(res_str)

    def solve_degree_1(self):
        a = self.search_instruction(1)
        if a == 0:
            exit_error("a can't be equal to 0")
        b = self.search_instruction(0)
        res = "The solution is:\n"
        res += str(b * -1 / a)
        return res

    def solve_degree_2(self):
        a = self.search_instruction(2)
        if a == 0:
            exit_error("a can't be equal to 0")
        b = self.search_instruction(1)
        c = self.search_instruction(0)
        delta = (b ** 2) - (4 * a * c)
        res = ""
        if delta < 0:
            delta_sqrt = math.sqrt(abs(delta))
            diviseur = 2 * a
            left = (b * -1) / diviseur
            right = delta_sqrt / diviseur
            res += "Discriminant is strictly negative, the two solutions using complex are:\n"
            x1_op = "+"
            x2_op = "-"
            if right < 0:
                right = abs(right)
                x1_op = "-"
                x2_op = "+"
            x1_str = x1_op + " " + str(right) + " i"
            x2_str = x2_op + " " + str(right) + " i"
            if left != 0:
                x1_str = str(left) + " " + x1_str
                x2_str = str(left) + " " + x2_str
            res += x1_str + "\n"
            res += x2_str
        elif delta == 0:
            x0 = -1 * (b / (2 * a))
            res += "Discriminant is strictly equal, the only solution is:\n"
            res += str(x0)
        else:
            x1 = (b * -1 - math.sqrt(delta)) / (2 * a)
            x2 = (b * -1 + math.sqrt(delta)) / (2 * a)
            res += "Discriminant is strictly positive, the two solutions are:\n"
            res += str(x1) + "\n"
            res += str(x2)
        return res

    def search_instruction(self, powl):
        for instruction in self.instructions:
            if instruction.powl == powl:
                return float(instruction.val)
        return float(0)
    
def exit_error(err):
    print("Error:", err)
    exit(1)

def format_val(val):
    if val in "-+=*X^":
        exit_error("Bad char")
    return round(float(val), 5) if "." in val else int(val) 

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

def parse_instructions_2(istr):
    # Set all char to uppercase
    istr = istr.upper()

    # Remove all spaces
    istr = istr.replace(" ", "")

    # Split into 2 member
    members = istr.split("=")
    instructions_left = parse_member(members[0])
    tmp_instructions_right = parse_member(members[1])

    instructions_right = []
    for instruction in tmp_instructions_right:
        instruction.val = instruction.val * -1
        instructions_right.append(instruction)
    
    instructions = instructions_left + instructions_right
    return instructions

def parse_member(member):
    instructions = []

    # Get idx of - or + bot preceded by ^
    if member[0] not in ["+", "-"]:
        member = "+" + member
    idx_lst = []
    for i in range(len(member)):
        if member[i] in ["-", "+"] and (i == 0 or member[i-1] != "^"):
            idx_lst.append(i)

    # Use idx list to create sub member and process them
    for i in range(len(idx_lst)):
        if i != len(idx_lst) - 1:
            part = member[idx_lst[i]:idx_lst[i+1]]
        else:
            part = member[idx_lst[i]:len(member)]

        part = part.split("*")
        powl = 0
        val = 1
        for p in part:
            if "X^" in p:
                p = p.replace("X^", "")
                powl = format_val(p)
            else:
                val = format_val(p)
        instructions.append(Instruction(val, powl))
    return instructions

def main_solver(istr):
    instructions = parse_instructions_2(istr)
    expression = Expression(instructions)
    expression.solve()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        exit_error("Error empty input")
    istr = sys.argv[1]
    main_solver(istr)