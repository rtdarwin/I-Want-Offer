#include <cassert>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename Key, typename T, typename Compare = std::less<T>>
class BSTree
{
public:
    explicit BSTree(const Compare& comp = Compare());
    // non-copyable, non-moveable
    BSTree(const BSTree&) = delete;
    BSTree& operator=(const BSTree&) = delete;
    BSTree(BSTree&&) = delete;
    BSTree& operator=(BSTree&&) = delete;
    ~BSTree();

    // element access
    T& at(const Key& k);
    const T& at(const Key& k) const;
    // 暂不实现 [] 语义
    // T& operator[](const Key& k);

    // capacity
    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }

    // modifiers
    // if @param k is already in the BSTree, return -1
    // if @param k is not in the BSTree, insert k-v, return 1
    int insert(const Key& k, const T& v);
    // 除 BSTree 为空时抛出 out_of_range("BSTree is empty") 异常外
    //   不抛出其他异常。当 @param k 不在 BSTree 中时，no nothing
    void erase(const Key& k);
    void eraseMin();
    void eraseMax();

    // lookup
    bool contains(const Key& k) const;

private:
    struct Node
    {
        Node(const Key& k, const T& v)
            : key(k)
            , value(v)
        {
        }

        Key key;
        T value;
        struct Node* pLeft = nullptr;
        struct Node* pRight = nullptr;
        /* struct BSTNode* pParent; */
    };

    Node* findNode(Node* root, const Key& k) const;
    void insertNode(Node** root, const Key& k, const T& v);
    Node* minNode(Node* root);
    Node* eraseMin(Node* root) noexcept;
    Node* eraseMax(Node* root) noexcept;

private:
    Node* _head = nullptr;
    size_t _size = 0;
    const Compare& _comp;
};

// ============================================================

template <typename Key, typename T, typename Compare>
BSTree<Key, T, Compare>::BSTree(const Compare& comp)
    : _comp{ comp }
{
}

template <typename Key, typename T, typename Compare>
BSTree<Key, T, Compare>::~BSTree()
{
    _size = 0;
    // TODO
}

template <typename Key, typename T, typename Compare>
T&
BSTree<Key, T, Compare>::at(const Key& k)
{
    return const_cast<T&>((static_cast<const BSTree*>(this))->at(k));
}

template <typename Key, typename T, typename Compare>
const T&
BSTree<Key, T, Compare>::at(const Key& k) const
{
    if (_head == nullptr)
        throw out_of_range("BSTree is empty");

    return findNode(_head, k)->value;
}

template <typename Key, typename T, typename Compare>
typename BSTree<Key, T, Compare>::Node*
BSTree<Key, T, Compare>::findNode(Node* root, const Key& k) const
{
    if (root == nullptr)
        throw out_of_range("not found");

    bool kless = _comp(k, root->key);
    bool rootless = _comp(root->key, k);
    if (!kless && !rootless) {
        return root;
    } else if (kless) {
        return findNode(root->pLeft, k);
    } else {
        return findNode(root->pRight, k);
    }
}

template <typename Key, typename T, typename Compare>
int
BSTree<Key, T, Compare>::insert(const Key& k, const T& v)
{
    int alreadyIn = 0;
    try {
        insertNode(&_head, k, v);
        _size++;
    } catch (const exception&) {
        alreadyIn = 1;
    }

    return alreadyIn ? -1 : 1;
}
template <typename Key, typename T, typename Compare>
void
BSTree<Key, T, Compare>::insertNode(Node** proot, const Key& k, const T& v)
{
    if (*proot == nullptr) {
        *proot = new Node(k, v);
        return;
    }

    bool kless = _comp(k, (*proot)->key);
    bool rootless = _comp((*proot)->key, k);

    if (!kless && !rootless) {
        // case 1: 所要插入的 key 已经在搜索二叉树里了
        throw exception();
    } else if (kless) {
        // case 2: key 比当前树根的 key 小
        insertNode(&(*proot)->pLeft, k, v);
    } else if (rootless) {
        // case 3: key 比当前树根的 key 大
        insertNode(&(*proot)->pRight, k, v);
    }
}

