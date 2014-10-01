#include "Polyline.h"
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#define NULL 0
using namespace std;
Stack initStack() {
	Stack newStack;
	newStack.stack = NULL;
	newStack.n = 0;
	return newStack;
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

Pos intersectionOfTwoLines(Pos A, Pos B, Pos C, Pos D, int& intersection) {
	// y = kx + b
	Pos result;
	intersection = 0;
	double k1, k2;
	double b1, b2;
	if (B.x != A.x) {
		k1 = (B.y-A.y)/(B.x-A.x)*1.0;
	} else {
		k1 = 0;
	}

	b1 = A.y-k1*A.x;

	if (D.x != C.x) {
		k2 = (D.y-C.y)/(D.x-C.x)*1.0;
	} else {
		k2 = 0;
	}

	b2 = C.y-k2*C.x;
	
	if ((A.x!=B.x) && (C.x != D.x) && (A.y!=B.y) && (C.y!=D.y)) {
		result.x = (b2-b1)/(k1-k2);
		result.y = k1*result.x+b1;
		intersection = 1;
		return result;
	} 
	
	if (A.y == B.y) {
		if (C.y == D.y) {
			if (A.y == C.y) {
				if ((B.x < C.x) || (D.x < A.x)) {
					intersection = 0;
					result.x = 0;
					result.y = 0;
					return result;
				} 
				else {
					intersection = 2;
					result.x = 0;
					result.y = 0;
					return result;
				}
				
			} else {
				intersection = 0;
				result.x = 0;
				result.y = 0;
				return result;
			}
		} else {
			intersection = 1;
			result.x = k2*(A.y-b1)/k1*1.0;
			result.y = A.y;
			return result;
		}
	} else {
		if (C.y == D.y) {
			intersection = 1;
			result.x = k1*(C.y-b2)/k2*1.0;
			result.y = C.y;
			return result;
		} else {
			intersection = 1;
			result.x = k1*(C.y-b2)/k2*1.0;
			result.y = C.y;
			return result;
		}
		
	}

}

bool exsistIntersection(Stack stack) {
	Pos A = pop(stack);
	Pos B = pop(stack);
	Pos C = pop(stack);
	Pos D = pop(stack);
	int intersection = false;
	Pos result = intersectionOfTwoLines(A, B, C, D, intersection);
	cout << result.x << endl << result.y << endl << intersection << endl;
	return true;
}



