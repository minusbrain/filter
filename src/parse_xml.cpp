#include "parse_xml.h"

#include <fstream>

#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/NamedNodeMap.h"
#include "Poco/DOM/NodeFilter.h"
#include "Poco/DOM/NodeIterator.h"
#include "Poco/SAX/InputSource.h"

#include "search_item.h"

void parseSearchItemAttributesXml(const Poco::XML::Node* pNode, SearchItem& searchItem)
{
    Poco::XML::NamedNodeMap* attributes = nullptr;
    if (pNode->hasAttributes())
    {
        attributes = pNode->attributes();

        for (unsigned int i = 0; i < attributes->length(); i++)
        {
            Poco::XML::Node* attribute = attributes->item(i);
            if (attribute->nodeName() == "color")
            {
                searchItem.fg_color = Np2InternalColor.at(attribute->nodeValue());
            }
            else if (attribute->nodeName() == "bgColor")
            {
                searchItem.bg_color = Np2InternalColor.at(attribute->nodeValue());
            }
            else if (attribute->nodeName() == "doSearch" && attribute->nodeValue() == "false")
            {
                searchItem.active = false;
            }
            else if (attribute->nodeName() == "searchType")
            {
                if (attribute->nodeValue() == "regex")
                {
                    searchItem.type = SearchItem::Type::RegExp;
                }
            }
            else if (attribute->nodeName() == "matchCase" && attribute->nodeValue() == "true")
            {
                searchItem.caseSensitive = true;
            }
            else if (attribute->nodeName() == "hide" && attribute->nodeValue() == "true")
            {
                searchItem.hide = true;
            }
        }
    }

    if (attributes != nullptr)
    {
        attributes->release();
    }
}

void parseFilterXml(const std::string& filename, std::vector<SearchItem>& searchItems)
{
    std::ifstream                      infile{filename, std::ifstream::in};
    Poco::XML::InputSource             src(filename);
    Poco::XML::DOMParser               parser;
    Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parse(&src);
    Poco::XML::NodeIterator            it(pDoc, Poco::XML::NodeFilter::SHOW_ALL);
    Poco::XML::Node*                   pNode = it.nextNode();
    while (pNode)
    {
        if (pNode->nodeName() == "SearchText")
        {
            SearchItem searchItem;
            searchItem.text = pNode->innerText();

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
        pNode = it.nextNode();
    }
}
