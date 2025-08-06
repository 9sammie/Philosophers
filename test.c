# include "philo.h"

pthread_t tid[4];
int counter;
pthread_mutex_t lock;

void* trythis(void* arg)
{
    pthread_mutex_lock(&lock);
    counter += 1;
    printf("\n Job %d has started\n", counter);

    printf("\n Job %d has finished\n", counter);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void)
{
    int i = 0;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0) 
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
    while (i < 4)
    {
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
        if (error != 0)
            printf("\non of the thread can't be created\n");
        i++;
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
