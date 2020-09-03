#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int list[] = {92,45,10,13,51,75,25,46,90,44,35,8};
void  *printi(void *param);
/* C implementation QuickSort */
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[])
{

    int start = 0;
    int stop = sizeof(list)/4 - 1;
    quickSort(list, start, stop);
    for(int i=0;i<=sizeof(list)/4;i++)
    {
        printf("%i ", list[i]);
    }
    /*
    pthread_t sortThread0, sortThread1, mergeThread0;
    pthread_create(&tid0, NULL, printi, NULL);
    pthread_join(tid0,NULL);
    */

}

void  *printi(void *param)
{
    printf("thread start");


}
