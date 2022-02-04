/*
xmlcleaner.cpp

Copyright (c) 2022 Dawn Moore

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

int main()
{
    std::filesystem::path path = std::filesystem::current_path();
    std::string ext(".xml");
    std::string extCap(".XML");
    std::vector<std::filesystem::path> xmlsToRemove;

    // Iterate through current path and find xml files, then push them into xmlsToRemove path vector
    for (const auto& activePath : std::filesystem::recursive_directory_iterator(path))
    {
        if (activePath.path().extension() == ext || activePath.path().extension() == extCap)
        {
            xmlsToRemove.push_back(activePath);
            std::cout << "Found: " << activePath.path() << std::endl;
        }
    }

    // If XML files found, give user the option to remove, and if yes, remove all in xmlsToRemove vector.
    // If none found, prompt user to exit.
    if (xmlsToRemove.size())
    {
        std::cout << "Found " << xmlsToRemove.size() << " in directory " << path << ".\nRemove ? Y / N" << std::endl;
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "Y")
        {
            std::cout << "Cleaning..." << std::endl;

            for (int i = 0; i < xmlsToRemove.size(); i++)
            {
                std::filesystem::remove(xmlsToRemove[i]);
            }
        }
    }
    else
    {
        std::cout << "Found no XML files in " << path << " to remove.\nPress enter to exit." << std::endl;
        std::cin.get();
    }
}
