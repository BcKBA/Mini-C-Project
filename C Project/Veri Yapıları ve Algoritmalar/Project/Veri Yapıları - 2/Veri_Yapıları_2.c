#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 50

typedef struct LinkedListQueue{ // linked list structs
	struct LinkedListQueue* next; // keeps next node's address .
	struct Stack* stack; // takes one stack .
}QUEUE;

typedef struct Stack{ // stack structs
	int top; // keeps track of the index at which the last word is in the array .
	char word[MAX][30]; // array of words .
}STACK;

void printFile(int );
void wordLadder(char[] ,char[] );
int readFromFile(STACK* ,char[] );
int isOneDifference(char[] ,char[] );
int isUniqueWord(char[] ,STACK* );
int isUniqueStack(char[] );
void deleteSimilarStack(char[] );
QUEUE* createQueueNode(STACK* );
STACK* createStack(STACK* ,char[] );
void enqueue(QUEUE* );
STACK* dequeue();
void showQueue(char[] );
void showStack(STACK* ,char[] );
void lowerCase(char[] );
void resetAll();

QUEUE* head; // global - head for queue first element .

int main(){
	char sourceWord[MAX];
	char aimWord[MAX];
	int choice=1;
	
	do{
		
		printf("Enter the source word -> ");
		scanf("%s",sourceWord); // takes source word from user .
		lowerCase(sourceWord); // makes it lowercase .
		printf("Enter the aim word -> ");
		scanf("%s",aimWord); // takes aim word from user .
		printFile(strlen(sourceWord)); 
		if(!strcmp(sourceWord,aimWord) || strlen(sourceWord)!=strlen(aimWord)){
			
			if(!strcmp(sourceWord,aimWord)){
				
				printf("\n-\x1b[31m You can not reach any path because your source word and aim word is same \x1b[0m-\n\n");
			}else{
				
				printf("\n-\x1b[31m You can not reach any path because your source and aim word's length is different \x1b[0m-\n\n");
			}
		}else{
			lowerCase(aimWord); // makes it lowercase too .
			printf("\n\nSearch Starting . . .\n");
			wordLadder(sourceWord,aimWord);
			printf("\nDo you want to enter new source word and aim word for new search ?\nYes -> 1\nNo -> 2\n>> ");
			scanf("%d",&choice); 
			printf("\n\n");
		}
	}while(choice == 1);
	return 0;
}

/* @brief a function creates a file from dictionary .
 *
 * @param takes source word length .
 *
 * @return
 */
 
void printFile(int length ){
 	FILE* fileToRead; // file to read .
 	FILE* fileToWrite; // file to write .
 	char word[30];
 	
 	fileToRead=fopen("dictionary.txt", "r"); // opens a file , reads that file .
 	fileToWrite=fopen("createdFile.txt","w"); // // opens a file , writes the file .
 	
 	if(fileToRead==NULL || fileToWrite==NULL){ // if it can not open return .
 		
 		printf("- FILE CAN NOT OPEN -\n\n");
 		return ;
	}
	while(fgets(word, sizeof(word), fileToRead) != NULL){ // reads the file line by line

		word[strcspn(word, "\n")] = '\0'; // deletes '\n' character at the end of the words .			
		if(strlen(word)==length){ // if word length equals source word length , then writes that word to new file .
		
			fputs(word, fileToWrite); // writes to file if length equals source word .
			fputs("\n", fileToWrite); // Her kelimenin sonuna bir alt satýr ekle
		}
	}
	fclose(fileToRead); // close file .
	fclose(fileToWrite); // close file too .
 }
 
 /* @brief a function like a main function creates mainStack and other stack derives from this stack.
 *
 * @param takes source word from user .
 *
 * @param takes aim word from user .
 *
 * @return
 */

void wordLadder(char sourceWord[] ,char aimWord[] ){
	STACK* mainStack=(STACK*)malloc(sizeof(STACK)); // allocates a main stack's address .
	if(mainStack==NULL){
		printf("- Allocation Error -\n\n");
		exit(0);
	}
	mainStack->top=0; // initialize stack top value .
	strcpy(mainStack->word[mainStack->top],sourceWord); // first start initialize , copeis the source word as the first word of the stack .
	int isDone=0; // this for controller for done or continue .

	do{ // loop continues until isDone equals 1 or queue's head equals null .
		
		isDone=readFromFile(mainStack,aimWord); // starts to read from file and return the value for done or continue .
		if(isDone==0){ // if it continues it has 2 options
			
			if(head!=NULL){ // if head is not equals to null , continue with new main stack
				
				mainStack=dequeue(); // takes new stack from queue
			}else{ // else loop is done and there is no path  between your source and aim words .
				
				printf("-\x1b[31m There is no Path \x1b[0m-\n\n");
				isDone=1; // it is done but negative way
			}
		}
	}while(isDone==0);
	resetAll(); // resets every nodes and stacks .
	free(mainStack); // free stack .
	if(remove("createdFile.txt")!=0) // removes created file .
		printf("- Something Went Wrong -");
}

