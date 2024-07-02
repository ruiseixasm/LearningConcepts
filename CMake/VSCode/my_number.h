#pragma once

#include <iostream>

class MyNumber
{
private:
    const int mynumber;
public:
    MyNumber();
    MyNumber(int number);
    ~MyNumber();
    void PrintMynumber();
};
