#include <iostream>

namespace utils {
template <class T>
T* getmid(T& l, T& m, T& r, bool comp(const T&, const T&))
{
    if ((comp(m, l) || comp(r, l)) && (comp(l, r) || comp(l, m)))
        return &l;
    if ((comp(l, m) || comp(r, m)) && (comp(m, r) || comp(m, l)))
        return &m;
    return &r;
}

template <class T>
size_t partition(T* arr, int l, int r, bool comp(const T&, const T&))
{
    T* pivot = (T*)0;
    if (l + 2 < r)
        pivot = getmid(arr[l], arr[(l + r) / 2], arr[r - 1], comp);
    else
        pivot = &arr[l];
    std::swap(*pivot, arr[r - 1]);

    size_t i = l;
    while (comp(arr[i], arr[r - 1]))
        ++i;

    int j = i;
    while (j < r - 1) {
        if (comp(arr[j], arr[r - 1]))
            std::swap(arr[i++], arr[j]);
        ++j;
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
}

template <class T>
T getKstat(T* arr, int l, int r, int k, bool comp(const T&, const T&))
{
    size_t pivotPos = 0;

    while (pivotPos = partition(arr, l, r, comp), pivotPos != k)
        (pivotPos < k) ? l = pivotPos + 1 : r = pivotPos;

    return arr[pivotPos];
}
} // namespace utils

template <class T>
bool comp(const T& l, const T& r)
{
    return l < r;
}

typedef unsigned long long bigint;

int main()
{
    int arrsize = 0;
    std::cin >> arrsize;
    bigint* arr = new bigint[arrsize];

    for (size_t i = 0; i < arrsize; ++i)
        std::cin >> arr[i];

    std::cout << utils::getKstat<bigint>(arr, 0, arrsize, arrsize * .1, comp<bigint>) << std::endl;
    std::cout << utils::getKstat<bigint>(arr, 0, arrsize, arrsize * .5, comp<bigint>) << std::endl;
    std::cout << utils::getKstat<bigint>(arr, 0, arrsize, arrsize * .9, comp<bigint>) << std::endl;

    delete[] arr;
    return 0;

    // int arr[5] = { 1, 2, 3, 4, 5 };
    // int *t = utils::getmid(arr[0], arr[4], arr[3], comp);
    // std::cout << *t << std::endl;
}
