#include "Parser.h"

std::tuple<std::optional<Operation>, std::vector<std::string>::const_iterator> 
Parser::MaxPriorityOperation(const std::vector<std::string>& source)
{
    std::optional<Operation> operation;
    std::vector<std::string>::const_iterator iter = source.cend();
    for (auto i = source.cbegin(); i < source.cend(); ++i)
    {
        const auto maybeOp = Operation::ParseFrom(*i);
        if (!maybeOp.has_value())
        {
            continue;
        }
        if (!operation.has_value() || (maybeOp.value() > operation.value()))
        {
            iter = i;
            operation = maybeOp;
        }
        if (operation.value().IsMaxPriority())
        {
            break;
        }
    }
    return { operation, iter };
}
