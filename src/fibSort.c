#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int Type;

typedef struct FibNode {
    Type key;                        //关键字(键值)
    int degree;                      //度数
    struct FibNode* left;            //左兄弟
    struct FibNode* right;           //右兄弟
    struct FibNode* child;           //第一个孩子结点
    struct FibNode* parent;          //父结点 
}FibNode;

typedef struct FibHeap {
    int   keyNum;                     //堆中结点的总数
    int   maxDegree;                  //最大度
    struct FibNode* min;              //最小结点(某个最小堆的根结点)
    struct FibNode** cons;            //最大度的内存区域
}FibHeap;

//将node从双链表移除
void fibNodeRemove(FibNode* node) {
    node->left->right = node->right;
    node->right->left = node->left;
}

//将单个结点node加入双向链表root之前
void fibNodeAdd(FibNode* node, FibNode* root) {
    node->left = root->left;
    root->left->right = node;
    node->right = root;
    root->left = node;
}

//将双向链表b链接到双向链表a的后面
void fibNodeCat(FibNode* a, FibNode* b) {
    FibNode* tmp;
    tmp = a->right;
    a->right = b->right;
    b->right->left = a;
    b->right = tmp;
    tmp->left = b;
}

//创建斐波那契堆
FibHeap* fibHeapMake() {
    FibHeap* heap;
    heap = (FibHeap*)malloc(sizeof(FibHeap));
    if (heap == NULL) {
        printf("Error: make FibHeap failed\n");
        return NULL;
    }
    heap->keyNum = 0;
    heap->maxDegree = 0;
    heap->min = NULL;
    heap->cons = NULL;
    return heap;
}

//创建斐波那契堆的结点
FibNode* fibNodeMake(Type key) {
    FibNode* node;
    node = (FibNode*)malloc(sizeof(FibNode));
    if (node == NULL) {
        printf("Error: make Node failed\n");
        return NULL;
    }
    node->key = key;
    node->degree = 0;
    node->left = node;
    node->right = node;
    node->parent = NULL;
    node->child = NULL;
    return node;
}

//将结点node插入到斐波那契堆heap中
void fibHeapInsert_node(FibHeap* heap, FibNode* node) {
    if (heap->keyNum == 0) {
        heap->min = node;
    }
    else {
        fibNodeAdd(node, heap->min);
        if (node->key < heap->min->key) {
            heap->min = node;
        }
    }
    heap->keyNum++;
}

//新建键值为key的结点，并将其插入到斐波那契堆中
void fibHeapInsert_key(FibHeap* heap, Type key) {
    FibNode* node;
    if (heap == NULL) {
        printf("The heap does not exist\n");
        return;
    }
    node = fibNodeMake(key);
    if (node == NULL) {
        printf("Cannot make node\n");
        return;
    }
    fibHeapInsert_node(heap, node);
}

//将"堆的最小结点"从根链表中移除，即"将最小结点所属的树"从堆中移除
FibNode* fibHeapRemove_min(FibHeap* heap) {
    FibNode* min = heap->min;
    if (heap->min == min->right) {
        heap->min = NULL;
    }
    else {
        fibNodeRemove(min);
        heap->min = min->right;
    }
    min->left = min->right = min;
    return min;
}

//将node链接到root根结点
void fibHeapLink(FibHeap* heap, FibNode* node, FibNode* root) {
    //将node从双链表中移除
    fibNodeRemove(node);
    //将node设为root的孩子
    if (root->child == NULL) {
        root->child = node;
    }
    else {
        fibNodeAdd(node, root->child);
    }
    node->parent = root;
    root->degree++;
}

//创建fib_heap_consolidate所需空间
void fibHeapConsInit(FibHeap* heap) {
    int old = heap->maxDegree;
    //计算log2(x)，向上取整
    heap->maxDegree = (int)(log((double)(heap->keyNum)) / log(2.0)) + 1;
    //如果原本空间不够，则再次分配内存
    if (old >= heap->maxDegree) {
        return;
    }
    //因为度为heap->maxDegree可能被合并，所以要maxDegree+1
    heap->cons = (FibNode**)realloc(heap->cons, sizeof(FibHeap*) * (heap->maxDegree + 1));
}

