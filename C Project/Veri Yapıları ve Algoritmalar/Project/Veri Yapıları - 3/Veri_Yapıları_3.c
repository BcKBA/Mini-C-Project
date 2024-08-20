#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 50

void multipleQueueImplementation(int[][MAX] ,int ,int ,int[] );
void printFinishingOrder(int[] ,int );
void deleteValue(int[] ,int );
void heapify(int[] ,int );
void createArr(int[][MAX] ,int ,int ,int[] );
void printArr(int[][MAX] ,int ,int ,int ,int );
void swap(int* ,int* );
int findBigChild(int[] ,int ,int );

int main(){
	int N,M;
	int Arr[MAX][MAX];
	int capacity[MAX];
	int i;
	
	printf("Enter the size of row ( N ) -> "); // takes value from user .
	scanf("%d",&N);
	printf("Enter the size of column ( M ) -> ");
	scanf("%d",&M);
	
	for( i=0 ; i<N ; i++ ){ // continues until it reaches the number of rows .
		
		printf("Enter the capacity of %d. queue -> ",i+1); // takes capacity array for all row .
		scanf("%d",&capacity[i]);
	}
	createArr(Arr,N,M,capacity); // creates array with unique number .
	printf("\n\n-- Main Array --"); 
	printArr(Arr,N,M,-1,1); // prints array .
	printf("\n--");
	multipleQueueImplementation(Arr,N,M,capacity); // calls main function .
	
	return 0;
}

/* @brief main function for the implementation .
 *
 * @param takes the matrix .
 *
 * @param takes row size .
 *
 * @param takes column size .
 *
 * @param takes capacity array for all row .
 *
 * @return
 */

void multipleQueueImplementation(int Arr[][MAX] ,int N ,int M ,int capacity[] ){
	int i,j;
	int max,maxIndex;
	int stop; // keeps flag .
	int* finishingOrder=(int*)calloc(N,sizeof(int)); // allocates hot vector and makes all value equals 0 .
	int finishedQueue=1; // keeps order for finish 1 - N
	
	printf("\n\n-- First Heapify --");
	for( j=0 ; j<N ; j++ ){ // creates max heap for all rows .
		
		heapify(Arr[j],capacity[j]); // creates first time max heap .
		printArr(Arr,N,M,j,1); // prints all matrix .
	}
	printf("\n\n--");
	while(stop!=1){ // continues until the all matrix contain only -1 .
		
		max=0; // max equals 0 .
		maxIndex=-1; // max index equals -1 . first enter .
		for( i=0 ; i<N ; i++ ){ // checks if the queue on each line is finished
			
			if(Arr[i][0]==-1 && finishingOrder[i]==0){ // checks first element of all row equals -1 , and is it new control .
				
				finishingOrder[i]=finishedQueue++; // keeps finish order 
			}
		}
		for( i=0 ; i<N ; i++ ){ // continues for all the first element of row .
			
			if(Arr[i][0]>max){ // finds max value .
				
				max=Arr[i][0]; // keeps max value .
				maxIndex=i; // keeps max value index .
			}
		}
		if(maxIndex!=-1){ // checks if the matrix contains only -1, if true then all rows in the matrix are empty .
			
			printf("\n\n--");
			printArr(Arr,N,M,-1,2); // prints matrix .
			printf("\n%d - removed \n",Arr[maxIndex][0]);
			deleteValue(Arr[maxIndex],M); // deletes the max value that was found .
			heapify(Arr[maxIndex],capacity[maxIndex]); // fixes the broken heap tree again (heapify) .
			printArr(Arr,N,M,maxIndex,1); // prints new array .
			printf("\n\n--");
		}else{
			
			stop=1; // stops the loop .
		}
	}
	printFinishingOrder(finishingOrder,N); // prints finishing order .
}

/* @brief a function prints the finishing order for matrix row .
 *
 * @param takes the hot vector array (finished order) .
 *
 * @param takes row size .
 *
 * @return
 */

void printFinishingOrder(int finishingOrder[] ,int N ){
	int i,j;
	int printed; // variable to check whether it has been written .
	
	printf("\n\nFinishing Order --> ");
	i=1;
	while(i<=N){ // look for all array .
		
		j=0;
		printed=0;
		while(printed==0){
			
			if(finishingOrder[j]==i){ // if finished order array[] equals number of lines , then print the finish order .				
				
				printf("%d ,",j+1);
				printed=1;
			}
			j++;
		}
		i++;
	}
}

/* @brief a function deletes the value in array .
 *
 * @param takes the array (matrix row) .
 *
 * @param takes column size .
 *
 * @return
 */

void deleteValue(int Arr[] ,int M){
	int i;
	
	while(Arr[i]!=-1 && i<M){ // continues until encounter -1 or reach the column size .
	
		Arr[i]=Arr[i+1]; // until then the value will shift left and first value will be deleted .
		i++; // index ++
	}
	Arr[i-1]=-1; // last value also makes -1 .
}

