#include <stdio.h>
#include <stdlib.h>

struct BinaryTreeNode
{
    int value;
    struct BinaryTreeNode* pLeft;
    struct BinaryTreeNode* pRight;
    struct BinaryTreeNode* pParent;
};

struct BinaryTreeNode*
inOrderNextNode(struct BinaryTreeNode* currNode)
{
    if (currNode == NULL) {
        return NULL;
    }

    struct BinaryTreeNode* pNext = NULL;

    if (currNode->pRight) {
        currNode = currNode->pRight;
        while (currNode->pLeft != NULL)
            currNode = currNode->pLeft;
        return currNode;
    } else {
        struct BinaryTreeNode* parrent = currNode->pParent;
        while (parrent->pLeft != currNode) {
            if (parrent->pParent) {
                parrent = parrent->pParent;
                currNode = currNode->pParent;
            } else {
                return NULL;
            }
        }
        return parrent;
    }
}

int
main()
{
    /*  1. 准备测试用的二叉树 */

    struct BinaryTreeNode bitreeNodes[8];
    struct BinaryTreeNode* tree = bitreeNodes + 3;

    int inOrderValues[8] = { 4, 7, 2, 1, 5, 3, 8, 6 };
    for (int i = 0; i < 8; i++) {
        bitreeNodes[i].value = inOrderValues[i];
    }

    // -1 indicates NULL
    int lrIdx[8][3] = { { -1, 1, 2 },  { -1, -1, 0 }, { 0, -1, 3 },
                        { 2, 5, -1 },  { -1, -1, 5 }, { 4, 7, 3 },
                        { -1, -1, 7 }, { 6, -1, 5 } };
    for (int i = 0; i < 8; i++) {
        bitreeNodes[i].pLeft =
            (lrIdx[i][0] != -1) ? bitreeNodes + lrIdx[i][0] : NULL;
        bitreeNodes[i].pRight =
            (lrIdx[i][1] != -1) ? bitreeNodes + lrIdx[i][1] : NULL;
        bitreeNodes[i].pParent =
            (lrIdx[i][2] != -1) ? bitreeNodes + lrIdx[i][2] : NULL;
    }

    /*  2. 开始测试 */

    for (int i = 0; i < 8; i++) {
        struct BinaryTreeNode* currNode = bitreeNodes + i;
        struct BinaryTreeNode* nextNode = inOrderNextNode(currNode);

        if (nextNode != NULL) {
            printf("%d's next is %d\n", currNode->value, nextNode->value);
        }
    }

    return 0;
}
