#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    char dept[20];
    float marks;
};

void addStudent();
void displayStudent();
void searchStudent();
void deleteStudent();
void updateStudent();

int main() {
    int choice;

    while(1) {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Department: ");
    scanf("%s", s.dept);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student Added!\n");
}

void displayStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("\nRoll: %d\nName: %s\nDepartment: %s\nMarks: %.2f\n",
            s.roll, s.name, s.dept, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found!\n");
            printf("Roll: %d\nName: %s\nDepartment: %s\nMarks: %.2f\n",
                s.roll, s.name, s.dept, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student NOT found!\n");

    fclose(fp);
}

void deleteStudent() {
    struct Student s;
    FILE *fp, *fp2;
    int roll, found = 0;

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb");
    fp2 = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, fp2);
        }
    }

    fclose(fp);
    fclose(fp2);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record Deleted!\n");
    else
        printf("Student NOT found!\n");
}

void updateStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Department: ");
            scanf("%s", s.dept);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            printf("Record Updated!\n");
            break;
        }
    }

    if (!found)
        printf("Student NOT found!\n");

    fclose(fp);
}
