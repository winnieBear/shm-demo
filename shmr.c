#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "test.h" 

 
int main(int argc, char** argv)
{
    int shm_id,i;
    key_t key;
    people *p_map;
    char pathname[30] ;
    strcpy(pathname,"/tmp") ;
    key = ftok(pathname,0x03);
    if(key == -1)
    {
        perror("ftok error");
        return -1;
    }
    printf("key=%d\n", key) ;
    shm_id = shmget(key,0, 0);
    if(shm_id == -1)
    {
        perror("shmget error");
        printf("Error:code:%d-%d,Errmsg:%s",errno, ENOENT, strerror(errno));
        return -1;
    }
    printf("shm_id=%d\n", shm_id) ;
    p_map = (people*)shmat(shm_id,NULL,0);
    for(i = 0;i<3;i++)
    {
        printf( "name:%s\n",(*(p_map+i)).name );
        printf( "age %d\n",(*(p_map+i)).age );
    }
    shmctl(shm_id, IPC_RMID, NULL) ;
    if(shmdt(p_map) == -1)
    {
        perror("detach error");
        return -1;
    }
    return 0 ;
}