#pragma once
#include <any>
#include <memory>
#include <vector>

class Node
{
private:
    std::any Value;
    std::shared_ptr<Node> Left, Right;

public:
    double operator()() const;

    Node(const double val);

    Node(const std::vector<std::string> &source);
};
