#include "datasingleton.h"


DataSingleton &DataSingleton::get()
{
    return instance;
}
