from contextlib import nullcontext
import random
import itertools

# Expressions
def sort(output):
    tokenCollection = []
    negated = []
    tokenIndex = 0
    new = []

    negated.append("")
    tokenCollection.append("")

    negatedIndex = 0
    outputIndex = 0
    for ele in output:
        if ele == '+':
            tokenCollection.append("+")
            tokenIndex +=1
            tokenCollection.append("")
            tokenIndex +=1
            
            negated.append("")
            negatedIndex += 1
        elif ele == '!':
            if outputIndex != len(output) -1:
                negated[negatedIndex] += output[outputIndex+1]
        else:
            tokenCollection[tokenIndex] += ele
        outputIndex += 1

    #print(tokenCollection)
    #print(negated)


    i = 0
    for token in tokenCollection:
        for ele in sorted(token):
            if ele == negated[i]:
                new.append("!")
            new.append(ele)
        if token != '+':
            i += 1
    #print(new)
    return new

def checkerino(list, variables):
    # there wil not be two negations of the same char present    
    #print(list)
    for i in range(0, len(list)):
        if(list[i] == '!' and i != len(list) and i != 0):
            i+= 1
        if(list[i] == '+'):
            previous = list[i+1]
        if (i == 0):
            previous = list[i]
        elif(ord(previous) > ord(list[i]) and list[i] != '+'):
            return 1
        else:
            previous = list[i]
        i += 1

    for searched in variables:
        for i in range(0, len(list) - 3):
            if list[i] == '!':
                if list[i+1] == searched:
                    if list[i+2] == '!':
                        if list[i+3] == searched:
                            return 1    

    return 0

def listToString(list, variables): 
    outputString = "" 
    outputArray = []

    for ele in list: 
        outputArray.append(ele)

    if checkerino(outputArray, variables):
        return "null"

    for ele in outputArray: 
        outputString += ele  

    return outputString 

def checkUsage(output, variables):
    # are all chars used from variables ?
    checker = []
    
    for i in variables:
        checker.append('0')

    for x in output:
        for y in variables:
            if x == y:
                checker[variables.index(y)] = '1'
                break
    
    for i in range(0, len(variables)):
        if checker[i] == '0':
            return 1
    return 0    

def polish(output, variables):
    # repeat this function until check is 1
    while output[0] == '+':
        output.pop(0)

    while output[-1] == '+' or output[-1] == '!':
        output.pop(-1)
    
    toRemove = 0
    for j in range(0, len(variables)):
        flag = 1

        while flag :
            flag = 0
            for i in range(0, len(output) - 1):
                # make sure that the are not duplicate chars or a combination of "+!" or "!+"
                if ((output[i] == variables[j]) and (output[i+1] == variables[j])) or ((output[i] == '!') and (output[i+1] == '+')) or ((output[i] == '+') and (output[i+1] == '!')):
                    output[i] = '0'
                    flag  = 1
                    toRemove += 1

    for f in range(0, toRemove):
        output.remove('0')
    
    if toRemove == 0:
        return 0
    else:
        return 1

def generate(variables):
    output = []
    previousIndex = 0
    curIndex = 0
    while(checkUsage(output, variables)):
        while (previousIndex == curIndex):
            curIndex = random.randint(0, len(variables)-1)
        
        previousIndex = curIndex
        output.append(variables[curIndex])

    output = sort(output)
    check = 1
    while(check):
        check = polish(output, variables)
    
    return listToString(output,variables)

def expression(size, tests, file):
    f = open(file, "w")
    
    variables = ['+', '!']

    for x in range(0, size):
        variables.append(chr(65+x))
        
    for x in range(0, tests):
        expression = "null"
        while expression == "null":
            expression = generate(variables)
        
        print(expression, file = f)
        #print(expression)
    
    f.close()

# Vector
def listToS(s): 
    str1 = "" 
    for ele in s: 
        str1 += ele  
    return str1 

def vector(size, file):
    f = open(file, "w")

    lst = list(itertools.product(["0", "1"], repeat=size))

    for ele in lst:
        output = listToS(ele)
        #print(output)
        print(output, file = f)

    f.close()    

def main():
    print("5000 Random Boolean Expressions\n>>Generating 13")
    expression(13, 5000, "13_expression.txt")
    vector(13, "13_vector.txt")
    
    print(">>Generating 15")
    expression(15, 5000, "15_expression.txt")
    vector(15, "15_vector.txt")

    print(">>Generating 20")
    expression(20, 5000, "20_expression.txt")
    vector(20, "20_vector.txt")
    
    print("done")

main()