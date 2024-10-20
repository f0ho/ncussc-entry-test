#include"bubbleSort.h"
#include"heapSort.h"
#include"fibSort.h"
#include<stdio.h>
#include <sys/resource.h>
#include<time.h>
#include <stdlib.h>


void main(){
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


    //冒泡排序测试
    // struct rusage usage;
    // getrusage(RUSAGE_SELF, &usage);
    // const int length = 100000;
    // int a[length];
    // int index = 0;
    // FILE* f = fopen("../data/5_3.txt","r");
    // while(fscanf(f,"%d",&a[index]) == 1){
    //     index++;
    // }
    // fclose(f);
     
    // clock_t start = clock();
    // bubbleSort(a, length);
    // clock_t end = clock();
    // double timeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    // FILE* file = fopen("../data/Ofast/bubbleSort_5_3.txt","w");
    // fprintf(file, "用时:%fs\n占用内存%ldKB\n排序结果为:\n", timeUsed, usage.ru_maxrss);
    // for(int i = 0; i < length; i++){
    //     fprintf(file, "%d ",a[i]);
    // }
    // fclose(file);

    //堆排序测试
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    const int length = 10;
    int a[length];
    int index = 0;
    FILE* f = fopen("../data/1_1.txt","r");
    while(fscanf(f,"%d",&a[index]) == 1){
        index++;
    }
    fclose(f);

    clock_t start = clock();
    int* b = (int*)malloc(sizeof(int) * length);
    b = heapSort(a, length);
    clock_t end = clock();
    double timeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    FILE* file = fopen("../data/O0/heapSort_1_1.txt","w");
    fprintf(file, "用时:%fs\n占用内存%ldKB\n排序结果为:\n", timeUsed, usage.ru_maxrss);
    for(int i = 0; i < length; i++){
        fprintf(file, "%d ",b[i]);
    }
    fclose(file);

    //斐波那契排序
    // struct rusage usage;
    // getrusage(RUSAGE_SELF, &usage);
    // const int length = 100000;
    // int a[length];
    // int index = 0;
    // FibHeap* heap = fibHeapMake();
    // FILE* f = fopen("../data/5_3.txt","r");
    // while(fscanf(f,"%d",&a[index]) == 1){
    //     fibHeapInsert_key(heap,a[index]);
    //     index++;
    // }
    // fclose(f);
    // int* b = (int*)malloc(sizeof(int) * length);
    // clock_t start = clock();
    // b = fibSort(heap);
    // clock_t end = clock();
    // double timeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    // FILE* file = fopen("../data/O0/fibSort_5_3.txt","w");
    // fprintf(file, "用时:%fs\n占用内存%ldKB\n排序结果为:\n", timeUsed, usage.ru_maxrss);
    // for(int i = 0; i < length; i++){
    //     fprintf(file, "%d ",b[i]);
    // }
    // fclose(file);


}