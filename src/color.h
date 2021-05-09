#pragma once

#include <map>
#include <string>

enum class Color
{
    None,
    Black,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Bright_Red,
    Bright_Green,
    Bright_Yellow,
    Bright_Blue,
    Bright_Magenta,
    Bright_Cyan
};

extern const std::map<std::string, Color> Np2InternalColor;
extern const std::map<Color, std::string> Internal2ConsoleBgColor;
extern const std::map<Color, std::string> Internal2ConsoleFgColor;
