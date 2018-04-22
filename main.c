#include <stdio.h>
#include <stdlib.h>

#define NAME_SIZE 5

typedef struct {
    char name[NAME_SIZE];
    int data;
} student_t;

void addStudent();
void listStudents(int c, student_t * student_p);
void listOptions();

int main() {

    student_t* student_p = malloc(10000 * sizeof(student_t*)); //TODO : is this right?
    int cmd = -1;
    int studentCount = 0;
    char in;

    printf("Welcome to CUDB - The C University Data Base\n\n");
    listOptions();

    while (cmd != 0) {

        printf("Enter action: ");

        scanf("%s", & in);
        cmd = in - '0';

        if (cmd == 1)
            listStudents(studentCount, student_p);
        else if (cmd == 2)
            addStudent();
        else if (cmd == 3)
            listOptions();
        else if (cmd != 0)
            printf("invalid input, try again (3 to list options).\n\n");
    }
}

void listStudents(int c, student_t * student_p) {

    if(c == 0){
        printf("There are no students in the database.\n");
        return;
    }

    //Placeholders. Find the stuff!
    int gradeSum = 0;
    char name = *student_p->name;
    int begYear = 0;
    int semester = 0;
    int GPA = 0;

    const char *a[2];
    a[0] = "Autumn";
    a[1] = "Spring";

    printf("Num.  Name Year sem.   GPA\n");

    for (int i = 0; i < c; i++) {

        printf("s%0004d %4s 20%2d %s %3d\n", i, &name, begYear+9, a[semester], GPA);
        gradeSum += GPA;
    }

    float avg = (float)GPA / (float)c;
    printf("\nAverage GPA = %f\n", avg);
}

void addStudent(){
    //TODO
}

void listOptions(){
    printf("Options:");
    printf("   0: Halt\n");
    printf("   1: List all students\n");
    printf("   2: Add a new student\n");
    printf("   3: List options\n\n");

}