/* @brief a function .
 *
 * @param takes main stack from word ladder function .
 *
 * @param takes aim word from user .
 *
 * @return returns a value for is Done .
 */

int readFromFile(STACK* mainStack ,char aimWord[] ){
	FILE* fileToRead;
	QUEUE* queueNode; // a pointer for new queue nodes .
	STACK* newStack; // a pointer for new stacks .
	char word[30]; // takes words in the file line by line .
	int wordLength=strlen(mainStack->word[mainStack->top]); // keeps word length that looking for .
	int isNewNodeCreated=0;
	
	fileToRead=fopen("createdFile.txt", "r"); // opens a file .
	if(fileToRead==NULL){
 		
 		printf("- FILE CAN NOT OPEN -\n\n");
 		return 1;
	}
	while(fgets(word, sizeof(word), fileToRead) != NULL){ // takes word from file until there are no words left .
		
		word[strcspn(word, "\n")] = '\0'; // deletes '\n' character at the end of the words .
//		lowerCase(word);  // if needs , if there is an uppercase letter, make it lowercase .
		if(isUniqueWord(word,mainStack) && isOneDifference(word,mainStack->word[mainStack->top]) && isUniqueStack(word)){
			// checks for word length .
			// checks for existence of word in the stack .
			// checks for one letter difference between words .
			// checks for unique stack words . 
			isNewNodeCreated=1; // makes true created new node info .
			newStack=createStack(mainStack,word); // takes new Stack .
			queueNode=createQueueNode(newStack); // takes new queue node .
			enqueue(queueNode); // enqueues the node .
			if(!strcmp(word,aimWord)){ // if the word equals aim word , the path is found .
				
				fclose(fileToRead); // closes the file .
				printf("\n\n");
				showQueue(aimWord);  // shows queue's stack
				printf("\n");
				printf("-\x1b[32m Path Found \x1b[0m-");
				return 1; // isDone equals 1 .
			}
		}
	}
	fclose(fileToRead); // closes the file .
	if(isNewNodeCreated==0 && head!=NULL)
		deleteSimilarStack(mainStack->word[mainStack->top]); // deletes similar stack . 
	return 0; // isDone equals 0 .
}

/* @brief this function checks if there is a letter difference between words .
 *
 * @param takes the words to be checked .
 *
 * @param takes the words from the stack's top  .
 *
 * @return returns whether a letter is different .
 */

int isOneDifference(char word[] ,char mainStackWord[] ){
	int difference=0; // the counter holds the number of different letters .
	int i; // for loop variable .
	
	for( i=0 ; word[i]!='\0' ; i++ ){ // it is continue until word[i] equals '\0' char .
		
		if(mainStackWord[i]!=word[i]) // checks equality for word letters .
			difference++; // if it is not equals , counter increases .
	}
	if(difference==1) // if it is equals 1 , one letter of this word is different .
		return 1;
	return 0; // else it is not .
}

/* @brief this function checks whether the word is on the stack or not .
 *
 * @param takes the words to be checked .
 *
 * @param takes the stack pointer .
 *
 * @return returns the uniqueness of the word .
 */

int isUniqueWord(char word[] ,STACK* stack){
	int i; // for loop variable .
	
	for( i=0 ; i<=stack->top ; i++ ){ // reaches every words in stack .
		
		if(!strcmp(stack->word[i],word)) // checks for equality .
			return 0; // word is not unique .
	}
	return 1; // word is unique , first use in the stack .
}

/* @brief this function checks whether the word is on the other stacks or not .
 *
 * @param takes the words to be checked .
 *
 * @return returns the uniqueness of the word .
 */

int isUniqueStack(char word[] ){
	QUEUE* queue=head; // keeps queue's head .
	STACK* stack;
	int i;
	
	if(head!=NULL){ // checks whether queue created or not .
		
		while(queue->next!=NULL){ // contiues until queue node's next equals null .
			
			stack=queue->stack; // keeps queue stack .
			for( i=0 ; i<=stack->top ; i++ ){ // browse stack words .
				
				if(!strcmp(stack->word[i],word)) // checks for equality .
					return 0;
			}
			queue=queue->next; // takes next queue node .
		}	
	}
	return 1;
}

/* @brief this function deletes similar stacks .
 *
 * @param takes used word .
 *
 * @return
 */

void deleteSimilarStack(char word[] ) {
    QUEUE* queue=head;
    STACK* stack=queue->stack;
    
    if(head!=NULL && !strcmp(stack->word[stack->top],word)){ // this similarity only can be in the head
    														// because of func is Unique Stack .
		head=head->next; 
		free(queue);
	}
}

