#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 7

typedef struct Node{
	int count;
	char address[MAX];
	struct Node* next;
	struct Node* previous;
}NODE;

int addInfoFromFile(int ,int ,int );
int addInfoFromKeyboard(int ,int ,int );
int isTheAddressAvailable(char[] ,int );
NODE* createNode(char[] );
void addNodeAtFront(NODE* );
void deleteLastNode();
void printList();
void deleteAllNodes();

NODE* head;

int main(){
	int choice,option;
	int linkedListSize;
	int T,L;
	
	head=NULL;
	linkedListSize=0;
	printf("\nEnter the limit required to get to the first place (T) -> "); // limits of count
	scanf("%d",&T);
	printf("\nEnter the max number of nodes (L) -> "); // limits of nodes .
	scanf("%d",&L);
	printf("\n-----------------------------------------------------------\n");
	do{
		
		printf("\nMAIN MENU\n-------------------------------\n|\x1b[32m Add Info From File -> 1    \x1b[0m |\n|\x1b[32m Add Info From Keyboard -> 2 \x1b[0m|\n|\x1b[32m Change parameters (T L)-> 3\x1b[0m |\n|\x1b[32m Exit -> 0                  \x1b[0m |\n-------------------------------\n->> ");
		scanf("%d",&choice);
		if(choice==1){
			
			linkedListSize=addInfoFromFile(linkedListSize,T,L);
			printf("\n\n\x1b[33mDo you want to delete them all\x1b[0m\n\x1b[32mYes -> 1\n\x1b[31mNo -> 2\x1b[0m\n->> ");
			scanf("%d",&option);
			if(option==1){
				
				deleteAllNodes(); // deletes all nodes in the list . 
				linkedListSize=0; // sets the size equal to 0 .
			}
		}else if(choice==2){
			
			linkedListSize=addInfoFromKeyboard(linkedListSize,T,L);
			printf("\n\n\x1b[33mDo you want to delete them all\x1b[32m\nYes -> 1\n\x1b[31mNo -> 2\x1b[0m\n->> ");
			scanf("%d",&option);
			if(option==1){
				
				deleteAllNodes(); // deletes all nodes in the list .
				linkedListSize=0; // sets the size equal to 0 .
			}
		}else if(choice==3){
				
			printf("\nEnter the new limit required to get to the first place (T) -> ");
			scanf("%d",&T);
			printf("\nEnter the new max number of nodes (L) -> ");
			scanf("%d",&L);
			printf("\nParameters Changed Successfully\n");
		}
		else if(choice==0){
			
			return 0; // end the min function
		}else{
			
			printf("\n\x1b[31mEnter a Valid Key\x1b[0m\n\n");
		}	
	}while(choice!=0);
}

/* @brief a function takes address from file .
 *
 * @param takes linked list size .
 *
 * @param takes T = the limit required to get to the first place .
 *
 * @param takes L = max number of addresses to keep .
 *
 * @return return updated linked list size .
 */

int addInfoFromFile(int linkedListSize ,int T ,int L ){
	FILE *file;
	char fileName[15];
	char address[MAX]; // variable for values read from file .
	NODE* p; // node for linked list processes .
	
	do{
		
		printf("\nEnter the file name (Enter -1 for Exit)-> ");
		fflush(stdin);
		scanf("%s",fileName);
		file=fopen(fileName,"r");
		if(!strcasecmp("-1",fileName))
			return linkedListSize;
		if(file==NULL)  // tries to open the file
			printf("\n\x1b[31m!- File Opening Error -!\x1b[0m\n\n");
	}while(file==NULL);
	while (fgets(address, sizeof(address), file) != NULL) { //retrieves data from the file until the row runs out of elements .
        
        address[strcspn(address, "\n")] = '\0'; // deletes '\n' characters at the end of the line .
        if(!isTheAddressAvailable(address,T)){ // checks if the address is in the linked list .
        	p=createNode(address); // creates a node for linked list and sets it equal to p .
        	addNodeAtFront(p); // adds to the top of the linked list .
        	linkedListSize++; // keeps linked list size .
        	while(linkedListSize>L){  // Checking is done to keep the list size constant that we entered the max list size.
        	
				deleteLastNode(); // deletes last element of list . calls the function .
        		linkedListSize--; // reduces the linked list size due to deletion .	
			}
		}
		printList(); // calls for print the whole list .
		printf("\n\n");
    }
	return linkedListSize;
}

/* @brief a function takes address from user's keyboard .
 *
 * @param takes linked list size .
 *	
 * @param takes T = the limit required to get to the first place .
 *
 * @param takes L = max number of addresses to keep .
 *
 * @return return updated linked list size .
 */

