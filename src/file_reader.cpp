#include "file_reader.h"
#include <iostream>

flaber::file_reader* flaber::file_reader::instance= nullptr;;


flaber::file_reader *flaber::file_reader::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new flaber::file_reader();
    }
    return instance;
}
