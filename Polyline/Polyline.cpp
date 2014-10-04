#include "Polyline.h"
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#define NULL 0

void initStack(Stack &stack) {
	stack.stack = NULL;
	stack.n = 0;
}

// Adding element to the stack
void push(Stack &s, Pos pos) {
	// Initialised new var to make a stack array with n+1 elements
	Stack newStack;
	// making array with n+1 size
	newStack.stack =  (Pos *)malloc((s.n+1)*sizeof(Pos));
	if (s.n == 0) {
		// that's why we don't need to copy array
		newStack.stack[0] = pos;
		newStack.n = 0;

	} else {

		// bad C syntax. It's not me:/
		int i;
		// copies old array into the new array to get old items with a new one
		for (i=0; i<s.n; i++) {

			newStack.stack[i] = s.stack[i];

		}

		newStack.stack[s.n] = pos;
	}
	// change references
	s.n++;
	s.stack = newStack.stack;
}

// Showing and removing element from the stack
Pos pop(Stack &s) {
	Pos result;
	// Initialised new var to make a stack array with n+1 elements
	Stack newStack;
	if (s.n == 1) {
		// last element
		//printf("x = %d; y = %d\n", s.stack[s.n-1].x, s.stack[s.n-1].y);
		result.x = s.stack[s.n - 1].x;
		result.y = s.stack[s.n - 1].y;
		s.stack = NULL;
		s.n--;
	} else if (s.n == 0) {
		printf("Error: Stack is empty\n");
		result.x = 0;
		result.y = 0;
	} else {
		newStack.n = s.n-1;
		// making array with n-1 size
		//printf("x = %d; y = %d\n", s.stack[newStack.n].x, s.stack[newStack.n].y);
		result.x = s.stack[newStack.n].x;
		result.y = s.stack[newStack.n].y;
		newStack.stack =  (Pos *)malloc((s.n-1)*sizeof(Pos));
		// one more time...
		int i;
		// copies old array into the new array to get old items with a new one
		for (i=0; i<newStack.n; i++) {

			newStack.stack[i] = s.stack[i];

		}
		s.n--;
		s.stack = newStack.stack;
	}



	return result;
}

void inputPolyline(Stack &s) {
	printf("How many points in the polyline?\n");
	int k;
	do {
		scanf("%d",&k);
		if (k<=0) {
			printf("Wrong points count value. Try again.\n");
		}
	} while(k<=0);

	int i;
	Pos pos;
	for (i=0; i<k; i++) {
		printf("x[%d] = ",i);
		scanf("%d",&pos.x);
		printf("y[%d] = ",i);
		scanf("%d",&pos.y);
		push(s,pos);
	}


}

void showPolyline(Stack s) {
	int i;
	for (i=s.n-1; i>=0; i--) {
		printf("x = %d, y = %d\n", s.stack[i].x, s.stack[i].y);
	}

}

void addSegment(Stack &stack, Pos pos) {
	push(stack, pos);
}

double perimeter(Stack stack) {
	double P=0;
	Pos a = pop(stack);
	Pos b;
	while (stack.n != 0) {
		b = pop(stack);
		P += sqrt(((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y))*1.0);
		a = b;
	}
	return P;
}



int max(int a, int b) {
	if (a>b) {
		return a;
	} else {
		return b;
	}
}

int min(int a, int b) {
	if (a<b) {
		return a;
	} else {
		return b;
	}
}
 
int area(Pos a, Pos b, Pos c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int intersect_1(int a, int b, int c, int d) {
	int swap;
	if (a > b) {
		swap = a;
		a = b;
		b = swap;
	}
	if (c > d) {
		swap = c;
		c = d;
		d = swap;
	}
	if (max(a,c) < min(b,d)) {
		return 1;
	} else {
		return 0;
	}
}
 
int intersect(Pos a, Pos b, Pos c, Pos d) {
	if (intersect_1 (a.x, b.x, c.x, d.x) && intersect_1 (a.y, b.y, c.y, d.y) && area(a,b,c) * area(a,b,d) <= 0 && area(c,d,a) * area(c,d,b) <= 0) {
		return 1;
	}
	return 0;
}

int exsistIntersection(Stack stack) {
	for (int i=0; i<stack.n-1; i++) {
		for (int j=0; j<stack.n-1; j++) {
			if (i==j) {
				j++;
			} else {
				if (intersect(stack.stack[i], stack.stack[i+1], stack.stack[j], stack.stack[j+1]) == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}



