#include <assert.h>
#include <iostream>

namespace utils {

template <class T>
class Queue {
public:
    Queue()
        : size(0)
    {
    }
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    size_t getSize() const { return size; }
    bool isEmpty() const { return !size; }

    void pushBack(const T& value);
    T popFront();

private:
    class Stack {
    public:
        Stack()
            : size(0)
        {
        }
        ~Stack();

        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;

        void push(const T& element);
        T pop();

        size_t getSize() const { return size; }
        bool isEmpty() const { return !size; }

    private:
        class Buffer {
        public:
            Buffer(size_t buffsize = 0);
            ~Buffer();

            void push(const T& value);
            T getTop() const;
            void pop();

            size_t getSize() const { return size; }
            bool isInited() const { return !!size; }
            bool isFull() const { return isfull; }

            void debugprint() const;

        private:
            size_t size;
            T* data;
            size_t head;
            size_t tail;
            bool isfull;
        };

    private:
        size_t size;
        Buffer buff;
    };

private:
    size_t size;
    Stack input;
    Stack output;
};

// !Stack
template <class T>
void Queue<T>::Stack::push(const T& element)
{
    buff.push(element);
    ++size;
}

template <class T>
T Queue<T>::Stack::pop()
{
    if (isEmpty())
        throw 1;

    T tmp = buff.getTop();
    buff.pop();

    --size;

    return tmp;
}

template <class T>
Queue<T>::Stack::~Stack()
{
}

// !Queue
template <class T>
void Queue<T>::pushBack(const T& value)
{
    input.push(value);
    ++size;
}

template <class T>
T Queue<T>::popFront()
{
    if (output.isEmpty() && input.isEmpty())
        throw 1;

    if (output.isEmpty())
        while (!input.isEmpty())
            output.push(input.pop());

    --size;

    return output.pop();
}

template <class T>
Queue<T>::~Queue()
{
}

// !Buffer
template <class T>
Queue<T>::Stack::Buffer::~Buffer()
{
    if (isInited())
        delete[] data;
}

template <class T>
Queue<T>::Stack::Buffer::Buffer(size_t buffsize)
    : size(buffsize)
    , data(nullptr)
    , head(0)
    , tail(head + 1)
    , isfull(false)
{
    if (size)
        data = new T[size];
}

template <class T>
void Queue<T>::Stack::Buffer::push(const T& value)
{
    if (!isInited()) {
        const size_t minsize = 7;
        data = new T[minsize];
        size = minsize;
        head = 0;
        data[head] = value;
        tail = 1;
        return;
    }

    if (isFull()) {
        T* tmp = new T[size * 2];
        size_t bi = head;
        size_t ni = 0;
        while (bi < size)
            tmp[ni++] = data[bi++];
        bi = 0;
        while (bi < tail)
            tmp[ni++] = data[bi++];
        size *= 2;
        head = 0;
        tail = ni;
        delete[] data;
        data = tmp;
        isfull = false;
    }

    data[tail++] = value;
    if (tail == getSize())
        tail = 0;

    if (head == tail)
        isfull = true;

    //std::cout << "PUSH: ";
    //debugprint();
}

template <class T>
void Queue<T>::Stack::Buffer::pop()
{
    if (!getSize())
        throw 1;

    ++head;
    if (head == getSize())
        head = 0;
    if (isfull)
        isfull = false;

    //std::cout << "POP: ";
    //debugprint();
}

template <class T>
T Queue<T>::Stack::Buffer::getTop() const
{
    if (!getSize())
        throw 1;

    return data[head];
}

template <class T>
void Queue<T>::Stack::Buffer::debugprint() const
{
    for (size_t i = 0; i < size; ++i) {
        if (i == tail)
            std::cout << "[";
        if (i == head)
            std::cout << "<";
        std::cout << data[i];
        if (i == head)
            std::cout << ">";
        if (i == tail)
            std::cout << "]";
        std::cout << " ";
    }
    std::cout << "\n";
}

} // namespace utils

int main()
{
    utils::Queue<int> q1;
    int n = 0;
    std::cin >> n;

    bool result = true;
    int command = 0;
    int value = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> command >> value;
        switch (command) {
        case 2: {
            if (q1.isEmpty()) {
                result = result && (-1 == value);
            } else {
                result = result && (q1.popFront() == value);
            }
            break;
        }
        case 3:
            q1.pushBack(value);
            break;
        default:
            assert(false);
        }
    }
    std::cout << (result ? "YES\n" : "NO\n");
    return 0;
}
