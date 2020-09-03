#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
static int list[] = {92,45,10,13,51,75,25,46,90,44,35,8, 3};
int listLength = sizeof(list)/sizeof(int);

void *SortList(void *param);
void *MergeList(void *param);
void PrintList();
typedef struct args{
    int* arr;
    int start;
    int stop;
} args;
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
    int firstStart = 0;
    int firstStop = listLength/2 - 1;
    int secondStart = listLength/2;
    int secondStop = listLength - 1;

    pthread_t sortThread0, sortThread1, mergeThread0;
    args args1, args2;

    args1.start = firstStart;
    args1.stop = firstStop;

    args2.start = secondStart;
    args2.stop = secondStop;

    pthread_create(&sortThread0, NULL, SortList, &args1);
    pthread_create(&sortThread1, NULL, SortList, &args2);

    pthread_join(sortThread0, NULL);
    pthread_join(sortThread1, NULL);

    pthread_create(&mergeThread0, NULL, MergeList, NULL);
    pthread_join(mergeThread0, NULL);

    PrintList();
}

void *SortList(void *param)
{
    args* ptr = (args*)param;
    int start = ptr->start;
    int stop = ptr->stop;
    quickSort(list, start, stop);
    pthread_exit(0);
}
void *MergeList(void *param)
{

    int firstStart = 0;
    int firstStop = listLength/2 - 1;
    int secondStart = listLength/2;
    int secondStop = listLength - 1;

    int temp[listLength];

    int runner1 = firstStart;
    int runner2 = secondStart;

    int i = 0;
    while(i<listLength)
    {
        if(runner1 > firstStop)
        {
            temp[i] = list[runner2];
            runner2 += 1;
        }
        else if(runner2 > secondStop)
        {
            temp[i] = list[runner1];
            runner1 += 1;
        }
        else if(list[runner1] < list[runner2])
        {
            temp[i] = list[runner1];
            runner1 += 1;
        }
        else
        {
            temp[i] = list[runner2];
            runner2 += 1;
        }

        i++;
    };
    for(int i=0;i<listLength;i++)
    {
        list[i] = temp[i];
    }

}

void PrintList()
{
    for(int i=0;i<sizeof(list)/4;i++)
    {
        printf("%i ", list[i]);
    }
}

