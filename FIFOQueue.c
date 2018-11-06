#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct
{
	int item[SIZE];
	int rear, front;
}Queue;

// function prototypes

void initQueue(Queue *); // initailise the rear and front
void enqueue(Queue *, int); // inserts the element passed to the enqueue func.
int dequeue(Queue *); // 'deletes' the front element from the Queue

void initQueue(Queue *qp)
{
	qp->front = 0;
	qp->rear = 0;
}

void enqueue(Queue *qp, int v)
{
	if (qp->rear == SIZE)
	{
		printf("Queue Overflow\n");
		return;
	}
	qp->item[qp->rear] = v;
	qp->rear = qp->rear + 1;
}

int dequeue(Queue *qp)
{
	if (qp->rear == qp->front)
	{
		return -9999; // if dequeue returns this absurd value the caller will understand the queue is empty
	}
	int v = qp->item[qp->front];
	qp->front = qp->front + 1;
	return v;
}


int main()
{
	Queue q;
	initQueue(&q);
	enqueue(&q, 5);
	enqueue(&q, 10);
	enqueue(&q, 15);
	enqueue(&q, 20);

	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));
	printf("%d\n", dequeue(&q));

	printf("%d\n", dequeue(&q));


	return 0;
}