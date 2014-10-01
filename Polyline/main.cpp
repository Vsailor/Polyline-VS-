#include <stdio.h>
#include "Polyline.h"


int main(void)
{
    Stack stack;
    stack = initStack();

    inputPolyline(stack);
    //showPolyline(stack);
	printf("%f", perimeter(stack));
	exsistIntersection(stack);
	int a;
	scanf_s("%d",&a);
    return 0;
}