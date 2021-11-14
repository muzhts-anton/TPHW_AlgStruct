#include <iostream>

ssize_t expSearch(size_t size, int* arr, int target)
{
    if (arr[0] == target)
        return 0;

    size_t i = 1;
    while (i < size && arr[i] < target)
        i <<= 1;

    return i;
}

ssize_t binSearch(int* arr, size_t left, size_t right, int key)
{
    size_t mid = 0;

    while (left <= right) {
        mid = (left + right) / 2;

        if (key == arr[mid]) {
            return mid;
        }

        if (key > arr[mid]) {
            if (key < arr[mid + 1])
                return (key - arr[mid] <= arr[mid + 1] - key) ? mid : mid + 1;
            left = mid + 1;
        } else {
            if (key > arr[mid - 1])
                return (key - arr[mid - 1] <= arr[mid] - key) ? mid - 1 : mid;
            right = mid;
        }
    }

    return -1;
}

ssize_t getTwin(size_t srcnum, int* src, int target)
{
    if (target < src[0])
        return 0;
    if (target > src[srcnum - 1])
        return srcnum - 1;

    ssize_t rightlim = expSearch(srcnum, src, target);
    if (rightlim == -1)
        return 0;

    size_t leftlim = rightlim >> 1;
    if (rightlim > srcnum - 1)
        rightlim = srcnum - 1;

    return binSearch(src, leftlim, rightlim, target);
}

int main()
{
    size_t srcnum = 0;
    std::cin >> srcnum;
    int* src = new int[srcnum];
    for (size_t i = 0; i < srcnum; ++i)
        std::cin >> src[i];

    size_t aimnum = 0;
    std::cin >> aimnum;
    int* aim = new int[aimnum];
    for (size_t i = 0; i < aimnum; ++i)
        std::cin >> aim[i];

    for (size_t i = 0; i < aimnum; ++i) {
        std::cout << getTwin(srcnum, src, aim[i]);
        if (i + 1 < aimnum)
            std::cout << " ";
    }

    delete[] src;
    delete[] aim;

    return 0;
}
