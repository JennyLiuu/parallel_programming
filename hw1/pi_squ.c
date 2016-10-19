#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"

double throwPI(long long N){
	int i, count;
	double x, y;

	for( count = 0, i = 0; i < N; ++i ){
		x = rand()/((double)RAND_MAX+1);
		y = rand()/((double)RAND_MAX+1);
		if( x*x + y*y < 1 ) ++count;
	}
	return 4.0 * count / N;
}

int main(void){
	int i;
	double start,finish,elapsed,pi;  

	srand( time(NULL) );
	GET_TIME(start);
	pi = throwPI(1000000000000) ;
	GET_TIME(finish);
	elapsed = finish-start;
	printf("time:%lf\n",elapsed);
}
