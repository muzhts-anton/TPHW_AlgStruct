#include <iostream>

namespace utils {

template <class T>
class AvlTree {
private:
    struct TreeNode {
        explicit TreeNode(const T& key)
            : key(key)
            , left(nullptr)
            , right(nullptr)
            , height(1)
            , weight(1)
        {
        }

        ~TreeNode()
        {
            if (left)
                delete left;
            if (right)
                delete right;
        }

        T key;
        TreeNode* left;
        TreeNode* right;
        int height;
        int weight;
    };

public:
    explicit AvlTree(bool (*comp)(const T&, const T&))
        : _root(nullptr)
        , _comp(comp) {};

    ~AvlTree() { delete _root; }

    inline bool search(const T& key) const { return find(key).first; }
    inline void append(const T& key) { _root = insert(_root, key); }
    bool erase(const T& key);
    inline int getPlace(const T& key) const { return computePosition(_root, key); }
    std::pair<bool, T> getKStat(int index) const;

private:
    inline int getWeight(TreeNode* node) const { return node ? node->weight : 0; }
    inline int getHeight(TreeNode* node) const { return node ? node->height : 0; }
    inline int getBalanceFactor(TreeNode* node) const { return getHeight(node->left) - getHeight(node->right); }

    int computePosition(TreeNode* node, const T& key) const;
    T computeKStat(TreeNode* node, int index) const;

    std::pair<bool, TreeNode*> find(const T& key) const;
    TreeNode* insert(TreeNode* node, const T& key);

    TreeNode* findAndRemoveMin(TreeNode* node, TreeNode*& min);
    TreeNode* findAndRemoveMax(TreeNode* node, TreeNode*& max);
    TreeNode* remove(TreeNode* node, const T& key);

    TreeNode* balance(TreeNode* node);
    void leftRotate(TreeNode* node);
    void rightRotate(TreeNode* node);

private:
    TreeNode* _root;
    bool (*_comp)(const T&, const T&);
};

template <class T>
bool AvlTree<T>::erase(const T& key)
{
    if (!search(key))
        return false;

    _root = remove(_root, key);
    return true;
}

template <class T>
std::pair<bool, T> AvlTree<T>::getKStat(int index) const
{
    if (index >= getWeight(_root)) {
        return std::make_pair(false, 0);
    }
    return std::make_pair(true, computeKStat(_root, index));
}

template <class T>
std::pair<bool, typename AvlTree<T>::TreeNode*> AvlTree<T>::find(const T& key) const
{
    TreeNode* tmp = _root;
    while (tmp) {
        if (!(_comp(tmp->key, key)) && !(_comp(key, tmp->key)))
            return std::make_pair(true, tmp);

        (_comp(key, tmp->key)) ? tmp = tmp->left : tmp = tmp->right;
    }

    return std::make_pair(false, nullptr);
}

template <class T>
int AvlTree<T>::computePosition(TreeNode* node, const T& key) const
{
    if (!node)
        return 0;

    if (_comp(key, node->key))
        return computePosition(node->left, key);

    return computePosition(node->right, key) + getWeight(node->left) + 1;
}

template <class T>
T AvlTree<T>::computeKStat(TreeNode* node, int index) const
{
    if (getWeight(node->left) == index)
        return node->key;

    if (index < getWeight(node->left))
        return computeKStat(node->left, index);

    return computeKStat(node->right, index - getWeight(node->left) - 1);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::insert(TreeNode* node, const T& key)
{
    if (!node)
        return new TreeNode(key);

    if (_comp(key, node->key))
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return balance(node);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::findAndRemoveMin(TreeNode* node, TreeNode*& min)
{
    if (!node->left) {
        min = node;
        return node->right;
    }

    node->left = findAndRemoveMin(node->left, min);

    return balance(node);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::findAndRemoveMax(TreeNode* node, TreeNode*& max)
{
    if (!node->right) {
        max = node;
        return node->left;
    }

    node->right = findAndRemoveMax(node->right, max);

    return balance(node);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::remove(TreeNode* node, const T& key)
{
    if (_comp(node->key, key))
        node->right = remove(node->right, key);
    else if (_comp(key, node->key))
        node->left = remove(node->left, key);
    else {
        TreeNode* left = node->left;
        TreeNode* right = node->right;

        node->left = node->right = nullptr;
        delete node;

        if (!left && !right)
            return nullptr;
        if (!right)
            return left;
        if (!left)
            return right;

        if (right->height >= left->height) {
            TreeNode* min = nullptr;
            TreeNode* tmp = findAndRemoveMin(right, min);
            min->right = tmp;
            min->left = left;
            return balance(min);
        } else {
            TreeNode* max = nullptr;
            TreeNode* tmp = findAndRemoveMax(left, max);
            max->left = tmp;
            max->right = right;
            return balance(max);
        }
    }
    return balance(node);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::balance(TreeNode* node)
{
    TreeNode* tmp = node;
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->left) == -1) {
            TreeNode* tmp = node->left;
            node->left = node->left->right;
            leftRotate(tmp);
        }
        tmp = node->left;
        rightRotate(node);
    } else if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->right) == 1) {
            TreeNode* tmp = node->right;
            node->right = node->right->left;
            rightRotate(tmp);
        }
        tmp = node->right;
        leftRotate(node);
    }

    tmp->weight = getWeight(tmp->left) + getWeight(tmp->right) + 1;
    tmp->height = std::max(getHeight(tmp->left), getHeight(tmp->right)) + 1;

    return tmp;
}

template <class T>
void AvlTree<T>::leftRotate(TreeNode* node)
{
    TreeNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->weight = getWeight(node->left) + getWeight(node->right) + 1;
    tmp->weight = getWeight(tmp->left) + getWeight(tmp->right) + 1;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    tmp->height = std::max(getHeight(tmp->left), getHeight(tmp->right)) + 1;
}

template <class T>
void AvlTree<T>::rightRotate(TreeNode* node)
{
    TreeNode* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->weight = getWeight(node->left) + getWeight(node->right) + 1;
    tmp->weight = getWeight(tmp->left) + getWeight(tmp->right) + 1;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    tmp->height = std::max(getHeight(tmp->left), getHeight(tmp->right)) + 1;
}

} // namespace utils

int main()
{
    int num;
    std::cin >> num;
    utils::AvlTree<size_t> tasker([](const size_t& l, const size_t& r) { return l > r; });
    for (size_t i = 0, operation = 0, obj = 0; i < num; ++i) {
        std::cin >> operation >> obj;
        if (operation == 1) {
            std::cout << tasker.getPlace(obj) << std::endl;
            tasker.append(obj);
        } else if (operation == 2) {
            tasker.erase(tasker.getKStat(obj).second);
        }
    }
    return 0;
}
