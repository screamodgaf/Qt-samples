#include "sitedownloader.h"
#include "termcolor.hpp"
#include "extract_nickandroom.h"
SiteDownloader::SiteDownloader(QObject *parent) :
    QObject(parent)
{
    //connect must be called only once!
    connect(  &manager, SIGNAL (finished(QNetworkReply*)),
              this, SLOT (fileDownloaded(QNetworkReply*)) );

    connect(this, SIGNAL(downloaded()), this, SLOT(downloadedData()));
}


void SiteDownloader::makeRequest(QUrl imageUrl)
{
    std::cout << termcolor::on_red << "SiteDownloader::makeRequest(QUrl imageUrl)" << termcolor::reset<< std::endl;

    qDebug()<< "imageUrl: " << imageUrl;

    QNetworkRequest request(imageUrl);
    manager.get(request);

}


SiteDownloader::~SiteDownloader() {
    std::cout << "~SiteDownloader::~SiteDownloader() { " << "\n";
}

void SiteDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();
   qDebug() << "fileDownloaded";


    //emit a signal
    pReply->deleteLater();

    emit downloaded();
}

void SiteDownloader::downloadedData() const { //repeats
    qDebug() << "downloadedData()";

    std::string website = m_DownloadedData.toStdString();

    if(website.size()!=0)
    {
        Parser parser;
        std::string title = parser.extract_tagContent(website, "title");
//        clearWeirdSigns(title);
        std::cout << termcolor::red << "3 "<< title << termcolor::reset<< std::endl;

        //        title = "\x02\x03""04" +title + "\x02";
        title = "\u00034" +title;

        std::string begTag = "<meta name=\"keywords\" content=\"";
        std::string endTag = "\">";

        std::string keywords = "\x03""12 | \x03""13 Tags: \u000312";
        keywords +=  parser.findYoutubeKeywords(begTag, endTag, website);
        if(keywords.find("film, udostępnianie, telefon z aparatem, telefon z kamerą, bezpłatnie")!=std::string::npos)
            keywords = " \x03""12 | \u00039Nie ma tagów";
        if(keywords != " \x03""12 | \u000399Nie ma tagów")
//            limitLengthOfYoutubeKeywords(keywords,130);

        std::cout << termcolor::red << title << termcolor::reset<< std::endl;

        title+= keywords;

        std::cout << termcolor::on_cyan << "title: " << title << termcolor::reset<< std::endl;

//        postToIRC(title); //post to IRC
    }else
        std::cout << termcolor::on_cyan << "website empty" << termcolor::reset<< std::endl;


}





QString SiteDownloader::checkKeyword(QString data)
{
    std::cout << termcolor::yellow<< "Youtube::checkKeyword" << termcolor::reset<< std::endl;

    QString indexCore;
    //std::cout << termcolor::yellow << "Youtube::provideData: " << this->thread()->currentThreadId() << termcolor::reset<< std::endl;

    if(data.indexOf("www.youtu")!=-1)
    {
        std::cout << "'www.youtu' Found" << "\n";
        Extract_NickAndRoom extract;
        room = extract.extractRoom(data);

        int indexBegin = data.indexOf("www.youtube"); //6
        //int indexEnd = data.indexOf(" "); //cant be  "\r\n" cause i dont want the end of the line but end of youtube link

        int indexEnd;
        if(data.indexOf(" ")!=-1)
            indexEnd = data.indexOf(" ");
        else
            indexEnd = data.indexOf("\r\n");

        indexCore = data.mid(indexBegin,(indexEnd -(indexBegin) ));
        qDebug()<< "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<indexCore;
        return indexCore ;

    }
    else if(data.indexOf("youtu.be")!=-1)
    {

        Extract_NickAndRoom extract;
        room = extract.extractRoom(data);

        int indexEnd;
        int indexBegin = data.indexOf("youtu.be"); //6
        if(data.indexOf(" ")!=-1)
            indexEnd = data.indexOf(" ");
        else
            indexEnd = data.indexOf("\r\n");

        indexCore = data.mid(indexBegin,(indexEnd -(indexBegin) ));
        qDebug()<< "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<indexCore;

        return indexCore ;
    }
    else
    {
        return "noLink";
    }
}

void SiteDownloader::limitLengthOfYoutubeKeywords(std::string& text, size_t limit)
{
    Parser p;
    text = p.limitKeysLength(text, limit);

}

void SiteDownloader::postToIRC(std::string newsText)
{
    std::cout << termcolor::yellow << "postToIRC" << termcolor::reset<< std::endl;
    std::string lineToPost;
    lineToPost = "PRIVMSG " + room + " :" + newsText + "\r\n ";
    emit sendYoutubeInfo(QByteArray::fromStdString(lineToPost));


}
