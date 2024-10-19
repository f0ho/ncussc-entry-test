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
            if (smallChilden < length && arry[smallChilden] > arry[smallChilden + 1]) smallChilden += 1;//如果有右孩且右孩子比左孩子小
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