#include <iostream>

namespace utils {

template <class T>
class Heap {
public:
    Heap(size_t, bool(const T&, const T&), bool(const T&, const T&));
    ~Heap();

    Heap(const Heap&) = delete;
    Heap& operator=(const Heap&) = delete;

    void build(const T* arr, size_t arrsize);
    void insert(T obj);

    T peekMax() const;
    T extractMax();

private:
    void siftDown(size_t i);
    void siftUp(size_t i);

    T* buff;
    size_t buffsize;
    bool (*strictcomp)(const T&, const T&);
    bool (*nostrictcomp)(const T&, const T&);
    size_t size;
};

template <class T>
Heap<T>::Heap(size_t heapsize, bool strcomp(const T& l, const T& r), bool nstrcomp(const T& l, const T& r))
    : buffsize(heapsize)
    , size(0)
{
    this->buff = new T[heapsize];
    this->strictcomp = strcomp;
    this->nostrictcomp = nstrcomp;
}

template <class T>
Heap<T>::~Heap()
{
    delete[] this->buff;
}

template <class T>
void Heap<T>::build(const T* arr, size_t arrsize)
{
    size = arrsize;
    for (size_t i = 0; i < arrsize; ++i)
        buff[i] = arr[i];

    for (int i = (size - 1) / 2; i >= 0; i--)
        siftDown(i);
}

template <class T>
void Heap<T>::siftDown(size_t i)
{
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    size_t largest = i;
    if (left < size && this->strictcomp(this->buff[i], this->buff[left]))
        largest = left;

    if (right < size && this->strictcomp(this->buff[largest], this->buff[right]))
        largest = right;

    if (largest != i) {
        std::swap(this->buff[i], this->buff[largest]);
        siftDown(largest);
    }
}

template <class T>
void Heap<T>::siftUp(size_t i)
{
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (this->nostrictcomp(this->buff[i], this->buff[parent]))
            return;

        std::swap(this->buff[i], this->buff[parent]);
        i = parent;
    }
}

template <class T>
void Heap<T>::insert(T obj)
{
    if (this->size == this->buffsize) {
        this->buffsize *= 2;
        T* tmpbuff = new T[this->buffsize];
        for (size_t i = 0; i < size; ++i)
            tmpbuff[i] = this->buff[i];

        delete[] this->buff;
        this->buff = tmpbuff;
    }
    this->buff[this->size++] = obj;
    siftUp(this->size - 1);
}

template <class T>
T Heap<T>::peekMax() const
{
    if (this->size <= 0)
        throw 0;
    
    return this->buff[0];
}

template <class T>
T Heap<T>::extractMax()
{
    if (size <= 0)
        throw 0;

    T result = this->buff[0];
    this->buff[0] = this->buff[--(this->size)];
    if (size > 0)
        siftDown(0);

    return result;
}
} // namespace utils

struct User {
    int id;
    int attendance;
};

bool strictcomp(const User& l, const User& r)
{
    return l.attendance >= r.attendance;
}

bool nostrictcomp(const User& l, const User& r)
{
    return l.attendance > r.attendance;
}

int main()
{
    int N, K;
    std::cin >> N >> K;
    User* tmp = new User[N];
    int id, att;
    for (size_t i = 0; i < N; ++i) {
        std::cin >> id >> att;
        tmp[i].id = id;
        tmp[i].attendance = att;
    }

    utils::Heap<User> h(K, strictcomp, nostrictcomp);
    h.build(tmp, K);

    for (size_t i = 0; i < N - K + 1; ++i) {
        if (strictcomp(tmp[K + i], h.peekMax())) {
            h.insert(tmp[K + i]);
            h.extractMax();
        }
    }

    for (size_t i = 0; i < K; ++i)
        std::cout << h.extractMax().id << " ";

    std::cout << std::endl;

    return 0;
}
