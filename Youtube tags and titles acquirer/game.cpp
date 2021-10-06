#include "game.h"
#include "qtcpsocket.h"
#include <QTimer>
#include <termcolor.hpp>
#include <vector>
#include <ctime>

int iteracja =0 ;
Game::Game(QObject *parent) : QObject(parent)
{
    srand(time(nullptr));

     s  = ":memphis PRIVMSG #programming \u000300:EmoGore <a href=\\\"https://www.youtube.com/watch?v=J424JTnM-a4\\\">http://www.youtube.com/watch?v=J424JTnM-a4\r\n";
    s1  = ":memphis PRIVMSG #programming \u000300:EmoGore <a href=\\\"https://www.youtube.com/watch?v=zz7K9w89_R0\\\">http://www.youtube.com/watch?v=zz7K9w89_R0\r\n";
    s2  = ":memphis PRIVMSG #programming \u000300:EmoGore <a href=\\\"https://www.youtube.com/watch?v=Ry2NBKMlksI\\\">http://www.youtube.com/watch?v=Ry2NBKMlksI\r\n";
    s3  = ":memphis PRIVMSG #programming \u000300:EmoGore <a href=\\\"https://www.youtube.com/watch?v=ZFz9ATsTuPc\\\">https://www.youtube.com/watch?v=ZFz9ATsTuPc\r\n";
    s4  = ":memphis PRIVMSG #programming \u000300:EmoGore <a href=\\\"https://www.youtube.com/watch?v=r9-42mu1D9Y\\\">http://www.youtube.com/watch?v=r9-42mu1D9Y\r\n";

//         s  = ":memphis PRIVMSG #programming http://www.youtube.com/watch?v=J424JTnM-a4";
//        s1  = ":memphis PRIVMSG #programming http://www.youtube.com/watch?v=zz7K9w89_R0";
//        s2  = ":memphis PRIVMSG #programming http://www.youtube.com/watch?v=Ry2NBKMlksI";
//        s3  = ":memphis PRIVMSG #programming https://www.youtube.com/watch?v=ZFz9ATsTuPc";
//        s4  = ":memphis PRIVMSG #programming http://www.youtube.com/watch?v=r9-42mu1D9Y";

    v_lines = {s, s1,s2,s3,s4};

    socket = new QTcpSocket;

//    youtube = new Youtube(this);
    siteDownloader =  new SiteDownloader();
    QTimer* timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(request()));
    timer->start(4000);

}
void Game::request( )
{
        std::cout << termcolor::on_red << "$$$========= NEW ITERATION ===========" << termcolor::reset<< std::endl;
        std::cout << "========= iteracja " << ++iteracja << " =========" << "\n";

        int r = std::rand()%4;

        auto indexCore = siteDownloader->checkKeyword(v_lines[r]);


        std::string s_index = indexCore.toStdString();
        size_t beg = 0;
        size_t beg2 = 0;
        if((s_index.find("https://"))==std::string::npos && s_index.find("http://")==std::string::npos)
            s_index = "https://" +  s_index;
        if((beg2 = s_index.find("https://"))==std::string::npos && beg2 >0 && s_index.find("http://")==std::string::npos)
            s_index = "https://" +  s_index;

        if((beg=s_index.find("\">http"))!=std::string::npos)
            s_index = s_index.substr(0, beg-1);

        if((s_index.find("https://"))==std::string::npos && s_index.find("http://")==std::string::npos)
            s_index = "https://" +  s_index;

        size_t hbeg =0;
        if((hbeg = s_index.find("http://"))!= std::string::npos)
            s_index.replace(hbeg, 7  , "https://");


        QUrl urlForCookies (QString::fromStdString(s_index));
        std::cout << termcolor::on_cyan << "ZAPYTANIOE s_index: " << s_index << termcolor::reset<< std::endl;


        std::cout << "siteDownloader->makeRequest(urlForCookies);" << "\n";
       siteDownloader->makeRequest(urlForCookies);
}


