import os
from subprocess import run


INPUT_DIR = "../realInputs/"
OUTPUT_DIR = "../realOutputs2/"

ids = [734, 749, 756, 758, 768, 781, 783, 784, 795, 797]


if not os.path.exists(INPUT_DIR):
    print("Error: input directory does not exist")
    exit()

if not os.path.exists(OUTPUT_DIR):
    os.mkdir(OUTPUT_DIR)

# loop through every file in input dir
for id in ids:
    file = "input_group" + str(id) + ".txt"

    inPath = os.path.join(INPUT_DIR, file)
    outPath = os.path.join(OUTPUT_DIR, file)

    # do not overwrite existing solutions
    if os.path.exists(outPath):
        print(f"output '{outPath}' already exists, skipping...")
        continue

    # only interested in files that end with .txt
    if os.path.isdir(inPath):
        continue
    if len(inPath) < 5 or inPath[-4:] != ".txt":
        continue

    # execute
    run(f"../generate_output-v2.exe {inPath} {outPath}".split())
