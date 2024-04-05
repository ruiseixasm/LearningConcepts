#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

struct PointArray {
    struct Point points[3];
};

struct Student {
    char* name;
};

void printPoint_c(struct Point* p) {
    printf("x: %d  y: %d\n", p->x, p->y);
}

void printPointArray_c(struct PointArray pa) {
    for (int i = 0; i < 3; i++) {
        printf("%d %d\n", pa.points[i].x, pa.points[i].y);
    }
}

struct Point* getPoint_c() {
    struct Point* p = malloc(sizeof(struct Point));
    if (p != NULL) {
        p->x = 10;
        p->y = 20;
    }
    return p;
}

void deletePoint_c(struct Point* p) {
    free(p);
    printf("Point deleted!\n");
}

void printStudent_c(struct Student s) {
    printf("%s\n", s.name);
}

struct Student* getStudent_c() {
    struct Student* s = malloc(sizeof(struct Student));
    if (s != NULL) {
        s->name = strdup("Coders Legacy");  // Allocated in RAM and it's mutable (must be deallocated)
        //s->name = "Coders Legacy";        // Allocated in ROM/Flash and it's immutable (string literal)
    }
    return s;
}

void deleteStudent_c(struct Student* s) {
    free(s->name);
    free(s);
    printf("Student deleted!\n");
}



// Generate the .so file with this command
// gcc clibrary.c -shared -o clibrary.so -fPIC