/* @brief this function creates new queue node for queue .
 *
 * @param gets the stack you want to add .
 *
 * @return returns created queue node .
 */

QUEUE* createQueueNode(STACK* stack ){
	QUEUE* queueNode=(QUEUE*)malloc(sizeof(QUEUE)); // allocates memory for new node .
	
	if(queueNode==NULL){
		
		printf("- Allocation Error -\n\n");
		exit(0);
	}
	queueNode->stack=stack; // // makes queue stack equals received stack .
	queueNode->next=NULL; // makes queue next equals null .
	return queueNode; // returns new queue node .
}

/* @brief this function creates new stack .
 *
 * @param takes the stack to derive from .
 *
 * @param takes the word for stack .
 *
 * @return returns new stack .
 */

STACK* createStack(STACK* mainStack ,char word[] ){
	STACK* newStack=(STACK*)malloc(sizeof(STACK)); // allocates memory for new stack .
	int i;
	
	if(newStack==NULL){
		
		printf("- Allocation Error -\n\n");
		exit(0);
	}
	newStack->top=mainStack->top; // equals top value .
	for( i=0 ; i<=mainStack->top ; i++ ) // takes all word in the stack .
		strcpy(newStack->word[i],mainStack->word[i]); // copies the word in the new stack .
	newStack->top++; // top increases for new word .
	strcpy(newStack->word[newStack->top],word); // adds new word .
	return newStack; // returns new stack .
}

/* @brief this function enqueues new queue node in queue .
 *
 * @param takes queue node .
 *
 * @return
 */

void enqueue(QUEUE* queue){
	
	if(head==NULL){ // checks for null . if it is true , creates new queue .
		queue->next=NULL;
		head=queue; // head keeps starting point .
	}else{
		
		QUEUE* tmp=head;
		while(tmp->next!=NULL) // continues until the reaches the end of the queue .
			tmp=tmp->next;
		tmp->next=queue; // last node's next equals new node .
		queue->next=NULL; // changes last node , last node's next equals null .
	}
}

/* @brief this function dequeues first element of queue . 
 *
 * @return first node's stack .
 */

STACK* dequeue(){
	QUEUE* queue=head; // keeps head pointer .
	STACK* stack;
	
	head=head->next;
	stack=queue->stack; // takes first element's stack of queue .
	free(queue); // free .
	return stack;
}

/* @brief this function reaches every element of queue .
 *
 * @return
 */

void showQueue(char word[] ){
	QUEUE* tmp=head;
	int i=1;
	
	if(head==NULL){ // queue is empty if head equals null .
		
		printf("\n-------------------------\n-\x1b[31m Queue is empty \x1b[0m-\n-------------------------\n\n");
	}else{
		
		while(tmp->next!=NULL){ // continues until reaches the last node - 1 .
			
			printf("%d. Queue Node -",i++);
			showStack(tmp->stack,word); // shows stack's words .
			tmp=tmp->next; // next node .
		}
		printf("%d. Queue Node -",i++); // this for last node .
		showStack(tmp->stack,word);
	}
}

/* @brief this function shows every queue node stack .
 *
 * @return
 */

void showStack(STACK* stack ,char word[] ){
	int i;
	
	printf(" - ");
	for( i=0 ; i<stack->top ; i++ ){
		
		if(i==0){
			
			printf("\x1b[32m%s\x1b[0m - ",stack->word[i]); // prints first element of stack in green .
		}else{
			
			printf("\x1b[33m%s\x1b[0m - ",stack->word[i]); // prints other in yellow .
		}
	}
	if(!strcmp(stack->word[i],word)){
		
		printf("\x1b[32m%s\x1b[0m - ",stack->word[i]); // if path created , prints last elements in green .
	}else{
		
		printf("\x1b[31m%s\x1b[0m - ",stack->word[i]); // else prints in red .
	}
	printf("\n");
}

/* @brief this function makes uppercase letters lowercase .
 *
 * @return
 */

void lowerCase(char word[] ){
	int i;
	
	for( i=0 ; word[i]!='\0' ; i++ ){ // reaches every word's letter .
		
		word[i] = tolower(word[i]); // and makes lowercase .
	}
}

/* @brief this function resets all queue nodes and stacks .
 *
 * @return
 */

void resetAll(){
    QUEUE* currentNode=head;
    QUEUE* nextNode;

    while(currentNode!=NULL){
    	
        nextNode = currentNode->next;
        free(currentNode->stack); // makes free all stack .
        free(currentNode); // makes free node .
        currentNode = nextNode;
    }
    head=NULL; // makes head equals null for new search .
}

