#include <getopt.h>
#include <iomanip>
#include <iostream>

#include "color.h"
#include "parse_xml.h"
#include "search_item.h"

void print_help()
{
    std::cout << "Example Usage:\n";
    std::cout << "cat can.log | ./filter -f canfilter.xml\n";
    std::cout << "Filters stdin based on rules defined in xml File. XML Format should follow that of notepad++ Analysis plugin.\n\n";
    std::cout << "-f <xmlfile>  Filter XML file\n";
    std::cout << "-c            Activate color output\n";
    std::cout << "-l            Activate linenumber output\n";
}

int main(int argc, char** argv)
{
    bool color = false;
    bool lines = false;
    std::string             filterFilename;
    std::ios_base::sync_with_stdio(false);
    std::vector<SearchItem> searchItems;

    if (argc <= 1) 
    {
        print_help();
        return 1;
    }

    for (;;)
    {
        switch (getopt(argc, argv, "clhf:"))
        {
            case '?':
            case 'h':
            default:
                print_help();
                break;

            case -1:
                break;

            case 'f':
                filterFilename.assign(optarg);
                continue;

            case 'c':
                color = true;
                continue;

            case 'l':
                lines = true;
                continue;
        }

        break;
    }

    if (filterFilename.empty()) {
        std::cout << "No filter file provided but mandatory.\n";
        print_help();
        return 1;        
    }

    try
    {
        parseFilterXml(filterFilename, searchItems);
    }
    catch (...)
    {
        std::cout << "Error: File " << filterFilename << " not found or could not be parsed!\n";
        return -2;
    }

    unsigned int linenum = 0;
    for (std::string line; std::getline(std::cin, line);)
    {
        ++linenum;
        for (const auto& item : searchItems)
        {
            if ((item.type == SearchItem::Type::PlainText && line.find(item.text) != std::string::npos) ||
                (item.type == SearchItem::Type::RegExp && std::regex_search(line, *(item.regex))))
            {
                if (item.hide == false)
                {
                    if (lines)
                        std::cout << std::setw(8) << linenum << ": ";
                    if(color && item.fg_color != Color::None) {
                        std::cout << "\033[0;" << Internal2ConsoleBgColor.at(item.bg_color) << ";" << Internal2ConsoleFgColor.at(item.fg_color) << "m" << line << "\033[0m";
                    }
                    else{
                        std::cout << line;
                    }
                    std::cout << "\n";
                }
                break;
            }
        }
    }

    return 0;
}
