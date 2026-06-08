#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 80

#define RECTANGLE 1
#define LINE 2
#define TRIANGLE 3
#define CIRCLE 4

typedef struct
{
    int type;

    int x, y;
    int x2, y2;

    int width, height;
    int radius;
    int size;

    int active;

} Shape;

char canvas[ROWS][COLS];
Shape shapes[100];
int count = 0;

/* ==========================
   Canvas Functions
   ========================== */

void initCanvas()
{
    int i, j;
    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = ' ';
        }
    }
}

void displayCanvas()
{
    int i, j;
    printf("\n");
    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

/* ==========================
   Drawing Functions
   ========================== */

void drawRectangle(int x, int y, int width, int height)
{
    int i;
    for(i = 0; i < width; i++)
    {
        int targetY = y + i;
        if (targetY >= 0 && targetY < COLS)
        {
            if (x >= 0 && x < ROWS) 
                canvas[x][targetY] = '*';
            if (x + height - 1 >= 0 && x + height - 1 < ROWS) 
                canvas[x + height - 1][targetY] = '*';
        }
    }

    for(i = 0; i < height; i++)
    {
        int targetX = x + i;
        if (targetX >= 0 && targetX < ROWS)
        {
            if (y >= 0 && y < COLS) 
                canvas[targetX][y] = '*';
            if (y + width - 1 >= 0 && y + width - 1 < COLS) 
                canvas[targetX][y + width - 1] = '*';
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int i;
    if(x1 == x2)
    {
        int startY = (y1 < y2) ? y1 : y2;
        int endY = (y1 < y2) ? y2 : y1;
        
        for(i = startY; i <= endY; i++)
        {
            if(x1 >= 0 && x1 < ROWS && i >= 0 && i < COLS)
            {
                canvas[x1][i] = '*';
            }
        }
    }
    else if(y1 == y2)
    {
        int startX = (x1 < x2) ? x1 : x2;
        int endX = (x1 < x2) ? x2 : x1;
        
        for(i = startX; i <= endX; i++)
        {
            if(i >= 0 && i < ROWS && y1 >= 0 && y1 < COLS)
            {
                canvas[i][y1] = '*';
            }
        }
    }
}

void drawTriangle(int x, int y, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        int targetX = x + i;
        if (targetX >= 0 && targetX < ROWS)
        {
            if (y >= 0 && y < COLS) 
                canvas[targetX][y] = '*';
            if (y + i >= 0 && y + i < COLS) 
                canvas[targetX][y + i] = '*';
        }
        
        int baseX = x + size - 1;
        if (baseX >= 0 && baseX < ROWS && (y + i) >= 0 && (y + i) < COLS)
        {
            canvas[baseX][y + i] = '*';
        }
    }
}

void drawCircle(int cx, int cy, int r)
{
    int x, y;
    for(x = 0; x < ROWS; x++)
    {
        for(y = 0; y < COLS; y++)
        {
            int value = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            if(abs(value - r * r) <= r)
            {
                canvas[x][y] = '*';
            }
        }
    }
}

/* ==========================
   Shape Creation
   ========================== */

void addRectangle()
{
    // Step 2: Storage Validation Check
    if(count >= 100)
    {
        printf("Shape storage full!\n");
        return;
    }

    Shape s;
    printf("Row: ");
    scanf("%d", &s.x);
    printf("Column: ");
    scanf("%d", &s.y);
    printf("Width: ");
    scanf("%d", &s.width);
    printf("Height: ");
    scanf("%d", &s.height);

    s.type = RECTANGLE;
    s.active = 1;
    shapes[count++] = s;
}

void addCircle()
{
    // Step 2: Storage Validation Check
    if(count >= 100)
    {
        printf("Shape storage full!\n");
        return;
    }

    Shape s;
    printf("Center Row: ");
    scanf("%d", &s.x);
    printf("Center Column: ");
    scanf("%d", &s.y);
    printf("Radius: ");
    scanf("%d", &s.radius);

    s.type = CIRCLE;
    s.active = 1;
    shapes[count++] = s;
}

void addTriangle()
{
    // Step 2: Storage Validation Check
    if(count >= 100)
    {
        printf("Shape storage full!\n");
        return;
    }

    Shape s;
    printf("Row: ");
    scanf("%d", &s.x);
    printf("Column: ");
    scanf("%d", &s.y);
    printf("Size: ");
    scanf("%d", &s.size);

    s.type = TRIANGLE;
    s.active = 1;
    shapes[count++] = s;
}

void addLine()
{
    // Step 2: Storage Validation Check
    if(count >= 100)
    {
        printf("Shape storage full!\n");
        return;
    }

    Shape s;
    printf("Start Row: ");
    scanf("%d", &s.x);
    printf("Start Column: ");
    scanf("%d", &s.y);
    printf("End Row: ");
    scanf("%d", &s.x2);
    printf("End Column: ");
    scanf("%d", &s.y2);

    s.type = LINE;
    s.active = 1;
    shapes[count++] = s;
}

/* ==========================
   Redraw
   ========================== */

void redrawAllShapes()
{
    int i;
    initCanvas();

    for(i = 0; i < count; i++)
    {
        if(!shapes[i].active)
            continue;

        switch(shapes[i].type)
        {
            case RECTANGLE:
                drawRectangle(shapes[i].x, shapes[i].y, shapes[i].width, shapes[i].height);
                break;
            case CIRCLE:
                drawCircle(shapes[i].x, shapes[i].y, shapes[i].radius);
                break;
            case TRIANGLE:
                drawTriangle(shapes[i].x, shapes[i].y, shapes[i].size);
                break;
            case LINE:
                drawLine(shapes[i].x, shapes[i].y, shapes[i].x2, shapes[i].y2);
                break;
        }
    }
}

/* ==========================
   Shape Management
   ========================== */

// Step 1: Replaced with Enhanced Shape Listing Function
void listShapes()
{
    int i;
    int activeCount = 0;

    printf("\n========== Stored Shapes ==========\n");

    for(i = 0; i < count; i++)
    {
        if(!shapes[i].active)
            continue;

        activeCount++;

        printf("ID %d -> ", i);

        switch(shapes[i].type)
        {
            case RECTANGLE:
                printf("Rectangle | Row=%d Col=%d Width=%d Height=%d",
                       shapes[i].x,
                       shapes[i].y,
                       shapes[i].width,
                       shapes[i].height);
                break;

            case CIRCLE:
                printf("Circle | Center=(%d,%d) Radius=%d",
                       shapes[i].x,
                       shapes[i].y,
                       shapes[i].radius);
                break;

            case TRIANGLE:
                printf("Triangle | Row=%d Col=%d Size=%d",
                       shapes[i].x,
                       shapes[i].y,
                       shapes[i].size);
                break;

            case LINE:
                printf("Line | (%d,%d) -> (%d,%d)",
                       shapes[i].x,
                       shapes[i].y,
                       shapes[i].x2,
                       shapes[i].y2);
                break;
        }

        printf("\n");
    }

    printf("\nTotal Active Shapes: %d\n", activeCount);
}

void deleteShape()
{
    int id;
    listShapes();
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    if(id >= 0 && id < count)
    {
        shapes[id].active = 0;
        redrawAllShapes();
        printf("Shape deleted.\n");
    }
    else
    {
        printf("Invalid ID.\n");
    }
}

// Step 3: Replaced with Full Comprehensive Modification Engine
void modifyShape()
{
    int id;

    listShapes();

    printf("Enter ID to modify: ");
    scanf("%d", &id);

    if(id < 0 || id >= count || !shapes[id].active)
    {
        printf("Invalid ID\n");
        return;
    }

    switch(shapes[id].type)
    {
        case RECTANGLE:
            printf("New Row: ");
            scanf("%d", &shapes[id].x);

            printf("New Column: ");
            scanf("%d", &shapes[id].y);

            printf("New Width: ");
            scanf("%d", &shapes[id].width);

            printf("New Height: ");
            scanf("%d", &shapes[id].height);
            break;

        case CIRCLE:
            printf("New Center Row: ");
            scanf("%d", &shapes[id].x);

            printf("New Center Column: ");
            scanf("%d", &shapes[id].y);

            printf("New Radius: ");
            scanf("%d", &shapes[id].radius);
            break;

        case TRIANGLE:
            printf("New Row: ");
            scanf("%d", &shapes[id].x);

            printf("New Column: ");
            scanf("%d", &shapes[id].y);

            printf("New Size: ");
            scanf("%d", &shapes[id].size);
            break;

        case LINE:
            printf("New Start Row: ");
            scanf("%d", &shapes[id].x);

            printf("New Start Column: ");
            scanf("%d", &shapes[id].y);

            printf("New End Row: ");
            scanf("%d", &shapes[id].x2);

            printf("New End Column: ");
            scanf("%d", &shapes[id].y2);
            break;
    }

    redrawAllShapes();
    printf("Shape modified successfully.\n");
}

/* ==========================
   Main
   ========================== */

int main()
{
    int choice;
    initCanvas();

    // Step 4: Nice Optional v1.1 Welcome Banner
    printf("====================================\n");
    printf("      2D GRAPHICS EDITOR v1.1\n");
    printf("====================================\n");

    while(1)
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Circle\n");
        printf("3. Add Triangle\n");
        printf("4. Add Line\n");
        printf("5. Display Canvas\n");
        printf("6. List Shapes\n");
        printf("7. Delete Shape\n");
        printf("8. Modify Shape\n");
        printf("9. Exit\n");
        printf("Enter choice: ");

        if(scanf("%d", &choice) != 1) {
            printf("Invalid text input! Exiting.\n");
            break;
        }

        switch(choice)
        {
            case 1: addRectangle(); redrawAllShapes(); break;
            case 2: addCircle();    redrawAllShapes(); break;
            case 3: addTriangle();  redrawAllShapes(); break;
            case 4: addLine();      redrawAllShapes(); break;
            case 5: displayCanvas(); break;
            case 6: listShapes();    break;
            case 7: deleteShape();   break;
            case 8: modifyShape();   break;
            case 9: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}