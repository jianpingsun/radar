#ifndef __APP_H
#define __APP_H





#define TASK_START_PRIO                                 (0)
#define TASK_START_STK_SIZE                             (384)

#define TASK_LED0_PRIO                                  (15)
#define TASK_LED0_STK_SIZE                              (320)



void taskStart(void *para);















#endif