#include <iostream>

int main()
{
    unsigned int num = 0, byteplace = 0;
    std::cin >> num >> byteplace;

    std::cout << ((num >> byteplace) & 1) << std::endl;

    return 0;
}
