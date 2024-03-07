#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define MAX 25

void startGame(int[][MAX] ,int ,int[][2] );

void updatePosition(int[][2] ,int ,int ,int );

void createSnake(int[][MAX] ,int ,int[][2] );

void createFood(int[][MAX] ,int ,int[][2] );

void createGameBoard(int[][MAX] ,int ,int[][2] );

void showGameBoard(int[][MAX] ,int );

void resetGameBoard(int[][MAX] ,int );

int main(){
	int gameBoard[MAX][MAX] = {0};
	int gameSize;
	int snakePosition[50][2];
	int choice;
	
	printf("\x1b[33m- Snake Game -\x1b[0m");
	do{
	
		printf("\nEnter the game size -> ");
		scanf("%d",&gameSize);
		createSnake(gameBoard,gameSize,snakePosition);
		createFood(gameBoard,gameSize,snakePosition);
		showGameBoard(gameBoard,gameSize);
		startGame(gameBoard,gameSize,snakePosition);
		printf("\nRestart Game -> 1\nQuit-> 2\n>> ");
		scanf("%d",&choice);
		resetGameBoard(gameBoard,gameSize);
	}while(choice==1);
	return 0;
}

void startGame(int gameBoard[][MAX] ,int gameSize ,int snakePosition[][2] ){
	char way[1];
	int flag,snakeSize;
	
	printf("\n- \x1b[33mGame is played with W , A , S , D keys \n\x1b[32mW -> \x1b[0mgo up\n\x1b[32mA -> \x1b[0mgo left\n\x1b[32mS -> \x1b[0mgo down\n\x1b[32mD ->\x1b[0m go right\n");
	sleep(1);
	flag=0;
	snakeSize=1;
	do{
		
		showGameBoard(gameBoard,gameSize);
		printf("\n>> ");
		fflush(stdin);
		scanf("%c",&way[0]);
		if(way[0] == 'w' || way[0] == 'W'){
			
			if(snakePosition[0][0]-1 < 0){
				
				printf("\n\n\x1b[31mYou Hit the Wall \n - Game Over - \x1b[0m\n");
				flag=1;
			}else if(gameBoard[snakePosition[0][0]-1][snakePosition[0][1]] == 2){
				
				snakeSize++;
				updatePosition(snakePosition,snakeSize,-1,0);
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
				createFood(gameBoard,gameSize,snakePosition);
			}else if(gameBoard[snakePosition[0][0]-1][snakePosition[0][1]] == 1){
				
				printf("\n\n\x1b[31mYou Hit Yourself \n - Game Over - \x1b[0m\n");
				flag=1;
			}else{
				
				updatePosition(snakePosition,snakeSize,-1,0);
				gameBoard[snakePosition[snakeSize][0]][snakePosition[snakeSize][1]]=0;
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
			}
		}else if(way[0] == 's' || way[0] == 'S'){
			
			if(snakePosition[0][0]+1 >= gameSize){
				
				printf("\n\n\x1b[31mYou Hit the Wall \n - Game Over - \x1b[0m\n");
				flag=1;
			}else if(gameBoard[snakePosition[0][0]+1][snakePosition[0][1]] == 2){
				
				snakeSize++;
				updatePosition(snakePosition,snakeSize,1,0);
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
				createFood(gameBoard,gameSize,snakePosition);
			}else if(gameBoard[snakePosition[0][0]+1][snakePosition[0][1]] == 1){
				
				printf("\n\n\x1b[31mYou Hit Yourself \n- Game Over - \x1b[0m\n");
				flag=1;
			}else{
				
				updatePosition(snakePosition,snakeSize,1,0);
				gameBoard[snakePosition[snakeSize][0]][snakePosition[snakeSize][1]]=0;
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
			}
		}else if(way[0] == 'a' || way[0] == 'A'){
			
			if(snakePosition[0][1]-1 < 0){
				
				printf("\n\n\x1b[31mYou Hit the Wall \n - Game Over - \x1b[0m\n");
				flag=1;
			}else if(gameBoard[snakePosition[0][0]][snakePosition[0][1]-1] == 2){
				
				snakeSize++;
				updatePosition(snakePosition,snakeSize,0,-1);
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
				createFood(gameBoard,gameSize,snakePosition);
			}else if(gameBoard[snakePosition[0][0]][snakePosition[0][1]-1] == 1){
				
				printf("\n\n\x1b[31mYou Hit Yourself \n - Game Over - \x1b[0m\n");
				flag=1;
			}else{
				
				updatePosition(snakePosition,snakeSize,0,-1);
				gameBoard[snakePosition[snakeSize][0]][snakePosition[snakeSize][1]]=0;
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
			}
		}else if(way[0] == 'd' || way[0] == 'D'){
			
			if(snakePosition[0][1]+1 >= gameSize){
				
				printf("\n\n\x1b[31mYou Hit the Wall \n - Game Over - \x1b[0m\n");
				flag=1;
			}else if(gameBoard[snakePosition[0][0]][snakePosition[0][1]+1] == 2){
				
				snakeSize++;
				updatePosition(snakePosition,snakeSize,0,1);
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
				createFood(gameBoard,gameSize,snakePosition);
			}else if(gameBoard[snakePosition[0][0]][snakePosition[0][1]+1] == 1){
				
				printf("\n\n\x1b[31mYou Hit Yourself \n - Game Over - \x1b[0m\n");
				flag=1;
			}else{
				
				updatePosition(snakePosition,snakeSize,0,1);
				gameBoard[snakePosition[snakeSize][0]][snakePosition[snakeSize][1]]=0;
				gameBoard[snakePosition[0][0]][snakePosition[0][1]]=1;
			}
		}else{
			
			printf("\n\n\x1b[31m!! ENTER A VALID KEY !!\n\x1b[0m");
		}
		if(snakeSize >= gameSize*gameSize/2){
			printf("\n\n\x1b[32mGame Ended Successfully\n\x1b[0m");
			showGameBoard(gameBoard,gameSize);
			flag=1;
		}
	}while(flag != 1);
}

