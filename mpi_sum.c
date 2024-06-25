#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) 
{
int size, rank,i=0,sum=0,gsum=0;

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

sum=0;
for(i=rank*10+1;i<=rank*10+10;i++){
	sum=sum+i;
}

MPI_Reduce(&sum,&gsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

printf("rank = %d sum %d   gsum = %d \n",rank, sum, gsum);
MPI_Finalize();

return 0;
}
