/*
test thoi gian th?c hien cua cac thu?t toan co ban

 

**/

 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h> // cho memcpy
#include <stdint.h>
#include <sys/time.h>
#include <bits/stdc++.h>
using namespace std;
// ham tru thoi gian
struct timeval timeSub(struct timeval s, struct timeval e)
{
    struct timeval tval_result;
    tval_result.tv_sec = e.tv_sec - s.tv_sec;
    tval_result.tv_usec = e.tv_usec - s.tv_usec;
    if(tval_result.tv_usec<0) {
        tval_result.tv_usec = 1000000+tval_result.tv_usec;
        tval_result.tv_sec--;
    }
    return tval_result;
}

 

// sinh mang ngau nhien
int * generateArray(int size)
{
    srand(time(NULL));
    int *retArr = (int*)malloc(size*sizeof(int));
    for(int i=0; i<size; i++)
        retArr[i]=rand();
    return retArr;
}
// tao ra copy cua mang ban dau
int *cloneArr(int * input, int size)
{
    int *copyArr = (int*)malloc(size*sizeof(int));
    memcpy(copyArr, input, size*sizeof(int));
    return copyArr;
}
// doi cho 2 phan tu
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
// ham in mang
void printArr(const int *input, int size)
{
    printf("Cac phan tu trong mang kich thuoc %d la: \n",size);
    for(int i=0; i<size; i++)
    {
        printf("%5d, ", input[i]);
        if((i+1)%10==0) printf("\n");
    }
        
    printf("\n");
}
// sap xep noi bot
void bubblesort(int *input, int size)
{
    for(int i=size; i>1; i--)
       for(int j=1; j<i; j++)
             if(input[j-1]>input[j]) swap(&input[j-1], &input[j]);
}

 

// sap xep noi bot v2 thêm dừng sớm
void bubblesort_v2(int *input, int size)
{
    int countSwap = 0;
    for(int i=size; i>1; i--)
    {
        countSwap = 0;
        for(int j=1; j<i; j++){
               if(input[j-1]>input[j]) {
                     swap(&input[j-1], &input[j]);
                     countSwap++;
             }            
       }
       if(countSwap==0) return;
    }   
}
// sap xep lua chon
void selectionsort(int *input, int size)
{
    for(int i=size; i>1; i--) // cuoi day la i-1
    {
        int vtMax = 0;
        for(int j=1; j<i; j++)
            if(input[j]>input[vtMax]) vtMax=j;
        
        swap(&input[vtMax], &input[i-1]);
    }
}

 

// sap xep lua chon ban 2 them dung som
void selectionsort_v2(int *input, int size)
{
    int count = 0;
    for(int i=size; i>1; i--) // cuoi day la i-1
    {
        count = 0;
        int vtMax = 0;
        for(int j=1; j<i; j++){
            if(input[j]>input[vtMax]) vtMax=j;
            if(input[j]<input[j-1]) count++;
        }    
        swap(&input[vtMax], &input[i-1]);
        if(count==0) return;
    }
}
// sap xep chen tren mang
void insertionSort(int *A, int N) {
  // index tu 1 -> N
  for(int k = 2; k <= N; k++)
  {
   int last = A[k];
   int j = k;
   while(j > 1 && A[j-1] > last)
   {
     A[j] = A[j-1];
     j--;
   }
   A[j] = last;
  }
}
// cải tiến dùng 1 mảng cấp phát động và đổi vai trò mảng chính/phụ
void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

 

  // mảng phụ dùng cho việc trộn 2 danh sách
  int L[n1], R[n2];

 

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

 

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

 

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

 

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }
}

 

void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

 

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

 

    merge(arr, l, m, r);
  }
}

 

// cải tiến: chọn chốt ngẫu nhiên
int partition (int arr[], int low, int high) 
{
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high) 
{
    if (low < high) 
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}



