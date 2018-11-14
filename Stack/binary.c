/*
-- Jason van Raamsdonk --
Modified Dynamic Stack
Each time overflow takes place, size of stack will double
With decimal to binary function
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *item;
	/*
	For the array to be dynamically allocated we need to have a pointer to hold the base address of the array, also, since
	the size will be different fot different instances of Stack so we need keep the size inside the struct object.
	*/
 	int top;
 	int size; // to keep track of the size of the stack object
}Stack; 

// prototypes declarations 
void init(Stack *, int);
void push(Stack *, int);// receives address of the stack object to which it should push
int pop(Stack *); // recieves stack address from which th elemnet will be deleted
void deallocate(Stack *); // the purpose of the deallocate func. is to deallocate the item array at runtime
int getSize(Stack *); // returns current size of array

int isUnderflow(Stack *);
int isOverflow(Stack *);

int printBinary(unsigned int);

int getSize(Stack *sp){
	return sp->size;
}

void push(Stack *sp, int value){ // sp is the pointer to the stack object
	if (isOverflow(sp)){ // in order to access a member od an onject using a pointer, use arrow notation
 		int *temp; // base address of the alllcated pointer
 		temp = (int *)malloc(sizeof(int) * sp->size * 2); // doubling size of array
 		if (temp == NULL){
 			printf("Stack Overflow\n");
 			return;
 		}
 		int i;
 		for(i = 0; i <= sp->top; i++){
 			temp[i] = sp->item[i];

 		}
 		free(sp->item); // deallocate existing item array
 		sp->item = temp; // will now point to newly allocated location
 		sp->size *= 2;
 	}

 	sp->top++;
 	sp->item[sp->top] = value;
}

int pop(Stack *sp){
	if (isUnderflow(sp)){
 		printf("Stack Underflow\n");
 		return -9999;
 	}
 	
 	int value;
 	value = sp->item[sp->top];
 	sp->top--;
 	return value;
 }

void init(Stack *sp, int size){
	sp->top = -1;
	sp->item = (int *)malloc(sizeof(int) * size);
	if (sp->item == NULL){
		printf("Unable to allocate memory\n");
		exit(1);
	}
	sp->size = size;
}

void deallocate(Stack *sp){
	if (sp->item != NULL)
		free(sp->item);
	sp->top = -1;
	sp->size = 0;
}

int isOverflow(Stack *sp){
	return sp->top == sp->size - 1; // equality operator returns 1 if true, or 0 if false
}

int isUnderflow(Stack *sp){
	return sp->top == -1; // equality operator returns 1 if true, or 0 if false
}

int printBinary(unsigned int n){
	Stack s;
	int temp = n;
	const int BASE = 2;
	init(&s, 10);

	while(n>0){
		int rem = n % BASE;
		push(&s, rem); // pushing result onto stack
		n /= BASE;

	}
	printf("Binary equivilant of %d is: \n", temp);
	// while(s.top != -1)
	while(!isUnderflow(&s)){ // stack is stack underflow
		printf("%d", pop(&s)); // gives the last inserted element

	}
	deallocate(&s);
}

int main(){

	printBinary(18);

 	return 0;
 } 
