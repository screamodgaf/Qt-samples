#include "extract_nickandroom.h"
#include <QDebug>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <termcolor.hpp>
Extract_NickAndRoom::Extract_NickAndRoom()
{
    nick = "";
    room = "";
    subText ="";
}



std::string Extract_NickAndRoom::extractNick(QString& data)
{
    std::string text = data.toStdString();
    if(text.find(":")!=std::string::npos &&
       text.find("!")!=std::string::npos)
    {
            size_t beginning = text.find_first_of(":");
            size_t exclamation = text.find_first_of(" ",beginning);
            nick = text.substr(beginning+1, exclamation-(beginning+1));

            size_t pos;
            if((pos = nick.find("@"))!=std::string::npos ||
               (pos = nick.find("%"))!=std::string::npos ||
               (pos = nick.find("+"))!=std::string::npos ||
               (pos = nick.find("!"))!=std::string::npos ||
               (pos = nick.find("~"))!=std::string::npos)
                nick = nick.erase(pos);
            //std::cout << nick << "\n";

    }
    return nick;

}

std::string Extract_NickAndRoom::extractRoom(QString &data)
{
    std::string text = data.toStdString();
    size_t posHash=0;
    size_t posColon=0;
    std::string room;
    bool privMSGisFound=false;
    bool colonisFound = false;
    if((posHash=text.find_first_of("#"))!=std::string::npos)
    {
        //std::cout << posPRIVMSG << "\n";
        privMSGisFound=true;
    }

    if((posColon=text.find_first_of(":", posHash))!=std::string::npos)
    {
        //std::cout << posColon << "\n";
        colonisFound = true;
    }

    if(privMSGisFound==true && colonisFound==true)
    {


        room=text.substr(posHash ,  (posColon-1)-(posHash ) );
        //std::cout << room  << "\n";
    }


    return room;
}

std::string Extract_NickAndRoom::extractRoomFromJoin(const QString &data)
{
    std::string text = data.toStdString();
    std::string temp = "";
    size_t posBeg = 0;
    size_t posEnd = 0;
    if((posBeg = text.find("JOIN :#"))!= std::string::npos &&
         text.find("PRIVMSG #")==std::string::npos)
    {
        posBeg+=7;
        posEnd = data.size()-1;
        temp  = text.substr(posBeg, posEnd);
        return temp;
    }
    else
        return ""; //returns empty


}

std::string Extract_NickAndRoom::extractRoomFromDeparture(const QString &data)
{
    std::string text = data.toStdString();
    std::string temp = "";
    size_t posBeg = 0;
    size_t posEnd = 0;
    if((posBeg = text.find("PART #"))!= std::string::npos
            && text.find("PRIVMSG #")==std::string::npos)
    {
        posBeg+=6;

        if((posEnd = text.find_first_of(' ',posBeg))!= std::string::npos){
            temp  = text.substr(posBeg, posEnd - posBeg);
            return temp;
        }

    }
    else
        return ""; //returns empty
}



std::string Extract_NickAndRoom::extractText(QString &data)
{
    std::string text = data.toStdString();
    size_t pos, pos2, pos3;
    std::string subText;
    if((pos=text.find("PRIVMSG #"))!=std::string::npos)
    {
        if((pos2=text.find(":",pos))!=std::string::npos)
        {
            subText = text.substr(pos2+1,text.size()-(pos2+1));
        }


        if((pos3=subText.find("\u0001ACTION "))!=std::string::npos)
        {
            subText = subText.substr(pos3+8 , subText.size()-3-(pos3+8));
        }
        //std::cout << subText<< "\n";
        return subText;
    }
    else
        return "";
}


std::string Extract_NickAndRoom::extractTextWithoutN(QString &data)
{
    std::string text = data.toStdString();
    size_t pos, pos2, pos3;
    std::string subText;
    if((pos=text.find("PRIVMSG #"))!=std::string::npos)
    {
        if((pos2=text.find(":",pos))!=std::string::npos)
        {
            subText = text.substr(pos2+1,text.size()-(pos2+3));//1
        }
        return subText;
    }
    else
        return "";
}

