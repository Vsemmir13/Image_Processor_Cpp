#include "Negative.h"
#include <stdexcept>

void UseNegative(Image& picture, std::vector<std::string> arguments) {
    if (!arguments.empty()) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в neg\n");
    }
    std::vector<Color> new_colors = picture.GetColors();
    for (size_t i = 0; i < new_colors.size(); ++i) {
        new_colors[i].red = 1 - new_colors[i].red;
        new_colors[i].green = 1 - new_colors[i].green;
        new_colors[i].blue = 1 - new_colors[i].blue;
    }
    picture.SetAllColors(new_colors);
}