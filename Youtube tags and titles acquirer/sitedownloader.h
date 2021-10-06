#ifndef SITEDOWNLOADER_H
#define SITEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "parser.h"
class SiteDownloader : public QObject
{



 Q_OBJECT
 public:
  explicit SiteDownloader(QObject *parent = 0);
  virtual ~SiteDownloader();


public slots:
    void makeRequest(QUrl imageUrl);
    void downloadedData() const ;
 signals:
  void downloaded();
    void sendYoutubeInfo(QByteArray);
 private slots:

  void fileDownloaded(QNetworkReply* pReply);
  private:
  QNetworkAccessManager manager;
  QByteArray m_DownloadedData;

private:
  std::string room;

public:
  QString checkKeyword(QString data);
   void limitLengthOfYoutubeKeywords(std::string& text, size_t limit);

void postToIRC(std::string newsText);
};




#endif // SITEDOWNLOADER_H
