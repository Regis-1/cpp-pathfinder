#include "lib.h"

#include <iostream>

void LibClass::greet(const std::string &name)
{
    std::cout << "Hello " << name << "!" << std::endl;
    std::cout << "Finished greeting from " << this->name << "." << std::endl;
}
