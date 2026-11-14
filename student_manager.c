#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 20
#define NAME_LENG 30

struct Student {
    char name[30];
    int score;
};

void addStudent(struct Student a[], int *n);
void displayStudents(const struct Student a[], int n);
void searchStudent(const struct Student a[], int n);
void changeStudentScore(struct Student a[], int n);
void displayHighest(const struct Student a[], int n);
void displayStatistics(const struct Student a[], int n);
void printStudents(const struct Student a[], int n);
int findName(const struct Student a[], int n, const char target[]);
int highestIndex(const struct Student a[], int n);
void updateScore(struct Student *s, int newScore);
double averageScore(const struct Student a[], int n);
int countAtOrAboveAverage(const struct Student a[], int n, double average);
int readInteger(void);

int main(void) {
    struct Student students[MAX_STUDENTS];
    int count = 0;
    int choice = 0;

    while (choice != 7) {
        printf("\n---- MENU ----\n");
        printf("1. Add student\n");
        printf("2. Display students\n");
        printf("3. Find student by name\n");
        printf("4. Update student score\n");
        printf("5. Display highest-scoring student\n");
        printf("6. Display average score and number of students scoring at or above average\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        choice = readInteger();

        switch (choice) {
            case 1: 
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                changeStudentScore(students, count);
                break;
            case 5:
                displayHighest(students, count);
                break;
            case 6:
                displayStatistics(students, count);
                break;
            case 7:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Enter 1 - 7.\n");
        }
    }

    return 0;
}

//Read and checks choice input
int readInteger(void) {
    char input[10];
    int num;
    char extra;

    while (1) {
        if (scanf("%9s", input) != 1) {
            printf("Invalid input. Enter an integer: ");
            continue;
        }

        if (sscanf(input, "%d %c", &num, &extra) == 1) {
            return num;
        } else {
            printf("Invalid input. Enter an integer: ");
        }
    }
}

//Adds a new student
void addStudent(struct Student a[], int *n) {
    int newScore;
    char name[30];

    if (*n == MAX_STUDENTS) {
        printf("Student list is full. Cannot add more students\n");
        return;
    }

    while (1) {
        printf("Enter name: ");

        if (scanf("%29s", name) != 1) {
            printf("Invalid name. Try again.\n");
            continue;
        }
        if (name[0] >= 'a' && name[0] <= 'z') {
            name[0] = name[0] - ('a' - 'A');
        }
        if (strlen(name) == 0 || strlen(name) >= NAME_LENG) {
            printf("Name is too long. Maximum is 29 characters.\n");
        } else {
            strcpy(a[*n].name, name);
            break;
        }
    }

    while (1) {
        printf("Enter score: ");
        newScore = readInteger();

        if (newScore < 0 || newScore > 100) {
            printf("Invalid score. Enter a score between 0 and 100.\n");
        } else {
            a[*n].score = newScore;
            break;
        }
    }
    (*n)++;

    printf("Student added successfully.\n");
}

//Display all student
void displayStudents(const struct Student a[], int n) {
    if (n == 0) {
        printf("No student have been added yet.\n");
        return;
    }
    printStudents(a, n);
}

//Prints student records
void printStudents(const struct Student a[], int n) {
    printf("\nStudent Records\n");

    for (int i = 0; i < n; i++) {
        printf("Student: %s | Score: %d\n", a[i].name, a[i].score);
    }
}

//Searches for a student
void searchStudent(const struct Student a[], int n) {
    char target[30];
    int index;

    if (n == 0) {
        printf("No students available to search.\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%29s", target);

    if (target[0] >= 'a' && target[0] <= 'z') {
        target[0] = target[0] - ('a' - 'A');
    }

    index = findName(a, n, target);

    if (index == -1) {
        printf("Student not found.\n");
    } else {
        printf("Student found: %s (%d)\n", a[index].name, a[index].score);
    }
}

//Finds a student by name
int findName(const struct Student a[], int n, const char target[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(a[i].name, target) == 0) {
            return i;
        }
    }

    return -1;
}

// Updates a student's score
void changeStudentScore(struct Student a[], int n) {
    char target[30];
    int index;
    int newScore;

    if (n == 0) {
        printf("No students available to update.\n");
        return;
    }

    printf("Enter student name: ");
    scanf("%29s", target);

    if (target[0] >= 'a' && target[0] <= 'z') {
        target[0] = target[0] - ('a' - 'A');
    }

    index = findName(a, n, target);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    while (1) {
        printf("Enter new score: ");
        newScore = readInteger();

        if (newScore < 0 || newScore > 100) {
            printf("Invalid score. Enter a score between 0 and 100.\n");
        } else {
            updateScore(&a[index], newScore);
            printf("Score updated successfully.\n");
            break;
        }
    }
}

// Updates the score using a pointer
void updateScore(struct Student *s, int newScore) {
    s->score = newScore;
}

// Displays the highest-scoring student
void displayHighest(const struct Student a[], int n) {
    int highest;

    if (n == 0) {
        printf("No students available.\n");
        return;
    }

    highest = highestIndex(a, n);

    printf("Highest-scoring student: %s (%d)\n",
           a[highest].name, a[highest].score);

    // Checks if other students have the same highest score
    for (int i = 0; i < n; i++) {

        if (i != highest && a[i].score == a[highest].score) {
            printf("Also tied: %s (%d)\n", a[i].name, a[i].score);
        }
    }
}

// Finds the index of the highest-scoring student
int highestIndex(const struct Student a[], int n) {
    int highest = 0;

    for (int i = 1; i < n; i++) {
        if (a[i].score > a[highest].score) {
            highest = i;
        }
    }

    return highest;
}

// Displays average and number of students at or above average
void displayStatistics(const struct Student a[], int n) {
    double average;
    int total;

    if (n == 0) {
        printf("No students available to calculate statistics.\n");
        return;
    }

    average = averageScore(a, n);
    total = countAtOrAboveAverage(a, n, average);

    printf("Average score: %.2f\n", average);
    printf("Students scoring at or above average: %d\n", total);
}

// Calculates average score
double averageScore(const struct Student a[], int n) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        total = total + a[i].score;
    }

    return (double)total / n;
}

// Counts students at or above average
int countAtOrAboveAverage(const struct Student a[], int n, double average) {
    int total = 0;

    for (int i = 0; i < n; i++) {
        if (a[i].score >= average) {
            total++;
        }
    }

    return total;
}

/**
 * SHORT QUESTIONS
 * 1. Why is an array of structures more appropriate than separate arrays
 *  of student names and scores for this program?
 *  - An array of structures keeps each student's name and score together.
 *      It is easier to organize and manage student records.
 * 
 * 2. Why does updateScore() receive a pointer to a Student structure?
 *  - It receives a pointer so it can update the original student's score 
 *      instead of changing a copy.
 * 
 * 3. Why is strcmp() used instead of == when comparing student names?
 *  - strcmp() compares the characters in two strings.
 *      The == operator compares addresses instead of the actual string contents.
 * 
 * 4. What is the purpose of const in the parameters of printStudents() and highestIndex()?
 *  - const prevents the functions from changing the student records.
 *      These functions only need to read the information.
*/