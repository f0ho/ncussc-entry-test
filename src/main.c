#include"bubbleSort.h"
#include"heapSort.h"
#include"fibSort.h"
#include<stdio.h>
#include<time.h>


void main(){
    const int length = 10;
    int a[length];
    int index = 0;
    FILE* f = fopen("../data/1_1.txt","r");
    while(fscanf(f,"%d",&a[index]) == 1){
        index++;
    }
    fclose(f);
    clock_t start = clock();
    bubbleSort(a, length);
    clock_t end = clock();
    double timeUsed = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("用时:%fms\n排序结果为:\n", timeUsed);
    for(int i = 0; i < 10; i++){
        printf("%d ",a[i]);
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