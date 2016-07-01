#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

static void* thread_start(void *arg)
{
    int *num = (int *)arg;

    cout << "in new thread" << endl;

    if (*num <= 10 || *num >20) {
        sleep(17);
        *num = 17;
    } else {
        sleep(*num);
    }

    return arg;
}

int main()
{
    pthread_t thread;
    pthread_attr_t attr;
    int arg = 7;
    int *ret;

    int res = pthread_attr_init(&attr);
    if (res != 0) {
        cout << "pthread_attr_init() is fail, res = " << res << endl;
        return 1;
    }

    res = pthread_create(&thread, &attr, &thread_start, &arg);
    if (res != 0) {
        cout << "pthread_create() is fail, res = " << res << endl;
        return 1;
    }

    res = pthread_attr_destroy(&attr);
    if (res != 0) {
        cout << "pthread_attr_destroy() is fail, res = " << res << endl;
        return 1;
    }

    res = pthread_join(thread, (void **)&ret);
    if (res != 0) {
        cout << "pthread_join() is fail, res = " << res << endl;
        return 1;
    }

    cout << "sleep() " << *ret << " sec" << endl;

    return 0;
}

