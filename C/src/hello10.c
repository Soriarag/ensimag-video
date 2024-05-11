
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <threads.h>
#include <stdbool.h>
#include <stdlib.h>  

typedef struct {

    mtx_t m;
    cnd_t c;
    int compteur;

} moniteur;

bool done = false;

void incr_compteur(void* mon){

    moniteur *m = (moniteur *)mon;
    mtx_lock(&m->m);
    m->compteur += 1;
    
    if (m->compteur == 10)
    {
        done = true;
        cnd_broadcast(&m->c);
    }

    mtx_unlock(&m->m);
}

void attendre_compteur(void* mon){

    moniteur *m = (moniteur *)mon;
    while (!done){
        cnd_wait(&m->c, &m->m);
    }
    
}

void printHelloWorld(void* mon){

    moniteur *m = (moniteur *)mon;
    incr_compteur(mon);
    printf("Hello World! %d\n", m->compteur);
    
}

void printDone(void* m){

    attendre_compteur(m);
    printf("Done !\n");

}

// int compteur = 0;
// mtx_t m;
// cnd_t c10;


int main(int argc, char const *argv[])
{

    thrd_t helloWorld_pid[10], done_pid;
    moniteur *m = malloc(sizeof(moniteur));

    void *args;
    for (int i = 0; i < 10; i++)
    {
        thrd_create(&helloWorld_pid[i], printHelloWorld, m);
    }
    
    thrd_create(&done_pid, printDone, m);

    for (int i = 0; i < 10; i++)
    {
        thrd_join(helloWorld_pid[i], NULL);
    }

    thrd_join(done_pid, NULL);
        
    return 0;
}
