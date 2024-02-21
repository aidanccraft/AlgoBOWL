import sys
# generate random integer values
from random import seed
from random import randint
# seed random number generator
seed()

# get output file from first command line argument
output_file = sys.argv[1]
do_not_include = [1, 2, 3, 4]
num_courses = 40
num_pre_reqs = 0
f = open(output_file, "a")
nm = str(num_courses) + "\n"
f.write(nm)

# --------------- generates strongly connected components of varying sizes ------------ #
course_counter = 1
while course_counter <= num_courses:
    cycle_size = randint(0, 5)

    if cycle_size+course_counter >= num_courses:
        cycle_size = num_courses - course_counter

    print(f'cycle_size {cycle_size}')

    if cycle_size == 0 or cycle_size == 1:
        m_i = 0
        s = str(m_i) + " "
        f.write(s)
        f.write("\n")
        course_counter += 1
    else:
        cycle_start = course_counter
        for j in range(cycle_size-1):
            pre_req_set = set()
            pre_req_set.add(course_counter+1)
            m_i = randint(1, cycle_size-1)
            s = str(m_i) + " "
            f.write(s)
            while len(pre_req_set) < m_i:
                # pre_req = course_counter
                coin_flip = randint(0, 100)
                if coin_flip % 2 == 0:
                    max = cycle_start+cycle_size-1
                else:  # if you let this be a rand int up to cycle_size then you can get some interesting interconnections
                    max = cycle_start+cycle_size
                while True:
                    pre_req = randint(cycle_start, max)
                    if pre_req == course_counter:
                        continue
                    else:
                        pre_req_set.add(pre_req)
                        break
            for p in pre_req_set:
                s = str(p) + " "
                f.write(s)
            f.write("\n")
            course_counter += 1
            num_pre_reqs += m_i
        
        s = "1 " + str(cycle_start)
        f.write(s)
        f.write("\n")
        course_counter += 1
        num_pre_reqs += 1

# --------------- generates cycles of varying sizes ------------ #
# course_counter = 1
# while course_counter <= num_courses:
#     cycle_size = randint(0, 10)

#     if cycle_size+course_counter >= num_courses:
#         cycle_size = num_courses - course_counter

#     # print(f'cycle_size {cycle_size}')

#     if cycle_size == 0 or cycle_size == 1:
#         m_i = 0
#         s = str(m_i) + " "
#         f.write(s)
#         f.write("\n")
#         course_counter += 1
#     else:
#         cycle_start = course_counter
#         for j in range(cycle_size-1):
#             m_i = 1
#             s = str(m_i) + " "
#             f.write(s)
            
#             s = str(course_counter+1) + " "
#             f.write(s)
#             f.write("\n")
#             course_counter += 1
#             num_pre_reqs += 1

#         s = "1 " + str(cycle_start)
#         f.write(s)
#         f.write("\n")
#         course_counter += 1
#         num_pre_reqs += 1
# -------------------- make random input with an average num of prereqs------------------#
# avg_pre_reqs_per_course = 2
# for i in range(1, num_courses+1):
#     m_i = randint(0, avg_pre_reqs_per_course)
#     s = str(m_i) + " "
#     f.write(s)
#     pre_req_set = set()
#     while len(pre_req_set) < m_i:
#         pre_req = i
#         while (pre_req == i) or (pre_req in do_not_include):
#             pre_req = randint(1, num_courses)
#         pre_req_set.add(pre_req)
#     for p in pre_req_set:
#         s = str(p) + " "
#         f.write(s)
#     f.write("\n")

# ------ make an input of a given size with every class connected to every other class --------#
# ---- note, num_courses cannot be > than 1000 for this to fit within the bounds of the problem
# m_i = num_courses - 1
# for i in range(1, num_courses):
#     s = str(m_i) + " "
#     f.write(s)
#     for j in range(1, num_courses+1):
#         if j != i:
#             s = str(j) + " "
#             f.write(s)
#     f.write("\n")
#     num_pre_reqs += m_i

# s = str('0')
# f.write(s)
# ------ make an input of a given size with every class to the previous and preceding class --------#
# for i in range(1, num_courses+1):
#     m_i = 0
#     s = ''
#     if i != num_courses:
#         pre_req = i + 1
#         s += str(pre_req) + " "
#         m_i += 1
#     if i != 1:
#         pre_req = i - 1
#         s += str(pre_req) + " "
#         m_i += 1
#     n = str(m_i) + " "
#     f.write(n)
#     f.write(s)
#     f.write("\n")
#     num_pre_reqs += n

# ------ make an input of a given size with a given number of 'nexus' nodes is nodes connected to all other nodes --------#
# nexus_nodes = 3
# node_list = []
# for k in range(1, nexus_nodes+1):
#     node_list.append(k)
#     m_i = num_courses - nexus_nodes
#     s = str(m_i) + " "
#     f.write(s)
    # num_pre_reqs += m_i
