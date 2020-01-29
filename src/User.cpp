//
// Created by Cojocaru Dragos on 1/19/2020.
//

#include <User.h>

#include <algorithm>
#include <unordered_set>
#include <queue>

User::User(const std::string& name) {
    m_name = name;
}

void User::forEachFriend(const UserIterFunc &func) const{
    std::for_each(m_friends.begin(), m_friends.end(), func);
}

bool User::isSame(User* other) const{
    return this == other;
}

const std::string &User::getName() const{
    return m_name;
}

void User::bfs(const UserIterFunc &func) const {
    std::queue<const User *> toVisit;
    std::unordered_set<const User *> visited;

    toVisit.push(this);

    while (!toVisit.empty()) {
        const User *curNode = toVisit.front();
        toVisit.pop();

        if (visited.end() == visited.find(curNode)) {
            func(curNode);
            visited.insert(this);

            curNode->forEachFriend([&func, &toVisit](const User *fr) -> void {
                toVisit.push(fr);
            });
        }
    }

}

void User::addFriend(User *fr) {
    if(!isSame(fr)) {
        this->m_friends.insert(fr);
    }
}

int User::getFriendsNo() {
    return m_friends.size();
}
