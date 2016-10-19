#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "timer.h"

long thread_count = 4;
long long number_of_tosses;
long long number_in_circle;
long long sum;
pthread_mutex_t mutex;

void* cal_PI();

int main(int argc , char* argv[])
{

	srand( time(NULL) );
	number_of_tosses = strtoll(argv[1],NULL,10);	
	long thread;
	double pi_estimate = 0.0;
	double start,finish,elapsed;

	pthread_t* thread_handles;
	thread_handles = (pthread_t*) malloc (thread_count*sizeof(pthread_t));
	pthread_mutex_init(&mutex,NULL);

	GET_TIME(start);
	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread],NULL,cal_PI,NULL);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);
	GET_TIME(finish);

	elapsed = finish - start;
	pi_estimate = 4*number_in_circle / ((double) number_of_tosses);
	printf("pi=%lf\n",pi_estimate);
	printf("time=%lf\n",elapsed);

	pthread_mutex_destroy(&mutex);
	free(thread_handles);

	return 0;
}

void* cal_PI()
{
	double x, y;
	long long i;
	long long my_circle = 0;


	for (i = 0; i <= number_of_tosses/thread_count; i++) 
	{
		x = rand()/((double)RAND_MAX); // 0~1
		y = rand()/((double)RAND_MAX);
		x = 1*(x*2-1);   // -1~1
		y = 1*(y*2-1);
		if( x*x + y*y < 1 ) ++my_circle;
	}
	printf("x=%lf,y=%lf\n",x,y);

	pthread_mutex_lock(&mutex);
	number_in_circle += my_circle;
	pthread_mutex_unlock(&mutex);

	return NULL;
}
/*
   void* cal_PI(void* rank)
   {
   double x, y;
   long my_rank = (long) rank;
   long long i;
   long long my_toss = number_of_tosses/thread_count;
   long long my_first_toss = my_toss*my_rank;
   long long my_last_toss = my_first_toss + my_toss;
   long long my_circle = 0;


   for (i = my_first_toss; i < my_last_toss; i++) 
   {
   x = rand()/((double)RAND_MAX+1);
   y = rand()/((double)RAND_MAX+1);
   if( x*x + y*y < 1 ) ++my_circle;
   }
   pthread_mutex_lock(&mutex);
   number_in_circle += my_circle;
   pthread_mutex_unlock(&mutex);

   return NULL;
   }
 */

