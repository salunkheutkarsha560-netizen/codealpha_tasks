
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

int rollNumberExists(int rollNo);

int main(void) {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please restart the program.\n");
            return 1;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Program closed.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

int rollNumberExists(int rollNo) {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Student s;

    if (fp == NULL)
        return 0;

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.rollNo == rollNo) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent(void) {
    struct Student s;
    FILE *fp;

    printf("Enter roll number: ");
    if (scanf("%d", &s.rollNo) != 1) {
        printf("Invalid roll number.\n");
        return;
    }

    if (rollNumberExists(s.rollNo)) {
        printf("This roll number already exists.\n");
        return;
    }

    printf("Enter student name (one word): ");
    if (scanf("%49s", s.name) != 1) {
        printf("Invalid name.\n");
        return;
    }

    printf("Enter marks: ");
    if (scanf("%f", &s.marks) != 1 || s.marks < 0 || s.marks > 100) {
        printf("Invalid marks. Enter a value from 0 to 100.\n");
        return;
    }

    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Error opening student file.\n");
        return;
    }

    if (fwrite(&s, sizeof(s), 1, fp) == 1)
        printf("Student added successfully!\n");
    else
        printf("Error saving student record.\n");

    fclose(fp);
}

void displayStudents(void) {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    int found = 0;

    if (fp == NULL) {
        printf("No student records found yet.\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("Roll No: %d | Name: %s | Marks: %.2f\n",
               s.rollNo, s.name, s.marks);
        found = 1;
    }

    if (!found)
        printf("No student records found.\n");

    fclose(fp);
}

void searchStudent(void) {
    struct Student s;
    FILE *fp;
    int rollNo, found = 0;

    printf("Enter roll number to search: ");
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid roll number.\n");
        return;
    }

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.rollNo == rollNo) {
            printf("Student found!\n");
            printf("Roll No: %d | Name: %s | Marks: %.2f\n",
                   s.rollNo, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

void updateStudent(void) {
    struct Student s;
    FILE *fp;
    int rollNo, found = 0;

    printf("Enter roll number to update: ");
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid roll number.\n");
        return;
    }

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.rollNo == rollNo) {
            printf("Enter new name (one word): ");
            if (scanf("%49s", s.name) != 1) {
                printf("Invalid name.\n");
                fclose(fp);
                return;
            }

            printf("Enter new marks: ");
            if (scanf("%f", &s.marks) != 1 ||
                s.marks < 0 || s.marks > 100) {
                printf("Invalid marks. Enter a value from 0 to 100.\n");
                fclose(fp);
                return;
            }

            fseek(fp, -(long)sizeof(s), SEEK_CUR);

            if (fwrite(&s, sizeof(s), 1, fp) == 1)
                printf("Student updated successfully!\n");
            else
                printf("Error updating student record.\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

void deleteStudent(void) {
    struct Student s;
    FILE *fp, *temp;
    int rollNo, found = 0;

    printf("Enter roll number to delete: ");
    if (scanf("%d", &rollNo) != 1) {
        printf("Invalid roll number.\n");
        return;
    }

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No student records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("Could not create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (s.rollNo == rollNo) {
            found = 1;
        } else {
            if (fwrite(&s, sizeof(s), 1, temp) != 1) {
                printf("Error writing temporary file.\n");
                fclose(fp);
                fclose(temp);
                remove("temp.dat");
                return;
            }
        }
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        printf("Student not found.\n");
        remove("temp.dat");
        return;
    }

    if (remove(FILE_NAME) != 0) {
        printf("Error replacing student records file.\n");
        remove("temp.dat");
        return;
    }

    if (rename("temp.dat", FILE_NAME) != 0) {
        printf("Error finalizing deletion. Records remain in temp.dat.\n");
        return;
    }

    printf("Student deleted successfully!\n");
}
