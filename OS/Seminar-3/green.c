#define _POSIX_SOURCE
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
#define PERIOD 100

static ucontext_t main_cntx = {0};
static green_t main_green = {&main_cntx, NULL, NULL, NULL, NULL, NULL, FALSE};

static green_t *running = &main_green;

static sigset_t block;

static void init() __attribute__((constructor));

static void enqueue_ready(green_t *thread){
    if(running == NULL) running = thread;
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

static green_t *next_running(){
    green_t *current = running;
    if(current->next != NULL) current = current->next;
    else current = &main_green;
    return current;
}

void timer_handler(int sig){
    green_yield();
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

int green_mutex_init(green_mutex_t *mutex){
    mutex->taken = FALSE;
    mutex->susp = NULL;
}

void green_thread(){
    green_t *this = running;

    void *result = (*this->fun)(this->arg);

    if(this->join != NULL){
        sigprocmask(SIG_BLOCK, &block, NULL);
        enqueue_ready(this->join);
        sigprocmask(SIG_UNBLOCK, &block, NULL);
    } 

    free(this->context->uc_stack.ss_sp);
    free(this->context);

    this->retval = result;

    this->zombie = TRUE;
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *next = next_running();

    running = next;
    this->next = NULL;
    setcontext(next->context);
    sigprocmask(SIG_UNBLOCK, &block, NULL);
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
    sigprocmask(SIG_BLOCK, &block, NULL);
    enqueue_ready(new);
    sigprocmask(SIG_UNBLOCK, &block, NULL);

    return 0;
}

int green_yield(){
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t * susp = running;
    if(susp->next != NULL){
        green_t *next = next_running();
        running = next;
        enqueue_ready(susp);
        swapcontext(susp->context, next->context);
    }
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}

int green_join(green_t *thread, void **res){
    if(!thread->zombie){
        sigprocmask(SIG_BLOCK, &block, NULL);
        green_t *susp = running;
        thread->join = susp;
        green_t *next = next_running();
        running = next;
        susp->next = NULL;
        swapcontext(susp->context, next->context);
        sigprocmask(SIG_UNBLOCK, &block, NULL);
    }
    res = thread->retval;

    return 0;
}

int green_mutex_lock(green_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *susp = running;
    if(mutex->taken){
        if(mutex->susp == NULL) mutex->susp = susp;
        else{
            green_t *current = mutex->susp;
            while(current->next != NULL) current = current->next;
            current->next = susp;
        }
        green_t *next = next_running();
        susp->next = NULL;
        running = next;
        swapcontext(susp->context, next->context);
    }
    mutex->taken = TRUE;
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}

int green_mutex_unlock(green_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &block, NULL);

    if(mutex->susp != NULL){
        green_t *susp = mutex->susp;
        if(susp->next == NULL) mutex->susp = NULL;
        else{
            green_t *next = susp->next;
            mutex->susp = next;
        }
        enqueue_ready(susp);
    }
    else mutex->taken = FALSE;
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}

int green_cond_wait(green_cond_t *cond, green_mutex_t *mutex){
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *susp = running;
    green_t *next = next_running();
    enqueue_cond(cond);
    if(mutex != NULL) green_mutex_unlock(mutex);
    running = next;
    swapcontext(susp->context, next->context);
    if(mutex != NULL) green_mutex_lock(mutex);
    sigprocmask(SIG_UNBLOCK, &block, NULL);
    return 0;
}

void green_cond_signal(green_cond_t *cond){
    if(cond->queue == NULL) return;
    sigprocmask(SIG_BLOCK, &block, NULL);
    green_t *signaled = cond->queue;
    if(signaled->next != NULL){
        green_t *next = signaled->next;
        cond->queue = next;
    }
    else cond->queue = NULL;
    enqueue_ready(signaled);
    sigprocmask(SIG_UNBLOCK, &block, NULL);
}