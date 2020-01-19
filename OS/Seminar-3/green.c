#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>
#include <assert.h>
#include <signal.h>
#include <sys/time.h>
#include "green.h"

#define FALSE 0
#define TRUE 1
#define STACK_SIZE 4096
#define PERIOD 1

static ucontext_t main_cntx = {0};
static green_t main_green = {&main_cntx, NULL, NULL, NULL, NULL, NULL, FALSE};

static green_t *running = &main_green;

static sigset_t block;

static void init() __attribute__((constructor));

static void enqueue_ready(green_t *thread){
    green_t *current = running;
    while(current->next != NULL) current = current->next;
    current->next = thread;
    thread->next = NULL;
}

static void enqueue_cond(green_cond_t *cond){
    green_t *thread = running;
    if(cond->queue == NULL) cond->queue = thread;
    else{
        green_t *current = cond->queue;
        while(current->next != NULL) current = current->next;
        current->next = thread;
    }
    thread->next = NULL;
}

void timer_handler(int sig){
    green_t *susp = running;
    green_t *next = susp->next;

    enqueue_ready(susp);

    running = next;
    swapcontext(susp->context, next->context);

}

void init(){
    getcontext(&main_cntx);
    sigemptyset(&block);
    sigaddset(&block, SIGVTALRM);

    struct sigaction act = {0};
    struct timeval interval;
    struct itimerval period;

    act.sa_handler = timer_handler;
    assert(sigaction(SIGVTALRM, &act, NULL) == 0);

    interval.tv_sec = 0;
    interval.tv_usec = PERIOD;
    period.it_interval = interval;
    period.it_value = interval;
    setitimer(ITIMER_VIRTUAL, &period, NULL);
}

void green_cond_init(green_cond_t *cond){
    cond->queue = NULL;
}

void green_thread(){
    green_t *this = running;

    void *result = (*this->fun)(this->arg);

    if(this->join != NULL) enqueue_ready(this->join);

    free(this->context->uc_stack.ss_sp);
    free(this->context);

    this->retval = result;

    this->zombie = TRUE;

    green_t *next = running->next;

    running = next;
    this->next = NULL;
    setcontext(next->context);
}

int green_create(green_t *new, void *(*fun)(void*), void *arg){

    ucontext_t *cntx = (ucontext_t *)malloc(sizeof(ucontext_t));
    getcontext(cntx);

    void *stack = malloc(STACK_SIZE);

    cntx->uc_stack.ss_sp = stack;
    cntx->uc_stack.ss_size = STACK_SIZE;
    makecontext(cntx, green_thread, 0);

    new->context = cntx;
    new->fun = fun;
    new->arg = arg;
    new->next = NULL;
    new->join = NULL;
    new->retval = NULL;
    new->zombie = FALSE;

    enqueue_ready(new);

    return 0;
}

int green_yield(){
    green_t * susp = running;

    green_t *next = running->next;

    running = next;
    susp->next = NULL;
    enqueue_ready(susp);
    swapcontext(susp->context, next->context);
    return 0;
}

int green_join(green_t *thread, void **res){
    if(!thread->zombie){
        green_t *susp = running;
        thread->join = susp;

        green_t *next = running->next;

        running = next;
        susp->next = NULL;
        swapcontext(susp->context, next->context);
    }
    res = thread->retval;

    //free(thread->context->uc_stack.ss_sp);
    //free(thread->context);

    return 0;
}

void green_cond_wait(green_cond_t *cond){
    green_t *susp = running;
    green_t *next = running->next;
    enqueue_cond(cond);

    running = next;
    swapcontext(susp->context, next->context);
}

void green_cond_signal(green_cond_t *cond){
    if(cond->queue == NULL) return;
    enqueue_ready(cond->queue);
    cond->queue = cond->queue->next;
}