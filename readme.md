Guide to automating graph state calculations.
---------------------------------------------

This code generates the 'graph state' corresponding to a particular mathematical graph. Graph states are entangled quantum states that are useful for various tasks in quantum information and computation. 

The quantum state corresponding to a graph is determined by initialising each vertex in the state |+>, and applying an operation known as controlled-Z (CZ) between each pair of vertices connected by an edge. The CZ operation on vertices (i, j) applies a Pauli-Z operation to vertex j if vertex i is in the state |1>, and does nothing otherwise.

Our code asks the user to input the structure of the graph, and outputs the quantum state that corresponds to it. This becomes particularly useful when the number of vertices in the graph increases.
