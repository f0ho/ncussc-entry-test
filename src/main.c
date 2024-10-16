#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>


void main(){
    // 冒泡排序
    //int a[] = {1, 2, 5, 3, 4, 7, 9};
    // int flag = 1;
    // int length = sizeof(a) / sizeof(a[0]);
    // for (int i = 0; i < length - 1; i++){
    //     flag = 1;
    //     for (int j = 0; j< length - 1 - i; j++){
    //         if (a[j] > a[j + 1]){
    //             int tmp = a[j];
    //             a[j] = a[j + 1];
    //             a[j + 1] = tmp;
    //             flag = 0;
    //         }
    //     }
    //     if (flag) break;
    // }
    // for (int i = 0; i < length; i++){
    //     printf("%d",a[i]);
    // }


    // 堆排序
    // int a[] = {0,3,4,5,2,1,9,7,4}; // 第一个是占位符
    // int length = sizeof(a) / sizeof(a[0]) - 1;
    // for (int i = length; i > 1; i--){//堆化
    //     int index = i; 
    //     while (index > 1) {
    //         if (a[index] < a[index / 2]){
    //             int tmp = a[index];
    //             a[index] = a[index / 2];
    //             a[index / 2] = tmp;
    //             index /= 2;
    //         }else break;
    //     }
    // }
    // int length2 = length;
    // int* result = (int*)(malloc((length2 + 1) * sizeof(int)));
    // result[0] = 0;
    // for (int i = 1; i < length2 + 1; i++){
    //     int min = 1;
    //     int smallChilden = min * 2;
    //     result[i] = a[1];
    //     a[1] = a[length];
    //     length -= 1;
    //     while (min * 2 < length + 1) {
    //         if (smallChilden < length && a[smallChilden] > a[smallChilden + 1]) smallChilden += 1;
    //         if (a[min] > a[smallChilden]) {
    //             int tmp = a[min];
    //             a[min] = a[smallChilden];
    //             a[smallChilden] = tmp;
    //             min = smallChilden;
    //             smallChilden *= 2;
    //         }else{
    //             break;
    //         }
    //     }
    // }
    // for (int i = 1; i < length2 + 1; i++){
    //     printf("%d",result[i]);
    // }
    // free(result);


    //斐波那契堆排序


    //生成随机数
    // 设置随机种子
    srand(time(NULL));
    int n = 10;
    FILE *f = fopen("../Data/1_1.txt","w");
    for (int i = 0; i < n; i++) {
        int random_num = rand() % 10000; // 生成0到9999之间的随机数
        fprintf(f, "%d ", random_num);
    }
    fclose(f);
}

// typedef struct Node{
//     int key;
//     int degree;
//     Node* parent;
//     Node* child;
//     Node* right;
//     Node* left;
//     bool mark;
// } Node;

// typedef struct FiboHeap{
//     Node* min;
//     int numberNodes;
// } FiboHeap;

// Node* createNode(int key) {
//     Node* newNode = (Node*)malloc(sizeof(Node));
//     newNode->key = key;
//     newNode->degree = 0;
//     newNode->parent = NULL;
//     newNode->child = NULL;
//     newNode->right = newNode;
//     newNode->left = newNode;
//     newNode->mark = false;
//     return newNode;
// }

// FiboHeap* createFiboHeap() {
//     FiboHeap* heap = (FiboHeap*)malloc(sizeof(FiboHeap));
//     heap->min = NULL;
//     heap->numberNodes = 0;
//     return heap;
// }

// void insert(FiboHeap* heap, int key){
//     Node* node = createNode(key);
//     if (heap->numberNodes == 0) {
//         heap->min = node;
//         return;
//     }
//     node->left = heap->min->left;
//     node->right = heap->min;
//     heap->min->left = node;
//     heap->min->left->right = node;
//     if (heap->min->key > node->key) {
//         heap->min = node;
//     }
//     heap->numberNodes += 1;
// }

// void move(FiboHeap* heap, Node* node){
//     if (heap->numberNodes == 0) {
//         heap->min = node;
//         return;
//     }
//     node->left = heap->min->left;
//     node->right = heap->min;
//     heap->min->left = node;
//     heap->min->left->right = node;
//     if (heap->min->key > node->key) {
//         heap->min = node;
//     }
//     heap->numberNodes += 1;
// }

// void findMin(FiboHeap* heap){

// }

// int getMin(FiboHeap* heap){

//     if (heap->min->child == NULL) {
//         int min = heap->min->key;
//         free(heap->min);
//         return min;
//     }
//     //移动子结点至根节点
//     Node* child = heap->min->child;
//     do {
//         Node* tmp = child->right;
//         heap->min->child->parent = NULL;
//         move(heap, child);
//         heap->numberNodes -= 1;
//         child = tmp;
//     }while(child != heap->min->child);

//     heap->min->left->right = heap->min->right;
//     heap->min->right->left = heap->min->left;
//     int min = heap->min->key;
//     //改变heap->min
//     child = heap->min;
//     if (heap->min == heap->min->right) {
//         heap->min = NULL;
//     } else {
//         heap->min = child->right;
//         findMin(heap);
//     }
//     free(child);
//     heap->numberNodes -= 1;
//     //合并相同度数树
//     FiboHeap* cons = createFiboHeap();
//     do{
//         move(cons, heap->min);
//         heap->numberNodes -= 1;
//         if(cons->numberNodes == 1){
//             cons->min = heap->min;

//         }
//         free(heap->min);
//     }while(heap->numberNodes);
// }