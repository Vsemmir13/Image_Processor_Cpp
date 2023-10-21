#include "Apply_Matrix_To_Filter.h"

std::vector<std::pair<int64_t, int64_t>> GetNeighbour(size_t loc_line, size_t loc_column, Image& picture) {
    std::vector<std::pair<int64_t, int64_t>> neighbours;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int64_t neighbour_line_coord = static_cast<int64_t>(loc_line) + i;
            int64_t neighbour_column_coord = static_cast<int64_t>(loc_column) + j;
            if (neighbour_line_coord >= static_cast<int64_t>(picture.GetLines())) {
                --neighbour_line_coord;
            } else if (neighbour_line_coord < 0) {
                ++neighbour_line_coord;
            }
            if (neighbour_column_coord >= static_cast<int64_t>(picture.GetColumns())) {
                --neighbour_column_coord;
            } else if (neighbour_column_coord < 0) {
                ++neighbour_column_coord;
            }
            neighbours.emplace_back(neighbour_line_coord, neighbour_column_coord);
        }
    }
    return neighbours;
}

void ApplyMatrixToFilter(Image& picture, const std::vector<float>& matrix) {
    std::vector<Color> new_colors(picture.GetColors().size());
    for (size_t local_line = 0; local_line < picture.GetLines(); ++local_line) {
        for (size_t local_column = 0; local_column < picture.GetColumns(); ++local_column) {
            std::vector<std::pair<int64_t, int64_t>> neighbours = GetNeighbour(local_line, local_column, picture);
            Color new_color = {0, 0, 0};
            for (size_t i = 0; i < 3 * 3; ++i) {
                new_color += (picture.GetColor(neighbours[i].first, neighbours[i].second) * matrix[i]);
            }
            new_color.red = std::min(1.0f, std::max(0.0f, new_color.red));
            new_color.green = std::min(1.0f, std::max(0.0f, new_color.green));
            new_color.blue = std::min(1.0f, std::max(0.0f, new_color.blue));
            new_colors[local_line * picture.GetColumns() + local_column] = new_color;
        }
    }
    picture.SetAllColors(new_colors);
}
