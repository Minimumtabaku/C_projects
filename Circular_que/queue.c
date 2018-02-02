
#include "queue.h"

 

/* creates a new queue with a given size */
queue_t* create_queue(int capacity){
	queue_t * queue = (queue_t*)malloc(sizeof(queue_t));
	queue->arr=(void**)malloc(sizeof(void*)*capacity);
	for(int i=0;i<capacity;i++)
		queue->arr[i]=NULL;
	queue->tail=0;
	queue->head=0;
	queue->count=0;
	queue->capacity=capacity;
	return queue;
}
 
/* deletes the queue and all allocated memory */
void delete_queue(queue_t *queue){
	free(queue->arr);
	free(queue);
}
 
/* 
 * inserts a reference to the element into the queue
 * returns: true on success; false otherwise
 */
bool push_to_queue(queue_t *queue, void *data){

	if(queue->count==queue->capacity)
		return false;
	else{
		
		queue->arr[(queue->head)%(queue->capacity)]=data;
		queue->head+=1;
		queue->count+=1;

		return true;
	}
}
 
/* 
 * gets the first element from the queue and removes it from the queue
 * returns: the first element on success; NULL otherwise
 */
void* pop_from_queue(queue_t *queue){

	if (queue->count==0){
		
		return NULL;
	}
	else{
		queue->tail+=1;
		queue->count-=1;
		void* a=queue->arr[(queue->tail-1)%(queue->capacity)];
		queue->arr[(queue->tail-1)%(queue->capacity)]=NULL;
		return a;
	}
	
	
}
 
/* 
 * gets idx-th element from the queue
 * returns the element that will be  popped after idx calls of the pop_from_queue() 
 * returns: the idx-th element on success; NULL otherwise
 */
void* get_from_queue(queue_t *queue, int idx){
	if(queue->count==0)
		return NULL;
	if(idx<0)
		idx*=-1;
	if (idx>=queue->count)
		return NULL;
	
	return queue->arr[(queue->tail+idx)%queue->capacity];
		
}
 
/* gets number of stored elements */
int get_queue_size(queue_t *queue){

	return queue->count;
}
 
