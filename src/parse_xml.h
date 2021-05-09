#pragma once
#include <string>
#include <vector>

struct SearchItem;

void parseFilterXml(const std::string& filename, std::vector<SearchItem>& searchItems);
