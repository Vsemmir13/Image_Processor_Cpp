#include "Grayscale.h"
#include <stdexcept>

void UseGrayscale(Image& picture, std::vector<std::string> arguments) {
    if (!arguments.empty()) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в gs\n");
    }
    const float for_red = 0.299f;
    const float for_green = 0.587f;
    const float for_blue = 0.114f;
    std::vector<Color> new_colors = picture.GetColors();
    for (size_t i = 0; i < new_colors.size(); ++i) {
        float local_color =
            for_red * new_colors[i].red + for_green * new_colors[i].green + for_blue * new_colors[i].blue;
        new_colors[i] = Color(local_color, local_color, local_color);
    }
    picture.SetAllColors(new_colors);
}