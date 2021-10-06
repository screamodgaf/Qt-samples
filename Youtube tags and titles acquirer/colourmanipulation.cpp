#include "colourmanipulation.h"
#include <vector>
#include <algorithm>
#include <QString>
#include <iostream>
ColourManipulation::ColourManipulation()
{

}

std::string ColourManipulation::addColours(std::string& line)
{
    std::cout << "LINE I GET IN COLOURS: " << line << std::endl;
//QString q = QString::fromStdString(line);
//q.replace("ą", "a");

// \x02 bold



    std::vector<std::string> coloursOrg =
    {

//"\x03""06"  hmm
// o ty masz zapisane tez jako \xyy i to jest ok, ale musza byc zawsze dwie a masz czasem tylko jedna

        "\x03\x36",
        "\x03\x35",
        "\x03\x34",
        "\x02",
        "\x03\x34",
        "\x03\x36",
        "\x03\x35",
        "\x03\x34",
        "\x02",
        "\x03\x34",
        "\x03\x31\x33",

    };

    std::vector<std::string> coloursOst =
    {
        //"\x03""06"  hmm
        "\x03""04",
        "\x03""13",
        "\x03""06",
        "\x03""04",
        "\x03""13",
        "\x03""06",
        "\x03""04",
        "\x03""13",
        "\x03""06",
        "\x03""04",
        "\x03""13",
        "\x03""06",

        "\u000304",
        "\u000313",
        "\u000307",
        "\u000302",
        "\u000303",
        "\u000311",

    };


    std::vector<std::string> colours22 =
    {
        "\x02",
        "\x02",
        "\x03""01",
        "\x03""02",
                "\x02",
        "\x03""03",
        "\x03""04",
        "\x03""05",
        "\x03""06",
          "\x02",
        "\x03""07",
        "\x03""08",
        "\x03""09",
          "\x02",
        "\x03""10",
        "\x03""11",
        "\x03""12",
          "\x02",
        "\x03""13",
        "\x02",
        "\x02",
        "\x02",
        "\x03""13",
        "\x02",
        "\x02",
        "\x02",        "\x03""03",
        "\x03""04",
        "\x03""05",
        "\x03""06",
        "\x02",
        "\x02",
        "\x02",
        "\x02",

    };

    std::vector<std::string> colours =
    {
        "\x03""05",
        "\x03""06",
        "\x03""04",
        "\x03""12",
        "\x03""13",
        "\x02",

        "\x03""04",
        "\x03""12",
         "\x02",
        "\x03""13",
    };
   std::random_shuffle(colours.begin(), colours.end());

 int counter = 0;
//si─Öw─ům czegos   się wąm czegoś


 //from end:
         for (int i = line.size()-15; i < line.size(); i++)
         {
             try {


                 if((unsigned int)line[i]<127 )
                    line.insert(++i, colours[counter]);
                 else
                    line.insert(i+=3, colours[counter]); // if current sign is part of polish sign move 2 forward to avoid putting in the middle. 2 forward cause insert[1, "Z"] puts z before what was previously on Z: now b so aZbc

                 if(colours[counter].size()==3) //if colour that is 3 bytes then move +1 so bold wont get in the middle of colour code (cause insert changes size)
                     i+=2;

                 if(++counter  >= colours.size() )
                     break;
             } catch (...)
             {
                 std::cout << "Error in Colour Manipulation try" << std::endl;
                 return "";
             }
         }




    std::vector<std::string> icons
    {
        "\xf0\x9f\x98\x87",
        "\xf0\x9f\xa5\xb3",
        "\xf0\x9f\xa4\x97",
        "\xf0\x9f\xa4\x91",
        "\xf0\x9f\x98\x8c",
        "\xf0\x9f\x98\xb7",
        "\xf0\x9f\xa5\xb0",
        "\xf0\x9f\x98\xb7",
        "\xf0\x9f\xa4\xac",
        "\xf0\x9f\xa4\xae",
        "\xf0\x9f\x98\xac",
        "\xf0\x9f\x99\x88",
        "\xf0\x9f\x99\x89",
        "\xf0\x9f\x99\x8a",
        "\xf0\x9f\x99\x8c",
        "\xf0\x9f\x91\xa9",
        "\xf0\x9f\x92\x80",
        "\xe2\x98\xa0",
        "\xf0\x9f\xa6\xb7",
        "\xf0\x9f\x98\x88",
        "\xf0\x9f\x92\x95",
        "\xf0\x9f\x92\x93",
        "\xf0\x9f\x92\x96",
        "\xf0\x9f\x92\x97",
        "\xf0\x9f\x92\x98",
        "\xf0\x9f\x92\x9d",
        "\xf0\x9f\x92\x9e",
        "\xf0\x9f\x92\x9f",
        "\xf0\x9f\x91\x99",
        "\xf0\x9f\x91\xa0",
        "\xf0\x9f\x91\xa1",
        "\xf0\x9f\x92\x84",
        "\xf0\x9f\x92\x85",
        "\xf0\x9f\x92\x8b",
        "🚿", "🛀", "🛁", "🚽", "🧻", "🧼", "🧽", "🧴", "💅", "🛒", "🔮", "💎", "💍", ",🎀",
        "🧡", "💛", "💚", "💙", "💜", "🖤", "❤", "♡", "♥",
        "💔", "🥀", "🤳", "💋", "💌", "💏", "💑", "👯", "💃", "🤰",
        " 🔞", " 🍎", " 🍑", " 🍒", " 🍌", " 🥒", " 🍆", " 🗡"

    };
    std::random_shuffle(icons.begin(), icons.end());
 



    //std::string i = " \xf0\x9f\x98\x87";
    //line.append(i);
    line+="\x03""03 ";
    line+=icons[1];
    line.push_back('\r\n');
    std::cout << "LINE in Coplours: " << line << std::endl;
    return line;
//https://donsnotes.com/tech/charsets/ascii.html

}

std::string ColourManipulation::removePolSigns(std::string &line)
{

//iso-8859-2 dziala

    QString q = QString::fromStdString(line);

std::cout << "COLOUR MANIPOUILATION INPUT: " << line << std::endl;



    std::string temp = q.toStdString();

    std::cout << "COLOUR MANIPOUILATION OUTPUT: " << temp << std::endl;
    return temp ;
}
