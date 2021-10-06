#ifndef COLOURMANIPULATION_H
#define COLOURMANIPULATION_H
#include <string>
#include <QString>
class ColourManipulation
{
public:
    ColourManipulation();
    std::string addColours(std::string& line);
    std::string removePolSigns(std::string& line);
};

#endif // COLOURMANIPULATION_H
