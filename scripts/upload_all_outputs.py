import os
from subprocess import run

OUTPUT_DIR = "../realOutputs/"

if not os.path.exists(OUTPUT_DIR):
    print("Error: output directory does not exist")
    exit()

# loop through every file in input dir
for file in os.listdir(OUTPUT_DIR):
    outPath = os.path.join(OUTPUT_DIR, file)

    # only interested in files that end with .txt
    if os.path.isdir(outPath):
        continue
    if len(outPath) < 5 or outPath[-4:] != ".txt":
        continue

    # execute
    print(f"Uploading file {file}")
    run(f"../algobowl.exe group output upload {outPath}".split())
