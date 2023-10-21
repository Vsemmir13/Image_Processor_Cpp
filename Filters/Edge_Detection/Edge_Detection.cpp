#include "Edge_Detection.h"
#include "../Grayscale/Grayscale.h"
#include "../../Classes_and_Functions/Apply_Matrix_To_Filter/Apply_Matrix_To_Filter.h"
#include <stdexcept>

void UseEdgeDetection(Image& picture, std::vector<std::string> arguments) {
    if (arguments.size() != 1) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в edge\n");
    }
    UseGrayscale(picture, {});
    float threshold = std::stof(arguments[0]);
    const std::vector<float> matrix = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    ApplyMatrixToFilter(picture, matrix);
    for (size_t local_line = 0; local_line < picture.GetLines(); ++local_line) {
        for (size_t local_column = 0; local_column < picture.GetColumns(); ++local_column) {
            if (picture.GetColor(local_line, local_column).red > threshold ||
                picture.GetColor(local_line, local_column).green > threshold ||
                picture.GetColor(local_line, local_column).blue > threshold) {
                picture.SetColor({1, 1, 1}, local_line, local_column);
            } else {
                picture.SetColor({0, 0, 0}, local_line, local_column);
            }
        }
    }
}