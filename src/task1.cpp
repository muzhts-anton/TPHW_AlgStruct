#include <iostream>

int main()
{
    std::cout << "Yo, give me N and K:\n> ";
    int num = 0;
    int byteplace = 0;
    std::cin >> num >> byteplace;
    if (byteplace < 0)
        return 1;

    int byte = 0;
    num >>= byteplace;
    byte = num & 1;
    std::cout << byte << std::endl;

    return 0;
}
