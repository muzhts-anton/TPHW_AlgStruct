#include <iostream>

int main()
{
    std::cout << "Yo, give me N and K:\n";
    int num = 0, byteplace = 0;
    std::cin >> num >> byteplace;

    std::cout << ((num >> byteplace) & 1) << std::endl;

    return 0;
}
