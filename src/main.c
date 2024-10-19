#include"bubbleSort.h"
#include"heapSort.h"
#include"fibSort.h"
#include<stdio.h>


void main(){
    int a[] = {0,1,4,2,3,5,1};
    FibHeap * heap = fibHeapMake();
    fibHeapInsert_key(heap, 1);
    fibHeapInsert_key(heap, 4);
    fibHeapInsert_key(heap, 2);
    fibHeapInsert_key(heap, 3);
    fibHeapInsert_key(heap, 5);
    fibHeapInsert_key(heap, 1);
    int* b = fibSort(heap);
    fibHeapDestroy(heap);
    for(int i = 0; i < 6; i++){
        printf("%d",b[i]);
    }

    

    //生成随机数
    // 设置随机种子
    // srand(time(NULL));
    // int n = 10;
    // FILE *f = fopen("../data/1_1.txt","w");
    // for (int i = 0; i < n; i++) {
    //     int random_num = rand() % 10000; // 生成0到9999之间的随机数
    //     fprintf(f, "%d ", random_num);
    // }
    // fclose(f);

}