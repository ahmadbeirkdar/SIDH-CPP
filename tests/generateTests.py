from random import *

def additionTests(x):
    input = open("add_inputs.txt","w")
    output = open("add_result.txt","w")
    min = 2**25
    max = 2**400
    for i in range(0,x):
        a = randint(min,max)
        b = randint(min,max)
        r = a + b
        input.write(f"{hex(a)}\n{hex(b)}\n")
        output.write((f"0x{hex(r)[2:].upper()}\n"))

additionTests(5000)