int partition_v2 (int arr[], int low, int high) 
{
    int pivot = (rand()%(high-low)) + low;
    int tmp = arr[high];
    arr[high]=arr[pivot];
    arr[pivot] = tmp;
    
    //int pivot = arr[high];
    pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high- 1; j++) 
    {
        if (arr[j] <= pivot) 
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

 

void quickSort_v2(int arr[], int low, int high) 
{
    if (low < high) 
    {
        int pi = partition_v2(arr, low, high);
        quickSort_v2(arr, low, pi - 1);
        quickSort_v2(arr, pi + 1, high);
    }
}

 

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

 

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
// thử đổi dãy tăng xem thời gian có cải thiện?
// shellsort dua tren thuat toan sap xep lua chon
void shellSort(int arr[], int n)
{
    for (int gap = n/2; gap > 0; gap /= 2) // dãy tăng đang là n/2
    {
        for (int i = gap; i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

 


 
// A utility function to swap the values pointed by
// the two pointers
void swapValue(int* a, int* b)
{
    int* temp = a;
    a = b;
    b = temp;
    return;
}
 
/* Function to sort an array using insertion sort*/
void InsertionSort(int arr[], int* begin, int* end)
{
    // Get the left and the right index of the subarray
    // to be sorted
    int left = begin - arr;
    int right = end - arr;
 
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
                greater than key, to one position ahead
                of their current position */
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
 
    return;
}
 
// A function to partition the array and return
// the partition point
int* Partition(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element
 
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot) {
            // increment index of smaller element
            i++;
 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (arr + i + 1);
}
 
// A function that find the middle of the
// values pointed by the pointers a, b, c
// and return that pointer
int* MedianOfThree(int* a, int* b, int* c)
{
    if (*a < *b && *b < *c)
        return (b);
 
    if (*a < *c && *c <= *b)
        return (c);
 
    if (*b <= *a && *a < *c)
        return (a);
 
    if (*b < *c && *c <= *a)
        return (c);
 
    if (*c <= *a && *a < *b)
        return (a);
 
    if (*c <= *b && *b <= *a)
        return (b);
    return NULL;
}
 
// A Utility function to perform intro sort
void IntrosortUtil(int arr[], int* begin, int* end,
                   int depthLimit)
{
    // Count the number of elements
    int size = end - begin;
 
    // If partition size is low then do insertion sort
    if (size < 16) {
        InsertionSort(arr, begin, end);
        return;
    }
 
    // If the depth is zero use heapsort
    if (depthLimit == 0) {
        make_heap(begin, end + 1);
        sort_heap(begin, end + 1);
        return;
    }
 
    // Else use a median-of-three concept to
    // find a good pivot
    int* pivot
        = MedianOfThree(begin, begin + size / 2, end);
 
    // Swap the values pointed by the two pointers
    swapValue(pivot, end);
 
    // Perform Quick Sort
    int* partitionPoint
        = Partition(arr, begin - arr, end - arr);
    IntrosortUtil(arr, begin, partitionPoint - 1,
                  depthLimit - 1);
    IntrosortUtil(arr, partitionPoint + 1, end,
                  depthLimit - 1);
 
    return;
}
 
/* Implementation of introsort*/
void Introsort(int arr[], int* begin, int* end)
{
    int depthLimit = 2 * log(end - begin);
 
    // Perform a recursive Introsort
    IntrosortUtil(arr, begin, end, depthLimit);
 
    return;
}

 

int main()
{
    int *A, size;
    size = 100000;
    A = generateArray(size);
    printf("Mang ban dau: \n");
    //printArr(A, size);
    struct timeval tval_before, tval_after, tval_result;
    
    // minh hoa bubble sort
    int *copiedArr = NULL;
    
    copiedArr = cloneArr(A, size);
    // tinh thoi gian
    printf("Sap xep noi bot:\n");
    gettimeofday(&tval_before, NULL);
    
    bubblesort(copiedArr, size);    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    //printf("Mang sau khi bubblesort: \n");
    //printArr(copiedArr, size);

 

    // minh hoa bubble sort V2
    printf("Sap xep noi bot ban 2:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    gettimeofday(&tval_before, NULL);
    
    bubblesort_v2(copiedArr, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    // minh hoa selection sort
    printf("Sap xep lua chon:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    gettimeofday(&tval_before, NULL);
    
    selectionsort(copiedArr, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    //printf("Mang sau khi selectionsort: \n");
    //printArr(copiedArr, size);
    
    // minh hoa selection sort
    printf("Sap xep lua chon ban 2:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    gettimeofday(&tval_before, NULL);
    
    selectionsort_v2(copiedArr, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    // minh hoa insertion sort
    printf("Sap xep chen - Insertion Sort:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    
    gettimeofday(&tval_before, NULL);
    
    insertionSort(copiedArr, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    //printf("Mang sau khi insertionsort: \n");
    //printArr(copiedArr, size);

 

    // Sap xep Shellsort - Shellsort 
    printf("Sap xep Shellsort - Shellsort:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    
    gettimeofday(&tval_before, NULL);
    
    shellSort(copiedArr,size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    // Sap xep tron - MergeSort 
    printf("Sap xep tron - Merge Sort:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    
    gettimeofday(&tval_before, NULL);
    
    mergeSort(copiedArr,0, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    // sap xep nhanh - Quick sort
    printf("Sap xep nhanh - Quick sort:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    
    gettimeofday(&tval_before, NULL);
    
    quickSort(copiedArr,0, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    // sap xep nhanh - Quick sort
    printf("Sap xep nhanh - Quick sort V2:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    srand(time(NULL));
    gettimeofday(&tval_before, NULL);
    
    quickSort_v2(copiedArr,0, size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    // sap xep vun dong - Heapsort
    printf("Sap xep vun dong - Heapsort:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    
    gettimeofday(&tval_before, NULL);
    
    heapSort(copiedArr,size);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    // sap xep IntroSort
    printf("Sap xep IntroSort - IntroSort:\n");
    free(copiedArr);
    copiedArr = cloneArr(A, size);    
    
    gettimeofday(&tval_before, NULL);
    
    Introsort(copiedArr,copiedArr, copiedArr + size-1);    
    
    gettimeofday(&tval_after, NULL);
    tval_result = timeSub(tval_before, tval_after);
    printf("thoi gian sap xep : %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    
    
    return 0;
}