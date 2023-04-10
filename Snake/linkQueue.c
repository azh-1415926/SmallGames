#include "linkQueue.h"
#include<stdlib.h>
void linkQueueInitalize(linkQueue* ppQueue){
    *ppQueue=(linkQueueNode*)malloc(sizeof(struct linkQueueNode));
    (*ppQueue)->next=NULL;
}
void linkQueueFree(linkQueue* ppQueue){
    linkQueue pQueue=NULL;
    while((*ppQueue)->next){
        pQueue=(*ppQueue)->next;
        (*ppQueue)->next=pQueue->next;
        free(pQueue);
    }
    free(*ppQueue);
    *ppQueue=NULL;
}
bool linkQueueIsEmpty(linkQueue queue){
    return queue->next==NULL;
}
void linkQueueEnqueue(linkQueue queue,void* const data){
    linkQueue pQueue=queue->next;
    queue->next=(linkQueueNode*)malloc(sizeof(struct linkQueueNode));
    queue->next->next=pQueue;
    queue->next->data=data;
}
void* linkQueueFront(linkQueue const queue){
    return queue->next->data;
}
void linkQueueDequeue(linkQueue queue){
    linkQueue pQueue=queue->next;
    queue->next=pQueue->next;
    free(pQueue);
}