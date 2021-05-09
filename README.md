# Filter

Command line filter tool using [Notepad++ Analysis Plugin](https://sourceforge.net/projects/analyseplugin/) 
XML files as rule for filtering.
You can think of it as a grep that gets its rules and regular expressions from an XML file.

```
filter: Filters stdin based on rules defined in xml File. XML Format should follow that of notepad++ Analysis plugin.
Synopsis: filter -f <xmlfile> [-c] [-l] [-h]

-h            Show this help
-f <xmlfile>  XML file with filter rules
-c            Activate color output
-l            Activate linenumber output

Example Usage:
cat can.log | filter -f canfilter.xml
```

# License

See [LICENSE](LICENSE)

# Dependencies

The following libraries should be installed to run and build:
* tinyxml2

# Build

* Clone this repository
* cd filter
* mkdir _build && cd _build
* cmake ..
* make  (or make install)

Example:

```text
aevers@homer:~/dev/filter(master)$ mkdir _build
aevers@homer:~/dev/filter(master)$ cd _build/
aevers@homer:~/dev/filter/_build(master)$ cmake ..
-- The C compiler identification is GNU 10.2.0
-- The CXX compiler identification is GNU 10.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/aevers/dev/filter/_build

aevers@homer:~/dev/filter/_build(master)$ make install
[ 50%] Building CXX object CMakeFiles/filter.dir/src/main.cpp.o
[ 50%] Building CXX object CMakeFiles/filter.dir/src/parse_xml.cpp.o
[ 75%] Building CXX object CMakeFiles/filter.dir/src/color.cpp.o
[100%] Linking CXX executable filter
[100%] Built target filter
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/bin/filter
aevers@homer:~/dev/filter/_build(master)$
```

# XML Format

The XML file with the filter rules has to follow the format defined by
the [Notepad++ AnalysePlugin](https://sourceforge.net/projects/analyseplugin/)  by Mattes H.

The format is described [here](https://sourceforge.net/p/analyseplugin/code/HEAD/tree/trunk/AnalyseDoc.xsd)

Here is an example:
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<AnalyseDoc xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="./AnalyseDoc.xsd">
    <SearchText color="black" bgColor="red">texlive</SearchText>
    <SearchText color="black" bgColor="green" searchType="regex">^d[a-z]+ [0-9.-]+1$</SearchText>
    <SearchText searchType="regex">0.0-1$</SearchText>
</AnalyseDoc>
```

The easiest way to configure a filter is to actually use the Notepad++ plugin and store the XML filters with it.

# Feature support

Supported attributes of 'SearchText'

* hits - NOT supported
* group - NOT supported
* searchType - See [support](#searchtype)
* matchCase - Supported
* wholeWord - NOT supported
* select - NOT supported
* hide - Supported
* bold - NOT supported
* italic - NOT supported
* underlined - NOT supported
* color - See [support](#colors)
* bgColor - See [support](#colors)
* comment - Ignored

## SearchType

Currently 'normal' and 'regex' is supported as search type

## Colors

Currently the following 'color' and 'bgColor' values are supported
* black
* white
* darkGrey
* liteGrey
* grey
* red
* liteRed
* yellow
* orange
* darkYellow
* darkRed
* offWhite
* brown
* liteBeige
* beige
* deepPurple
* purple
* pink
* darkBlue
* veryLiteBlue
* blue
* cyan
* liteBlue
* darkGreen
* blueGreen
* liteGreen
* green
* veryLiteGrey
* litePink
* veryLitePurple

As the number of colors supported by shell with ANSI/VT100 control sequences is limited to 16 some of the above
XML colors are mapped to the same Shell color. You can find the mapping inside [color.cpp](src/color.cpp)
