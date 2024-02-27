import os

# folders to check:
INPUT_FOLDERS = ["testInputs","finalInput","realInputs"]
OUTPUT_FOLDERS = ["testOutputs"]



def checkInputFile(filepath:str):
    file = open(filepath, "r")
    edges = set()
    try:
        lines = [line.strip() for line in file.readlines() if line != ""]
        n = int(lines[0])
        if n < 2 or n > 10**4: return "n is out of bounds"
        if len(lines) != n+1: return "invalid number of lines in file"
        for i in range(1,n+1):
            line = list(map(int, lines[i].split()))
            m = line[0]
            if m < 0 or m > n-1: return f"m is out of bounds on line {i+1}"
            if len(line) != m+1: return f"invalid number of edges on line {i+1}"
            for x in line[1:]:
                if x == i: return f"self edge on line {i+1}"
                if x < 1 or x > n: return f"out of bounds edge on line {i+1}"
                if (i,x) in edges: return f"duplicate edge on line {i+1}"
                edges.add((i,x))
    except:
        return "invalid file formatting"
    finally:
        file.close()
    if len(edges) > 10**5: return "too many edges"
    return ""

def checkOutputFile(filepath:str):
    file = open(filepath, "r")
    try:
        lines = [line.strip() for line in file.readlines() if line != ""]
        n = int(lines[0])
        if n == 0:
            if len(lines) != 1: return "invalid number of lines in file"
        else:
            if len(lines) != 2: return "invalid number of lines in file"
            removed = list(map(int, lines[1].split()))
            if len(removed) != n: return "invalid amount of removed vertices"
            if len(removed) != len(set(removed)): return "duplate vertices"
    except:
        return "invalid file formatting"
    finally:
        file.close()
    return ""


# check input folders
for folder in INPUT_FOLDERS:
    for file in os.listdir(folder):
        filepath = os.path.join(folder, file)

        # only check .txt files
        if not os.path.isfile(filepath): continue
        if len(filepath) < 4 or filepath[-4:] != ".txt": continue

        if result := checkInputFile(filepath):
            print(f"input file '{filepath}' failed:  {result}")

# check output folders
for folder in OUTPUT_FOLDERS:
    for file in os.listdir(folder):
        filepath = os.path.join(folder, file)

        # only check .txt files
        if not os.path.isfile(filepath): continue
        if len(filepath) < 4 or filepath[-4:] != ".txt": continue

        if result := checkOutputFile(filepath):
            print(f"input file '{filepath}' failed:  {result}")