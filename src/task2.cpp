#include <iostream>
#include <stack>

template <typename T>
class BinTree {
public:
    BinTree(bool (*comp)(const T&, const T&))
        : _root(nullptr)
        , _comp(comp) {};
    ~BinTree();

    BinTree(const BinTree&) = delete;
    BinTree& operator=(const BinTree&) = delete;

    void append(const T& key);
    void print();

private:
    struct TreeNode {
        TreeNode(T key, TreeNode* left, TreeNode* right)
            : key(key)
            , left(left)
            , right(right) {};

        T key;
        TreeNode* left;
        TreeNode* right;
    };

private:
    void postorder(void (*worker)(TreeNode*));

private:
    TreeNode* _root;
    bool (*_comp)(const T&, const T&);
};

template <typename T>
BinTree<T>::~BinTree()
{
    this->postorder([](TreeNode* obj) { delete obj; });
}

template <typename T>
void BinTree<T>::append(const T& key)
{
    TreeNode* tmp = _root;

    if (!tmp) {
        _root = tmp = new TreeNode(key, nullptr, nullptr);
        return;
    }

    while (tmp) {
        if (_comp(key, tmp->key)) {
            if (tmp->left)
                tmp = tmp->left;
            else {
                tmp->left = new TreeNode(key, nullptr, nullptr);
                return;
            }
        } else {
            if (tmp->right)
                tmp = tmp->right;
            else {
                tmp->right = new TreeNode(key, nullptr, nullptr);
                return;
            }
        }
    }
}

template <typename T>
void BinTree<T>::print()
{
    this->postorder([](TreeNode* obj) { std::cout << obj->key << " "; });
}

template <typename T>
void BinTree<T>::postorder(void (*worker)(TreeNode*))
{
    if (!_root)
        return;

    TreeNode* tmp = _root;

    std::stack<TreeNode*> s1;
    std::stack<TreeNode*> s2;
    s1.push(tmp);
    while (!s1.empty()) {
        tmp = s1.top();
        s1.pop();
        s2.push(tmp);
        if (tmp->left)
            s1.push(tmp->left);
        if (tmp->right)
            s1.push(tmp->right);
    }

    while (!s2.empty()) {
        worker(s2.top());
        s2.pop();
    }
}

int main()
{
    BinTree<int> maboi([](const int& l, const int& r) { return l < r; });

    int size = 0;
    std::cin >> size;
    for (int i = 0, tmp = 0; i < size; ++i) {
        std::cin >> tmp;
        maboi.append(tmp);
    }

    maboi.print();

    return 0;
}