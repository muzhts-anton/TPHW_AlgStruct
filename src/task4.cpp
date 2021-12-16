#include <iostream>
#include <list>

template <class T>
class AvlTree {
public:
    AvlTree()
        : _root(nullptr) {};
    ~AvlTree();

    void append(const T& data);
    void erase(const T& data);

    size_t getPlace(size_t data);

private:
    struct TreeNode {
        TreeNode(const T& data, TreeNode* left, TreeNode* right)
            : data(data)
            , height(1)
            , numelems(1)
            , left(left)
            , right(right) {};
        ~TreeNode()
        {
            if (left)
                delete left;
            if (right)
                delete right;
        }

        T data;
        uint8_t height;
        size_t numelems;
        TreeNode* left;
        TreeNode* right;
    };

private:
    TreeNode* insert(TreeNode* node, const T& data);

    TreeNode* removemin(TreeNode* node, TreeNode*& min);
    TreeNode* remove(TreeNode* node, const T& data);

    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* balance(TreeNode* node);

    uint8_t getHeight(TreeNode* node) { return node ? node->height : 0; }
    size_t getNumElems(TreeNode* node) { return node ? node->numelems : 0; }
    size_t computeNumElems(TreeNode* node) { return 1 + getNumElems(node->right) + getNumElems(node->left); }
    int8_t getBalanceFactor(TreeNode* node) { return this->getHeight(node->right) - this->getHeight(node->left); }
    void recountHeight(TreeNode* node);

private:
    TreeNode* _root;
};

template <class T>
void AvlTree<T>::recountHeight(TreeNode* node)
{
    uint8_t lh = getHeight(node->left);
    uint8_t rh = getHeight(node->right);
    node->height = std::max(lh, rh) + 1;
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::rotateRight(TreeNode* node)
{
    TreeNode* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    recountHeight(node);
    recountHeight(tmp);

    node->numelems = computeNumElems(node);
    tmp->numelems = computeNumElems(tmp);

    return tmp;
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::rotateLeft(TreeNode* node)
{
    TreeNode* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    recountHeight(node);
    recountHeight(tmp);

    node->numelems = computeNumElems(node);
    tmp->numelems = computeNumElems(tmp);

    return tmp;
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::balance(TreeNode* node)
{
    node->numelems = computeNumElems(node);
    recountHeight(node);

    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    return node;
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::insert(TreeNode* node, const T& data)
{
    if (!node)
        return new TreeNode(data, nullptr, nullptr);

    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);

    return balance(node);
}

template <class T>
void AvlTree<T>::append(const T& data)
{
    _root = insert(_root, data);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::removemin(TreeNode* node, TreeNode*& min)
{
    if (!node->left) {
        min = node;
        return node->right;
    }

    node->left = removemin(node->left, min);

    return balance(node);
}

template <class T>
typename AvlTree<T>::TreeNode* AvlTree<T>::remove(TreeNode* node, const T& data)
{
    if (!node)
        return nullptr;

    if (data < node->data)
        node->left = remove(node->left, data);
    else if (data > node->data)
        node->right = remove(node->right, data);
    else {
        TreeNode* r = node->right;
        TreeNode* l = node->left;

        node->left = nullptr;
        node->right = nullptr;
        delete node;
        if (!r)
            return l;

        TreeNode* min = nullptr;
        TreeNode* tmp = removemin(r, min);
        min->left = l;
        min->right = tmp;

        return balance(min);
    }

    return balance(node);
}

template <class T>
void AvlTree<T>::erase(const T& data)
{
    _root = remove(_root, data);
}

template <class T>
AvlTree<T>::~AvlTree()
{
    delete _root;
}

template <class T>
size_t AvlTree<T>::getPlace(size_t data)
{
    TreeNode* tmp = _root;
    size_t resplace = getNumElems(tmp->left);

    while (resplace != data) {
        if (resplace > data)
    }
}

int main()
{
    AvlTree<int> a;
    int n = 0;
    std::cin >> n;
    int num = 0;
    size_t statistic = 0;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> num >> statistic;
        num > 0 ? a.append(num) : a.erase(abs(num));
        std::cout << a.getPlace(statistic) << "\n";
    }
    return 0;
}
