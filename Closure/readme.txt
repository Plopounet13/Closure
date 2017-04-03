DBDM : Closure Algorithm for Functional Dependencies
====================================================

PAULIN Loĩs
MENET Hugo


Content
=======

readme.txt : this file
results.csv : raw results
plot.png : figure depicting results

main.cpp: parse the parameters of the entry and call the wanted closure function from functions.cpp
attribute.cpp: define the class attribute
attSet.cpp: define the class set of attributes and the functions used on them in the closure algorihtms
fd.cpp: define the class functional dependencies
functions.cpp: the naive and improved closure algorithm
Makefile 

Open questions
==============

4.1 Justifications of data structures
-------------------------------------
We choose to represent attributes by string ordered by an id.
We define a template for set. Sets are represented by ordered vector of their elements. Though the ordered characteristic slow down the time to add an element to a set, it is useful when comparing sets (inclusion) and when doing union or differences of two sets (functions we execute for attributes in the closure algorithm and for FDs in the reduce algorithm).
So sets of attributes are defined using our set template.
For sets of sets of attributes, we only need to iterate on them, so a vector is enough for this.
For functional dependencies, we use a pair of set of attributes plus an ID, for we want to have access to both sets and to the ID for the count data structure.
We first thought that for set of FDs we will only need to be able to iterate on them, so a list of FDs would be enough. However we also need to do minus, so we use the same set template as for set of attributes.
List (resp. count) is a vector of list of FDs (resp. int) indexed by the attributes (resp. FDs) ID.

4.2 Strategy for Choose A
-------------------------
We choose the first A. It is naïve but in constant time and computing an heuristic to choose A could have a high cost in complexity, possibly comparable with the cost of the whole algorithm, which would then be useless even if we could win on the remaining part of the algorithm.

4.3 Find the bug
-------------------------
If the FD (W -> Z) is non standard i.e. W empty, then we should add this Z to the closure. However for there is no attributes in W it is in no list[A] for any attribute A, so the improved closure algorithm won't add it. So we should add it at the beginning of the algorithm.


6.1 Interestingness of generate
-------------------------------
It is a case where we can see the improvement between the two versions of the closure algorithm. With the naive one, at each iteration of the while loop, we add only (and exactly for the n first) one attribute to the closure, so we have n iteration of the while loop, which is the maximum number of iteration for an entry of size n, the loop is executed in quadratic time when the while loop iterated n times in the improved version is executed in constant time.

6.2 Setup and methodology
-------------------------
For timing, we time internally to the program, not through bash (as it is done in the perf.sh example provided) (so we avoid noise like launch time of the program).
We construct a bach script using grep and sed for timing our closure algorithms on several examples generated using generate (which is an interesting case). We do test for n going from 100 to 1000 with a step of 100, for each n we do the average on 5 draws. We attached a figure of those points (time depending of n) for the naive and improved algotrihm.

6.3 Analysis

------------


Additional comments
===================
On exercice 7 : decomposition
First the pseudo code algorithm provided in the subject seems incorrect with no mention of R when looking for a non trivial non key FD, and so always doing the same step in the while loop. We tried to correct this by replacing U by R in checking if X non key and by only considering functional dependencies that are considered to be inside the schema when testing BCNF.

