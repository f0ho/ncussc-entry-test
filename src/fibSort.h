#ifndef FIBO_SORT
#define FIBO_SORT

typedef int Type;

typedef struct FibNode {
    Type key;                     
    int degree;                  
    struct FibNode* left;        
    struct FibNode* right;        
    struct FibNode* child;         
    struct FibNode* parent;          
}FibNode;

typedef struct FibHeap {
    int   keyNum;                    
    int   maxDegree;                  
    struct FibNode* min;             
    struct FibNode** cons;            
}FibHeap;

void fibHeapInsert_key(FibHeap* heap, Type key);

FibHeap* fibHeapMake();

int* fibSort(FibHeap* heap);

void fibHeapDestroy(FibHeap* heap);

#endif