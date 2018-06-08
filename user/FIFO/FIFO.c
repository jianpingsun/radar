#include "FIFO.h"

#pragma data_alignment = 4
unsigned char fifoBuff[FIFO_SIZE] = {0};


struct fifo tFifo;


void fifoInit(struct fifo *f,unsigned int size)
{
    f->buffer = fifoBuff;
    f->in = 0;
    f->out = 0;
    f->size = size;
}


unsigned int fifoPutData(struct fifo *f,unsigned char *buffer,unsigned int len)
{
    unsigned int l = 0;
    
    len = min(len,f->size - f->in + f->out);
    l = min(len,f->size - (f->in & (f->size - 1)));  
 
    memcpy(f->buffer + (f->in & (f->size - 1)),buffer,l);
    memcpy(f->buffer,buffer + l, len - l); 
    f->in += len;   
    return len; 
}

unsigned int fifoGetData(struct fifo *f,unsigned char *buffer,unsigned int len)
{
    unsigned int l;   
  
    len = min(len,f->in - f->out);
    l = min(len,f->size - (f->out & (f->size - 1)));
    
    memcpy(buffer, f->buffer + (f->out & (f->size - 1)),l);   
    memcpy(buffer + l,f->buffer,len - l); 
    
    f->out += len;   
    return len; 
}


unsigned int fifoGetLen(struct fifo *f)
{
    return (f->in - f->out);
}



