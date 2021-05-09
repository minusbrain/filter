#pragma once
#include <memory>
#include <regex>
#include <string>

#include "color.h"

struct SearchItem
{
    bool active;
    enum class Type
    {
        PlainText,
        RegExp
    } type;
    std::string                 text;
    std::unique_ptr<std::regex> regex;
    Color                       fg_color;
    Color                       bg_color;
    bool                        caseSensitive;
    bool                        hide;

    SearchItem()
        : active(true),
          type(Type::PlainText),
          text(""),
          regex(nullptr),
          fg_color(Color::None),
          bg_color(Color::None),
          caseSensitive(false),
          hide(false)
    {
    }
};
