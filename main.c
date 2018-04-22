#include <stdio.h>

#define NAME_SIZE 5

typedef struct {
    char name[NAME_SIZE];
    int data;
} student_t;

void addStudent();
void listStudents();

int main() {

    int cmd = -1;
    char ci;

    printf("Welcome to CUDB - The C University Data Base\n\n");

    while (cmd != 0) {

        printf("0: Halt\n");
        printf("1: List all students\n");
        printf("2: Add a new student\n\n");
        printf("Enter action: ");

        scanf("%s", & ci);
        cmd = ci - '0';

        if (cmd == 1)
            listStudents();
        else if (cmd == 2)
            addStudent();
        else if (cmd != 0)
            printf("invalid input, try again.\n\n");
    }
}

void listStudents(){

    for(int i = 0; i < 10000; i++){

    }



}

void addStudent(){

}