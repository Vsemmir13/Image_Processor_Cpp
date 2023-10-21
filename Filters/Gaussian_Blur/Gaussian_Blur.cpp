#include "Gaussian_Blur.h"
#include <cmath>
#include <numbers>
#include <stdexcept>

std::vector<float> CalculationKernel(float sigma, int kernel_size) {
    const int centre = kernel_size / 2;
    std::vector<float> kernel_calc(kernel_size);
    const float constant_first = 2 * sigma * sigma;
    const float constant_second = 1.0f / std::sqrt(static_cast<float>(std::numbers::pi) * constant_first);
    for (int x = 0; x < kernel_size; ++x) {
        int distance_centre = std::abs(centre - x);
        kernel_calc[x] =
            std::exp(-static_cast<float>(distance_centre) * static_cast<float>(distance_centre) / constant_first) *
            constant_second;
    }
    return kernel_calc;
}

void UseGaussianBlur(Image& picture, std::vector<std::string> arguments) {
    if (arguments.size() != 1) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в blur\n");
    }
    float sigma = std::stof(arguments[0]);
    int kernel_size = 2 * static_cast<int>(3 * sigma) + 1;
    std::vector<float> kernel = CalculationKernel(sigma, kernel_size);
    std::vector<Color> new_colors(picture.GetColumns() * picture.GetLines());
    const int centre = kernel_size / 2;
    for (size_t local_line = 0; local_line < picture.GetLines(); ++local_line) {
        for (size_t local_column = 0; local_column < picture.GetColumns(); ++local_column) {
            Color new_color = {0, 0, 0};
            for (int distance = 0; distance <= kernel_size / 2; ++distance) {
                int64_t y_right = static_cast<int64_t>(local_column) + distance;
                int64_t y_left = static_cast<int64_t>(local_column) - distance;
                if (distance == 0) {
                    new_color += picture.GetColor(local_line, local_column) * kernel[centre + distance];
                    continue;
                }
                // смотрим умножение по строке при проходе вправо
                if (y_right >= picture.GetColumns()) {
                    new_color += picture.GetColor(local_line, picture.GetColumns() - 1) * kernel[centre + distance];
                } else {
                    new_color += picture.GetColor(local_line, y_right) * kernel[centre + distance];
                }
                // смотрим умножение по строке при проходе влево
                if (y_left < 0) {
                    new_color += picture.GetColor(local_line, 0) * kernel[centre - distance];
                } else {
                    new_color += picture.GetColor(local_line, y_left) * kernel[centre - distance];
                }
            }
            new_colors[picture.GetColumns() * local_line + local_column] = new_color;
        }
    }
    picture.SetAllColors(new_colors);
    std::vector<Color> new_colors_again(picture.GetColumns() * picture.GetLines());
    for (size_t local_line = 0; local_line < picture.GetLines(); ++local_line) {
        for (size_t local_column = 0; local_column < picture.GetColumns(); ++local_column) {
            Color new_color = {0, 0, 0};
            for (int distance = 0; distance <= kernel_size / 2; ++distance) {
                int64_t x_upper = static_cast<int64_t>(local_line) - distance;
                int64_t x_under = static_cast<int64_t>(local_line) + distance;
                if (distance == 0) {
                    new_color += picture.GetColor(local_line, local_column) * kernel[centre + distance];
                    continue;
                }
                // смотрим умножение по cтолбцу при проходе вниз
                if (x_under >= picture.GetLines()) {
                    new_color += picture.GetColor(picture.GetLines() - 1, local_column) * kernel[centre + distance];
                } else {
                    new_color += picture.GetColor(x_under, local_column) * kernel[centre + distance];
                }
                // смотрим умножение по столбцу при проходе вверх
                if (x_upper < 0) {
                    new_color += picture.GetColor(0, local_column) * kernel[centre - distance];
                } else {
                    new_color += picture.GetColor(x_upper, local_column) * kernel[centre - distance];
                }
            }
            new_colors_again[picture.GetColumns() * local_line + local_column] = new_color;
        }
    }
    picture.SetAllColors(new_colors_again);
}