std::string Extract_NickAndRoom::extractCleanedCommandWithoutN(QString &data)
{
    std::string text = data.toStdString();
    size_t pos, pos2, pos3;
    std::string subText;
    if((pos=text.find("PRIVMSG #"))!=std::string::npos)
    {
        if((pos2=text.find(":",pos))!=std::string::npos)
        {
            subText = text.substr(pos2+1,text.size()-(pos2+3));//1
        }

        std::stringstream ss; // we only need first word - the command
        ss << subText;
        for (int i = 0; i < 1; ++i) {
            ss >>subText;
        }
        return subText;
    }
    else
        return "";
}

std::string Extract_NickAndRoom::extractTextfromNotice(QString &data_, std::string &nick)
{

    std::string data = data_.toStdString();
    size_t pos;
    std::string textReturn;
    std::string searched = "NOTICE " + nick + " :";
    if((pos=data.find(searched))!=std::string::npos)
    {
        textReturn = data.substr(pos + searched.size(), data.size()-(pos + searched.size()));
        std::cout << textReturn << "\n";

    }
    return textReturn;
}

std::vector<std::string> Extract_NickAndRoom::extractCommandElements(QString data_, std::string command)
{
    /*from data we have:  ":Kiki!~Kiki@380D1B81.E8B15BFB.E88F59CB.IP PRIVMSG #metal :!give 100\r\n"
      but we know our command is ex. "!give" so now we want to get the rest "100" */
    std::string data = data_.toStdString();

    size_t pos, pos2;
    std::string subText;
    std::vector<std::string> assetElements_v;

    if( (pos  = data.find(command)) ==std::string::npos &&
        (pos2 = data.find("\r\n",pos + command.size())) ==std::string::npos &&
         pos2 - (pos + command.size()+1)<=0)
    {
        /*return empty vector that will cause atomizeCommand() = false only when
          if in data command is not found, if "\r\n" is not found there
          and if command touches escape: "command\r\n" - cause then SIZE of element would be ZERO and it causes CRASH!
        */
            std::cout << termcolor::blue << "return assetElements_v;" << termcolor::reset<< std::endl;
            return assetElements_v;
    }
    subText = data.substr(pos + command.size()+1, pos2 - (pos + command.size()+1) );
    //std::cout << "sub: " <<  subText << std::endl;

    std::stringstream ss;
    ss <<subText;
    std::string word;
    while(ss >> word){
        assetElements_v.push_back(word);
    }
    std::cout << "Extract_NickAndRoom::extractCommandElements assetElements_v.size(): " << assetElements_v.size() << std::endl;
    return assetElements_v;
}


std::string Extract_NickAndRoom::round_float_fToS(float money)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << money;
    return ss.str();
}


std::string Extract_NickAndRoom::reduceZerosInFloatString(std::string i)
{
    std::cout << termcolor::on_cyan << "i: " << i << termcolor::reset<< std::endl;
    std::cout << "reduceZerosInFloatString: " << i  << std::endl;
    //instead of "emo 10.000000 farbyka" we get "emo 10.00 farbyka"
    std::stringstream ss;
    std::vector<std::string> temp_v;
    ss <<i; //whole line of "emo 10.000000 farbyka" we put into sstring
    std::string s;
    while (ss >> s) {
        temp_v.push_back(s);
    }

    std::string str_temp = temp_v[0] + " " ; //nick

    str_temp += round_float_fToS(std::stof(temp_v[2])) + " "; //money

    /*starting from i = 3 cause if i= 2 it was giving: "Kiki 1338.00 ma 1338.000000 fircoinów, a pozycję społeczną 0"
    and with i = 3 it's: "aaa 80.00 fircoinów, a pozycję społeczną 0"  */
    for (int i = 3; i < temp_v.size();   i++ ) {
       // if(i)
        str_temp+= temp_v[i] + " ";
    }
    return str_temp;
}
