#include <QApplication>
#include <game.h>
int main(int argc, char *argv[])
{
    srand (static_cast <unsigned> (time(0))); // Seed the time

    QApplication a(argc, argv);
    Game game;
    return a.exec();
}
