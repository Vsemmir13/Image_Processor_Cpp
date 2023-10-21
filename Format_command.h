#pragma once
#include <string>
#include <string_view>
#include <vector>

struct Filter {
    std::string_view name_filter;
    std::vector<std::string> arguments;
};

std::vector<Filter> CommandSplit(int count, char* commands[]);