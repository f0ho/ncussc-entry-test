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
    // struct rusage usage;
    // getrusage(RUSAGE_SELF, &usage);
    // const int length = 100000;
    // int a[length + 1];//第一个为占位符
    // a[0] = 1;
    // int index = 1;
    // FILE* f = fopen("../data/5_3.txt","r");
    // while(fscanf(f,"%d",&a[index]) == 1){
    //     index++;
    // }
    // fclose(f);

    // clock_t start = clock();
    // int* b = (int*)malloc(sizeof(int) * length + 1);
    // b = heapSort(a, length);
    // clock_t end = clock();
    // double timeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    // FILE* file = fopen("../data/Ofast/heapSort_5_3.txt","w");
    // fprintf(file, "用时:%fs\n占用内存%ldKB\n排序结果为:\n", timeUsed, usage.ru_maxrss);
    // for(int i = 1; i < length + 1; i++){
    //     fprintf(file, "%d ",b[i]);
    // }
    // fclose(file);

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

    //对实验数据求平均值
    // FILE* f1 = fopen("../data/O0/heapSort_1_1.txt","r");
    // FILE* f2 = fopen("../data/O0/heapSort_1_2.txt","r");
    // FILE* f3 = fopen("../data/O0/heapSort_1_3.txt","r");
    // int m1,m2,m3,m0;
    // double t1,t2,t3,t0;
    // char buffer[100];

    // // 从 f1 读取
    // fgets(buffer, sizeof(buffer), f1);  // 第一行：用时
    // sscanf(buffer, "用时:%lfs", &t1);
    // fgets(buffer, sizeof(buffer), f1);  // 第二行：占用内存
    // sscanf(buffer, "占用内存%dKB", &m1);

    // // 从 f2 读取
    // fgets(buffer, sizeof(buffer), f2);
    // sscanf(buffer, "用时:%lfs", &t2);
    // fgets(buffer, sizeof(buffer), f2);
    // sscanf(buffer, "占用内存%dKB", &m2);

    // // 从 f3 读取
    // fgets(buffer, sizeof(buffer), f3);
    // sscanf(buffer, "用时:%lfs", &t3);
    // fgets(buffer, sizeof(buffer), f3);
    // sscanf(buffer, "占用内存%dKB", &m3);
    // m0 = (m1 + m2 + m3) / 3;
    // t0 = (t1 + t2 + t3) / 3;
    // FILE* f = fopen("../data/result/O0/heapSort1.txt","w");
    // fprintf(f,"平均用时:%lfs\n占用%dKB内存",t0,m0);
    // fclose(f1);
    // fclose(f2);
    // fclose(f3);
    // fclose(f);


}