//合并斐波那契堆的根链表中左右相同度数的树
void fibHeapConsolidate(FibHeap* heap) {
    //开辟所用空间
    fibHeapConsInit(heap);
    int i;
    int D = heap->maxDegree + 1;
    for (i = 0; i < D; i++) {
        heap->cons[i] = NULL;
    }
    //合并相同度的根结点，使每个度数的树唯一
    while (heap->min != NULL) {
        FibNode* x = fibHeapRemove_min(heap);    //取出堆中的最小树(最小结点所在的树)
        int d = x->degree;                       //获取最小树的度数
        //heap->cons[d] != NULL，意味着有两棵树(x和y)的"度数"相同。
        while (heap->cons[d] != NULL) {
            FibNode* y = heap->cons[d];         //y是"与x的度数相同的树" 
            if (x->key > y->key) {              //保证x的键值比y小
                FibNode* tmp = x;
                x = y;
                y = tmp;
            }
            fibHeapLink(heap, y, x);            //将y链接到x中
            heap->cons[d] = NULL;
            d++;
        }
        heap->cons[d] = x;
    }
    heap->min = NULL;
    //将heap->cons中的结点重新加到根表中
    for (i = 0; i < D; i++) {
        if (heap->cons[i] != NULL) {
            if (heap->min == NULL) {
                heap->min = heap->cons[i];
            }
            else {
                fibNodeAdd(heap->cons[i], heap->min);
                if ((heap->cons[i])->key < heap->min->key) {
                    heap->min = heap->cons[i];
                }
            }
        }
    }
}

//移除最小结点min
FibNode* fibHeapExtractMin_node(FibHeap* heap) {
    if (heap == NULL || heap->min == NULL) {
        return NULL;
    }
    FibNode* child = NULL;
    FibNode* min = heap->min;
    //将min每一个儿子(儿子和儿子的兄弟)都添加到"斐波那契堆的根链表"中
    while (min->child != NULL) {
        child = min->child;
        fibNodeRemove(child);
        if (child->right == child) {//感觉可以优化
            min->child = NULL;
        }
        else {
            min->child = child->right;
        }
        fibNodeAdd(child, heap->min);
        child->parent = NULL;
    }
    //将min从根链表中移除
    fibNodeRemove(min);
    if (min->right == min) { //若min是堆中唯一结点，则设置堆的最小结点为NULL；
        heap->min = NULL;
    }
    else {                   //否则，设置堆的最小结点为一个非空结点(min->right)，然后再进行调节。
        heap->min = min->right;
        fibHeapConsolidate(heap);
    }
    heap->keyNum--;
    return min;
}

int fibHeapExtractMin(FibHeap* heap) {
    FibNode* node;
    if (heap == NULL || heap->min == NULL) {
        return 0;
    }
    node = fibHeapExtractMin_node(heap);
    if (node != NULL) {
        int a = node->key;
        free(node);
        return a;
    }
}
//从node开始销毁结点 
void fibNodeDestroy(FibNode* node) {
    FibNode* start = node;
    if (node == NULL) {
        return;
    }
    do {
        fibNodeDestroy(node->child);
        // 销毁node，并将node指向下一个
        node = node->right;
        free(node->left);
    } while (node != start);
}

//销毁斐波那契堆
void fibHeapDestroy(FibHeap* heap) {
    fibNodeDestroy(heap->min);
    free(heap->cons);
    free(heap);
}

int* fibSort(FibHeap* heap) {
    int* a = (int*)malloc(sizeof(int) * heap->keyNum);
    int length = heap->keyNum;
    for (int i = 0; i < length; i++) {
        a[i] = fibHeapExtractMin(heap);
    }
    return a;
}
