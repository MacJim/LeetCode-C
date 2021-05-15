//
// Created by Jim Macintosh Shi on 5/14/21.
//

#ifndef LEETCODECACHE_FLOAT_EQUAL_H
#define LEETCODECACHE_FLOAT_EQUAL_H


#include <cmath>


// Source: https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type isClose(const T& a, const T& b, T relativeTolerance = 1e-5, T absoluteTolerance = 1e-8) {
    const auto lhs = std::fabs(a - b);
    const auto rhs = relativeTolerance * std::fabs(b) + absoluteTolerance;

    return (lhs <= rhs);
}


#endif //LEETCODECACHE_FLOAT_EQUAL_H
