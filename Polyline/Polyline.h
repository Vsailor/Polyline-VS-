typedef struct Pos* Polyline;

struct Pos{
    Polyline next;
	int x;
	int y;
};

extern void init(Polyline &p);
extern void push(Polyline &p, int x, int y);
extern Polyline pop(Polyline &p);
extern void inputPolyline(Polyline &p);
extern void showPolyline(Polyline &p);
extern void addSegment(Polyline &p, int x, int y);
extern double perimeter(Polyline &p);
extern int exsistIntersection(Polyline &p);  