#include <stdio.h>
#include "Polyline.h"


int input(int mode, Polyline &stack) {
	if (mode == 1) {
		inputPolyline(stack);
	} else {
		FILE *file;
		file = fopen("Polyline_test.txt","r");
		Pos pos;
		while(!feof(file)) {
			fscanf(file, "%d", &pos.x);
			fscanf(file, "%d\t", &pos.y);
			push(stack,pos.x,pos.y);
		}
		fclose(file);
	}
	return 0;
}

void outputInFile(Polyline &stack) {
	Polyline t = stack;
	int count=0;
	while (t != NULL) {
		count++;
		t = t->next;
	}
	t = stack;
	FILE *file;
	file = fopen("Polyline_output.txt","w");
	for (int l=0; l<count; l++) {
		fprintf(file, "x = %d, ",t->x);
		fprintf(file, "y = %d\n",t->y);
		t = t->next;
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
    Polyline stack;
	init(stack);

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