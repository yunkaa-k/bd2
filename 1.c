#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 100
#define MAX_STUDENTS 1000000

typedef struct {
    char lastName[50];
    char firstName[50];
    int grade;
    int classroom;
    int bus;
    char teacherLastName[50];
    char teacherFirstName[50];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void loadStudents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Не вдалося відкрити файл list.txt");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        Student s;
        sscanf(line, "%[^,], %[^,], %d, %d, %d",
               s.lastName, s.firstName, &s.grade, &s.classroom, &s.bus);
        students[studentCount++] = s;
    }

    fclose(file);
}

void loadTeachers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Не вдалося відкрити файл teachers.txt");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        char teacherLastName[50], teacherFirstName[50];
        int classroom;

        sscanf(line, "%[^,], %[^,], %d", teacherLastName, teacherFirstName, &classroom);

        for (int i = 0; i < studentCount; i++) {
            if (students[i].classroom == classroom) {
                strcpy(students[i].teacherLastName, teacherLastName);
                strcpy(students[i].teacherFirstName, teacherFirstName);
            }
        }
    }

    fclose(file);
}

void searchStudentByLastName(const char *lastName, int busNumber) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            if (busNumber == -1 || students[i].bus == busNumber) {
                printf("Студент: %s %s, Клас: %d, Викладач: %s %s, Автобус: %d, Оцінка: %d\n",
                       students[i].firstName, students[i].lastName, 
                       students[i].classroom,
                       students[i].teacherFirstName, students[i].teacherLastName, 
                       students[i].bus, students[i].grade);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Учень з прізвищем %s не знайдений.\n", lastName);
    }
}

void searchStudentByTeacherLastName(const char *teacherLastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].teacherLastName, teacherLastName) == 0) {
            printf("Викладач: %s %s, Студент: %s %s, Клас: %d,  Автобус: %d, Оцінка: %d\n",
                   students[i].teacherFirstName, students[i].teacherLastName, 
                   students[i].firstName, students[i].lastName, 
                   students[i].classroom,
                   students[i].bus, students[i].grade);
            found = 1;
        }
    }
    if (!found) {
        printf("Учнів у викладача з призвіщем %s не знайдено.\n", teacherLastName);
    }
}

void searchByClassroom(int classroom) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].classroom == classroom) {
            printf("Клас: %d, Студент: %s %s, Викладач: %s %s, Автобус: %d, Оцінка: %d\n",
                   students[i].classroom, students[i].firstName, students[i].lastName, 
                   students[i].teacherFirstName, students[i].teacherLastName, 
                   students[i].bus, students[i].grade);
            found = 1;
        }
    }
    if (!found) {
        printf("Студенти у класі номер %d не знайдені.\n", classroom);
    }
}

void searchTeachersByClassroom(int classroom) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].classroom == classroom) {
            printf("Викладач: %s %s, Клас: %d\n",
                   students[i].teacherFirstName, students[i].teacherLastName, classroom);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Викладача у класі %d не знайдено.\n", classroom);
    }
}

void searchStudentsByGrade(int grade) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].grade == grade) {
            printf("Оцінка: %d, Студент: %s %s, Клас: %d, Викладач: %s %s, Автобус: %d\n",
                   students[i].grade, students[i].firstName, students[i].lastName, 
                   students[i].classroom,
                   students[i].teacherFirstName, students[i].teacherLastName, 
                   students[i].bus);
            found = 1;
        }
    }
    if (!found) {
        printf("Немає учнів з оцінкою %d.\n", grade);
    }
}

void searchTeacherByGrade(int grade) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].grade == grade) {
            printf("Вчитель: %s %s, Оцінка: %d, Студент: %s %s\n",
                   students[i].teacherFirstName, students[i].teacherLastName, grade,
                   students[i].firstName, students[i].lastName);
            found = 1;
        }
    }
    if (!found) {
        printf("Не знайдено вчителів, які поставили оцінку %d.\n", grade);
    }
}

void searchStudentBus(const char *lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].lastName, lastName) == 0) {
            printf("Студент: %s %s, Номер автобуса: %d\n",
                   students[i].firstName, students[i].lastName, students[i].bus);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Учня з прізвищем %s не знайдено.\n", lastName);
    }
}

void searchByBusRoute(int busNumber) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].bus == busNumber) {
            printf("Автобус: %d, Студент: %s %s, Клас: %d, Викладач: %s %s, Оцінка: %d\n",
                   students[i].bus, students[i].firstName, students[i].lastName, 
                   students[i].classroom,
                   students[i].teacherFirstName, students[i].teacherLastName, 
                   students[i].grade);
            found = 1;
        }
    }
    if (!found) {
        printf("Автобус %d не знайдено.\n", busNumber);
    }
}

int main() {
    loadStudents("list.txt");
    loadTeachers("teachers.txt");

    int choice;
    char lastName[50];
    int busNumber, classroom, score;

    while (1) {
        printf("1. Знайти учня за прізвищем\n");
        printf("2. Знайти маршрут автобуса за прізвищем учня\n");
        printf("3. Знайти учнів за прізвищем вчителя\n");
        printf("4. Знайти учнів за номером автобуса\n");
        printf("5. Знайти учнів за номером класу\n");
        printf("6. Знайти вчителя за номером класу\n");
        printf("7. Знайти учнів за оцінкою\n");
        printf("8. Знайти вчителя, який поставив оцінку\n");
        printf("0. Вихід\n");
        printf("Введіть вибір: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введіть прізвище студента: ");
                scanf("%s", lastName);
                printf("Чи шукати учнів за призвіщем і за автобусом? (0/1): ");

                int res;
                scanf("%d", &res);
                if (res > 1 || res < 0) {
                    printf("Неправильний вибір! Спробуйте ще.\n");
                    break;
                }

                if (res) {
                    printf("Введіть номер автобуса: ");
                    scanf("%d", &busNumber);
                    searchStudentByLastName(lastName, busNumber);
                } 
                else {
                    searchStudentByLastName(lastName, -1);
                }
                break;

            case 2:
                printf("Введіть прізвище студента: ");
                scanf("%s", lastName);
                searchStudentByLastName(lastName, -1);
                break;

            case 3:
                printf("Введіть прізвище вчителя: ");
                scanf("%s", lastName);
                searchStudentByTeacherLastName(lastName);
                break;

            case 4:
                printf("Введіть номер автобуса: ");
                scanf("%d", &busNumber);
                searchByBusRoute(busNumber);
                break;

            case 5:
                printf("Введіть номер класу: ");
                scanf("%d", &classroom);
                searchByClassroom(classroom);
                break;

            case 6:
                printf("Введіть номер класу: ");
                scanf("%d", &classroom);
                searchTeachersByClassroom(classroom);
                break;

            case 7:
                printf("Введіть оцінку: ");
                scanf("%d", &score);
                searchStudentsByGrade(score);
                break;

            case 8:
                printf("Введіть оцінку для пошуку вчителя: ");
                scanf("%d", &score);
                searchTeacherByGrade(score);
                break;

            case 0: return 0;
            default:
                printf("Неправильний вибір. Спробуйте ще раз.\n");
                break;
        }
    }
}
