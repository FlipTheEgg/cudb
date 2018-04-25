#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NAME_SIZE 5
#define KRED  "\x1B[31m"
#define KHDR  "\x1B[4m"
#define RESET "\x1B[0m"

typedef struct {
    char name[NAME_SIZE];
    int data;
} student_t;

void addStudent(int * c, student_t * student_p);
void listStudents(int c, student_t * student_p);
void listOptions();

int main() {

    student_t* student_p = malloc(10000 * sizeof(student_t));
    int cmd = -1;
    int * studentCount = calloc(1, sizeof(int*));
    studentCount[0] = 0;
    char in;

    printf("Welcome to CUDB - The C University Data Base\n");
    listOptions();

    while (cmd != 0) {

        printf("Enter action: ");

        scanf("%s", & in);
        cmd = in - '0';

        if (cmd == 1)
            listStudents(*studentCount, student_p);
        else if (cmd == 2)
            addStudent(studentCount, student_p);
        else if (cmd == 3)
            listOptions();
        else if (cmd != 0)
            printf("invalid input, try again (3 to list options).\n\n");
    }
    printf("Goodbye!");
    return EXIT_SUCCESS;
}

void printStudent(char name[NAME_SIZE], int data, int n){
    int year = 0; //bits 0-4
    for(int i = 0; i < 5; i++)
        year += ((data / (int)pow(2, i)) % 2) * pow(2, i);

    int semester = (data / 32) % 2; //bit 5

    int GPA = 0; //bits 6-13
    for(int i = 6; i < 14; i++)
        GPA += ((data / (int)pow(2, i)) % 2) * pow(2, i-6);

    const char * a[2];
    a[0] = "Autumn";
    a[1] = "Spring";

    printf("s%0004d %4s 20%2d %s %3d\n", n, name, year+9, a[semester], GPA);
}

void listStudents(int c, student_t * student_p) {
    if(c <= 0){
        printf("There are no students in the database.\n\n");
        return;
    }

    int gradeSum = 0;

    printf("\n%ssNum. Name Year Sem.   GPA%s\n", KHDR, RESET);

    for (int i = 0; i < c; i++) {
        int GPA = 0;
        for(int j = 6; j < 14; j++)
            GPA += ((student_p[i].data / (int)pow(2, j)) % 2) * pow(2, j-6);

        printStudent(student_p[i].name, student_p[i].data, i);
        gradeSum += GPA;
    }

    float avg = (float)gradeSum / (float)c;
    printf("\nAverage GPA = %.2f\n\n", avg);
}

void addStudent(int * c, student_t * student_p) {
    if(*c >= 10000)
        printf("%sERROR: Database full%s\n", KRED, RESET);

    char name[NAME_SIZE];
    int data = 0;
    char in[4];
    int d;

    printf("Enter name (4 characters only): ");
    scanf("%s", name);
    //printf("%s\n", name);

    while (1){
        printf("Enter start year (2009-2040): ");
        scanf("%d", &d);
        d -= 2009;
        //printf("(Year: %d)\n", d);
        if(d >= 0 && d <= 31){
            for(int i = 4; i >= 0; i--) {
                int val = (int)pow(2, i);
                if(d >= val) {
                    data += val;
                    d -= val;
                }
            }
            break;
        }
        else
            printf("%sinvalid input!%s\n\n", KRED, RESET);
    }

    while (1){
        printf("Enter start semester (0=Autumn/1=Spring): ");
        scanf("%1d", &d);
        if(d >= 0 && d <= 1) {
            if (d == 1)
                data += 32;
            break;
        } else
            printf("%sinvalid input!%s\n\n", KRED, RESET);
    }

    while (1){
        printf("Enter GPA (0-255): ");
        scanf("%d", &d);
        if(d >= 0 && d <= 255) {
            for(int i = 13; i >= 6; i--) {
                int val = (int)pow(2, i);
                int cval = (int)pow(2, i-6);
                if(d >= cval) {
                    data += val;
                    d -= cval;
                }
            }
            break;
        } else
            printf("%sinvalid input!%s\n\n", KRED, RESET);
    }

    printf("\nData entered: %d\n", data);
    printStudent(name, data, *c);
    printf("\nIs this OK? (y/n): ");
    scanf("%1s", in);
    if(in[0] == 'Y' || in[0] == 'y'){
        strcpy(student_p[*c].name, name);
        student_p[*c].data = data;
        c[0]++;
        printf("Student successfully added to database!\n\n");
    } else {
        printf("Student add aborted.\n\n");
    }
}

void listOptions(){
    printf("\n");
    printf("Options:\n");
    printf("  0: Halt\n");
    printf("  1: List all students\n");
    printf("  2: Add a new student\n");
    printf("  3: List options\n\n");
}
