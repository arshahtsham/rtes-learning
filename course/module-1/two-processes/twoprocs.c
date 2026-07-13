#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

int main()
{
    sem_t *parentToChild;
    sem_t *childToParent;

    parentToChild = sem_open("/p2c", O_CREAT, 0700, 0);
    childToParent = sem_open("/c2p", O_CREAT, 0700, 0);

    if (fork() == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            sem_wait(parentToChild);
            printf("Child: running step %d\n", i + 1);
            sem_post(childToParent);
        }

        sem_close(parentToChild);
        sem_close(childToParent);
        exit(0);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Parent: starting step %d\n", i + 1);
            sem_post(parentToChild);
            sem_wait(childToParent);
        }

        wait(NULL);

        sem_close(parentToChild);
        sem_close(childToParent);

        sem_unlink("/p2c");
        sem_unlink("/c2p");
    }

    return 0;
}