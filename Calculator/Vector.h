#pragma once
#include <vector>
#include <iterator>

template<typename T> std::ostream &operator<<(std::ostream &out, const std::vector<T> &vec)
{
    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<T>(out, " "));
    return out;
}

template<typename T> std::istream &operator>>(std::istream &in, std::vector<T> &vec)
{
    for (auto &i : vec)
    {
        in >> i;
    }
    return in;
}