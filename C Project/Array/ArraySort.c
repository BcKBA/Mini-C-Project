#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>

int createArray(int[] ,int[] );

void resetArray(int[] ,int[] ,int );

void bubbleSort(int[] ,int );

void selectionSort(int[] ,int );

void insertionSort(int[] ,int );

void printArray(int[] ,int ,int[] ,int );

int main(){
	int choice,size,i;
	int sortedArr[1000],unsortedArr[1000];
	int indis[2];
	
	indis[0]=-1;
	printf("\t -- WELCOME TO THE PROGRAM -- \n");
	printf("Purpose -- > Sorting the elements in an unordered array using various techniques >> \n\n");
	size = createArray(unsortedArr,sortedArr);
	
	do{
		
		printf("\n\n      - Options - \n-------------------------\n| Bubble Sort -> 1      |\n| Selection Sort -> 2   |\n| Insertion Sort ->3    |\n| Create New Array -> 4 |\n| Close to Program -> 9 |\n-------------------------\n Your Choice -- > ");
		scanf("%d",&choice);
		if(choice == 1){
			
			bubbleSort(sortedArr,size);
			printf("--- Sorted Array ---\n");
			printArray(sortedArr,size,indis,0);
			resetArray(sortedArr,unsortedArr,size);
		}
		else if(choice == 2){
			
			selectionSort(sortedArr,size);
			printf("\n--- Sorted Array ---\n");
			printArray(sortedArr,size,indis,0);
			resetArray(sortedArr,unsortedArr,size);
		}
		else if(choice == 3){
			
			insertionSort(sortedArr,size);
			printf("\n--- Sorted Array ---\n");
			printArray(sortedArr,size,indis,0);
			resetArray(sortedArr,unsortedArr,size);
		}
		else if(choice == 4){
			printf("\n\n");
			size = createArray(unsortedArr,sortedArr);
			
		}
		else if(choice == 9){
			
			return 0;
			
		}
		else{
			
			printf("\n\n-- PLEASE ENTER A VALID VALUES ! --\n\n");
			
		}
	}while(choice != 9);
}

int createArray(int arr_1[] ,int arr_2[] ){
	int size,upper_bound,lower_bound,choice;
	int i;

	do{

		printf("----------------------------\n| Enter an Array -> 1      |\n| Create Random Array -> 2 |\n----------------------------\nYour Choice -> ");
		scanf("%d",&choice);
		if(choice == 1){
			
			printf("\nEnter the size of Array -> ");
			scanf("%d",&size);
			for( i=0 ; i<size ; i++ ){
				
				printf("Enter %d. Element -> ",i+1);
				scanf("%d",&arr_1[i]);
				arr_2[i] = arr_1[i];
			}
		}
		else if(choice == 2){
			
			srand(time(NULL));
			printf("\nEnter the size of Array -> ");
			scanf("%d",&size);
			printf("Please Enter the Lower Bound of Array -> ");
			scanf("%d",&lower_bound);
			printf("Please Enter the Upper Bound of Array -> ");
			scanf("%d",&upper_bound);
			for( i=0 ; i<size ; i++ ){
				
				arr_1[i] = lower_bound + rand() % (upper_bound + lower_bound);
				arr_2[i] = arr_1[i];	
			}
		}	
		else{
			
			printf("-- PLEASE ENTER A VALID VALUES ! --\n\n");	
		}
	}while(!(choice == 1 || choice == 2));
	printf("\n-- Your Array Created Successfully --\n");
	return size;
}

void resetArray(int sortedArray[] ,int unsortedArray[] ,int size ){
	int i;
	
	for( i=0 ; i<size ; i++ ){
		
		sortedArray[i] = unsortedArray[i];
	}
}

void bubbleSort(int arr_1[] ,int size ){
	int i,j;
	int temp;
	int ind[2];
	
	printf("\n\n\x1b[32m     BUBBLE SORT STARTING .....\x1b[34m\n-----------------------------------\n\x1b[0m");
	for( i=0 ; i<size-1 ; i++ ){
		
		for( j=0 ; j<size-i-1 ; j++){
			
			ind[0]=j;
			ind[1]=j+1;
			if(arr_1[j] > arr_1[j+1]){

				printArray(arr_1,size,ind,1);
				temp = arr_1[j];
				arr_1[j] = arr_1[j+1];
				arr_1[j+1] = temp;
				sleep(1);
				printArray(arr_1,size,ind,2);
				sleep(1);
				printf("\n");
			}else{
				
				printArray(arr_1,size,ind,1);
				sleep(1);
				printArray(arr_1,size,ind,3);
				sleep(1);
				printf("\n");
			}
		}	
	}
}

void selectionSort(int arr[] ,int size ){
	int i,j;
	int minIndis,temp;
	int ind[2];
	
	printf("\n\n\x1b[32m     SELECTION SORT STARTING .....\x1b[34m\n-----------------------------------\n\x1b[0m");
	for( i=0 ; i<size-1 ; i++ ){
		
		minIndis=i;
		for( j=i ; j<size ; j++){
			
			if(arr[minIndis]>arr[j]){
				
				minIndis=j;
			}
		}
		ind[0]=i;
		ind[1]=minIndis;
		printArray(arr,size,ind,1);
		sleep(1);
		temp=arr[i];
		arr[i]=arr[minIndis];
		arr[minIndis]=temp;
		printArray(arr,size,ind,2);
		sleep(1);
	}
}

void insertionSort(int arr[] ,int size ){
	int i,j;
	int value;
	int ind[2];
	
	printf("\n\n\x1b[32m     INSERTION SORT STARTING .....\x1b[34m\n-----------------------------------\n\x1b[0m");
	for( i=1 ; i<size ; i++ ){
		
		value = arr[i];
		j=i-1;
		while(j>=0 && value<arr[j]){
			ind[0]=j;
			ind[1]=j+1;
			printArray(arr,size,ind,3);
			sleep(1);
			arr[j+1]=arr[j];
			ind[0]=-1;
			printArray(arr,size,ind,1);
			sleep(1);
			j--;
		}
		arr[j+1]=value;
		ind[1]=j+1;
		printArray(arr,size,ind,2);
		sleep(1);
	}
}

void printArray(int arr[] ,int size ,int ind[] ,int mode ){
	int i;
	
	if(mode == 0){
		
		for( i=0 ; i<size ; i++){
		
			printf("\x1b[32m%d ",arr[i]);
			if(i > 0 && i % 10 == 0){
			
				printf("\n");
			}
		}
		printf("\n\x1b[0m");
	}else if(mode == 1){
		
		for( i=0 ; i<size ; i++){
			
			if(i==ind[0] || i==ind[1]){
				
				printf("\x1b[33m%d\x1b[0m ",arr[i]);
			}else{
				
				printf("%d ",arr[i]);
			}
			if(i > 0 && i % 10 == 0){
			
				printf("\n");
			}
		}
		printf("\n");
	}else if(mode == 2){
		
		for( i=0 ; i<size ; i++){
			
			if(i==ind[0] || i==ind[1]){
				
				printf("\x1b[32m%d \x1b[0m",arr[i]);
			}else{
				
				printf("%d ",arr[i]);
			}	
			if(i > 0 && i % 10 == 0){
			
				printf("\n");
			}
		}
		printf("\n");
	}else{
		
		for( i=0 ; i<size ; i++){
			
			if(i==ind[0] || i==ind[1]){
				
				printf("\x1b[31m%d \x1b[0m",arr[i]);
			}else{
				
				printf("%d ",arr[i]);
			}
			if(i > 0 && i % 10 == 0){
			
				printf("\n");
			}
		}
		printf("\n");
	}
}
