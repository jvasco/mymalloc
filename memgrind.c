#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

void main(){

	//Detectable Errors
	struct timeval t1, t0;
	int* x;
	int np;
	char* p = (char*)myMalloc(500);

	//char* d = (char*)myMalloc(500);
	
	//A
	myFree(&np);
	
	//B
	myFree(x);

	//C
	myFree(p);
	myFree(p);
	
	//D
	char* toobig = (char*)myMalloc(10000);
		
	
	//Testing and Instrumentation
	
	//A
	gettimeofday(&t0, 0);
	int temp=0;
	
	
	int* vars[3000];
	int i;
	
	for(i=0; i<3000; i++){
		vars[i] = (int*)myMalloc(1);
	}
	
	for(i=0; i<3000; i++){
		myFree(vars[i]);
	}
	
	//B
	
	for(i=0; i<3000; i++){
		vars[i] = (int*)myMalloc(1);
		myFree(vars[i]);
	}
	
	//C
	
	int free[3000] = {0};
	int m = 0;
	int f = 0;
	int j;
	
	for(j=0; j<6000; j++){
		int r = rand()%2;
		if(r==0){
			for(i=0; i<3000; i++){
				if(free[i]==0){
					vars[i] = (int*)myMalloc(1);
					free[i] = 1;
					m++;
					break;
				}
			}
		}else{
			for(i=0; i<3000; i++){
				if(free[i]==1){
					myFree(vars[i]);
					free[i] = 0;
					f++;
					break;
				}
			}
		}
	}
	
	//printf("%d %d", m, f);
	
	for(i=0; i<3000; i++){
		myFree(vars[i]);
	}
	
	//D
	
	int free2[3000] = {0};
	m = 0;
	f = 0;
	
	for(j=0; j<6000; j++){
		int r = rand()%2;
		if(r==0){
			for(i=0; i<3000; i++){
				if(free2[i]==0){
					int b = rand()%500;
					vars[i] = (int*)myMalloc(b);
					free2[i] = 1;
					m++;
					break;
				}
			}
		}else{
			for(i=0; i<3000; i++){
				if(free2[i]==1){
					myFree(vars[i]);
					free2[i] = 0;
					f++;
					break;
				}
			}
		}
	}
	
	//printf("%d %d\n", m, f);
	
	//E
	
	char* zerotest = (char*)myMalloc(0);
	
	//F
	
	for(i=0; i<3000; i++){
		myFree(vars[i]);
	}
	
	for(i=0; i<3000; i++){
		vars[i] = (int*)myMalloc(1);
		myFree(vars[i]);
		myFree(vars[i]);
	}

	gettimeofday(&t1, 0);
long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
printf("elapsed time is %d\n", elapsed);
	
	
}