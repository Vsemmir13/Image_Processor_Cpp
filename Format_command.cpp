#include "Format_command.h"
#include <iostream>
#include <vector>
#include <set>

std::vector<Filter> CommandSplit(int count, char* commands[]) {
    if (count < 3) {
        std::cerr << "Слишком мало аргументов в" << commands[0] << std::endl;
        std::cerr << "Пример ввода в командную строку {имя программы} {путь к входному файлу} {путь к выходному файлу} "
                     "[-{имя фильтра 1} [параметр фильтра 1] [параметр фильтра 2] ...] [-{имя фильтра 2} "
                     "[параметр фильтра 1] [параметр фильтра 2] ...] ..."
                  << std::endl;
        throw std::runtime_error("Ошибка в Format_command.cpp\n");
    }
    std::string input_file = commands[1];
    std::string output_file = commands[2];
    std::vector<Filter> filters;
    Filter local_filter;
    std::set<std::string_view> all_filters = {"crop", "gs", "neg", "sharp", "edge", "blur", "px"};
    for (int i = 3; i < count; i++) {
        if (commands[i][0] == '-') {
            if (!local_filter.name_filter.empty()) {
                filters.push_back(local_filter);
            }
            local_filter = {commands[i] + 1, {}};
            if (all_filters.count(local_filter.name_filter) == 0) {
                throw std::runtime_error("Ошибка в Format_command.cpp. Дан несуществующий фильтр \n");
            }
        } else {
            local_filter.arguments.push_back(commands[i]);
        }
        if (i == count - 1) {
            filters.push_back(local_filter);
        }
    }
    std::cout << "Путь к входному файлу: " << input_file << std::endl;
    std::cout << "Путь к выходному файлу: " << output_file << std::endl;
    std::cout << "Фильтры:" << std::endl;
    for (const auto& filter : filters) {
        std::cout << filter.name_filter << " Аргументы: ";
        for (const auto& arg : filter.arguments) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
    return filters;
}
