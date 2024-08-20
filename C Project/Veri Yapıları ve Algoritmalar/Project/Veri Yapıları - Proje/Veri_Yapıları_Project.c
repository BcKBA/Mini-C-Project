#include<stdio.h>
#include<stdlib.h>

typedef struct Node{ // vertex nodes
	char Char; // keeps A , B , C  etc. .
    int vertex; // vertex .
    int weight; // wight of edge .
    struct Node* next; // next node .
} NODE;

typedef struct Graph{ // graph
    int NumberOfVertices; // number of vertex .
    struct Node** adjList; // adjList .
    int* visited; // visited array .
} GRAPH;

typedef struct PathNode{ // path node
	int* path; // keeps array path .
	int length; // keeps path's length
	struct PathNode* next; // keeps next path .
}PATH;

void findPath(GRAPH* );
void DFS(GRAPH* ,int ,int ,PATH** ,int* ,int ,int );
GRAPH* createAdjList();
void addEdge(GRAPH* ,int ,int ,int );
void addPath(PATH** ,int* ,int ,int );
GRAPH* createGraph(int );
NODE* createNode(int ,int );
PATH* createPathNode(int * ,int );
int isUniquePath(PATH** ,int* ,int ,int );
int isValidNode(GRAPH* ,int ,int ,int );
int findNumberOfVertices(char[] );
int findNumberOfShapes(PATH** ,int );
int charToIndex(char );
char indexToChar(int );
void printAdjacencyList(GRAPH* );
void print(PATH** ,int );

int main(){
	printf(" --\x1b[33m Welcome to the Program \x1b[0m--\n\n");

	GRAPH* graph = createAdjList();
	if(graph == NULL){
		
		printf("\n- \x1b[31mGraph Could Not Be Created\x1b[0m -\n\n");
		return 0;
	}
	printAdjacencyList(graph);
	findPath(graph);
	return 0;
}

/* @brief main function for the finding paths for all shapes .
 *
 * @param takes the graphs pointer .
 *
 * @return
 */
 
void findPath(GRAPH* graph ){
	int i; // for iterator .
	int* path = (int*)malloc(graph->NumberOfVertices+1 * sizeof(int)); // allocations for a path array .
	PATH** paths = (PATH**)malloc((graph->NumberOfVertices - 2) * sizeof(PATH*)); // allocations for all paths .
	
	for( i=0 ; i<graph->NumberOfVertices-2 ; i++ ){
		
		paths[i] = NULL; // makes null whole paths array .
	}
	for( i=0 ; i<graph->NumberOfVertices ; i++ ){ // continues until reaches the last vertex .
		
		DFS(graph,i,i,paths,path,0,0); // starts from every node for the find all paths .
		graph->visited[i] = 0; // makes visited array is not visited .
	}
	print(paths,graph->NumberOfVertices); // prints all paths which found .
}

/* @brief uses depth first search algorithm for the find paths , this functions is a recursive function also .
 *
 * @param takes the graphs pointer .
 *
 * @param takes next vertex .
 *
 * @param keeps starting vertex ( source ) .
 *
 * @param keeps all paths pointer .
 *
 * @param takes the current path .
 *
 * @param takes the current depth .
 *
 * @param keeps path length .
 *
 * @return
 */

void DFS(GRAPH* graph ,int vertex ,int source ,PATH** paths ,int* path ,int level ,int length ){
	NODE* tmp = graph->adjList[vertex]; // takes connected vertex with taken vertex from out of functions .
    graph->visited[vertex] = 1; // makes current vertex is visited .
    path[level] = vertex; // adds current vertex in the path .
    
    while (tmp != NULL) { // continues until the next connected vertex is null .
    	
        if (graph->visited[tmp->vertex] == 0) { // checks for vertex whether visited or not .
        	
			DFS(graph ,tmp->vertex ,source ,paths ,path ,level+1 ,length+tmp->weight); // if it is not visited call DFS for current vertex .
        }else if(graph->visited[tmp->vertex] == 1 && tmp->vertex == source && level >1){ // else if vertex turns back the starts vertex and level is bigger than 1 checks for the paths whether unique or not .
        	
			path[level+1] = tmp->vertex; // adds last vertex to the path array .
        	if(isUniquePath(paths,path,level+2,graph->NumberOfVertices)){ // checks uniqueness .
        		
				addPath(paths,path,level+2,length+tmp->weight); // if it is unique adds path .
			}
		}
        tmp = tmp->next; // continues for the next vertex if it is exist .
    }
    graph->visited[vertex] = 0; // makes current vertex is not visited when leaves from the function .
}

