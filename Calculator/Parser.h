#pragma once
#include <tuple>
#include "Operation.h"

namespace Parser
{
    std::tuple<std::optional<Operation>, std::vector<std::string>::const_iterator> MaxPriorityOperation(
        const std::vector<std::string> &source);
    
}