#ifndef MYMALLOC_H_INCLUDED
#define MYMALLOC_H_INCLUDED

#include<stdio.h>
#include<stddef.h>

char myblock[10000];

typedef struct node{
    size_t size;
	int free;
    struct node* next;
} block;

block* freeList = (void*)myblock;

void initialize();
void split(block* slot, size_t size);
void merge();
void* myMalloc(size_t bytes);
void myFree(void* ptr);


#endif