#     for j in range(nexus_nodes, num_courses+1):
#         pre_req = j
#         s = str(pre_req) + " "
#         f.write(s)
#     f.write("\n")
# for i in range(nexus_nodes, num_courses+1):
#     m_i = nexus_nodes
#     s = str(m_i) + " "
#     f.write(s)
#     for n in node_list:
#         pre_req = n
#         s = str(pre_req) + " "
#         f.write(s)
#     f.write("\n")

# ------ make a random input for a large number of courses --------#
# max_pre_reqs = 10**5 if num_courses*num_courses > 10**5 else (num_courses -1)

# for i in range(1, num_courses+1):
#     if num_courses - i > 0:
#         m_i = randint(0, (max_pre_reqs//(num_courses-i)))
#     elif max_pre_reqs != 0:
#         m_i = randint(0, max_pre_reqs)
#     else:
#         m_i = 0
#     max_pre_reqs -= m_i
#     print(max_pre_reqs)
#     s = str(m_i) + " "
#     f.write(s)
#     num_pre_reqs += m_i
#     pre_req_set = set()
#     while len(pre_req_set) < m_i:
#         pre_req = i
#         while pre_req == i:
#             pre_req = randint(1, num_courses)
#         pre_req_set.add(pre_req)
#     for j in range(m_i):
#         pre_req = i
#         while pre_req == i:
#             pre_req = randint(1, num_courses)
#     for p in pre_req_set:
#         s = str(p) + " "
#         f.write(s)
#     f.write("\n")

# --------------- make a random input for a smaller number of courses -------#
# num_pre_reqs = 0
# for i in range(1, num_courses//2):
#     num = num_courses-1
#     m_i = randint(0, num)
#     s = str(m_i) + " "
#     f.write(s)
#     num_pre_reqs += m_i
#     pre_req_set = set()
#     while len(pre_req_set) < m_i:
#         pre_req = i
#         while pre_req == i:
#             pre_req = randint(1, num_courses)
#         pre_req_set.add(pre_req)
#     print(pre_req_set)
#     for p in pre_req_set:
#         s = str(p) + " "
#         f.write(s)
#     f.write("\n")

# generate file with varied subgraphs
# for i in range(1, num_courses//2):
#     num = num_courses-1
#     m_i = randint(0, num)
#     s = str(m_i) + " "
#     f.write(s)
#     num_pre_reqs += m_i
#     pre_req_set = set()
#     while len(pre_req_set) < m_i:
#         pre_req = i
#         while pre_req == i:
#             pre_req = randint(1, num_courses)
#         pre_req_set.add(pre_req)
#     for p in pre_req_set:
#         s = str(p) + " "
#         f.write(s)
#     f.write("\n")

# for i in range(num_courses//2, num_courses+1):
#     num = 20
#     m_i = randint(0, num)
#     s = str(m_i) + " "
#     f.write(s)
#     num_pre_reqs += m_i
#     pre_req_set = set()
#     while len(pre_req_set) < m_i:
#         pre_req = i
#         while pre_req == i:
#             pre_req = randint(1, num_courses)
#         pre_req_set.add(pre_req)
#     for p in pre_req_set:
#         s = str(p) + " "
#         f.write(s)
#     f.write("\n")

# ---------------------------- make a graph with num courses not exceeding 10^4 ---------------------------#
# num_pre_reqs = 0
# for i in range(1, num_courses//2):
#     num = num_courses-1
#     m_i = randint(0, num)
#     s = str(m_i) + " "
#     f.write(s)
#     num_pre_reqs += m_i
#     pre_req_set = set()
#     while len(pre_req_set) < m_i:
#         pre_req = i
#         while pre_req == i:
#             pre_req = randint(1, num_courses)
#         pre_req_set.add(pre_req)
#     print(pre_req_set)
#     for p in pre_req_set:
#         s = str(p) + " "
#         f.write(s)
#     f.write("\n")
    
# ---------------------------- make a graph with num pre-reqs not exceeding 10^5 ---------------------------#
# max_pre_reqs = 10**5 if num_courses*num_courses > 10**5 else (num_courses -1)
# # max_reached = False
# for i in range(1, num_courses+1):
#     m_i = randint(100, num_courses-1)
#     if (num_pre_reqs + m_i < max_pre_reqs):
#         s = str(m_i) + " "
#         f.write(s)
#         pre_req_set = set()
#         while len(pre_req_set) < m_i:
#             pre_req = i
#             while pre_req == i:
#                 pre_req = randint(1, num_courses)
#             pre_req_set.add(pre_req)
#         for p in pre_req_set:
#             s = str(p) + " "
#             f.write(s)
#         f.write("\n")
#         num_pre_reqs += m_i
#     else:
#         s = str(0) + "\n"
#         f.write(s)

# ---------------------------- make a graph with connected components of size 2 ---------------------------#
# for i in range(1, num_courses+1):
#     m_i = 1
#     s = str(m_i) + " "
#     f.write(s)

#     if i % 2 == 1:
#         pre_req = i + 1
#         s = str(pre_req) + " "
#     else:
#         pre_req = i - 1
#         s = str(pre_req) + " "

#     f.write(s)
#     f.write("\n")
#     num_pre_reqs += 1

print(f'num nodes: {num_courses}, num edges: {num_pre_reqs}')
f.close()