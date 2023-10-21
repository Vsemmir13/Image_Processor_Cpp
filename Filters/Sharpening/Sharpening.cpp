#include "Sharpening.h"
#include "../../Classes_and_Functions/Apply_Matrix_To_Filter/Apply_Matrix_To_Filter.h"
#include <stdexcept>

void UseSharpening(Image& picture, std::vector<std::string> arguments) {
    if (!arguments.empty()) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в sharp\n");
    }
    const std::vector<float> matrix = {0, -1, 0, -1, 5, -1, 0, -1, 0};
    ApplyMatrixToFilter(picture, matrix);
}