/* @brief creates adjacency list in the graph struct .
 *
 * @return returns created graph .
 */

GRAPH* createAdjList(){
	int i;
	FILE *file;
	char alphabet[26]; // alphabet array .
	char line[256],fileName[20];
	char node1, node2; // first column and second column for the file .
    int weight; // third column is a wight .
    for ( i=0 ; i<26 ; i++ ) { // creates alphabet array .
        alphabet[i] = 'A' + i;
    }
    do{
    	
		printf("Enter the File Name -> ");
	    scanf("%s",fileName); // takes file name .
	    fflush(stdin);	
    	file = fopen(fileName, "r"); // tries to open file .
    	if (file == NULL) { // if it is null returns .
    	
        	printf("\n-\x1b[31m File Can Not Open , Enter a Valid File Name\x1b[0m -\n\n");
    	}
	}while(file == NULL);
    GRAPH* graph = createGraph(findNumberOfVertices(fileName)); // creates graph .
    while (fgets(line, sizeof(line), file) != NULL) {
    	
        if (sscanf(line, " %c %c %d", &node1, &node2, &weight) == 3) {
        	if(isValidNode(graph,charToIndex(node1),charToIndex(node2),weight)){
        		
				addEdge(graph,charToIndex(node1),charToIndex(node2),weight); // adds edge between first and second column .
			}else{
				
				return NULL;
			}
        } else {
        	
            printf("\n-\x1b[31mThe Line Could Not Be Read or Is In An Unexpected Format: %s \x1b[0m -\n\n", line);
        	return NULL;
		}
    }
    fclose(file); // closes the file .
    return graph; // returns created graph .
}

/* @brief adds edge between source and destination .
 *
 * @param takes the graph .
 *
 * @param takes source vertex .
 *
 * @param takes destination vertex .
 *
 * @param takes weight for the edge .
 *
 * @return
 */

void addEdge(GRAPH* graph ,int source ,int destination ,int weight ){
	NODE* newNode = createNode(destination,weight); // creates edge for destination .
	if(newNode == NULL){ // checks for allocation error .
		printf("\n- \x1b[31mAllocaiton Error\x1b[0m - \n");
		exit(0);
	}
	newNode->next = graph->adjList[source]; // new node's next equals source .
	graph->adjList[source] = newNode; // adds adjList .
	
	
	newNode = createNode(source,weight); // creates edge for source .
	if(newNode == NULL){ // checks for allocation error .
		printf("\n- \x1b[31mAllocaiton Error\x1b[0m - \n");
		exit(0);
	}
	newNode->next = graph->adjList[destination];  // new node's next equals destination .
	graph->adjList[destination] =newNode; // adds adjList .
}

/* @brief adds path .
 *
 * @param takes the paths pointer .
 *
 * @param takes path array .
 *
 * @param takes current level .
 *
 * @param takes path length .
 *
 * @return
 */

void addPath(PATH** paths, int* array, int level, int length) {
	PATH* newNode = createPathNode(array, level); // creates path node .
	newNode->length = length; // path nodes equals length .
    PATH** tmp = &paths[level - 4]; // adds paths array .
    
    if (*tmp == NULL) { // if paths array is null , adds first place .
    	
        *tmp = newNode;
    } else {
    	
        PATH* current = *tmp;
        while (current->next != NULL) { // continues until reaches to last place .
        	
            current = current->next; // continues next node .
        }
        current->next = newNode; // equals new node last node's next .
    }
}

/* @brief creates graph .
 *
 * @param takes number of vertices from the file .
 *
 * @return new graph .
 */

