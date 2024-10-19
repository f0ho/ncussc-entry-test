### C 语言排序算法性能测试

## 摘要

## 前言
什么样的程序才是好的程序?对于用户来说好的程序代表着人性化的交互界面,高效率,安全等等.而效率就像货币一样,通过牺牲效率我们可以换来更安全的程序,更方便的图形界面.一个好的算法往往可以带来更高的效率.本次实验将实现三个经典的排序算法:冒泡排序,堆排和斐波那契排序并测试这三种算法在不同数据量下的性能.

# 环境配置
-   下载VMware和Ubuntu22.04 LTS
    本实验在Linux虚拟机中进行所以先安装虚拟机软件.在[VMware官网](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion)下载VMware并进行安装,再到[ubuntu官网](https://cn.ubuntu.com/download)下载Ubuntu22.04 LTS.
-   安装Linux系统
    打开VMware创建新的虚拟机,选择自定义后按下一步至选择系统文件处.选择下载好的Ubuntu系统并按下一步安装.设置密码后设置虚拟机安装位置.选择合适的配置后安装虚拟机.按推荐方式安装Ubuntu后将自动进行网络配置.
-   安装gcc,vscode
    待Ubuntu安装完成后在终端中执行
    `sudo apt install gcc`
    `sudo apt install build-essential`
    安装gcc.通过`gcc --version`检查gcc是非安装成功.
    并于[vscode官网](https://code.visualstudio.com/)安装vscode安装包,
    下载完后双击安装.
## 算法实现
-   #冒泡排序
    ```c
    #include "bubbleSort.h"

    void bubbleSort(int* arry, int length){
        int flag = 1;
        for (int i = 0; i < length - 1; i++){
            flag = 1;
            for (int j = 0; j< length - 1 - i; j++){
                if (arry[j] > arry[j + 1]){
                   int tmp = arry[j];
                    arry[j] = arry[j + 1];
                   arry[j + 1] = tmp;
                    flag = 0;
                }
            }
            if (flag) break;
        }
    }
-   #堆排序
    ```c
    #include<stdlib.h>

    int* heapSort(int* arry, int length){
        //堆化
       for (int i = length; i > 1; i--){
            int index = i; 
           while (index > 1) {
                if (arry[index] < arry[index / 2]){
                   int tmp = arry[index];
                   arry[index] = arry[index / 2];
                   arry[index / 2] = tmp;
                   index /= 2;
               }else break;
           }
      }

       int length2 = length;
       int* result = (int*)(malloc((length2 + 1) * sizeof(int)));
       result[0] = 0;
      //取出堆中最小值
      for (int i = 1; i < length2 + 1; i++){
          int min = 1;
          int smallChilden = min * 2;
          result[i] = arry[1];
          arry[1] = arry[length];//将最后一个叶子节点放至根节点
          length -= 1;
          //当有子结点时进行循环，维持堆结构
          while (min * 2 < length + 1) {
              if (smallChilden < length && arry[smallChilden] > arry[smallChilden + 1]) smallChilden +=   1;//如果有右孩且右孩子比左孩子小
               if (arry[min] > arry[smallChilden]) {
                   int tmp = arry[min];
                   arry[min] = arry[smallChilden];
                   arry[smallChilden] = tmp;
                   min = smallChilden;
                   smallChilden *= 2;
               }else{
                   break;
               }
           }
       }

       return result;
    }
-   #斐波那契排序
    ```c
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
##  测试数据生成
    ```c
    srand(time(NULL)); //设置随机种子
    int n = 10;
    FILE *f = fopen("../data/1_1.txt","w");
    for (int i = 0; i < n; i++) {
        int random_num = rand() % 10000; // 生成0到9999之间的随机数
        fprintf(f, "%d ", random_num);
    }
    fclose(f);
    /*
        在main函数中使用以上代码随机生成一些数并储存在data文件夹中,每次手动改变n数量为10,100,1000,10000,100000后运行三次分别生成1_1.txt,1_2.txt,1_3.txt以及2_1.txt,2_2.txt等等
    */

















































































































































































































































































    


















































































































































































































































