#include "Color.h"

Color::Color(float r, float g, float b) : red(r), green(g), blue(b) {
}

Color &Color::operator+=(Color color_second) {
    red += color_second.red;
    green += color_second.green;
    blue += color_second.blue;
    return *this;
}

Color Color::operator+(const Color &color_second) {
    Color result = *this;
    result += color_second;
    return result;
}

Color &Color::operator*=(const float &number) {
    red *= number;
    green *= number;
    blue *= number;
    return *this;
}

Color Color::operator*(const float &number) {
    Color result = *this;
    result *= number;
    return result;
}