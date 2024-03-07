#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <unistd.h>

#define MAX 100

void game(char[][12] ,int[][2] ,int );

int givenLettersControl(int[] ,int ,int );

int showLettersControl(int[] ,int ,int );

void showScoreBoard(int[][2] ,char[][15] ,int );

int main(){	
	int player ,choice ;
	char name[MAX][15] ,word[MAX][12] ;
	int points[MAX][2];
	
	player=0;
	do{

		printf(" \x1b[31m     - Main Manu -\n\x1b[32m-------------------------\n|\x1b[33m New Game -> 1        \x1b[32m |\n|\x1b[33m Show Score Board -> 2 \x1b[32m|\n|\x1b[33m Exit -> 0            \x1b[32m |\n-------------------------\n\x1b[0mYour Choice -> ");
		scanf("%d",&choice);			
		switch(choice){
			
			case 0:
				
				printf("\n\x1b[35m<< THANKS FOR PLAYING >>\n\n\x1b[0m");
				break;
			case 1:
				
				printf("\n\x1b[32mEnter Your Nickname -> \x1b[0m");
				fflush(stdin);
				scanf("%15[^\n]",name[player]);
				game(word,points,player);
				player++;
				break;
			case 2:
				
				showScoreBoard(points,name,player);
				fflush(stdin);
				break;			
			default:
				
				break;		
		}
	}while(choice != 0);
	
	return 0;
}

void game(char word[][12] ,int points[][2] ,int player ){
	FILE *file;
	char fileName[15] ,copy[15] ,guess[15] ;
	int i ,j ;
	int wordLength ,givenLetter ,givenLettersCount ,wordsCount ,spaceCount ;
	int givenLetters[15];
	
	srand(time(NULL));
	do{
			
		printf("\n\x1b[32mEnter the Name of the Word File -> \x1b[0m");
		scanf("%s",fileName);
		file = fopen(fileName,"r");
		if(file == NULL){
				
			printf("\n\x1b[31m- ENTER A VALID WORD FILE NAME FOR PLAY -\n\x1b[0m");
		}
	}while(file == NULL);
	wordsCount=0;
	while(fgets(copy, 15, file) != NULL ){
		
		copy[strcspn(copy, "\n")] = '\0';
		strcpy(word[wordsCount],copy);
		strlwr(word[wordsCount]);
		wordsCount++;
	}
	printf("\x1b[32m\n<< Game Starting >>\n");
	printf("3\n");
	sleep(1);
	printf("2\n");
	sleep(1);
	printf("1\n\x1b[0m");
	sleep(1);
	
	points[player][0]=0;
	points[player][1]=0;
	i=0;
	givenLettersCount=0;
	wordLength = strlen(word[i]);
	printf("\n\x1b[33mGuess the Word or Take Letter (Enter 0)\x1b[0m\n\n");
	do{
		
		spaceCount=0;	
		j=0;
		printf("\x1b[33mYOUR WORD ->>  \x1b[0m");
		while(word[i][j] != '\0'){
				
			if(word[i][j] == ' '){
				
				spaceCount++;
				printf(" ");
			}else{
					
				if(showLettersControl(givenLetters,givenLettersCount,j) == 1){
				
					printf("%c",word[i][j]);
				}else{
					
					printf("_");
				}
			}
			j++;
		}
		printf("\n>> ");
		fflush(stdin);
		scanf("%[^\n]",guess);
		if(strcmp(guess,"0")==0){
				
			do{

				givenLetter = rand() % wordLength;
			}while(givenLettersControl(givenLetters,givenLetter,givenLettersCount) != 0 || word[i][givenLetter] == ' ');
			givenLettersCount++;
			if(wordLength == givenLettersCount + spaceCount){
				
				printf("\x1b[31mYour Word Was ->\x1b[0m %s\n\n",word[i]);
				i++;
				points[player][1] += givenLettersCount;
				if(i<wordsCount){
						
					givenLettersCount = 0;
					wordLength = strlen(word[i]);
					printf("\x1b[32m\n<< New Word Coming >>\n");
					sleep(1);
					printf("3\n");
					sleep(1);
					printf("2\n");
					sleep(1);
					printf("1\n\x1b[0m\n");
					sleep(1);
				}else{
						
					printf("\x1b[34m\n<< Games Ending >>\n\x1b[0m");
					printf("\n\n\x1b[32m-- Your Points -> %d \n-- Take Letters %d Times \n\n\x1b[0m",points[0][0],points[0][1]);	
					sleep(5);
				}

			}
		}else{
			if(strcmp(guess,word[i])==0){
				
				points[player][0] += 8 - givenLettersCount;
				printf("\n\x1b[32mCongratulations\n");
				i++;
				points[player][1] += givenLettersCount;
				if(i<wordsCount){
						
					givenLettersCount = 0;
					wordLength = strlen(word[i]);
					printf("\x1b[32m\n<< New Word Coming >>\n");
					sleep(1);
					printf("3\n");
					sleep(1);
					printf("2\n");
					sleep(1);
					printf("1\n\x1b[0m\n");
					sleep(1);
				}else{
						
					printf("\x1b[34m\n<< Games Ending >>\n\x1b[0m");
					printf("\n\n\x1b[32m-- Your Points -> %d \n-- Take Letters %d Times \n\n\x1b[0m",points[0][0],points[0][1]);	
					sleep(5);	
				}
					
			}else{
				
				points[player][0] -= 2;
				printf("\x1b[31m! Wrong Answer Try Again !\x1b[0m\n");
			}
		}
	}while(i != wordsCount);
}

int givenLettersControl(int givenLetters[] ,int givenLetter ,int givenLettersCount ){
	int i;
	
	for( i=0 ; i<givenLettersCount ; i++ ){
		
		if(givenLetters[i] == givenLetter)
		return 1;
	}
	givenLetters[i]=givenLetter;
	return 0;
}

int showLettersControl(int givenLetters[] ,int givenLettersCount ,int j ){
	int i;
	
	for( i=0 ; i<givenLettersCount ; i++ ){
		
		if(givenLetters[i] == j)
		return 1;
	}
	return 0;
}

void showScoreBoard(int points[][2] ,char name[][15] ,int player){
	int i;

	printf("\n\x1b[32m          Score Board\x1b[0m\n---------------------------------------\n\x1b[31m Nickname     \x1b[32m   Points    \x1b[33m   Letters\n---------------------------------------\n\x1b[0m");
	for( i=0 ; i<player ; i++){
		
		printf("\x1b[31m%-18s \x1b[32m%-12d \x1b[33m%d\n",name[i],points[i][0],points[i][1]);
	}
}
