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
#include "parse_xml.h"

#include <iostream>
#include <fstream>

#include <tinyxml2.h>

#include "search_item.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) (a_eResult == XML_SUCCESS)
#endif

void parseSearchItemAttributesXml(XMLElement * pEle, SearchItem& searchItem)
{
    const XMLAttribute* attribute = pEle->FirstAttribute();

    while (attribute)
    {
        std::string name{attribute->Name()};
        std::string value{attribute->Value()};
        if (name == "color")
        {
            searchItem.fg_color = Np2InternalColor.at(value);
        }
        else if (name == "bgColor")
        {
            searchItem.bg_color = Np2InternalColor.at(value);
        }
        else if (name == "doSearch" && value == "false")
        {
            searchItem.active = false;
        }
        else if (name == "searchType")
        {
            if (value == "regex")
            {
                searchItem.type = SearchItem::Type::RegExp;
            }
        }
        else if (name == "matchCase" && value== "true")
        {
            searchItem.caseSensitive = true;
        }
        else if (name == "hide" && value == "true")
        {
            searchItem.hide = true;
        }
        attribute = attribute->Next();
    }
}

void parseFilterXml(const std::string& filename, std::vector<SearchItem>& searchItems)
{
    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile(filename.c_str());
    if (!XMLCheckResult(eResult)) {
        std::cerr << "XML Parsing error: " << eResult << "\n";
        return;
    }

    XMLElement * pNode = xmlDoc.FirstChildElement();
    std::string name{pNode->Name()};
    if (name == "AnalyseDoc")
    {
        pNode = pNode->FirstChildElement();
        while (pNode)
        {
            name.assign(pNode->Name());
            if (name == "SearchText")
            {
                SearchItem searchItem;
                searchItem.text = pNode->GetText();

                parseSearchItemAttributesXml(pNode, searchItem);

                if (searchItem.active)
                {
                    std::regex::flag_type options = std::regex_constants::egrep | std::regex_constants::optimize;
                    if (!searchItem.caseSensitive)
                    {
                        options |= std::regex_constants::icase;
                    }
                    if (searchItem.type == SearchItem::Type::RegExp)
                    {
                        searchItem.regex.reset(new std::regex{searchItem.text, options});
                    }
                    searchItems.push_back(std::move(searchItem));
                }
            }
            pNode = pNode->NextSiblingElement();
        }
    }
}
