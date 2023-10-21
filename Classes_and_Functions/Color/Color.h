#pragma once

struct Color {
    float red;
    float green;
    float blue;
    Color& operator=(const Color& color_second) = default;
    bool operator==(const Color& color_second) const = default;
    Color operator+(const Color& color_second);
    Color& operator+=(Color color_second);
    Color() = default;
    Color(float r, float g, float b);
    Color operator*(const float& number);
    Color& operator*=(const float& number);
};