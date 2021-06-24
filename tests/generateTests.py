from random import *

def additionTests(x):
    input = open("add_inputs.txt","w")
    output = open("add_result.txt","w")
    min = -2**4000
    max = 2**4000
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
    min = -2**4000
    max = 2**4000
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
    min = -2**400
    max = 2**400
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

def compareTest(x: int) ->  None:
    input = open("compare_inputs.txt","w")
    output = open("compare_result.txt","w")

    min = -2**400
    max = 2**400

    for i in range(0,x):
        a = randint(min,max)
        b = randint(min,max)
        r = 1 if bool(a > b) == True else 0

        input.write(f"{hex(a)}\n{hex(b)}\n")
        output.write((f"{r}\n"))

additionTests(5000)
subTests(5000)
mulTest(5000)
compareTest(5000)