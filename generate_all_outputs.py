import os
from subprocess import run


INPUT_DIR = "./realInputs/"
OUTPUT_DIR = "./realOutputs/"


if not os.path.exists(INPUT_DIR):
    print("Error: input directory does not exist")
    exit()

if not os.path.exists(OUTPUT_DIR):
    os.mkdir(OUTPUT_DIR)

# loop through every file in input dir
for file in os.listdir(INPUT_DIR):

    inPath = os.path.join(INPUT_DIR, file)
    outPath = os.path.join(OUTPUT_DIR, file)

    # do not overwrite existing solutions
    if os.path.exists(outPath):
        print(f"output '{outPath}' already exists, skipping...")
        continue

    # only interested in files that end with .txt
    if os.path.isdir(inPath): continue
    if len(inPath) < 5 or inPath[-4:] != ".txt": continue

    # execute
    run(f"./generate_output {inPath} {outPath}".split())
