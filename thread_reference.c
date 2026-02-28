#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *print_message(void *ptr)
{
    char *message = (char *)ptr;

    for (int i = 0; i < 3; i++)
    {
        printf("%s: iteration %d\n", message, i);
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    const char *msg1 = "Thread 1";
    const char *msg2 = "Thread 2";

    // Arguments: (thread_id, attributes, function_to_run, argument_to_pass)
    if (pthread_create(&thread1, NULL, print_message, (void *)msg1))
    {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, print_message, (void *)msg2))
    {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // (wait for them to finish)
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished execution.\n");

    return 0;
}