void updatePosition(int snakePosition[][2] ,int snakeSize ,int updateX ,int updateY ){
	int i;
	
	for( i=snakeSize ; i>0 ; i-- ){
		
		snakePosition[i][0]=snakePosition[i-1][0];
		snakePosition[i][1]=snakePosition[i-1][1];
	}
	snakePosition[i][0]=snakePosition[i+1][0]+updateX;
	snakePosition[i][1]=snakePosition[i+1][1]+updateY;
}

void createSnake(int gameBoard[][MAX] ,int gameSize ,int snakePosition[][2] ){
	int row,column;
	
	srand(time(NULL));
	do{   // snake start position
		row = rand() % gameSize;
		column = rand() % gameSize;
	}while(gameBoard[row][column] != 0);
	snakePosition[0][0]=row;
	snakePosition[0][1]=column;
	gameBoard[row][column] = 1;
}

void createFood(int gameBoard[][MAX] ,int gameSize ,int snakePosition[][2] ){
	int row,column;
	
	srand(time(NULL));
	do{   // meat position
		
		row = rand() % gameSize;
		column = rand() % gameSize;
	}while(gameBoard[row][column] != 0);
	gameBoard[row][column] = 2;
}

void createGameBoard(int gameBoard[][MAX] ,int gameSize ,int snakePosition[][2] ){
	int row,column;

	srand(time(NULL));
	do{   // snake start position
		row = rand() % gameSize;
		column = rand() % gameSize;
	}while(gameBoard[row][column] != 0);
	snakePosition[0][0]=row;
	snakePosition[0][1]=column;
	gameBoard[row][column] = 1;
	
	do{   // meat position
		
		row = rand() % gameSize;
		column = rand() % gameSize;
	}while(gameBoard[row][column] != 0);
	gameBoard[row][column] = 2;
}

void showGameBoard(int gameBoard[][MAX] ,int gameSize ){
	int i,j,k;
	
	printf("\n\n");
	for( i=0 ; i<gameSize ; i++ ){
	
		for( k=0 ; k<gameSize ; k++ ){
			
			printf("----");
		}
		printf("\n");
		for( j=0 ; j<gameSize ; j++ ){
			
			if(gameBoard[i][j] == 1){
				
				printf("| \x1b[32mo \x1b[0m");	
			}else if(gameBoard[i][j] == 2){
				
				printf("| \x1b[33mo \x1b[0m");
			}else{
				
				printf("|   ");
			}
		}
		printf("|\n");
	}
}

void resetGameBoard(int gameBoard[][MAX] ,int gameSize ){
	int i,j;
	
	for( i=0 ; i<gameSize ; i++ ){
		
		for( j=0 ; j<gameSize ; j++ ){
			
			gameBoard[i][j]=0;
		}
	}
}
