// MIT License

// Copyright (c) 2021 Andreas Evers

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include "color.h"

const std::map<std::string, Color> Np2InternalColor{
    {"black", Color::Black},
    {"white", Color::White},
    {"darkGrey", Color::Black},
    {"liteGrey", Color::White},
    {"grey", Color::Black},
    {"red", Color::Red},
    {"liteRed", Color::Bright_Red},
    {"yellow", Color::Bright_Yellow},
    {"orange", Color::Yellow},
    {"darkYellow", Color::Yellow},
    {"darkRed", Color::Red},
    {"offWhite", Color::White},
    {"brown", Color::Red},
    {"liteBeige", Color::White},
    {"beige", Color::White},
    {"deepPurple", Color::Magenta},
    {"purple", Color::Magenta},
    {"pink", Color::Bright_Magenta},
    {"darkBlue", Color::Blue},
    {"veryLiteBlue", Color::Bright_Cyan},
    {"blue", Color::Bright_Blue},
    {"cyan", Color::Cyan},
    {"liteBlue", Color::Cyan},
    {"darkGreen", Color::Green},
    {"blueGreen", Color::Bright_Green},
    {"liteGreen", Color::Bright_Green},
    {"green", Color::Bright_Green},
    {"veryLiteGrey", Color::White},
    {"litePink", Color::Bright_Magenta},
    {"veryLitePurple", Color::Bright_Magenta},
};

const std::map<Color, std::string> Internal2ConsoleBgColor{       {Color::None, "40"},
                                                                  {Color::Black, "40"},
                                                                  {Color::Red, "41"},
                                                                  {Color::Green, "42"},
                                                                  {Color::Yellow, "43"},
                                                                  {Color::Blue, "44"},
                                                                  {Color::Magenta, "45"},
                                                                  {Color::Cyan, "46"},
                                                                  {Color::White, "47"},
                                                                  {Color::Bright_Red, "101"},
                                                                  {Color::Bright_Green, "102"},
                                                                  {Color::Bright_Yellow, "103"},
                                                                  {Color::Bright_Blue, "104"},
                                                                  {Color::Bright_Magenta, "105"},
                                                                  {Color::Bright_Cyan, "106"}};

const std::map<Color, std::string> Internal2ConsoleFgColor{
    {Color::Black, "30"},          {Color::Red, "31"},           {Color::Green, "32"},
    {Color::Yellow, "33"},         {Color::Blue, "34"},          {Color::Magenta, "35"},
    {Color::Cyan, "36"},           {Color::White, "37"},         {Color::Bright_Red, "91"},
    {Color::Bright_Green, "92"},   {Color::Bright_Yellow, "93"}, {Color::Bright_Blue, "94"},
    {Color::Bright_Magenta, "95"}, {Color::Bright_Cyan, "96"},   {Color::None, "37"}};