template <typename Key, typename T, typename Compare>
void
BSTree<Key, T, Compare>::erase(const Key& k)
{
    if (_head == nullptr)
        throw out_of_range("BSTree is empty");

    function<Node*(Node*, const Key&)> deleteHelper =
        [this, &deleteHelper](Node* root, const Key& k) -> Node* {
        if (root == nullptr)
            throw out_of_range("not found");

        bool kless = _comp(k, root->key);
        bool rootless = _comp(root->key, k);

        if (!kless && !rootless) {
            if (root->pRight == nullptr)
                return root->pLeft;
            if (root->pLeft == nullptr)
                return root->pRight;

            Node* target = root;
            Node* next = new Node(*minNode(root->pRight));
            next->pRight = eraseMin(target->pRight);
            next->pLeft = target->pLeft;
            return next;
        } else if (kless) {
            root->pLeft = deleteHelper(root->pLeft, k);
        } else /* if(rootless) */ {
            root->pRight = deleteHelper(root->pRight, k);
        }

        return root;
    };

    _head = deleteHelper(_head, k);
}

template <typename Key, typename T, typename Compare>
typename BSTree<Key, T, Compare>::Node*
BSTree<Key, T, Compare>::minNode(Node* root)
{
    if (root == nullptr)
        return nullptr;

    Node* curr = root;
    while (curr->pLeft) {
        curr = curr->pLeft;
    }
    return curr;
}

template <typename Key, typename T, typename Compare>
void
BSTree<Key, T, Compare>::eraseMin()
{
    if (_head == nullptr)
        throw out_of_range("BSTree is empty");

    _head = eraseMin(_head);
    --_size;
}

template <typename Key, typename T, typename Compare>
typename BSTree<Key, T, Compare>::Node*
BSTree<Key, T, Compare>::eraseMin(Node* root) noexcept
{
    if (!root->pLeft) {
        auto right = root->pRight;
        delete root;
        return right;
    } else {
        root->pLeft = eraseMin(root->pLeft);
        return root;
    }
}

template <typename Key, typename T, typename Compare>
void
BSTree<Key, T, Compare>::eraseMax()
{
    if (_head == nullptr)
        throw out_of_range("BSTree is empty");

    _head = eraseMax(_head);
    --_size;
}

template <typename Key, typename T, typename Compare>
typename BSTree<Key, T, Compare>::Node*
BSTree<Key, T, Compare>::eraseMax(Node* root) noexcept
{
    if (!root->pRight) {
        auto left = root->pLeft;
        delete root;
        return left;
    } else {
        root->pRight = eraseMax(root->pRight);
        return root;
    }
}

template <typename Key, typename T, typename Compare>
bool
BSTree<Key, T, Compare>::contains(const Key& k) const
{
    bool contain = 1;
    try {
        findNode(_head, k);
    } catch (const exception&) {
        contain = 0;
    }

    return contain;
}

int
main()
{
    BSTree<int, int> tree;

    int a[] = { 5, 0, 7, 6, 11, 4, 1, 1, 2, 3, 0 };
    for (int i = 0; i < 11; i++) {
        tree.insert(a[i], i);
    }

    for (int i = 0; i < 11; i++) {
        cout << "tree[" << a[i] << "] = " << tree.at(a[i]) << endl;
    }
    cout << endl;

    assert(tree.size() == 9);

    assert(tree.contains(0));
    tree.erase(0);
    assert(!tree.contains(0));

    assert(tree.contains(7));
    tree.erase(7);
    assert(!tree.contains(7));

    assert(tree.contains(3));
    tree.erase(3);
    assert(!tree.contains(3));

    assert(tree.contains(11));
    tree.erase(11);
    assert(!tree.contains(11));

    assert(tree.contains(1));
    assert(tree.contains(2));
}
