from random import *

def additionTests(x):
    input = open("add_inputs.txt","w")
    output = open("add_result.txt","w")
    min = -2**400
    max = 2**400
    for i in range(0,x):
        a = randint(min,max)
        b = randint(min,max)
        r = a + b
        input.write(f"{hex(a)}\n{hex(b)}\n")
        if(r>=0):
            r =  "0x"+ hex(r)[2:].upper()
        else:
            r = "-0x"+ hex(r)[3:].upper()
        output.write((f"{r}\n"))

def subTests(x):
    input = open("sub_inputs.txt","w")
    output = open("sub_result.txt","w")
    min = -2**400
    max = 2**400
    for i in range(0,x):
        a = randint(min,max)
        b = randint(min,max)
        r = a - b
        input.write(f"{hex(a)}\n{hex(b)}\n")
        if(r>=0):
            r =  "0x"+ hex(r)[2:].upper()
        else:
            r = "-0x"+ hex(r)[3:].upper()
        output.write((f"{r}\n"))

def mulTest(x):
    input = open("mul_inputs.txt","w")
    output = open("mul_result.txt","w")
    min = -2**40
    max = 2**40
    for i in range(0,x):
        a = randint(min,max)
        b = randint(min,max)
        r = a * b
        input.write(f"{hex(a)}\n{hex(b)}\n")
        if(r>=0):
            r =  "0x"+ hex(r)[2:].upper()
        else:
            r = "-0x"+ hex(r)[3:].upper()
        output.write((f"{r}\n"))

additionTests(5000)
subTests(5000)
mulTest(1000)