#include <stdio.h>
#include <unistd.h>
#include "green.h"

#define LOOP 10

int flag = 0;
green_cond_t cond;
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
            green_cond_wait(&cond);
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

int main(){
    green_t g0, g1;
    int a0 = 0;
    int a1 = 1;
    green_cond_init(&cond);
    green_mutex_init(&mutex);
    green_create(&g0, mutex_test_pass, &a0);
    green_create(&g1, mutex_test_pass, &a1);
    green_mutex_unlock(&mutex);

    green_join(&g0, NULL);
    green_join(&g1, NULL);
    printf("done\n");
    return 0;
}