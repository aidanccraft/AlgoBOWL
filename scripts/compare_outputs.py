import os
from subprocess import run


OUTPUT_DIR_1 = "../realOutputs/"
OUTPUT_DIR_2 = "../realOutputs2/"


if not os.path.exists(OUTPUT_DIR_1):
    print("Error: output directory 1 does not exist")
    exit()

if not os.path.exists(OUTPUT_DIR_2):
    print("Error: output directory 2 does not exist")
    exit()

# loop through every file in input dir
for file in os.listdir(OUTPUT_DIR_1):

    outPath1 = os.path.join(OUTPUT_DIR_1, file)
    outPath2 = os.path.join(OUTPUT_DIR_2, file)

    if not os.path.exists(outPath1) or not os.path.exists(outPath2):
        continue

    # only interested in files that end with .txt
    if os.path.isdir(outPath1):
        continue
    if len(outPath1) < 5 or outPath1[-4:] != ".txt":
        continue

    if os.path.isdir(outPath2):
        continue
    if len(outPath2) < 5 or outPath2[-4:] != ".txt":
        continue

    # compare outputs

    with open(outPath1, 'r') as f:
        with open(outPath2, 'r') as g:
            nodes1 = int(f.readline())
            nodes2 = int(g.readline())

            print(file, nodes1, nodes2, nodes2 < nodes1)

            if nodes2 < nodes1:
                print(f"Uploading file {file}")
                run(f"../algobowl.exe group output upload {outPath2}".split())
