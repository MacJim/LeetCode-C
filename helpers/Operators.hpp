//
// Created by Jim Macintosh Shi on 9/2/20.
//

#ifndef LEETCODECACHE_OPERATORS_HPP
#define LEETCODECACHE_OPERATORS_HPP


#include <iostream>
#include <vector>
#include <set>
#include <queue>


/*
 * Unfortunately I cannot separate template functions/classes into `hpp` and `cpp` files.
 *
 * If I do that, when the compiler sees `main.cpp` and `Operators.cpp` files alone, it won't generate a template function for type `int` (which is used in `main.cpp`).
 *
 * More info here: https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 */


//#pragma mark pair
//template <typename A, typename B>
//std::ostream& operator << (std::ostream& os, const std::pair<A, B>& p);
//
//
//#pragma mark vector
//template <typename T>
//std::ostream& operator << (std::ostream& os, const std::vector<T>& v);
//
//
//#pragma mark set
//template <typename T>
//std::ostream& operator << (std::ostream& os, const std::set<T>& s);
//
//template <typename T, typename UnusedComparator>
//std::ostream& operator << (std::ostream& os, const std::set<T, UnusedComparator>& s);


#pragma mark pair
template <typename A, typename B>
std::ostream& operator << (std::ostream& os, const std::pair<A, B>& p) {
    os << "(" << p.first << " " << p.second << ")";
    return os;
}


#pragma mark vector
template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (const auto& element: v) {
        os << " " << element;
    }
    os << " ]";
    return os;
}


#pragma mark set
template <typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
    os << "[";
    for (const auto& element: s) {
        os << " " << element;
    }
    os << " ]";
    return os;
}


template <typename T, typename UnusedComparator>
std::ostream& operator << (std::ostream& os, const std::set<T, UnusedComparator>& s) {
    os << "[";
    for (const auto& element: s) {
        os << " " << element;
    }
    os << " ]";
    return os;
}


#pragma mark queue
template <typename T>
std::ostream& operator << (std::ostream& os, std::priority_queue<T> q) {
    os << "[";
    while (!q.empty()) {
        os << " " << q.top();
        q.pop();
    }
    os << " ]";
    return os;
}


template <typename T, typename UnusedContainer, typename UnusedComparator>
std::ostream& operator << (std::ostream& os, std::priority_queue<T, UnusedContainer, UnusedComparator> q) {
    os << "[";
    while (!q.empty()) {
        os << " " << q.top();
        q.pop();
    }
    os << " ]";
    return os;
}


#endif //LEETCODECACHE_OPERATORS_HPP
