#ifndef EXTRACT_NICKANDROOM_H
#define EXTRACT_NICKANDROOM_H
#include <QObject>
#include <iostream>
class Extract_NickAndRoom
{
public:
    Extract_NickAndRoom();

    std::string extractNick(QString& data);
    std::string extractRoom(QString& data);
    std::string extractRoomFromJoin(const QString &data);
    std::string extractRoomFromDeparture(const QString &data);
    std::string extractText(QString& data);
    std::string extractTextWithoutN(QString &data);
    std::string extractTextfromNotice(QString &data, std::string &nick);
    std::string extractCleanedCommandWithoutN(QString &data);
    std::vector<std::string> extractCommandElements(QString data_, std::string command);
    float strFloat_toFloat(std::string strinput);
    std::string round_float_fToS(float money);
    std::string reduceZerosInFloatString(std::string i);

private:
    std::string nick;
    std::string room;
    std::string subText;
};

#endif // EXTRACT_NICKANDROOM_H
