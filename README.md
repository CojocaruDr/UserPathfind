 I have chosen to represent the social network using pointers, stored as a set in each user's class. This method allows for constant time for adding/removing friends from an user however it does duplicate the needed information, as the friendship relation is bidirectional. Another method for storing this information would be using an adjacency matrix. Although in this case it still duplicates the information as it is symmetrical, the upper part of the matrix can be used to store the final distances.

The path finding algorithm is based on a BFS search in the graph. Starting from the source, we try to find the destination node in all adjacent nodes, in a BFS manner, going through the graph level by level relative to the source node. This way, the moment the destination node ends up in the front of our visiting queue, we know that is the shortest path, as no node is visited twice, and the distance in this case is actually the level number. This ends up with a time complexity of O(|E|), where E is the set of edges in the graph, and space complexity of O(|V|), where V is the set of nodes in the graph.
This solution however explores nodes in a radial manner, not taking into account any specific direction. As the problem only gives the information that this is a social network we are working on, it is hard to place an heuristic to estimate such direction. Thus, an A* algorithm might not perform as good as this generic implementation. We can however, following the logic of the A* algorithm, create a potential optimization for this algorithm. Let's consider the same algorithm, but each level has it's own queue to explore. More precisely, each level will have a priority queue from which nodes will be extracted to be visited, and the sorting will be based on the number of friends an user has. The reasoning is that, considering there is a solution (a valid path in the graph between two users), we can consider a closely connected network of people in which these two are included. Most likely, these people are socially similar, meaning they might have a relatively close number of friends each. Based on this logic, we can sort the nodes that will be explored next, exploring the ones that have a number of friends close to the source node, or increases/decreases towards the number of friends of the destination node. This, for a small graph will only bring an extra overhead to maintain the priority queue, but for graphs large enough, it can be considered an heuristic that's generic for a social network.
An important note on this algorithm is that, if applied from destination to source, we can also recreate the path taken to get there, by taken the minimum distance stored for each node, for each step.

Testing this implementation, we need to validate the common edge cases, like a graph with no nodes, searching for paths from root-root or destination-destination, as well as normal situations in the graph, like long lines of friends, cycles and isolated components. This will ensure the result of the algorithm in normal conditions. Besides this, we can think of testing the way memory is handled when a large number of nodes is considered. To store the visited nodes as well as the distance to them during the algorithm, a hash map is used. Since the keys are pointers, there should not be collisions, but a test with an abnormal amount of nodes and connections can show this, as well as validate there are no memory leaks. Also, another valid test case is to ensure the algorithm is working on different platforms and architectures.

