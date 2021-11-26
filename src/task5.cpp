#include <iostream>

namespace utils {

template <class T, class TComparator = std::greater<T>>
void merge(T* arr, T* tmp, size_t l, size_t m, size_t r, TComparator comp = TComparator())
{
    size_t i = l;
    size_t j = m;
    size_t k = l;

    while (i < m || j < r)
        if ((comp(arr[j], arr[i]) || j == r) && i < m)
            tmp[k++] = arr[i++];
        else if ((comp(arr[i], arr[j]) || i == m) && j < r)
            tmp[k++] = arr[j++];
        else {
            tmp[k++] = arr[i++];
            tmp[k++] = arr[j++];
        }

    for (size_t s = l; s < r; ++s)
        arr[s] = tmp[s];
}

template <class T, class TComparator = std::greater<T>>
void mergeSort(T* arr, T* tmp, size_t l, size_t r, TComparator comp = TComparator())
{
    if (r - l > 1) {
        mergeSort(arr, tmp, l, (r - l) / 2 + l);
        mergeSort(arr, tmp, (r - l) / 2 + l, r);
        merge(arr, tmp, l, (r - l) / 2 + l, r);
    }
}

} // namespace utils

struct Date {
    Date() = default;
    Date(int day, int month, int year)
        : day(day)
        , month(month)
        , year(year)
    {
    }
    bool operator>(const Date& other) const;

    size_t day;
    size_t month;
    size_t year;
};

bool Date::operator>(const Date& other) const
{
    if (this->year > other.year)
        return true;
    if (this->year < other.year)
        return false;

    if (this->month > other.month)
        return true;
    if (this->month < other.month)
        return false;

    if (this->day > other.day)
        return true;
    return false;
}

struct DateCell {
    DateCell() = default;
    DateCell(int day, int month, int year, bool isfirst)
        : date(day, month, year)
        , isfirst(isfirst)
    {
    }
    bool operator>(const DateCell& other) const { return this->date > other.date; }

    Date date;
    bool isfirst;
};

size_t initdatesarr(DateCell* arr, int size)
{
    for (int i = 0; i < size; ++i) {
        bool isMeetable = true;

        size_t day, month, year;
        std::cin >> day >> month >> year;
        DateCell bdate(day, month, year, true);
        std::cin >> day >> month >> year;
        DateCell ddate(day, month, year, false);

        DateCell tmp = bdate;
        tmp.date.year += 80;
        if (ddate > tmp) {
            ddate = tmp;
            ddate.isfirst = false;
        }

        bdate.date.year += 18;
        if (!(ddate > bdate))
            isMeetable = false;

        if (isMeetable) {
            arr[i * 2] = bdate;
            arr[i * 2 + 1] = ddate;
        } else {
            --i;
            --size;
        }
    }

    return size;
}

size_t getmax(DateCell* dates, size_t size)
{
    int count = 0;
    size_t max = count;
    for (int i = 0; i < size; ++i) {
        (dates[i].isfirst) ? ++count : --count;
        if (count > max)
            max = count;
    }
    return max;
}

int main()
{
    int n;
    std::cin >> n;

    DateCell* dates = new DateCell[2 * n];

    size_t m = initdatesarr(dates, n);

    DateCell* tmp = new DateCell[2 * m];
    utils::mergeSort(dates, tmp, 0, 2 * m);
    delete[] tmp;

    std::cout << getmax(dates, 2 * m);

    delete[] dates;

    return 0;
}
