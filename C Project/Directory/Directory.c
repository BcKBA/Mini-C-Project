#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 100

bool addContact(char[][15] ,char[][15] ,double[] ,int );

void showContact(char[][15] ,char[][15] ,double[] ,int );

void setContact(char[][15] ,char[][15] ,double[] ,int );

void deleteContact(char[][15] ,char[][15] ,double[] ,int ,int );

void searchContact(char[][15] ,char[][15] ,double[] ,int );

int main(){
	int choice;
	char name[MAX][15],surname[MAX][15];
	double phoneNumber[MAX];
	int size = 0;
	int setIndis,flag;
	
	printf("-- Welcome to the Program --");
	
	do{
		printf("\n    - MAIN MENU - ");
		printf("\n\x1b[31m------------------------");
		printf("\n|\x1b[0m Add Contact -> 1     \x1b[31m|\n|\x1b[0m Show Contacts -> 2   \x1b[31m|\n|\x1b[0m Contact Setting -> 3 \x1b[31m|\n|\x1b[0m Delete Contact -> 4  \x1b[31m|\n|\x1b[0m Search Contact -> 5  \x1b[31m|\n|\x1b[0m Exit -> 9            \x1b[31m|\n------------------------\n\x1b[0mYour Choice -> ");
		scanf("%d",&choice);
		
		switch(choice){
			
			case 1 :
				
				if(addContact(name,surname,phoneNumber,size)== true){
					
					size++;
					
				}
				break;
			
			case 2:
				
				showContact(name,surname,phoneNumber,size);
				
				break;
			case 3:
				
				if(size == 0){
					printf("\x1b[31m\n-- YOU HAVE NO CONTACT , PLEASE ENTER A CONTACT BEFORE USING THIS SERVICE --\n\x1b[0m");
				}else{
					do{
						flag = 0;
						showContact(name,surname,phoneNumber,size);
						printf("Enter 0 for Exit \nWhich Contact Do You Want To Set -> ");
						scanf("%d",&setIndis);
						if(setIndis<=size && setIndis>0){
							
							setContact(name,surname,phoneNumber,setIndis);
							flag = 1;
							printf("\n\x1b[32m-- CONTACTS UPDATED --\x1b[32m\n");
							
						}else if(setIndis == 0){
							
							flag = 1;
							
						}else{
							
							printf("\x1b[31m\n-- PLEASE ENTER A VALID NUMBER \n\x1b[0m");
					
						}
					}while(flag != 1);

				}
				break;
			case 4:
				
				if(size == 0){
				
					printf("\x1b[31m\n-- YOU HAVE NO CONTACT , PLEASE ENTER A CONTACT BEFORE USING THIS SERVICE --\n\x1b[0m");
				
				}else{
					do{
						flag = 0;
						showContact(name,surname,phoneNumber,size);
						printf("Enter 0 for Exit \nWhich Contact Do You Want To Delete -> ");
						scanf("%d",&setIndis);
						if(setIndis<=size && setIndis>0){
							
							deleteContact(name,surname,phoneNumber,setIndis,size);
							flag = 1;
							printf("\n\x1b[32m-- CONTACT DELETED SUCCESSFULLY --\x1b[32m\n");
							size--;
							
						}else if(setIndis == 0){
						
							flag = 1;

						}else{
							printf("\x1b[31m\n-- PLEASE ENTER A VALID NUMBER \n\x1b[0m");
						}
					}while(flag != 1);
				}
				break;
			case 5:
				if(size == 0){
					
					printf("\x1b[31m\n-- YOU HAVE NO CONTACT , PLEASE ENTER A CONTACT BEFORE USING THIS SERVICE --\n\x1b[0m");
					
				}else{
					searchContact(name,surname,phoneNumber,size);
				}
				break;
			default :
				printf("\n\x1b[31m !- Enter a Valid Key -!\x1b[0m\n");
		}
	printf("\n");
	}while(choice != 9);
	
	return 0;
}

bool addContact(char name[][15] ,char surname[][15] ,double phoneNumber[] ,int size ){
	int i;
	
	printf("\n\x1b[32m  - Adding Contact - \n-----------------------\n\x1b[0m\x1b[31mName -> ");
	fflush(stdin);
	scanf("%15[^\n]",name[size]);	
	printf("\x1b[32mSurname -> ");
	fflush(stdin);
	scanf("%15[^\n]",surname[size]);
	printf("\x1b[33mEnter a Phone Number -> ");
	fflush(stdin);
	scanf("%lf",&phoneNumber[size]);
	printf("\n\x1b[32mCONTACT ADDED SUCCESSFULLY\x1b[0m\n");
	return true;
}

