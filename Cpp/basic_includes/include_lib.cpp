
#include "include_lib.h"

IncludeLib::IncludeLib() {
    value = 10;
    std::cout << "IncludeLib created!" << std::endl; 
}

IncludeLib::~IncludeLib() {
    std::cout << "IncludeLib destroyed!" << std::endl; 
}

void IncludeLib::PrintText()
{
    std::cout << "IncludeLib print text!" << std::endl; 
}
