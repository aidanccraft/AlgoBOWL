# AlgoBOWL

## Algorithm Details

1. Read input file
    - Store graph and transpose graph as adjacency lists

2. Separate graph into SCCs
    - Apply SCC algorithm from class (Attendence Sheet 6)
    - Any single node SCCs are not cycles and can be ignored
    - Store each SCC as ```unordered_set```
        - Place SCCs in a ```queue``` for processing

3. Apply cycle heuristic to each cyclic SCC
    - Pop SCC from ```queue```
    - Apply DFS (or BFS, IDK if they give the same weights or not) to SCC
        - Ensure that only edges to nodes within the SCC are checked
    - Choose arbitrary start node
        - Calculate weight as below with $\text{weight}[\text{parent}[i]] = 0$
    - As traversal progresses, calculate the weight of each undiscovered node *i* as
        $$\text{weight}[i] = \text{weight}[\text{parent}[i]] + (\text{inDegree}[i] - 1) - (\text{outDegree}[\text{parent}[i]] - 1)$$
        - $\text{inDegree}[i]$ is given by the size of the transposed adjacency list at $i$
        - $\text{outDegree}[i]$ is given by the size of the regular adjacency list at $i$
    - Keep track of highest weighted node
    - Once the traversal has finished, delete the node with the highest weight
        - Save node in a list of deleted nodes

4. Repeat steps 2 and 3 on newly formed subgraphs until all SCCs are single nodes

5. Write deleted nodes to output file

6. Verify that the resulting graph is a DAG
