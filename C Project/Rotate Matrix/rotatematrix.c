#include<stdio.h>
#define MAX 10

void rotateRight(int[][MAX] ,int[][MAX] ,int ,int );

void rotateLeft(int[][MAX] ,int[][MAX] ,int ,int );

void rotateFull(int[][MAX] ,int[][MAX] ,int ,int );

void oldNewChange(int[][MAX] ,int[][MAX] ,int ,int );

void showMatrix(int[][MAX] ,int[][MAX] ,int ,int ,int );

int main(){
	int row,column,tmp;
	int newMatrix[MAX][MAX],oldMatrix[MAX][MAX];
	int i,j,choice;
	
	printf("Enter a Size of row -> ");
	scanf("%d",&row);
	printf("Enter a Size of column -> ");
	scanf("%d",&column);
	printf("\x1b[31m----------------\n\x1b[0m");
	for( i=0 ; i<row ; i++ ){
		
		for( j=0 ; j<column ; j++ ){
			
			printf("\x1b[32mEnter matrix [\x1b[33m%d\x1b[32m][\x1b[33m%d\x1b[32m]. element - > \x1b[0m",i,j);
			scanf("%d",&newMatrix[i][j]);
		}
	}
	
	do{
		printf("\n\x1b[32m------------------------\n|\x1b[0m Rotate Right 90 -> 1 \x1b[32m|\n|\x1b[0m Rotate Left 90 -> 2  \x1b[32m|\n|\x1b[0m Rotate 180 -> 3      \x1b[32m|\n|\x1b[0m Exit -> 4            \x1b[32m|\n------------------------\x1b[0m\nYour Choice -> ");
		scanf("%d",&choice);
		if(choice == 1){  // 90 degree right rotate
			rotateRight(newMatrix,oldMatrix,row,column);
			tmp = row;
			row = column;
			column = tmp;
			showMatrix(newMatrix,oldMatrix,row,column,choice);
			
		}else if(choice == 2 ){	 // 90 degree left rotate
			rotateLeft(newMatrix,oldMatrix,row,column);
			tmp = row;
			row = column;
			column = tmp;
			showMatrix(newMatrix,oldMatrix,row,column,choice);
		
		}else if(choice == 3 ){  // 180 degree rotate
			rotateFull(newMatrix,oldMatrix,row,column);
			showMatrix(newMatrix,oldMatrix,row,column,choice);
		}else if(choice == 4){
			printf("\x1b[32m\n!! HAVE A GOOD DAY !!");
		}
		else{
			printf("\x1b[31m\n! ENTER A VALID NUMBER !\x1b[0m\n");
		}
		
	}while(choice != 4);

	return 0;
}

void rotateRight(int newMatrix[][MAX] ,int oldMatrix[][MAX] ,int row ,int column ){
	int i,j;
	
	oldNewChange(newMatrix,oldMatrix,row,column);
	
	for( i=0 ; i<column ; i++ ){
		
		for( j=0 ; j<row ; j++ ){
			
			newMatrix[i][j] = oldMatrix[row-1-j][i];
			
		}
	}	
}

void rotateLeft(int newMatrix[][MAX] ,int oldMatrix[][MAX] ,int row ,int column ){
	int i,j;
	
	oldNewChange(newMatrix,oldMatrix,row,column);
	for( i=0 ; i<column ; i++ ){
		
		for( j=0 ; j<row ; j++ ){
			
			newMatrix[i][j] = oldMatrix[j][column-1-i];
			
		}
	}
}

void rotateFull(int newMatrix[][MAX] ,int oldMatrix[][MAX] ,int row ,int column ){
	int i,j;
	
	oldNewChange(newMatrix,oldMatrix,row,column);
	for( i=0 ; i<row ; i++ ){
		
		for( j=0 ; j<column ; j++ ){
			
			newMatrix[i][j] = oldMatrix[row-1-i][column-1-j];
			
		}
	}
}

void oldNewChange(int newMatrix[][MAX] ,int oldMatrix[][MAX] ,int row ,int column ){
	int i,j;
	
	for( i=0 ; i<row ; i++ ){
		
		for( j=0 ; j<column ; j++ ){
			oldMatrix[i][j] = newMatrix[i][j];
		} 
	}
	
}

void showMatrix(int newMatrix[][MAX] ,int oldMatrix[][MAX] ,int row ,int column ,int choice ){
	int i,j;
	
	if(choice == 1 || choice == 2){
		
		printf("\x1b[33m---- Old Matrix ----\n");
		for( i=0 ; i<column ; i++ ){
		
			for( j=0 ; j<row ; j++ ){
				printf("\x1b[31m%d\t",oldMatrix[i][j]);
			}
			printf("\n");
		}
	
		printf("\x1b[33m---- New Matrix ----\n");
		for( i=0 ; i<row ; i++ ){
		
			for( j=0 ; j<column ; j++ ){
				printf("\x1b[32m%d\t",newMatrix[i][j]);
			}
			printf("\n\x1b[0m");
		}
	}
	else{
		
		printf("\x1b[33m---- Old Matrix ----\n");
		for( i=0 ; i<row ; i++ ){
		
			for( j=0 ; j<column ; j++ ){
				printf("\x1b[31m%d\t",oldMatrix[i][j]);
			}
			printf("\n");
		}
	
		printf("\x1b[33m---- New Matrix ----\n");
		for( i=0 ; i<row ; i++ ){
		
			for( j=0 ; j<column ; j++ ){
				printf("\x1b[32m%d\t",newMatrix[i][j]);
			}
			printf("\n\x1b[0m");
		}
	}
}
