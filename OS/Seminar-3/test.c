#include <stdio.h>
#include <unistd.h>
#include "green.h"

#define LOOP 10

int flag = 0;
int buffer = 0;
green_cond_t cond,full,empty;
green_mutex_t mutex;

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
        while(buffer == 1) green_cond_wait(&empty, &mutex); //Buffer (flag) = full
        buffer = 1;
        printf("thread %d: %d\n", id, buffer);
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
        while(buffer == 0) green_cond_wait(&full, &mutex); //Buffer (flag) = empty
        buffer = 0;
        printf("thread %d: %d\n", id, buffer);
        green_cond_signal(&empty);
        green_mutex_unlock(&mutex);
        loop--;
    }
}

int main(){
    green_t g0, g1;
    int a0 = 0;
    int a1 = 1;
    green_cond_init(&cond);
    green_mutex_init(&mutex);
    green_create(&g0, producer, &a0);
    green_create(&g1, consumer, &a1);

    green_join(&g0, NULL);
    green_join(&g1, NULL);
    printf("done\n");
    return 0;
}