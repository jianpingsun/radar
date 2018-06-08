#ifndef __FIFO_H
#define __FIFO_H


#include <stdio.h>
#include <string.h>


struct fifo
{
    unsigned int in;
    unsigned int out;
    unsigned int size;
    unsigned char *buffer;
};


#define FIFO_SIZE               (65536)

#define  min(a,b)               ((a) > (b) ? (b) : (a))

#define  max(a,b)               ((a) > (b) ? (a) : (b))

#define  IS_FIFO_EMPTY(fifo)    ((fifo->out) == (fifo->in))

#define  IS_FIFO_FULL(fifo)     ((fifo->out + 1) == (fifo->in))


void fifoInit(struct fifo *f,unsigned int size);
unsigned int fifoPutData(struct fifo *f,unsigned char *buffer,unsigned int len);
unsigned int fifoGetData(struct fifo *f,unsigned char *buffer,unsigned int len);
unsigned int fifoGetLen(struct fifo *f);























#endif