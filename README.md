## K Shortest Paths

# Abstract

The problem of finding the best K elementary paths in a network is studied here. Shortest path
problem is one of the most widely studied classic network optimization problems. It started with
the most basic problem of finding the shortest path between an OD pair in a given network with
non-negative costs. Multiple variants of the problem like finding the best K shortest path
between an OD pair and finding the shortest path in a network with time-varying costs have been
studied over the years. The problem of finding the best K paths has many applications in vehicle
routing, artificial intelligence, network optimisation, transportation planning among many others.
The problem of finding the best K unconstrained paths also has its own applications in the form
of scheduling rides which involve tours. In this paper, the computational complexity of the
algorithm is optimised in two steps after discussing the existing algorithms. First, the data
structure for the storage of the K labels for every node is made optimal. Then, the presence of
cycles in a path is detected in a constant time instead of linear. It is done by storing the product
of the primes of nodes in a path in different 128 bit variables. A theoretical computational time
complexity of O(Km(log(Kn)+C)) was accomplished after this step. Then, the graph is reduced
to contain the nodes and arcs present in the best K shortest paths and a few more. Then, the
algorithm is run in both the directions to find the paths faster. A better practical running time was
observed when tested in various real world networks and square grid networks after the second
set of optimizations. Finally the practical relevance of large values of K is explained through the
NP hard multiobjective optimization problem.

The one directional version of the code is available in the directory 'code' and the bidirectional version is available in the directory 'bi-direction k shortest paths algorithms'
