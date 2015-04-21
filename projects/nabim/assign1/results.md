# Verifying correctness of implmentation of Dijkstra's shortest path algorithm

## What I checked 
For the implmentation of Dijkstra's shortest path algorithm, my harness initially asserted the following:

- cost of path is >= 0
- cost of path is <= INFINITY
- all nodes in the path actually exist in the graph
- the path actually begins from the source i.e. path leads from source to destination

CBMC proved the program incorrect for the first assertion i.e. cost of path>=0. Also, if this assertion is suppressed 
and the rest of the assertions are allowed to execute, then CBMC falls into a loop unwinding assertion error while 
verifying the path because if negative edge weights are allowed then CBMC generated a graph where a node had a self loop
which had the least cost. In such a case, trying to traverse the path output by the Dijkstra will be equivalent to traversing 
an infinite loop, so CBMC correctly caught this.

However, if an assumption was added to the harness that all edge weights were >=0, in such a case CBMC was able to successfully
verify the code.

Next, I also asserted the following:
- cost of actually traversing the path is equal to the cost reported by the algorithm

## What I was not able to specify
However, I was not able to think of a way to assert the correctness of the "shortest" property of the
path reported by the C program i.e. a way to verify whether the C program was actually returning the
shortest path.

## CBMC Runtime
For a GRAPHSIZE of 3 and a loop unwinding of 15 times, with bounds check and pointer check, the
verification took approximately 34 seconds. For the same parameters but without bounds check and
pointer check the verification took approximately 24 seconds.

For a GRAPHSIZE of 4 and a loop unwinding of 20 times, without bounds check and pointer check, the
verification took 1 min 22 seconds approximately. For the same parameters but with bounds check and
pointer check, the verification took approximately 2 min 4 seconds. 

For a GRAPHSIZE of 5 and a loop unwinding of 20 times, without bounds check and pointer check, the
verification took 3 min 34 seconds approximately.

## Checking correctness of harness using a buggy version
I also created a buggy version of dijkstra by replacing < operator with > in the portion of code which
determines the current unvisited node with the shortest path i.e. now instead of choosing the node which
has had the least cost until now, my introduced bug would cause to choose the complete opposite node.

My harness ended up verifying this evil version dijkstra as well, because I had not been able to ensure
asserting the "shortest" property of the path.