GRAPH* createGraph(int numberOfVertices){
    int i; // i for iteration .
    GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH)); // allocation for new graph .
    if(graph == NULL){ // checks allocation error .
		printf("\n- \x1b[31mAllocaiton Error\x1b[0m - \n");
		exit(0);
	}
    graph->NumberOfVertices = numberOfVertices; // equals number of vertices .
    graph->adjList = (NODE**)malloc(numberOfVertices * sizeof(NODE*)); // allocations adjList .
    graph->visited = (int*)malloc(numberOfVertices * sizeof(int)); // alocations for visited array .
    
	for (i = 0; i < numberOfVertices; i++) {
    	
        graph->adjList[i] = NULL; // makes all index null .
        graph->visited[i] = 0; // makes all index 0 .
    }
    return graph; // returns graph .
}

/* @brief creates node .
 *
 * @param takes vertex number .
 *
 * @param takes edge weight .
 *
 * @return node .
 */

NODE* createNode(int v ,int weight ){
	NODE* newV = (NODE*)malloc(sizeof(NODE)); // allocations node .
	if(newV == NULL){
		printf("\n- \x1b[31mAllocaiton Error\x1b[0m - \n");
		exit(0);
	}
	newV->vertex = v; // equals vertex .
	newV->Char = indexToChar(v); // equals char indexTochar function .
	newV->weight = weight; // equals weight .
	newV->next = NULL; // makes next null .
	
	return newV; // returns new node .
}

/* @brief creates path node .
 *
 * @param takes path array .
 *
 * @param takes length of array .
 *
 * @return path node .
 */

PATH* createPathNode(int * array ,int length ){
	int i;
	PATH* newNode = (PATH*)malloc(sizeof(PATH)); // allocations .
	if(newNode == NULL){
		printf("\n- \x1b[31mAllocaiton Error\x1b[0m - \n");
		exit(0);
	}
	newNode->path = (int*)malloc(length * sizeof(int)); // allocations for array .
	newNode->next = NULL; // makes next null .
	
	for ( i=0 ; i<length ; i++ ) {
		
        newNode->path[i] = array[i]; // keeps path .
    }
    return newNode; // returns path node .
}

/* @brief checks path whether unique or not .
 *
 * @param takes paths pointer .
 *
 * @param takes path array .
 *
 * @param takes level .
 *
 * @param takes number of vertices .
 *
 * @return returns true for uniqueness .
 */

int isUniquePath(PATH** paths ,int* path ,int level ,int N ) {
    int i, flag = 1;
    PATH* tmp = paths[level - 4];
    
    if (tmp == NULL) { // checks null .
    	
        return flag;
    }
    while (tmp != NULL && flag == 1) { // control for all paths .
    	
        flag = 0;
        int* vector1 = (int*)calloc(N, sizeof(int)); // allocations for path 1 .
        int* vector2 = (int*)calloc(N, sizeof(int)); // allocations for path 2 .
        
        for (i = 0; i < level; i++) { // creates hot vector for path .
        	
            vector1[tmp->path[i]] = 1;
        }
        for (i = 0; i < level; i++) { // creates hot vector for path .
        	
            vector2[path[i]] = 1;
        }
        for (i = 0; i < N; i++) { // checks whether it is equals or not .
        	
            if (vector1[i] != vector2[i]) {
            	
                flag = 1; // if it is not equal , it is unique .
            }
        }
        free(vector1); // free .
        free(vector2); // free .
        tmp = tmp->next; // continues for next nodes .
    }
    return flag; // returns flag .
}

/* @brief checks the nodes for validation .
 *
 * @param takes paths pointer .
 *
 * @param takes node 1 .
 *
 * @param takes node 2 .
 *
 * @param takes edge weight .
 *
 * @return returns node valid or not  .
 */

