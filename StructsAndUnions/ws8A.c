#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AREAWIDTH 100
#define AREAHEIGHT 100

typedef struct Rectangle
{
    int x;
    int y;
    int width;
    int height;
} Rectangle;

typedef struct Point
{
    int x;
    int y;
    char name[20];
} Point;

_Bool equals_point(Point point1, Point point2)
{
    return (point1.x == point2.x) && (point1.y == point2.y);
}

_Bool equals_rect(Rectangle rect1, Rectangle rect2)
{
    return memcmp(&rect1, &rect2, sizeof(Rectangle)) == 0;
}

_Bool contains(Rectangle rect, Point point)
{
    return (point.x >= rect.x) && (point.x < rect.x + rect.width) &&
           (point.y >= rect.y) && (point.y < rect.y + rect.height);
}

int main(void)
{
    srand((unsigned int)time(NULL));

    // 1. Generate a 50x50 rectangle at a random position within the 100x100 area
    Rectangle rect;
    rect.width = 50;
    rect.height = 50;
    rect.x = rand() % (AREAWIDTH - rect.width + 1);
    rect.y = rand() % (AREAHEIGHT - rect.height + 1);

    printf("Generated Rectangle: x=%d, y=%d, width=%d, height=%d\n\n",
           rect.x, rect.y, rect.width, rect.height);

    // 2. Generate every point in the 100x100 area
    Point points[AREAWIDTH * AREAHEIGHT];
    int index = 0;

    for (int y = 0; y < AREAHEIGHT; y++)
    {
        for (int x = 0; x < AREAWIDTH; x++)
        {
            points[index].x = x;
            points[index].y = y;
            index++;
        }
    }

    printf("Generated %d points (from (0,0) to (99,99))\n\n", index);

    // 3. Check which points are inside the rectangle
    int insideCount = 0;
    for (int i = 0; i < index; i++)
    {
        if (contains(rect, points[i]))
            insideCount++;
    }

    // 4. Print percentage of points inside
    double percentage = ((double)insideCount / (double)index) * 100.0;

    printf("Points inside the rectangle: %d\n", insideCount);
    printf("Total points: %d\n", index);
    printf("Percentage inside: %.2f%%\n\n", percentage);

    return 0;
}
