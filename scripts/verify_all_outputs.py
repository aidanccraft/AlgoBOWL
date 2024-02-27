import os
from subprocess import run


INPUT_DIR = "../realInputs/"
OUTPUT_DIR = "../realOutputs/"


if not os.path.exists(INPUT_DIR):
    print("Error: input directory does not exist")
    exit()

if not os.path.exists(OUTPUT_DIR):
    print("Error: output directory does not exist")
    exit()

# loop through every file in input dir
for file in os.listdir(INPUT_DIR):

    inPath = os.path.join(INPUT_DIR, file)
    outPath = os.path.join(OUTPUT_DIR, file)

    # only interested in files that end with .txt
    if os.path.isdir(inPath):
        continue
    if len(inPath) < 5 or inPath[-4:] != ".txt":
        continue

    # execute
    run(f"../verify_output.exe {inPath} {outPath}".split())
