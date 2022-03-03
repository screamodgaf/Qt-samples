#ifndef DATASINGLETON_H
#define DATASINGLETON_H
#include "player.h"

class DataSingleton
{
public:
    DataSingleton() = delete;
    static DataSingleton& get();

private:
    static DataSingleton instance;
};

#endif // DATASINGLETON_H
