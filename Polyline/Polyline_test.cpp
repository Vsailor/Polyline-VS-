#include <stdio.h>
#include "Polyline.h"
#include <iostream>
using namespace std;

int input(int mode, Stack &stack) {
	if (mode == 1) {
		inputPolyline(stack);
	} else {
		FILE *file;
		file = fopen("Polyline_test.txt","r");
		Pos pos;
		while(!feof(file)) {
			fscanf(file, "%d", &pos.x);
			fscanf(file, "%d\t", &pos.y);
			push(stack,pos);
		}
		fclose(file);
	}
	return 0;
}

void outputInFile(Stack &stack) {
	Stack s;
	initStack(s);
	int count=stack.n;
	FILE *file;
	Stack hstack;
	initStack(hstack);
	file = fopen("Polyline_output.txt","w");
	for (int l=0; l<count; l++) {
		push(s, pop(stack));
	}
	Stack sortedS;
	initStack(sortedS);
	Pos a;
	for (int l=0; l<count; l++) {
		a = pop(s);
		push(sortedS, a);
		push(stack,a);
	}

	Pos pos;	
	for (int l=0; l<count; l++) {
		pos = pop(sortedS);
		fprintf(file, "x = %d, ",pos.x);
		fprintf(file, "y = %d\n",pos.y);
	}
	fprintf(file, "P = %f\n",perimeter(stack));
	fprintf(file, "Intersections : %d\n",exsistIntersection(stack));
	fclose(file);
}

int mode() {
	printf("Choose input mode:\n1. Console\n2. File\n");
	int mode=1;
	int badInput = 0;
	do{
		scanf_s("%d",&mode);
		if ((mode !=1) && (mode!=2)) {
			printf("Wrong input. Repeat please.\n");
			badInput = 1;
		}
	} while(badInput==1);
	return mode;
}

int main(void)
{
    Stack stack;
	initStack(stack);

	input(mode(),stack);
	outputInFile(stack);
    showPolyline(stack);

	Pos pos;

	printf("%f\n", perimeter(stack));
	printf("%d\n", exsistIntersection(stack));
	int a;
	scanf_s("%d",&a);
    return 0;
}