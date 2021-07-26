#include <iostream>
#include "date.hpp"
#include <time.h>



int main()
{   
    Date date;

    std::cout << Date::random_date() << "\n";
    return 0;
}