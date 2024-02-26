import sys
# generate random integer values
from random import seed
from random import randint
# seed random number generator
seed()

# get output file from first command line argument
output_file = sys.argv[1]
num_courses = 10**4
num_pre_reqs = 10**5
f = open(output_file, "w")
f.write(str(num_courses) + "\n")


curr_node = 1
num_edges = 0

# -------------------- create chain with 1000 nodes ------------------#
f.write("1 "+str(curr_node+1)+"\n")
curr_node += 1
num_edges += 1
for _ in range(998):
    f.write("2 "+str(curr_node-1)+" "+str(curr_node+1)+"\n")
    curr_node += 1
    num_edges += 2
f.write("1 "+str(curr_node-1)+"\n")
curr_node += 1
num_edges += 1

# -------------------- create giant loop with 1000 nodes ------------------#
loop_start = curr_node
for _ in range(999):
    f.write("1 "+str(curr_node+1)+"\n")
    curr_node += 1
    num_edges += 1
f.write("1 "+str(loop_start)+"\n")
curr_node += 1
num_edges += 1

# -------------------- create fully connected section with 100 nodes ------------------#
# (only 100 because there will be n^2 edges)
for i in range(100):
    f.write("99 ")
    for j in range(100):
        if (i != j):
            f.write(str(curr_node+j)+" ")
    f.write("\n")
    num_edges += 99
curr_node += 100

# -------------------- create acyclic section with 1000 nodes and 5000 edges ------------------#
edges = [[] for _ in range(1000)]
count = 0
while count < 5000:
    r1 = randint(0,999)
    r2 = randint(0,999)
    if r1 == r2: continue # do not add self edge
    if r1 > r2: r1,r2 = r2,r1 #swap (make r1 smaller)
    if r2 in edges[r1]: continue # do not add duplicate edge
    edges[r1].append(r2)
    num_edges += 1
    count += 1
for i in range(1000):
    f.write(str(len(edges[i]))+" "+" ".join([str(x+curr_node) for x in edges[i]])+"\n")
curr_node += 1000

# -------------------- fill in the rest with random ------------------#
edges = [[] for _ in range(num_courses-curr_node+1)]
while num_edges < num_pre_reqs:
    r1 = randint(0,num_courses-curr_node)
    r2 = randint(0,num_courses-curr_node)
    if r1 == r2: continue # do not add self edge
    if r2 in edges[r1]: continue # do not add duplicate edge
    edges[r1].append(r2)
    num_edges += 1
for i in range(num_courses-curr_node+1):
    f.write(str(len(edges[i]))+" "+" ".join([str(x+curr_node) for x in edges[i]])+"\n")

print(f'num nodes: {num_courses}, num edges: {num_pre_reqs}')
f.close()