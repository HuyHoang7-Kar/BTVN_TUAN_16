#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int a;
    struct Node *left;
    struct Node *next;
    int height;
} Node;

// Hàm lấy chiều cao của cây
int getHeight(Node *AVL) {
    if (AVL == NULL) {
        return 0;
    }
    return AVL->height;
}

// Hàm tạo node mới
Node *createAVL(int a) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->a = a;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->next = NULL;
    return newNode;
}

// Hàm tính toán độ cân bằng của cây
int getBalance(Node *AVL) {
    if (AVL == NULL) {
        return 0;
    }
    return getHeight(AVL->left) - getHeight(AVL->next);
}

// Hàm quay phải
Node *rightRot(Node *k2) {
    Node *k1 = k2->left;
    Node *T = k1->next;
    k1->next = k2;
    k2->left = T;
    k2->height = 1 + (getHeight(k2->left) > getHeight(k2->next) ? getHeight(k2->left) : getHeight(k2->next));
    k1->height = 1 + (getHeight(k1->left) > getHeight(k1->next) ? getHeight(k1->left) : getHeight(k1->next));
    return k1;
}

// Hàm quay trái
Node *leftRot(Node *k2) {
    Node *k1 = k2->next;
    Node *T = k1->left;
    k1->left = k2;
    k2->next = T;
    k2->height = 1 + (getHeight(k2->left) > getHeight(k2->next) ? getHeight(k2->left) : getHeight(k2->next));
    k1->height = 1 + (getHeight(k1->left) > getHeight(k1->next) ? getHeight(k1->left) : getHeight(k1->next));
    return k1;
}

// Hàm chèn node vào cây AVL
Node *insert(Node *AVL, int a) {
    if (AVL == NULL) {
        return createAVL(a);
    }
    if (a < AVL->a) {
        AVL->left = insert(AVL->left, a);
    } else if (a >= AVL->a) {
        AVL->next = insert(AVL->next, a);
    }

    AVL->height = 1 + (getHeight(AVL->left) > getHeight(AVL->next) ? getHeight(AVL->left) : getHeight(AVL->next));
    int balance = getBalance(AVL);

    // Trường hợp Left Left
    if (balance > 1 && a < AVL->left->a)
        return rightRot(AVL);

    // Trường hợp Right Right
    if (balance < -1 && a > AVL->next->a)
        return leftRot(AVL);

    // Trường hợp Left Right
    if (balance > 1 && a > AVL->left->a) {
        AVL->left = leftRot(AVL->left);
        return rightRot(AVL);
    }

    // Trường hợp Right Left
    if (balance < -1 && a < AVL->next->a) {
        AVL->next = rightRot(AVL->next);
        return leftRot(AVL);
    }
    return AVL;
}

// Hàm in cây theo cấu trúc yêu cầu
void printTree(Node *root, int space) {
    const int COUNT = 5; // Khoảng cách giữa các mức
    if (root == NULL) {
        return;
    }

    // Tăng khoảng cách giữa các mức
    space += COUNT;

    // In cây con bên trái
    printTree(root->left, space);

    // In gốc
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d", root->a);

    // In cây con bên phải
    printTree(root->next, space);
}

// Hàm duyệt cây theo thứ tự in-order
void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);  // Duyệt cây con trái
        printf("%d ", root->a); // In giá trị gốc
        inOrder(root->next);  // Duyệt cây con phải
    }
}

int main() {
    Node *root = NULL;
    int a[] = {17, 23, 201, 98, 67, 23, 13, 10, 58, 84, 191};
    int n = sizeof(a) / sizeof(a[0]);

    // Chèn các phần tử vào cây AVL
    for (int i = 0; i < n; i++) {
        root = insert(root, a[i]);
    }
   
    // In cây theo cấu trúc yêu cầu
    printf("Cay AVL theo cau truc:\n");
    printTree(root,0);

    // In cây theo thứ tự in-order
    printf("\nDuyet cay AVL theo thu tu tang dan:\n");
    inOrder(root);
    printf("\n");

    return 0;
}
