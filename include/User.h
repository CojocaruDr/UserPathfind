//
// Created by Cojocaru Dragos on 1/19/2020.
//

#ifndef USERFINDING_USER_H
#define USERFINDING_USER_H

#include <vector>
#include <set>
#include <functional>

class User;
using UserIterFunc = std::function<void(const User*)>;

/**
 * Model for an user in the social network.
 */
class User {
private:

    /**
     * Vector of pointers to other users, representing friends of this one.
     */
    std::set<const User*> m_friends;

    /**
     * Name of this user, for clean stdout printing.
     */
    std::string m_name;
public:

    explicit User(const std::string& name);

    /**
     * Add one or more friends to this user, as bidirectional relationship
     * @tparam Args - User class type
     * @param args  - users to add
     */
    template<class ...Args>
    void addFriendTwoWay(Args*... args);

    /**
     * Adds the user as a friend
     * @param fr - user to add to friend list
     */
    void addFriend(User* fr);

    /**
     * Getter for number of friends
     * @return
     */
    int getFriendsNo();

    /**
     * Iterate through all friends of this users, applying given function
     * @param func - function to call for each friend of this user
     */
    void forEachFriend(const UserIterFunc& func) const;

    /**
     * Comparison function used on two users
     * @param other - user to compare with
     * @return true, if both users point to the same structure, false otherwise
     */
    [[nodiscard]] bool isSame(User* other) const;

    /**
    * BFS type exploration of the friends graph through this node.
    * @param func - func to call for each node
    */
    void bfs(const UserIterFunc& func) const;

    /**
     * Getter for name
     * @return - user name
     */
    [[nodiscard]] const std::string& getName() const;
};

template<typename ...Args>
void User::addFriendTwoWay(Args*... args) {
    auto friends = {args...};
    for(const auto fr : friends) {
        if(!isSame(fr)) {
            m_friends.insert(fr);
            fr->addFriend(this);
        }
    }
}

#endif //USERFINDING_USER_H
