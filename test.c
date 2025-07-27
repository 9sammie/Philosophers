# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

// typedef struct s_data
// {
//     bool eats;
//     bool thinks;
//     bool sleeps;
//     int  fork_array[2];
// }   t_data;

// void    *philo_routine(void *arg)
// {
//     s_data *data = (s_data *)arg;

    
//     return (NULL);
// }

// int    main()
// {
//     pthread_t thread1;
//     pthread_t thread2;
//     s_data data;

//     data.eats = false;
//     data.thinks = false
//     data.sleeps = false;
//     data.fork_array[0] = 1;
//     data.fork_array[1] = 1;
//     pthread_create(&thread1, NULL, philo_routine, &data);
//     pthread_create(&thread2, NULL, philo_routine, &data);
//     pthread_join(thread, NULL);
//     printf("i: %d\nj: %d\n", i, k);
//     return (0);
// }

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* trythis(void* arg)
{
    pthread_mutex_lock(&lock);
    // unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started\n", counter);

    // i++;

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
    while (i < 2) {
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
        if (error != 0)
            printf("\non of the thread can't be created\n");
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}