#include "Crop.h"
#include <stdexcept>

void UseCrop(Image& picture, std::vector<std::string> arguments) {
    if (arguments.size() != 2) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в crop\n");
    }
    size_t width = std::stoi(arguments[0]);
    size_t height = std::stoi(arguments[1]);
    if (height > picture.GetLines() || width > picture.GetColumns() || height == 0 || width == 0) {
        return;
    }
    picture.SetLines(height);
    picture.SetColumns(width);
}