/* @brief a function creates max heap tree (heapify).
 *
 * @param takes the matrix .
 *
 * @param takes capacity of all row (queue) .
 *
 * @return
 */

void heapify(int Arr[] ,int capacity ){
	int index,bigChild;
	
	index=0; 
	while(index<capacity){ // checks for capacity , this one for get rid of unnecessary control .
		
		bigChild=findBigChild(Arr,index,capacity); // this function find the bigger child .
		if(bigChild!=-1){ // if this parent has a child , makes some control . 
			
			if(Arr[index]<Arr[bigChild]){ // if child is bigger than parent , swaps the value .
				
				swap(&Arr[index],&Arr[bigChild]); // swap function .
				if(index!=0){ // if parent is top of the max heap tree (index = 0) parent wont change .
					
					index=(index-1)/2; // else new parent index will be minues 1 and divide 2 .
				}
			}else{
				
				index++; // we need to control all array until array is max heap tree .
			}
		}else{
			
			index++;
		}
	}
}

/* @brief a function creates matrix .
 *
 * @param takes the matrix .
 *
 * @param takes value of row .
 *
 * @param takes value of column .
 *
 * @param takes the capacity of all row .
 *
 * @return
 */
 
void createArr(int Arr[][MAX] ,int N ,int M ,int capacity[] ){
	int i,j;
	int randomNr; // takes random number .
	int* numbers = (int*)calloc(N*M+1,sizeof(int)); // hot vector for number
	// if it is in the matrix value will be 1. else it is 0 .
	srand(time(NULL)); // for random number func .
	for( i=0 ; i<N ; i++){ // this loop for all row .
		
		for( j=0 ; j<M ; j++ ){ // this loop for all column .
			
			if(capacity[i] > j){ // checks row capacity . if it is bigger , add nothing .
				
				do{ // loop for new random number . it is continue until creates a new number that is not in the matrix . 
					
					randomNr=rand() % (N*M)+1; // creates a random number in 0 - N*M+1 .
				}while(numbers[randomNr]!=0); // checks the new number .
				numbers[randomNr]=1; // makes hot vector numbers[new random number] equals 1 .
				Arr[i][j]=randomNr; // adds this value to the matrix .
			}else{
				
				Arr[i][j]=-1; // if j bigger than capacity , adds -1 .
			}
		}
	}
}

/* @brief a function prints the whole matrix .
 *
 * @param takes the matrix .
 *
 * @param takes value of row .
 *
 * @param takes value of column .
 *
 * @param takes the selected row for color .
 *
 * @param takes mode for the color .
 *
 * @return
 */

void printArr(int Arr[][MAX] ,int N ,int M ,int row ,int mode ){
	int i,j;
	
	printf("\n\n");
	if(mode == 1){ // this one is 1 mode .
		for( i=0 ; i<N ; i++ ){ // loop for the all row .
		
			for( j=0 ; j<M ; j++ ){ // loop for the all column
			
				if(i==row && Arr[i][j]!=-1){
				
					printf("\x1b[32m%d\t\x1b[0m",Arr[i][j]); // prints the value in green .
				}else{
				
				printf("%d\t",Arr[i][j]); // prints the value in normal color .
				}
			}
			printf("\n");
		}
	}else{ // this one is other mode .
		for( i=0 ; i<N ; i++ ){
			
			for( j=0 ; j<M ; j++){
				
				if(j==0 && Arr[i][j]!=-1){ // controls for the empty space . 
					
					printf("\x1b[33m%d\t\x1b[0m",Arr[i][j]); // prints the value in yellow .
				}else{
					
					printf("%d\t",Arr[i][j]); // prints the value in normal color .
				}
			}
			printf("\n");
		}
	}
}

/* @brief a function swaps the value .
 *
 * @param takes first value .
 *
 * @param takes second value .
 *
 * @return
 */

void swap(int* x ,int* y ){
	int temp = *x; // temporary value .
	*x=*y; // swaps the value .
    *y=temp;
}

/* @brief a function finds the bigger value from the heap tree .
 *
 * @param takes the array - matris row -.
 *
 * @param takes the index where it start .
 *
 * @param takes the capacity of array (also queue).
 *
 * @return returns the index of the bigger value
 */

int findBigChild(int Arr[] ,int index ,int capacity ){
	
	if(2*index+2<capacity){ // checks the existence of right child and left child .
		
		return Arr[2*index+1]>Arr[2*index+2] ? 2*index+1 : 2*index+2; // returns bigger one .
	}else if(2*index+1<capacity){ // else checks the existence of left child only .
		
		return 2*index+1; // if it has , then returns .
	}else{ // if has no child return -1 .
		
		return -1;
	}
}

