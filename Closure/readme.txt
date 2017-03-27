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

/* to be completed with the list of your source files, */
/* feel free to add relevant supplementary material */
/* prevent yourselves from adding binaries or the originaly provided examples */


Open questions
==============

4.1 Justifications of data structures
-------------------------------------
We choose to represent attributes by string ordered by an id.
Set of attributes are represented by ordered vector of attributes. Though the ordered characteristic slow down the time to add an element to a set, it is useful when comparing sets (inclusion) and when doing union or differences of two sets (functions we execute in the closure algorithm).
For functional dependencies, we use a pair of set of attributes plus an ID, for we want to have access to both sets and to the ID for the count data structure.
For set of FDs we only need to be able to iterate on them, so a list of FDs is enough for this. 
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

6.3 Analysis
------------


Additional comments
===================

/* if any */

