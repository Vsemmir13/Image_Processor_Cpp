#pragma once
#include "../Color/Color.h"
#include <vector>

class Image {
public:
    Image(size_t column, size_t line);
    Image();
    Color GetColor(size_t x, size_t y) const;
    void SetColor(const Color& color, size_t x, size_t y);
    void Create(const char* path) const;
    void Read(const char* path);
    size_t GetLines() const;
    size_t GetColumns() const;
    std::vector<Color> GetColors();
    void SetLines(size_t new_lines);
    void SetColumns(size_t new_columns);
    void SetAllColors(std::vector<Color> new_colors);

private:
    size_t lines_;
    size_t columns_;
    std::vector<Color> colors_;
};