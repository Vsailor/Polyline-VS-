#include "Polyline.h"
#include <stdio.h>
#include <math.h>
#define NULL 0

void init(Polyline &p) {
	p = NULL;
}

void push(Polyline &p, int x, int y) {
	Polyline k;
	init(k);
	k = new Pos;
	k->x = x;
	k->y = y;
	k->next = p;
	p = k;
}

Polyline pop(Polyline &p) {
	if (p != NULL) {
		p = p->next;
		return p;
	}
	else {
		printf("Error : Stack is empty.\n");
		return NULL;
	}
}

void inputPolyline(Polyline &p) {
	printf("How many points in the polyline?\n");
	int k;
	do {
		scanf("%d",&k);
		if (k<=0) {
			printf("Wrong points count value. Try again.\n");
		}
	} while(k<=0);

	int i;
	int x, y;
	for (i=0; i<k; i++) {
		printf("x[%d] = ",i);
		scanf("%d",&x);
		printf("y[%d] = ",i);
		scanf("%d",&y);
		push(p,x,y);
	}


}

void showPolyline(Polyline &p) {
	int i;
	Polyline k = p;
	while (k != NULL) {
		printf("x = %d, y = %d\n", k->x, k->y);
		k = k->next;
	}
}

void addSegment(Polyline &p, int x, int y) {
	push(p, x, y);
}

double perimeter(Polyline& p) {
	double P=0;
	Polyline k = p;
	Polyline a = pop(k);
	Polyline b;
	while (k->next != NULL) {
		b = pop(k);
		P = P + sqrt(((b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y))*1.0);
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
 // Повертає подвоєну площу трикутника
int area(Pos a, Pos b, Pos c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int intersect_1(int a, int b, int c, int d) {
	// Тимчасова змінна для заміни значень змінних 
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
 // Повертає 1, якщо відрізки ab і cd перетинаються
int intersect(Pos a, Pos b, Pos c, Pos d) {
	if (intersect_1 (a.x, b.x, c.x, d.x) && intersect_1 (a.y, b.y, c.y, d.y) && area(a,b,c) * area(a,b,d) <= 0 && area(c,d,a) * area(c,d,b) <= 0) {
		return 1;
	}
	return 0;
}

int exsistIntersection(Polyline& stack) {
	Polyline k = stack;
	Polyline t;
	while (k->next != NULL) {
		t = k->next;
		while (t->next != NULL) {
			// Оскільки k - вказівник на Pos, а intersect приймає в параметри Pos, то ми його розіменовуємо за допомогою *
			if (intersect(*k, *k->next, *t, *t->next))
			{
				return 1;
			}
			t = t->next;
		}
		k = k->next;
	}
	return 0;
}



