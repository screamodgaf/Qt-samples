#ifndef GAME_H
#define GAME_H
#include "youtube.h"
#include <QObject>
#include "sitedownloader.h"
class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
public slots:
    void request();
signals:
private:
    QTcpSocket* socket = nullptr;
    Youtube* youtube = nullptr;
    QString s, s1, s2, s3, s4;
    std::vector<QString> v_lines;

    SiteDownloader* siteDownloader = nullptr;
};

#endif // GAME_H
