#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "device_id_fifo.h"

#define BUFFERSIZE 20
#define FIFONAME_PATH "../deviceid_fifo"

//flag 表示读写 ,0表示读,1表示写
int static fifo_init(int flag)
{
    int fifo_fd;
    //创建管道文件,如果文件存在则不创建
    if((mkfifo(FIFONAME_PATH,0666) < 0 ) && (errno != EEXIST))
    {
        fprintf(stderr,"Fail to mkfifo %s :%s\n",FIFONAME_PATH,strerror(errno));
        exit(EXIT_FAILURE);
    }
    //打开管道文件
    if(flag)
    {
        if((fifo_fd=open(FIFONAME_PATH,O_WRONLY))< 0)
        {
            fprintf(stderr,"Fail to open %s:%s\n",fifoname,strerror(errno));
            exit(EXIT_FAILURE);
        }
    }else
    {
        if((fifo_fd=open(FIFONAME_PATH,O_RDONLY))< 0)
        {
            fprintf(stderr,"Fail to open %s:%s\n",fifoname,strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    return fifo_fd;
}
Tbl_Device_Control  read_device_id_fifo()
{

    Tbl_Device_Control device_struct;
    int fifo_fd,deviceid;
    char sql[20];
    fifo_fd=fifo_init(0);
    if((read(fifo_fd,&deviceid,sizeof(int)))<0)
    {
        fprintf(stderr,"Fail to read deviceid_fifo :%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    sprintf(sql," and deviceid = %d",deviceid);
    device_struct= Tbl_Device_ControlFindSingle(sql);
    printf("DeviceID:%d\n RFIDSet:%d\n,AlarmSet:%d\n,LedSet:%d\n,BeepSet:%d\n,FanSet:%d\n,SegSet:%d\n,IsSet:%d\n",device_struct.DeviceID,device_struct.RFIDSet,device_struct.AlarmSet,device_struct.LedSet,device_struct.BeepSet,device_struct.FanSet,device_struct.SegSet,device_struct.IsSet);
    close(fifo_fd);
    return device_struct;

}
void write_device_id_fifo(int deviceid)
{
    int fifo_fd;
    char buf[BUFFERSIZE]="deviceid_fifo";
    fifo_fd=fifo_init(buf,1);
    memset(buf,0,sizeof(buf));
    if((write(fifo_fd,&deviceid,sizeof(int)))<0)
    {
        fprintf(stderr,"Fail to write deviceid_fifo :%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    close(fifo_fd);
}
