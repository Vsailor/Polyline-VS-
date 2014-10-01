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
		while(fscanf(file, "%d%d", &pos.x, &pos.y)) {
			push(stack,pos);
		}
	}
	return 0;
}

int mode() {
	printf("Choose input mode:\n1. Console\n2. File\n");
	int mode=1;
	bool badInput = false;
	do{
		scanf_s("%d",&mode);
		if ((mode !=1) && (mode!=2)) {
			printf("Wrong input. Repeat please.\n");
			badInput = true;
		}
	} while(badInput);
	return mode;
}

int main(void)
{
    Stack stack;
	stack = initStack();

	input(mode(),stack);
    showPolyline(stack);

	Pos pos;
	pos.x = 1;
	pos.y = 15;

	push(stack, pos);
	printf("%f", perimeter(stack));
	exsistIntersection(stack);

	int a;
	scanf_s("%d",&a);
    return 0;
}