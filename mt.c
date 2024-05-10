#include <stdlib.h>
#include <pthread.h>
#define NUM_THR 10
#define NUM_WRK 10000
void * work(void *);
struct cr {
int id;
int *c;
pthread_mutex_t *mtx;
};
int main(int argc, char *argv[])
{
int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct cr ctx[NUM_THR];
pthread_t worker[NUM_THR] = {};
int i;
for (i = 0; i < NUM_THR; i++) {
ctx[i].id = i;
ctx[i].c = &counter;
ctx[i].mtx = &mutex;
pthread_create(&worker[i], NULL, work, &ctx[i]);
}
for (i = 0; i < NUM_THR; i++) {
pthread_join(worker[i], NULL);
}
printf("Counter: %d\n\n", counter);
system("pause");
return 0;
}
void * work(void *ctx) {
struct cr *ptr = (struct cr *)ctx;
pthread_mutex_lock(ptr->mtx);
int i;
for (i = 0; i < NUM_WRK; i++) *ptr->c += 1;
*ptr->c += ptr->id;
printf("Thread %d inc %d + %d: %d\n", ptr->id, NUM_WRK, ptr->id, *ptr->c);
pthread_mutex_unlock(ptr->mtx);
}