void showContact(char name[][15] ,char surname[][15] ,double phoneNumber[] ,int size ){
	int i;
	
	printf("\n\n---- Contacts ----\n");
	printf("\x1b[31m    Name     \x1b[32m   Surname\t\t \x1b[33m Phone Number\x1b[0m\n-----------   -------------   ------------------");
	for( i=0 ; i<size ; i++ ){
		
		printf("\n%d   %-10s  %-15s  %-13.0lf |",i+1,name[i],surname[i],phoneNumber[i]);
		
	}
	printf("\n------------------------------------------------\n\n");
}

void setContact(char name[][15] ,char surname[][15] ,double phoneNumber[] ,int setIndis ){
	
	printf("\n\x1b[31mOld Name -> %s \x1b[0m\t \x1b[32mNew Name -> \x1b[0m",name[setIndis-1]);
	fflush(stdin);
	scanf("%15[^\n]",name[setIndis-1]);
	printf("\n\x1b[31mOld Surname -> %s \x1b[0m\t \x1b[32mNew Surname -> \x1b[0m",surname[setIndis-1]);
	fflush(stdin);
	scanf("%15[^\n]",surname[setIndis-1]);
	printf("\n\x1b[31mOld Phone Number -> %.0lf \x1b[0m\t \x1b[32mNew Phone Number -> \x1b[0m",phoneNumber[setIndis-1]);
	scanf("%lf",&phoneNumber[setIndis-1]);	
}

void deleteContact(char name[][15] ,char surname[][15] ,double phoneNumber[] ,int deleteIndis ,int size ){
	int i,j;
	
	for( i=deleteIndis-1 ; i<size-1 ; i++ ){
		j=0;
		while(name[i][j] != '\0'){
			name[i][j] = name[i+1][j];
			j++;
		}
		j=0;
		while(surname[i][j] != '\0'){
			surname[i][j] = surname[i+1][j];
			j++;
		}
		phoneNumber[i] = phoneNumber[i+1];
	}
	j=0;
	while(name[i][j] != '\0'){
		name[i][j] = ' ';
		j++;
	}
	j=0;
	while(surname[i][j] != '\0'){
		surname[i][j] = ' ';
		j++;
	}
	phoneNumber[i] = 0;
}

void searchContact(char name[][15] ,char surname[][15] ,double phoneNumber[] ,int size ){
	int i;
	int choice;
	int flag = 0,result;
	char name1[15],surname1[15];
	int phone;
	
	do{
		
		printf("\nSearch With\n\x1b[32m---------------------\n| \x1b[0mName -> 1         \x1b[32m|\n| \x1b[0mSurname -> 2     \x1b[32m |\n|\x1b[0m Phone Number -> 3 \x1b[32m|\n|\x1b[0m Main Menu -> 4    \x1b[32m|\n---------------------\n\x1b[0mYour Choice -> ");
		scanf("%d",&choice);
		if(choice == 1){
			printf("Enter a Name -> ");
			fflush(stdin);
			scanf("%[^\n]",name1);
			for( i=0 ; i<size ; i++ ){
				result = strcasecmp(name1,name[i]);
				if(result == 0){
					printf("\n\x1b[34m   %-10s  %-15s  %-13.0lf \x1b[0m\n",name[i],surname[i],phoneNumber[i]);
				}
			}
			printf("\n\x1b[32mSEARCH COMPLETED SUCCESSFULLY\x1b[0m\n");
			flag = 1;
		}else if(choice == 2){
			printf("Enter a Surname -> ");
			fflush(stdin);
			scanf("%[^\n]",surname1);
			for( i=0 ; i<size ; i++ ){
				result = strcasecmp(surname1,surname[i]);
				if(result == 0){
					printf("\n\x1b[34m   %-10s  %-15s  %-13.0lf \x1b[0m\n",name[i],surname[i],phoneNumber[i]);
				}
			}
			printf("\n\x1b[32mSEARCH COMPLETED SUCCESSFULLY\x1b[0m\n");
			flag = 1;
		}else if(choice == 3){
				printf("Enter a Phone Number -> ");
				scanf("%d",&phone);
			for( i=0 ; i<size ; i++){
				if(phoneNumber[i] == phone){
					printf("\n\x1b[34m   %-10s  %-15s  %-13.0lf \x1b[0m\n",name[i],surname[i],phoneNumber[i]);
				}
			}
			printf("\n\x1b[32mSEARCH COMPLETED SUCCESSFULLY\x1b[0m\n");
			flag = 1;
		
		}else if(choice == 4){
			
			flag = 1;
			
		}else{
			printf("\x1b[31m\n-- PLEASE ENTER A VALID NUMBER \n\x1b[0m");
		}
	
	}while(flag != 1);

}
