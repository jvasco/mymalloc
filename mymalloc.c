#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mymalloc.h"

void initialize(){
	freeList->size = 10000 - sizeof(block);
	freeList->free = 1;
	freeList->next = NULL;
}

void* myMalloc(size_t bytes){
	block *curr, *prev;
	void* result;
	
	if(!(freeList->size)){ 
		initialize();
		//printf("memory initialized\n");
	}
	
	curr = freeList;
	
	while((((curr->size) < bytes) || ((curr->free)==0)) && (curr->next != NULL)){
		prev = curr;
		curr = curr->next;
	}
	
	if((curr->size) == bytes){
		curr->free = 0;
		result = (void*)(++curr);
		//printf("exact fitting block allocated\n");
		return result;
	}else if((curr->size) > (bytes + sizeof(block))){
		split(curr, bytes);
		result = (void*)(++curr);
		//printf("fitting block allocated with a split\n");
		return result;
	}else{
		result = NULL;
		printf("line %d in %s - no sufficient memory to allocate\n", __LINE__, __FILE__);
		return result;
	}
}

void split(block* slot, size_t size){
	//block* temp = (void*)((void*)slot + size + sizeof(block)); gcc
	block* temp = (void*)((char*)slot + size + sizeof(block));
	temp->size = (slot->size) - size - sizeof(block);
	temp->free = 1;
	temp->next = slot->next;
	slot->size = size;
	slot->free = 0;
	slot->next = temp;
}

void myFree(void* ptr){
	 if(((void*)myblock <= ptr) && (ptr <= (void*)(myblock+10000))){
		block* curr = ptr;
		--curr;
		if(curr->free == 1){
			printf("line %d in %s - already freed\n", __LINE__, __FILE__);
			return;
		}
		curr->free = 1;
		merge();
		//printf("freed\n");
	 }else{
		printf("line %d in %s - enter a valid pointer allocated by myMalloc\n", __LINE__, __FILE__);
	 }
}

void merge(){
	block *curr, *prev;
	curr = freeList;
	while(curr && curr->next){
		if((curr->free) && (curr->next->free)){
			curr->size += (curr->next->size) + sizeof(block);
			curr->next = curr->next->next;
		}
		
		prev = curr;
		curr = curr->next;
	}
}