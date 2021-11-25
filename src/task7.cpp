#include <iostream>

int getdig(long long number, const size_t n)
{
    return number >> (n * 8) & 255;
}

void countSort(long long* buff, const size_t size, const size_t n)
{
    size_t countsize = 1 << 8;
    size_t countbuff[countsize] = { 0 };

    for (size_t i = 0; i < size; ++i)
        countbuff[getdig(buff[i], n)]++;

    for (size_t i = 0; i < countsize - 1; ++i)
        countbuff[i + 1] += countbuff[i];

    long long* tmp = new long long[size];

    for (int i = size - 1; i >= 0; --i)
        tmp[--countbuff[getdig(buff[i], n)]] = buff[i];

    for (size_t i = 0; i < size; ++i)
        buff[i] = tmp[i];

    delete[] tmp;
}

void LSDSort(long long* buff, size_t size)
{
    for (size_t b = 0; b < sizeof(long long); ++b)
        countSort(buff, size, b);
}

int main()
{
    size_t size = 0;
    std::cin >> size;
    if (size <= 0)
        return 0;

    long long* buff = new long long[size];
    for (size_t i = 0; i < size; ++i)
        std::cin >> buff[i];

    LSDSort(buff, size);

    for (size_t i = 0; i < size; ++i) {
        std::cout << buff[i];
        if (i + 1 < size)
            std::cout << " ";
    }
    std::cout << "\n";

    delete[] buff;

    return 0;
}
