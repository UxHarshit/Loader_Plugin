#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <linux/fb.h>
#define EVENT_DEVICE    "/dev/input/event9"

void tap(char* X,char* Y){
  char buff[999];
  snprintf(buff,sizeof(buff),"sendevent %s 3 %d 371 &&",EVENT_DEVICE,ABS_MT_TRACKING_ID);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d %s &&",buff,EVENT_DEVICE,ABS_MT_POSITION_X,X);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d %s &&",buff,EVENT_DEVICE,ABS_MT_POSITION_Y,Y);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d 1 &&",buff,EVENT_DEVICE,ABS_MT_TOUCH_MAJOR);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d 1000 &&",buff,EVENT_DEVICE,ABS_MT_PRESSURE);
  snprintf(buff,sizeof(buff),"%s sendevent %s 1 %d 1 &&",buff,EVENT_DEVICE,BTN_TOUCH);
  snprintf(buff,sizeof(buff),"%s sendevent %s 0 %d 0 &&",buff,EVENT_DEVICE,SYN_REPORT);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d 0 &&",buff,EVENT_DEVICE,ABS_MT_TOUCH_MAJOR);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d 0 &&",buff,EVENT_DEVICE,ABS_MT_PRESSURE);
  snprintf(buff,sizeof(buff),"%s sendevent %s 3 %d 4294967295 &&",buff,EVENT_DEVICE,ABS_MT_TRACKING_ID);
  snprintf(buff,sizeof(buff),"%s sendevent %s 1 %d 0 &&",buff,EVENT_DEVICE,BTN_TOUCH);
  snprintf(buff,sizeof(buff),"%s sendevent %s 0 %d 0",buff,EVENT_DEVICE,SYN_REPORT);
  system(buff);
}
int main(int argc,char* argv[]){
  int fd;
  fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  if(fd < 0){
    printf("Uinput open Failed ");
    exit(EXIT_FAILURE);
  }
  printf("Event Device: %s\n",EVENT_DEVICE);
  printf("ABS TRACKING ID Device: %d\n",ABS_MT_TRACKING_ID);
  printf("ABS LOCATION X %d\n",ABS_MT_POSITION_X);
  printf("ABS LOCATION Y %d\n",ABS_MT_POSITION_Y);
  printf("ABS PRESSURE %d\n",ABS_MT_PRESSURE);
  printf("ABS MAJOR %d\n",ABS_MT_TOUCH_MAJOR);
  printf("ABS TRACKING_ID %d\n",ABS_MT_TRACKING_ID);
  tap(argv[1],argv[2]);
}