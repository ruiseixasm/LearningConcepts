#include "my_number.h"



MyNumber::MyNumber() : mynumber(0)
{

}

MyNumber::MyNumber(int number) : mynumber(number)
{

}

MyNumber::~MyNumber()
{

}


void MyNumber::PrintMynumber()
{
    std::cout << mynumber << std::endl;
}