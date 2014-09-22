#include <stdio.h>
#include "Polyline.h"


int main(void)
{
    Stack stack;
    stack = initStack();


   // Problem is here! printf("%d", stack.n);
    inputPolyline(stack);
    showPolyline(stack);
	/*pop(stack);
	pop(stack);
	pop(stack);
	pop(stack);
	pop(stack);*/

	int a;
	scanf_s("%d",&a);
    return 0;
}