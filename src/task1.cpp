#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

typedef unsigned long hash_t;

template <typename T>
class HashSet {
public:
    HashSet(hash_t(const std::string&), hash_t(const hash_t&));

    bool append(const T&);
    bool contain(const T&) const;
    bool remove(const T&);

private:
    struct Node {
        enum class Stage {
            FILLED = 0,
            DELETED,
            FREE,
        };
        Node()
            : stage(Stage::FREE)
        {
        }

        T data;
        Stage stage;
    };

    static constexpr float alpha = .75;
    void grow();

private:
    hash_t (*_mainhash)(const std::string&);
    hash_t (*_secondhash)(const hash_t&);

    std::vector<Node> _buckets;
    size_t _size;
};

template <typename T>
HashSet<T>::HashSet(hash_t h1(const std::string&), hash_t h2(const hash_t&))
    : _mainhash(h1)
    , _secondhash(h2)
    , _buckets(8)
    , _size(0)
{
}

template <typename T>
void HashSet<T>::grow()
{
    std::vector<Node> buckets(2 * _buckets.size());
    for (size_t i = 0; i < _buckets.size(); ++i) {
        if (_buckets[i].stage != Node::Stage::FILLED)
            continue;

        Node tmp = _buckets[i];
        hash_t hash = _mainhash(tmp.data);
        hash_t step = _secondhash(hash);

        for (size_t j = 0, idx = 0; j < buckets.size(); ++j) {
            idx = (hash + j * step) % buckets.size();
            if (buckets[idx].stage == Node::Stage::FREE) {
                buckets[idx].stage = Node::Stage::FILLED;
                buckets[idx].data = tmp.data;
                break;
            }
        }
    }
    _buckets = std::move(buckets);
}

template <typename T>
bool HashSet<T>::append(const T& data)
{
    if (_size > _buckets.size() * HashSet::alpha)
        this->grow();

    hash_t hash = _mainhash(data);
    hash_t step = _secondhash(hash);

    ssize_t emptyidx = -1;
    for (size_t i = 0, idx = 0; i < _buckets.size(); ++i) {
        idx = (hash + i * step) % _buckets.size();
        if (_buckets[idx].stage == Node::Stage::DELETED && emptyidx < 0) {
            emptyidx = idx;
            continue;
        }

        if (_buckets[idx].stage == Node::Stage::FILLED && _buckets[idx].data == data)
            return false;

        if (_buckets[idx].stage == Node::Stage::FREE) {
            size_t j = (emptyidx >= 0) ? emptyidx : idx;

            _buckets[j].stage = Node::Stage::FILLED;
            _buckets[j].data = data;
            ++_size;
            return true;
        }
    }

    if (emptyidx >= 0) {
        _buckets[emptyidx].stage = Node::Stage::FILLED;
        _buckets[emptyidx].data = data;
        ++_size;
        return true;
    }

    return false;
}

template <typename T>
bool HashSet<T>::remove(const T& data)
{
    hash_t hash = _mainhash(data);
    hash_t step = _secondhash(hash);

    for (size_t i = 0, idx = 0; i < _buckets.size(); ++i) {
        idx = (hash + i * step) % _buckets.size();
        if (_buckets[idx].stage == Node::Stage::DELETED)
            continue;

        if (_buckets[idx].stage == Node::Stage::FILLED && _buckets[idx].data == data) {
            _buckets[idx].stage = Node::Stage::DELETED;
            --_size;
            return true;
        }

        if (_buckets[idx].stage == Node::Stage::FREE)
            return false;
    }

    return false;
}

template <typename T>
bool HashSet<T>::contain(const T& data) const
{
    hash_t hash = _mainhash(data);
    hash_t step = _secondhash(hash);
    for (size_t i = 0, idx; i < _buckets.size(); ++i) {
        idx = (hash + i * step) % _buckets.size();
        if (_buckets[idx].stage == Node::Stage::DELETED)
            continue;

        if (_buckets[idx].stage == Node::Stage::FILLED && _buckets[idx].data == data)
            return true;

        if (_buckets[idx].stage == Node::Stage::FREE)
            return false;
    }

    return false;
}

int main()
{
    HashSet<std::string> almostMap([](const std::string& str) {
        hash_t hash = 0;
        hash_t hash_coefficient = 7;
        for (size_t i = 0; i < str.size(); ++i)
            hash = hash * hash_coefficient + str[i];
        return hash; }, [](const hash_t& hash) { return (hash_t)(2 * hash + 1); });

    char operation = 0;
    std::string data;
    while (std::cin >> operation >> data) {
        switch (operation) {
        case '+':
            std::cout << (almostMap.append(data) ? "OK" : "FAIL");
            break;
        case '-':
            std::cout << (almostMap.remove(data) ? "OK" : "FAIL");
            break;
        case '?':
            std::cout << (almostMap.contain(data) ? "OK" : "FAIL");
            break;
        default:
            assert(false);
        }
        std::cout << "\n";
    }

    return 0;
}