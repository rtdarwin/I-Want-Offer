#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode
{
    int value;
    struct BinaryTreeNode* pLeft;
    struct BinaryTreeNode* pRight;
};

// [begin, end]
struct BinaryTreeNode*
reConstructSubBiTree(int* preOdrBegin, int* preOdrEnd, int* inOdrBegin,
                     int* inOdrEnd)
{
    struct BinaryTreeNode* root =
        (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    root->value = *preOdrBegin;
    root->pLeft = NULL;
    root->pRight = NULL;

    /*  1. 递归触底 */

    if (preOdrBegin == preOdrEnd)
        return root;

    /*  2. 持续递归下去 */

    int* pInOdr = inOdrBegin;
    while (*pInOdr != root->value) {
        pInOdr++;
    }

    int lSubTreeLen = pInOdr - inOdrBegin;
    int rSubTreeLen = inOdrEnd - pInOdr;
    if (lSubTreeLen) {
        root->pLeft = reConstructSubBiTree(
            preOdrBegin + 1, preOdrBegin + lSubTreeLen, inOdrBegin, pInOdr - 1);
    }
    if (rSubTreeLen) {
        root->pRight = reConstructSubBiTree(preOdrBegin + 1 + lSubTreeLen,
                                            preOdrEnd, pInOdr + 1, inOdrEnd);
    }

    return root;
}

struct BinaryTreeNode*
reConstructBiTree(int* preOrder, int* inOrder, int len)
{
    if (preOrder == NULL || inOrder == NULL || len == 0)
        return NULL;

    return reConstructSubBiTree(preOrder, preOrder + len - 1, inOrder,
                                inOrder + len - 1);
}

void
preOrderTraverseRecursively(struct BinaryTreeNode* tree)
{
    if (tree == NULL)
        return;

    printf("%d ", tree->value);
    if (tree->pLeft) {
        preOrderTraverseRecursively(tree->pLeft);
    }
    if (tree->pRight) {
        preOrderTraverseRecursively(tree->pRight);
    }
}

void
preOrderTraverseNonRecursively(struct BinaryTreeNode* tree)
{
    if (tree == NULL)
        return;

    // [0, topInx]
    struct BinaryTreeNode* stack[100];
    int topIdx = -1;

    stack[++topIdx] = tree;
    do {
        struct BinaryTreeNode* currNode = stack[topIdx--];
        printf("%d ", currNode->value);

        if (currNode->pRight) {
            stack[++topIdx] = currNode->pRight;
        }
        if (currNode->pLeft) {
            stack[++topIdx] = currNode->pLeft;
        }
    } while (topIdx != -1);
}

void
inOrderTraverseRecursively(struct BinaryTreeNode* tree)
{
    if (tree == NULL)
        return;

    if (tree->pLeft)
        inOrderTraverseRecursively(tree->pLeft);

    printf("%d ", tree->value);

    if (tree->pRight)
        inOrderTraverseRecursively(tree->pRight);
}

void
inOrderTraverseNonRecursively(struct BinaryTreeNode* tree)
{

    if (tree == NULL)
        return;

    // [0, topInx]
    struct BinaryTreeNode* stack[100] = { 0 };
    int topIdx = -1;
    stack[++topIdx] = tree;

    do {
        struct BinaryTreeNode* currNode = stack[topIdx];

        while (currNode) {
            currNode = currNode->pLeft;
            stack[++topIdx] = currNode;
        }

        // 空指针退栈
        // 解释：这一步为什么要退一个空指针？
        --topIdx;

        if (topIdx != -1) {
            currNode = stack[topIdx--];
            printf("%d ", currNode->value);
            stack[++topIdx] = currNode->pRight;
        }
    } while (topIdx != -1);
}

int
main()
{
    int preOrder[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
    int inOrder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };

    /*  1. 重建 */

    struct BinaryTreeNode* tree =
        reConstructBiTree(preOrder, inOrder, sizeof(preOrder) / sizeof(int));

    /*  2. 遍历以验证重建所得树的正确性 */

    preOrderTraverseRecursively(tree);
    fputc('\n', stdout);

    preOrderTraverseNonRecursively(tree);
    fputc('\n', stdout);

    inOrderTraverseRecursively(tree);
    fputc('\n', stdout);

    inOrderTraverseNonRecursively(tree);
    fputc('\n', stdout);

    // 后序遍历同中序遍历，易写出递归解法，难写出非递归写法。
    // 此处不再实现

    return 0;
}
