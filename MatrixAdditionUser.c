#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>





struct v{
	int p1;
	int p2;
	int *p3;
};

void *runner(void *param);

int main(int argc, char *argv[]){

	int K;
	int M;
	printf( "Enter the number of row :");
	scanf("%d",&M);
	printf( "Enter the number of column :");
	scanf("%d",&K);
	int A[M][K];
	int B[M][K];
	int C[M][K];
	printf( "Enter the 1st matrix : \n");
	int q;
	int e;
	int w;
	for (q=0;q<M;q++){
		for (w=0;w<K;w++){
			scanf("%d",&e);
			A[q][w]=e;
		}		
	}
	printf( "\nEnter the 2nd matrix : \n");
	w=0;
	q=0;
	for (q=0;q<M;q++){
		for (w=0;w<K;w++){
			scanf("%d",&e);
			B[q][w]=e;
		}
	}
	int i, j;
	for (i = 0; i < M; i++){
		for (j = 0; j < K; j++){
		//Assign a row and column for each thread
		struct v *data = (struct v *)malloc(sizeof(struct v));
		data->p1 = A[i][j];
		data->p2 = B[i][j];
		data->p3 = &C[i][j];
		/* Now create the thread passing it data as a parameter */
		pthread_t tid;       //Thread ID
		pthread_attr_t attr; //Set of thread attributes
		//Get the default attributes
		pthread_attr_init(&attr);
		//Create the thread
		pthread_create(&tid, &attr, runner, data);
		//Make sure the parent waits for all thread to complete
		pthread_join(tid, NULL);
		}
	}

	//Print out the resulting matrix
	for (i = 0; i < M; i++)
	{
	for (j = 0; j < K; j++)
	{
	    printf("%d ", C[i][j]);
	}
	printf("\n");
	}
}

//The thread will begin control in this function
void *runner(void *param){
	struct v *data = param; // the structure that holds our data
	int sum = 0;         //the counter and sum

	sum = data->p1 + data->p2;
	*(data->p3) = sum;

	//Exit the thread
	pthread_exit(0);
}
