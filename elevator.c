#include <stdio.h>
#include "elevator.h"
#include <stdlib.h>
#include <limits.h>


#ifdef REC 
int solve(int nrid, int nst, int *dests){
	int i,stop;
	int nflat = nfl(dests , nrid); 
	int MinCost = INT_MAX;
	for (i = 0; i <= nflat; i++) { /* searh for the minimum cost of each floor*/
		int cost = M(i, nst , dests , nrid); /* recursive formula*/
		if (MinCost > cost) {
			MinCost = cost;
			stop = i; /* elevator stops on the floor i */
		}
	}
	if( nst == 0){
		printf("No elevator stops\n");
		return fw(0, INT_MAX , dests , nrid);
	}
	else
		printf("Last stop at floor %d \n",stop);

	return MinCost;

}
#endif
#ifdef MEM
int solve(int nrid, int nst, int *dests){
	int i,stop,**array,j;
	int nflat = nfl(dests , nrid); 
	array = allocateArray(nflat , nst);
	for(i = 0; i <= nflat; i++){ /* 0<= i <= nflat*/
		for(j = 0; j <= nst ; j++) /* 0<=j<=nst*/
			array[i][j] = -1; /* initialization array*/
	    }

	for(i = 0; i <= nflat; i++){
	    	array[i][0] = fw(0, INT_MAX, dests, nrid); /* keep the Mi,0*/
	    }

	int MinCost = INT_MAX; /* initialization Min*/

	for (i = 0; i <= nflat; i++) { /* searh for the minimum cost of each floor*/
		int cost = Mm(i ,nst , dests , nrid , array); /* recursive formula*/
		if (MinCost > cost) {
			MinCost = cost;
			stop = i; /* elevator stops on the floor i */
		}
	}

    if(nst == 0){
    	printf("No elevator stops\n");
    	return fw(0, INT_MAX , dests, nrid);
    }
    else
	printf("Last stop at floor %d \n",stop);
    free(array);
	return MinCost;
}
#endif

#ifdef DP
int solve(int nrid , int nst, int *dests){
	int i,k,j;
	int ** P , ** M;
	int MinCost;
	int stop, min;
	int temp, temp1;
	int stops;
	int *st;
	int nflat = nfl(dests, nrid);
	M = allocateArray(nflat , nst);
	P = allocateArray(nflat , nst);
	st = malloc((nst + 1 )*sizeof(int));
	for( j = 0;  j< nst + 1 ; j++){
		min = fw(0, INT_MAX, dests, nrid);
		for( i = 0;  i <= nflat; i++){
		M[i][0] = fw(0, INT_MAX , dests, nrid); /* initialization Mi0*/
			for(k = 0; k <= i; k++){
				temp = M[k][j-1] - fw(k, INT_MAX, dests, nrid) + fw(k, i, dests, nrid) + fw(i, INT_MAX, dests, nrid);
				if( temp < min){	
					min = temp; /* keep k  and min */
					temp1 = k;
				}
			}
			P[i][j] = temp1;
			M[i][j] = min;
		}
	}/* end for */
	

	MinCost = INT_MAX;
	for(i = 0; i <= nflat; i++){ /* find the min */
		for(j=0; j <= nst; j++){
			if(M[i][j] < MinCost){
				MinCost = M[i][j];
					stop = i;
		 	}/*end if*/
		} 
	}/*end for*/
	if(nst == 0){
		printf("No elevator stops\n");
		return fw(0, INT_MAX , dests , nrid);
	}
	else {
		for( j = nst; j>= 0; j--){
			st[j] = stop;
			stop = P[stop][j];
		}
		printf(" Elevator stops are :");
		for( j = 0; j <= nst; j++){
			if( st[j] > 0)
				printf(" %d",st[j]);
		}

	}
	printf("\n \n ");
	
	printArray2(nflat, nst , M);

	for(i = 0; i <= nflat ; i++){ /*free both of array's*/
		free(M[i]);
		free(P[i]);
	}
	free(P);
	free(M);

	return MinCost;
}
#endif

int main() {
	int nst;
	int nrid;
	scanf("%d %d",&nrid , &nst);

	int *dests = allocate_array(nrid);

	scanArray(nrid, dests);

	int cost = solve(nrid, nst, dests);

	printf("Cost is: %d\n", cost);

	free(dests);
	return 0;
}