int isValidNode(GRAPH* graph ,int node1 ,int node2 ,int weight ){
	
	if(weight <= 0){ // checks weight .
		
		printf("\n- \x1b[31mWeight Can Not Be 0 or Less %c %c %d\x1b[0m -\n\n",indexToChar(node1),indexToChar(node2),weight);
		return 0;
	}
	if(node1 == node2){ // checks equality .
		
		printf("\n- \x1b[31mNode1 and Node2 Can Not Be Equals %c %c %d\x1b[0m -\n\n",indexToChar(node1),indexToChar(node2),weight);
		return 0;
	}
	NODE* tmp = graph->adjList[node1];
	while(tmp != NULL){ // checks node is in the adj list or not .
		
		if(tmp->vertex == node2){
			
			printf("\n- \x1b[31mThis Edge Already Added %c %c %d \x1b[0m -\n\n",indexToChar(node1),indexToChar(node2),weight);
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;
}

/* @brief finds number of vertices .
 *
 * @param takes file name from user .
 *
 * @return returns number of vertices from file .
 */

int findNumberOfVertices(char fileName[] ){
	FILE *file = fopen(fileName, "r");
	char line[256];
    char maxChar = 'A'; // A = 0 vertex B = 1 etc. .
    char column1, column2;
	int weight;

    while (fgets(line, sizeof(line), file) != NULL) {
    	
        if (sscanf(line, " %c %c %d", &column1, &column2, &weight) == 3) {

            if (column1 > maxChar) { // if we find a char bigger than 'A' changes max char .
            	
                maxChar = column1;
            }
            if (column2 > maxChar) {
            	
                maxChar = column2;
            }
        } else {
        	
            printf("\n\n\x1b[31m- The Line Could Not Be Read or Is In An Unexpected Format \x1b[0m-\n\n");
        }
    }
    fclose(file); // close file . 
    return charToIndex(maxChar) + 1; // returns max char in int form . maxChar -'A' .
}

/* @brief finds number of shapes .
 *
 * @param takes all paths array .
 *
 * @param takes number of vertices .
 *
 * @return returns number of shapes .
 */

int findNumberOfShapes(PATH** paths ,int N ){
	int i;
	int count=0; // keeps number .
	
	for( i=0 ; i<N-2 ; i++ ){
		
		PATH* tmp = paths[i]; // starts for all path . 
		while(tmp != NULL){ // continues until tmp will be null .
			
			count++; // if there is no null , there is a path .
			tmp = tmp->next; // checks continues for next path .
		}
	}
	return count; // return count .
}

/* @brief finds int form .
 *
 * @param takes char .
 *
 * @return returns char in int form .
 */

int charToIndex(char ch) {
    return ch - 'A';
};

/* @brief finds char form .
 *
 * @param takes int index .
 *
 * @return returns int in char form .
 */

char indexToChar(int index) {
    return 'A' + index;
}

/* @brief prints adj list from graph struct .
 *
 * @param takes graph pointer .
 *
 * @return
 */

void printAdjacencyList(GRAPH* graph){
	int i;
	NODE* tmp; // temporary node variable .
	
	printf("\n\n-- Adjacency List -\n\n");
	for( i=0 ; i<graph->NumberOfVertices ; i++ ){ // continues until reaches the number of vertices .
		
		printf("\x1b[32m%d -> ",i);
		tmp = graph->adjList[i]; // tmp equals to first element of row .
		while(tmp != NULL){ // continues until tmp equals to null .
			
			printf("\x1b[33m%d,\x1b[0m%d  ",tmp->vertex,tmp->weight); // prints vertex and weight .
			tmp = tmp->next;
		}
		printf("\n");
	}
	printf("\n--------------\n");
}

/* @brief prints all found paths .
 *
 * @param takes all paths pointer array .
 *
 * @param takes number of vertices .
 *
 * @return
 */

void print(PATH** paths ,int N ){
	int i,j,k; // i j for iteration k keeps number of same shapes triangle , etc. .
	
	printf("Sekil Sayisi -> \x1b[32m%d\n\n",findNumberOfShapes(paths,N) );
	for( i=0 ; i<N-2 ; i++ ){ // continues until reaches the max shape . N=5 then min shape is triangle(3) max is pentagon (4) -> first shape is N-2 = 3 .
		PATH* tmp = paths[i];
		k=1;
		while(tmp != NULL){
			printf("\x1b[32m%d. %d gen -> \x1b[0m",k++,i+3);
			for( j=0 ; j<i+4 ; j++ ){
				printf("\x1b[33m%c ",indexToChar(tmp->path[j])); // prints vertex in char form .
			}
			printf("\x1b[0m,\x1b[32m uzunluk -> \x1b[33m%d\x1b[0m",tmp->length); // prints path length .
			printf("\n");
			tmp = tmp->next; // next paths if it is exist .
		}
		printf("\n");
	}
}

