#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "elevator.h"

int** allocateArray(int x, int y) {
	int i;
	int ** array;
	array = malloc((x+1)*sizeof(int*)); /* osa malloc kaneis toses theseis desmeueis*/
		if(array == NULL)
			return NULL;
	for (i = 0; i <= x ; i++) {
		array[i] = malloc((y+1)*sizeof(int)); /* ex: if nst =2  then nst = 0 1 2  (3)*/
		if( array[i] == NULL)
			return NULL;
	}
	return array;
}



int* allocate_array(int nrid) {
	int *array;
	array = malloc(nrid*sizeof(int));
	if(array == NULL)
		return NULL;
	return array;
}

void scanArray(int nrid, int *dests) { /* scan dests*/
	int i;
	for (i = 0; i < nrid; i++) {
		scanf("%d",&dests[i]);
	}
}
void printArray2( int nfl, int nst, int **array){
	int i,j;
	
	for(j = 0; j <= nst; j++){
		for(i = 0; i <= nfl; i++)
			printf("%d\t", array[i][j]);
		printf("\n");
	}
}


void printArray(int nrid, int *dests) { /* print the dests*/
	int i;
	for (i = 0; i < nrid; i++)
		printf("%d ", dests[i]);
	printf("\n");
}

int fw(int a,int b, int *dests, int nrid) { /*implementation of fw */
	int i;
	int c = 0; /* initialization cost*/

	for (i = 0; i < nrid; i++) {
		if (dests[i] > a && dests[i] <= b) { /* if a < destination > b*/
			if (b - dests[i] < dests[i] - a) /* check the difference*/
				c += b - dests[i]; /* cost is equal to difference each time*/
			else
				c += dests[i] - a;
		}
	}
	return c;
}

int nfl(int *dests, int nrid) { /* finding nfl*/
	int max = dests[0];
	int i;
	for (i = 1; i < nrid; i++) {
		if (dests[i] > max)
			max = dests[i];
	}
	return max;
}

#ifdef REC

int M(int i, int j, int *dests , int nrid){ /* implementation of recursive Mij*/ 
	
	int nflat = nfl(dests,nrid);
	if (j==0)
		return fw(0,INT_MAX,dests,nrid); /* base case */
	int k;
	int min = INT_MAX;
	for (k = 0; k <= i; k++) { /* search the minimum cost for k's smaller than the given i(floor) */
		int temp = M(k,j-1,dests,nrid) - fw(k,INT_MAX,dests,nrid) + fw(k,i,dests,nrid) + fw(i,INT_MAX,dests,nrid); /* recursive*/
		if (temp < min   ) /* keep the mincost for  the given k  each time */
			min = temp;
	}
		return min; 
}
#endif

#ifdef MEM
int Mm(int i, int j, int *dests, int nrid, int **M) { /* implementation of recursive Mij*/ 
	if (M[i][j] != -1) {
		return M[i][j]; /* if Mij is calculated then take it */
	}
  
	int min;
	if (j==0) { 
		min = fw(0, INT_MAX, dests, nrid); /* base case */
	}
	else {  /* if it doesn't then calculate it */
		int k;
		int nflat = nfl(dests, nrid);
		min = Mm(0, j-1, dests, nrid, M) - fw(0, INT_MAX, dests, nrid) + fw(0, i, dests, nrid) + fw(i, INT_MAX, dests, nrid); /* initialization of mincost*/
		for (k = 1; k <= i; k++) { /* search the minimum cost for k's smaller than the given i(floor) */
			int temp = Mm(k, j-1, dests, nrid, M) - fw(k, INT_MAX, dests, nrid) + fw(k, i, dests, nrid) + fw(i, INT_MAX, dests, nrid); /* recursive*/
			if (temp < min)
				min = temp;
		}
	}
	M[i][j] = min; /* keep Mij */
	return min; 
}
#endif










		
	





