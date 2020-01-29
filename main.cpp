#include <iostream>
#include <vector>
#include <sstream>
#include <queue>

#include <User.h>

static int bfsSearch(User* rootUser, User* targetUser) {
    if(nullptr == rootUser || nullptr == targetUser) return -1;

    std::queue<const User*> toVisit;
    int nodesInCurrent;

    // map with visited nodes, to avoid loops and to store the
    // length of the path from rootUser to given node
    std::unordered_map<const User*, int> visited;

    // start with target user and SE
    toVisit.push(rootUser);
    nodesInCurrent = 1;
    int levelNo = 1;
    int nodesInNext = 0;

    while(!toVisit.empty()) {
        const User* curNode = toVisit.front();
        toVisit.pop();
        --nodesInCurrent;

        if(visited.end() == visited.find(curNode)) {

            visited.insert(std::make_pair(curNode, levelNo));
            curNode->forEachFriend([&nodesInNext, &toVisit](const User *fr) -> void {
                toVisit.push(fr);
                ++nodesInNext;
            });
        }

        // when nodesInCurrent reaches 0, the whole level is visited.
        // the final path will have one more step
        if(nodesInCurrent == 0) {
            nodesInCurrent = nodesInNext;
            nodesInNext = 0;
            ++levelNo;
        }
    }

    if(visited.end() != visited.find(targetUser)) {
        return visited[targetUser] - 1;
    }
    else {
        return -1;
    }
}

int main() {
    User rootUser("root");
    User A("A"), B("B"), C("C"), D("D"), E("E"), F("F"), G("G"), H("H"), I("I"), J("J"), K("K");
    User targetUser("target");

    #if 0 // Simple case, when root is friend with everyone except the target,
      // and the target is friend with one of the others. Result should be 2
    rootUser.addFriendTwoWay(&A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K);
    A.addFriendTwoWay(&targetUser);

    #elif 0 // Case when the friend connections are complex, but there is no path to target.
            // Result should be -1
    rootUser.addFriendTwoWay(&A, &C, &D, &E, &H);
    A.addFriendTwoWay(&B, &D, &rootUser, &K, &J);
    C.addFriendTwoWay(&A, &I, &D, &C, &E, &H);
    D.addFriendTwoWay(&A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K);

    #elif 0 // Same as previous, but there is a solution
            // The shortest path should be root -> A/D/C -> J -> targetUser
            // Result should be 3
    rootUser.addFriendTwoWay(&A, &C, &D, &E, &H);
    A.addFriendTwoWay(&B, &D, &rootUser, &K, &J);
    C.addFriendTwoWay(&A, &I, &D, &C, &E, &H, &J);
    D.addFriendTwoWay(&A, &B, &C, &D, &E, &F, &G, &H, &I, &J, &K);
    J.addFriendTwoWay(&targetUser);

    #elif 1 // A longer path but more direct, and more loops
            // Result should be 4
    rootUser.addFriendTwoWay(&A);
    A.addFriendTwoWay(&B);
    B.addFriendTwoWay(&A, &C, &D, &E, &F);
    F.addFriendTwoWay(&A, &B, &C, &D, &E, &G);
    G.addFriendTwoWay(&A, &B, &C, &D, &E, &F, &H, &I, &J, &K);
    K.addFriendTwoWay(&targetUser);
    #endif

    int distance = bfsSearch(&rootUser, &targetUser);
    std::cout << "Found distance: " << distance << std::endl;

    return 0;
}
