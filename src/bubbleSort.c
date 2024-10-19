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