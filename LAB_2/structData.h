// we use file guards
#ifndef SRUCTDATA // start def of STRUCTDATA
#define STRUCTDATA

// enum for option GEOMETRIC SHAPE selector
enum shape_t
{
    TRIANGLE = 1,
    CIRCLE = 2,
    RECTANGLE = 3
};

// structure to hold data required to process point
typedef struct _point
{
    float x;
    float y;
} point;

// structure to hold data required to process triangles
typedef struct _triangle
{
    point p1, p2, p3;
} triangle;

// structure to hold data required to process circles
typedef struct _circle
{
    point origin;
    float radius;
} circle;

// structure to hold data required to process rectangles
typedef struct _rectangle
{
    point A, B;
} rectangle;

// structure to store user input shapes
typedef struct _geometricShape
{
    enum shape_t flag : 2;

    union
    {
        triangle T;
        circle C;
        rectangle R;
    } shape;

} geometricShape_t;

#endif // ending the def of STRUCTDATA