int addInfoFromKeyboard(int linkedListSize ,int T ,int L ){
	char address[MAX]; // variable for values read from keyboard .
	int choice;
	NODE* p;  // node for linked list processes .
	
	printf("\nReturn for enter -> 0");
	printList();
	do{

		printf("\n\nEnter the address -> ");
		fflush(stdin);
		scanf("%s",address);
		if(!isTheAddressAvailable(address,T) && strcmp(address,"0")){ // checks if the address is in the linked list .
        	
        	p=createNode(address); // creates a node for linked list and sets it equal to p .
        	addNodeAtFront(p); // adds to the top of the linked list .
        	linkedListSize++; // keeps linked list size .
        	while(linkedListSize>L){  // Checking is done to keep the list size constant that we entered the max list size.
        		
				deleteLastNode(); // deletes last element of list . calls the function .
        		linkedListSize--; // reduces the linked list size due to deletion .
			}
		}
		printList();
		printf("\n\n");
	}while(strcmp(address,"0")); // checks user want to go main menu .
	return linkedListSize;
}

/* @brief checks the nodes in the list .
 *	
 * @param taken information from the file ( address ) .
 *
 * @param takes T = the limit required to get to the first place .
 *
 * @return return existence of node in the linked list .if it is exist return 1 else 0 .
 */

int isTheAddressAvailable(char address[] ,int T ){
	NODE* tmp;
	tmp=head;
	
	if(head==NULL){ // checks for the existence of the list .
		
		return 0;
	}else{
		
		while(tmp -> next!=NULL){ // travels all nodes except the last node .
			
			if(!strcmp(tmp->address,address)){ // compares the received address with the addresses on the nodes .
				
				tmp -> count++; // if it is equal count increase
				if(tmp -> count == T+1 && tmp -> previous != NULL){ // checks for nodes that repeat more than the limit value .
						
					tmp -> previous -> next = tmp -> next;
					tmp -> next -> previous = tmp -> previous;
					addNodeAtFront(tmp); // if it is exist , adds that node as the first element of the list .		
				}
				return 1;
			}	
			tmp=tmp -> next;
		}
		if(!strcmp(tmp -> address,address)){ // this control for the last node
			
			tmp->count++;
			if(tmp -> count == T+1 && tmp -> previous !=NULL){
				tmp -> previous -> next = NULL;
				addNodeAtFront(tmp);
			}
			return 1;
		}
	}
	return 0;
}

/* @brief a function that creates a new node for linked list and sets node's address equal to parameter address .
 *	
 * @param taken information from the file ( address ) .
 *
 * @return returns the nodes pointer that created .
 */
 
NODE* createNode(char address[] ){
	NODE* p;
	
	p=(NODE*)malloc(sizeof(NODE)); // allocates space the size of struct .
	if(p==NULL){ // if it is null -> gives warning .
		
		printf("Allocation Error\n");
		exit(0);
	}
	p -> count=1; // keeps track of how many times the same address appears .
	p -> next=NULL;
	p -> previous=NULL;
	strcpy(p -> address,address); // copies the taken address from file to node's address .
	return p;
}

/*@brief adds the node at first element of linked list .
 *
 *@param takes a node pointer .
 *
 *@return
 */
 
void addNodeAtFront(NODE* p){
	
	p -> previous =NULL;
	p -> next=head; // replaces the previously found node and points to that node .
	if(p -> next!=NULL) // checks for the existence of the list .
		p -> next -> previous=p; // if it is not created , creates and head points to first node of the list .
	head=p;
}

/*@brief deletes the last node of the list .
 *
 *@param takes size of linked list .
 *
 *@param takes L = max number of addresses to keep .
 *
 *@return
 */

void deleteLastNode(){
	NODE* tmp;
	
	tmp=head;
	while(tmp -> next!=NULL){ // this loop continues until it finds the last node .
		
		tmp = tmp -> next;
	}
	tmp -> previous -> next=NULL;
	free(tmp); // deletes the node and fress up space .
}

/*@brief a function that prints the created list .
 *
 *@return
 */

void printList(){
	NODE* tmp;
	
	tmp=head;
	printf("\n\n");
	if(tmp==NULL){
		printf("\nLinked List Empty\n\n");
	}else{
		
		while(tmp -> next!=NULL){
		
			printf("(\x1b[32m %s , \x1b[33m%d \x1b[0m) ----> ",tmp -> address,tmp -> count); // prints the node's address and count .
			tmp=tmp -> next;
		}
		printf("(\x1b[32m %s ,\x1b[33m %d\x1b[0m ) ",tmp -> address,tmp -> count);
	}
}

/*@brief a function that deletes all nodes .
 *
 *@return
 */

void deleteAllNodes(){
	NODE* current;
	
	current=head;
	while(current->next!=NULL){
		
		current=current -> next;
		free(current -> previous);
	}
	free(current); // free space .
	head=NULL; // delete head info .
	printf("----- All Nodes Deleted Successfully -----\n");
}
