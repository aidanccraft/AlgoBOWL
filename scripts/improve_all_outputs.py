import os
from subprocess import run


INPUT_DIR = "../realInputs/"
OUTPUT_DIR = "../bestOutputs/"
NEW_OUTPUT_DIR = "../realOutputs3/"


if not os.path.exists(INPUT_DIR):
    print("Error: input directory does not exist")
    exit()

if not os.path.exists(OUTPUT_DIR):
    print("Error: input directory does not exist")
    exit()

if not os.path.exists(NEW_OUTPUT_DIR):
    os.mkdir(NEW_OUTPUT_DIR)

# loop through every file in input dir
for file in os.listdir(INPUT_DIR):

    inPath = os.path.join(INPUT_DIR, file)
    outPath = os.path.join(OUTPUT_DIR, file)
    newOutPath = os.path.join(NEW_OUTPUT_DIR, file)

    # do not overwrite existing solutions
    if os.path.exists(newOutPath):
        print(f"output '{newOutPath}' already exists, skipping...")
        continue

    # only interested in files that end with .txt
    if os.path.isdir(inPath):
        continue
    if len(inPath) < 5 or inPath[-4:] != ".txt":
        continue

    # execute
    print(file)
    run(f"../improve_output.exe {inPath} {outPath} {newOutPath}".split())
