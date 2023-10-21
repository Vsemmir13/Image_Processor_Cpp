#include "Pixelize.h"
#include <stdexcept>

void UsePixelize(Image& picture, std::vector<std::string> arguments) {
    if (arguments.size() != 1) {
        throw std::runtime_error("Ошибка: неправильное количество аргументов в px\n");
    }
    size_t pixel_size = std::stoi(arguments[0]);
    if (pixel_size == 0 || pixel_size > picture.GetLines() || pixel_size > picture.GetColumns()) {
        throw std::runtime_error("Ошибка: размер пикселя не может быть такого размера\n");
    }
    for (size_t local_pixel_line = 0; local_pixel_line < picture.GetLines(); local_pixel_line += pixel_size) {
        for (size_t local_pixel_column = 0; local_pixel_column < picture.GetColumns();
             local_pixel_column += pixel_size) {
            Color sum_color;
            int pixel_count = 0;
            for (size_t local_line_in_pixel = local_pixel_line;
                 local_line_in_pixel < local_pixel_line + pixel_size && local_line_in_pixel < picture.GetLines();
                 ++local_line_in_pixel) {
                for (size_t local_column_in_pixel = local_pixel_column;
                     local_column_in_pixel < local_pixel_column + pixel_size &&
                     local_column_in_pixel < picture.GetColumns();
                     ++local_column_in_pixel) {
                    sum_color += picture.GetColor(local_line_in_pixel, local_column_in_pixel);
                    ++pixel_count;
                }
            }
            Color mid_color = sum_color * (1.0f / static_cast<float>(pixel_count));
            for (size_t local_line_in_pixel = local_pixel_line;
                 local_line_in_pixel < local_pixel_line + pixel_size && local_line_in_pixel < picture.GetLines();
                 ++local_line_in_pixel) {
                for (size_t local_column_in_pixel = local_pixel_column;
                     local_column_in_pixel < local_pixel_column + pixel_size &&
                     local_column_in_pixel < picture.GetColumns();
                     ++local_column_in_pixel) {
                    picture.SetColor(mid_color, local_line_in_pixel, local_column_in_pixel);
                }
            }
        }
    }
}