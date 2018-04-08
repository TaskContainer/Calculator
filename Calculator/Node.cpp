#include "Node.h"
#include "Operation.h"
#include "Parser.h"
#include <string>


double Node::operator()() const
{
    if (Value.type() == typeid(Operation))
    {
        return std::any_cast<Operation>(Value)((*Left)(), (*Right)());
    }
    return std::any_cast<double>(Value);
}

Node::Node(const double val) : Value(val)
{
}

Node::Node(const std::vector<std::string>& source)
{
    auto[operation, iter] = Parser::MaxPriorityOperation(source);
    if (!operation.has_value())
    {
        Value = source.empty()? 0: std::stod(source.front());
        return;
    }
    // path to "a / -b"
    if (iter != source.cbegin())
    {
        if (const auto prev = Operation::ParseFrom(*(iter - 1)); 
        prev.has_value() && prev.value() < operation.value())
        {
            operation = prev;
            --iter;
        }
    }
    //
    Value = operation.value();
    Left = std::make_shared<Node>(Node({ source.cbegin(), iter }));
    Right = std::make_shared<Node>(Node({ iter + 1, source.cend() }));
}
