#include "Image.h"
#include <iostream>
#include <fstream>

Image::Image(size_t column, size_t line)
    : lines_(line), columns_(column), colors_(std::vector<Color>(lines_ * columns_)) {
}

Color Image::GetColor(size_t x, size_t y) const {
    return colors_[columns_ * x + y];
}

void Image::SetColor(const Color &color, size_t x, size_t y) {
    colors_[columns_ * x + y].red = color.red;
    colors_[columns_ * x + y].green = color.green;
    colors_[columns_ * x + y].blue = color.blue;
}

const float NORM_COLOR = 255.0f;
const size_t FIVE = 5;
const size_t SIX = 6;
const size_t SEVEN = 7;
const size_t EIGHT = 8;
const size_t NINE = 9;
const size_t TEN = 10;
const size_t ELEVEN = 11;
const size_t SIXTEEN = 16;
const size_t TWENTY_FOUR = 24;

unsigned char ToBytes(size_t size, size_t position) {
    unsigned char bytes[4];
    bytes[0] = size;
    bytes[1] = size >> EIGHT;
    bytes[2] = size >> SIXTEEN;
    bytes[3] = size >> TWENTY_FOUR;
    return bytes[position];
}

void Image::Create(const char *path) const {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка: файл не может быть открыт. \n");
    }
    unsigned char addition[3] = {0, 0, 0};
    size_t addition_count = (4 - (columns_ * 3) % 4) % 4;
    const size_t file_header_size = 14;
    const size_t information_header_size = 40;
    size_t file_size = file_header_size + information_header_size + lines_ * columns_ * 3 + addition_count * lines_;
    unsigned char file_header[file_header_size] = {'B',
                                                   'M',
                                                   ToBytes(file_size, 0),
                                                   ToBytes(file_size, 1),
                                                   ToBytes(file_size, 2),
                                                   ToBytes(file_size, 3),
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   file_header_size + information_header_size};
    unsigned char information_header[information_header_size] = {information_header_size,
                                                                 0,
                                                                 0,
                                                                 0,
                                                                 ToBytes(columns_, 0),
                                                                 ToBytes(columns_, 1),
                                                                 ToBytes(columns_, 2),
                                                                 ToBytes(columns_, 3),
                                                                 ToBytes(lines_, 0),
                                                                 ToBytes(lines_, 1),
                                                                 ToBytes(lines_, 2),
                                                                 ToBytes(lines_, 3),
                                                                 1,
                                                                 0,
                                                                 TWENTY_FOUR};
    file.write(reinterpret_cast<char *>(file_header), file_header_size);
    file.write(reinterpret_cast<char *>(information_header), information_header_size);
    for (size_t i = 0; i < lines_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            unsigned char red = static_cast<unsigned char>(GetColor(i, j).red * NORM_COLOR);
            unsigned char green = static_cast<unsigned char>(GetColor(i, j).green * NORM_COLOR);
            unsigned char blue = static_cast<unsigned char>(GetColor(i, j).blue * NORM_COLOR);
            unsigned char color[] = {blue, green, red};
            file.write(reinterpret_cast<char *>(color), 3);
        }
        file.write(reinterpret_cast<char *>(addition), static_cast<std::streamsize>(addition_count));
    }
    file.close();
}

void Image::Read(const char *path) {
    std::ifstream file;
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка: файл не может быть открыт. \n");
    }
    const size_t file_header_size = 14;
    const size_t information_header_size = 40;
    unsigned char file_header[file_header_size];
    file.read(reinterpret_cast<char *>(file_header), file_header_size);
    if (file_header[0] != 'B' || file_header[1] != 'M') {
        throw std::runtime_error("Ошибка: неправильный файл. \n");
    }
    unsigned char information_header[information_header_size];
    file.read(reinterpret_cast<char *>(information_header), information_header_size);
    columns_ = information_header[4] + (information_header[FIVE] << EIGHT) + (information_header[SIX] << SIXTEEN) +
               (information_header[SEVEN] << TWENTY_FOUR);
    lines_ = information_header[EIGHT] + (information_header[NINE] << EIGHT) + (information_header[TEN] << SIXTEEN) +
             (information_header[ELEVEN] << TWENTY_FOUR);
    colors_.resize(columns_ * lines_);
    size_t addition_count = (4 - (columns_ * 3) % 4) % 4;
    for (size_t i = 0; i < lines_; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            unsigned char color[3];
            file.read(reinterpret_cast<char *>(color), 3);
            colors_[columns_ * i + j].red = static_cast<float>(color[2]) / NORM_COLOR;
            colors_[columns_ * i + j].green = static_cast<float>(color[1]) / NORM_COLOR;
            colors_[columns_ * i + j].blue = static_cast<float>(color[0]) / NORM_COLOR;
        }
        file.ignore(static_cast<std::streamsize>(addition_count));
    }
    file.close();
}

size_t Image::GetLines() const {
    return lines_;
}

size_t Image::GetColumns() const {
    return columns_;
}

std::vector<Color> Image::GetColors() {
    return colors_;
}

void Image::SetLines(size_t new_lines) {
    std::vector<Color> new_colors(new_lines * columns_);
    for (size_t i = 0; i < new_lines; ++i) {
        for (size_t j = 0; j < columns_; ++j) {
            new_colors[columns_ * i + j] = colors_[columns_ * (i + (lines_ - new_lines)) + j];
        }
    }
    lines_ = new_lines;
    colors_ = new_colors;
}

void Image::SetColumns(size_t new_columns) {
    std::vector<Color> new_colors(lines_ * new_columns);
    for (size_t i = 0; i < lines_; ++i) {
        for (size_t j = 0; j < new_columns; ++j) {
            new_colors[new_columns * i + j] = colors_[columns_ * i + j];
        }
    }
    colors_ = new_colors;
    columns_ = new_columns;
}

void Image::SetAllColors(std::vector<Color> new_colors) {
    colors_ = new_colors;
}

Image::Image() : lines_(0), columns_(0) {
}
