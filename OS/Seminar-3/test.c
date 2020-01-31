#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "green.h"

#define LOOP 1000000
#define ROUNDS 1000
#define THREADS 2

int flag = 0;
int buffer = 0;
green_cond_t cond,full,empty;
pthread_cond_t pfull,pempty;
green_mutex_t mutex;
pthread_mutex_t pmutex;

void *test(void *arg){
    int i = *(int*)arg;
    int loop = LOOP;
    while(loop > 0){
        printf("thread %d: %d\n", i, loop);
        loop--;
        green_yield();
    }
}

void *cond_test(void *arg){
    int id = *(int*)arg;
    int loop = LOOP;
    while(loop > 0){
        if(flag == id){
            printf("thread %d: %d\n", id, loop);
            loop--;
            flag = (id + 1) % 2;
            green_cond_signal(&cond);
        }else{
            green_cond_wait(&cond, NULL);
        }
    }
}

void *interrupt_test(void *arg){
    int id = *(int*)arg; 
    int loop = LOOP;
    while(loop > 0){
        if(flag == id){
            printf("thread %d: %d\n", id, loop);
            loop--;
            flag = (id + 1) % 2;
        }
    }
}

void *mutex_test_pass(void *arg){
    int id = *(int*)arg;
    int i;
    
    for(i = 0;i < 10000; i++){
        green_mutex_lock(&mutex);
        int temp = flag;
        int j;
        for(j = 0; j < 1000; j++){
            j = j;
        }
        temp++;
        flag = temp;
        green_mutex_unlock(&mutex);
    }
    
    printf("thread %d done, flag: %d\n", id, flag);
}

void *mutex_test_fail(void *arg){
    int id = *(int*)arg;
    int i;
    for(i = 0;i < 10000; i++){
        int temp = flag;
        int j;
        for(j = 0; j < 1000; j++){
            j = j;
        }
        temp++;
        flag = temp;
    }
    printf("thread %d done, flag: %d\n", id, flag);
}

void *producer(void *arg){
    int id = *(int*)arg;
    int loop = LOOP;
    while (loop > 0){
        green_mutex_lock(&mutex);
        if(buffer == 1) green_cond_wait(&empty, &mutex); //Buffer (flag) = full
        buffer = 1;
        green_cond_signal(&full);
        green_mutex_unlock(&mutex);
        loop--;
    }
}

void *consumer(void *arg){
    int id = *(int*)arg;
    int loop = LOOP;
    while (loop > 0){
        green_mutex_lock(&mutex);
        if(buffer == 0) green_cond_wait(&full, &mutex); //Buffer (flag) = empty
        buffer = 0;
        green_cond_signal(&empty);
        green_mutex_unlock(&mutex);
        loop--;
    }
}

void *pproducer(void *arg){
    int id = *(int*)arg;
    int loop = LOOP;
    while (loop > 0){
        pthread_mutex_lock(&pmutex);
        while(buffer == 1) pthread_cond_wait(&pempty, &pmutex); //Buffer (flag) = full
        buffer = 1;
        printf("thread %d: %d\n", id, buffer);
        pthread_cond_signal(&pfull);
        pthread_mutex_unlock(&pmutex);
        loop--;
    }
}

void *pconsumer(void *arg){
    int id = *(int*)arg;
    int loop = LOOP;
    while (loop > 0){
        pthread_mutex_lock(&pmutex);
        while(buffer == 0) pthread_cond_wait(&pfull, &pmutex); //Buffer (flag) = empty
        buffer = 0;
        printf("thread %d: %d\n", id, buffer);
        pthread_cond_signal(&pfull);
        pthread_mutex_unlock(&pmutex);
        loop--;
    }
}

void *green_benchmark(){ 
    clock_t start, end;
    double time_used, average;
    int i, j;
    green_t threads[THREADS];
    int a[THREADS];
    for(i = 0; i < THREADS; i++){
        green_t g;
        threads[i] = g;
        a[i] = i;
    }
    for(j = 0; j < ROUNDS; j++){
        green_cond_init(&empty);
        green_cond_init(&full);
        green_mutex_init(&mutex);
        buffer = 0;
        for(i = 0; i < THREADS; i++){
            if(i % 2 == 0)  green_create(&threads[i], producer, &a[i]);
            else            green_create(&threads[i], consumer, &a[i]);
        }
        start = clock();
        for(i = 0; i < THREADS; i++){
            green_join(&threads[i], NULL);
        }
        end = clock();
        time_used = (double)(end - start)/CLOCKS_PER_SEC;
        average += time_used;
    }
    //printf("Green average time: %fs\n", average/ROUNDS);
    printf("\t%f\n", average/ROUNDS);
}

void *posix_benchmark(){
    clock_t start, end;
    double time_used, average;
    int i, j;
    pthread_t threads[THREADS];
    int a[THREADS];
    for(i = 0; i < THREADS; i++){
        pthread_t g;
        threads[i] = g;
        a[i] = i;
    }
    for(j = 0; j < ROUNDS; j++){
        pthread_cond_init(&pfull, NULL);
        pthread_cond_init(&pempty, NULL);
        pthread_mutex_init(&pmutex, NULL);
        buffer = 0;
        for(i = 0; i < THREADS; i++){
            if(i % 2 == 0)  pthread_create(&threads[i], NULL, pproducer, &a[i]);
            else            pthread_create(&threads[i], NULL, pconsumer, &a[i]);
            printf("a\n");
        }
        start = clock();
        for(i = 0; i < THREADS; i++){
            printf("b\n");
            pthread_join(threads[i], NULL);
            
        }
        end = clock();
        time_used = (double)(end - start)/CLOCKS_PER_SEC;
        average += time_used;
    }
    printf("Posix average time: %fms\n", average/ROUNDS);
}

int main(){
    green_t g0, g1;
    int a0 = 0;
    int a1 = 1;
    green_cond_init(&cond);
    green_cond_init(&full);
    green_cond_init(&empty);
    green_mutex_init(&mutex);
    pthread_cond_init(&pfull, NULL);
    pthread_cond_init(&pempty, NULL);
    pthread_mutex_init(&pmutex, NULL);

    printf("%d",LOOP);
    green_benchmark();
    //posix_benchmark();

    //green_create(&g0, producer, &a0);
    //green_create(&g1, consumer, &a1);

    //green_join(&g0, NULL);
    //green_join(&g1, NULL);
    //printf("done\n");
    return 0;
}