#include <sys/shm.h>

#define KEY "Foo" 
#define SIZE 1024
#define SHM_MODE 0600

int main(void)
{
    int shmid;
    char * shmptr;

    printf("begin ---\n");
    if((shmid = shmget(KEY, 0, SHM_MODE)) < 0){
        printf("shmget error");
        return -1;
    }
    if((shmptr = shmat(shmid, 0, 0)) == (void *)-1){
        printf("shmat error");
        return -1;
    }

    printf("%s",shmptr);

    i(shmctl(shmid,IPC_RMID, 0) < 0){
        printf("shmctrl error");
        return -1;
    }

    return 0;
} 

