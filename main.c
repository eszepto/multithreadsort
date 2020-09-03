#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int list[] = {92,45,10,13,51,75,25,46,90,44,35,8};
void  *printi(void *param);

int main(int argc, char *argv[])
{


    for(int i=0;i<sizeof(list)/sizeof(int);i++)
    {
        printf("%i ", list[i]);

    }
    /*
    pthread_t sortThread0, sortThread1, mergeThread0;
    pthread_create(&tid0, NULL, printi, NULL);
    pthread_join(tid0,NULL);
    */
    printf("end");
}

void  *printi(void *param)
{
    printf("thread start");


}
