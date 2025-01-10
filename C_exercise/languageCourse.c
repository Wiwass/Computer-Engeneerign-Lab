// languageCourse.c
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NAME_LEN 10
#define COURSES_NUM 30
struct Student {
    char name[NAME_LEN + 1];
    char surname[NAME_LEN + 1];
    unsigned short int age;
};
struct Course {
    char language[NAME_LEN];
    unsigned short int level;
    unsigned short int numberEnrolled;
    struct Student students[10];

};
int main()
{
    struct Course school[COURSES_NUM];

    srand(time(0));

    for (int i = 0; i < COURSES_NUM; i++)
    {
        switch (i % 4) {
        case 0:
            strcpy(school[i].language, "ENGLISH");
            school[i].level = i;
            school[i].numberEnrolled = 10;
            for (int j = 0; j < school[i].numberEnrolled; j++)
            {
                sprintf(school[i].students[j].name, "Name%d%d\0", i, j);
                sprintf(school[i].students[j].surname, "Surname%d%d\0", i, j);
                school[i].students[j].age = (rand() % (60 - 20 + 1)) + 20;
                printf("%d: age %d\t", i, school[i].students[j].age);
            }
            break;
        case 1:
            strcpy(school[i].language, "FRENCH");
            school[i].level = i;
            school[i].numberEnrolled = 9;
            for (int j = 0; j < school[i].numberEnrolled; j++)
            {
                sprintf(school[i].students[j].name, "Name%d%d\0", i, j);
                sprintf(school[i].students[j].surname, "Surname%d%d\0", i, j);
                school[i].students[j].age = (rand() % (60 - 20 + 1)) + 20;
                printf("%d: age %d\t", i, school[i].students[j].age);
            }
            break;
        case 2:
            strcpy(school[i].language, "SPANISH");
            school[i].level = i;
            school[i].numberEnrolled = 8;
            for (int j = 0; j < school[i].numberEnrolled; j++)
            {
                sprintf(school[i].students[j].name, "Name%d%d\0", i, j);
                sprintf(school[i].students[j].surname, "Surname%d%d\0", i, j);
                school[i].students[j].age = (rand() % (60 - 20 + 1)) + 20;
                printf("%d: age %d\t", i, school[i].students[j].age);
            }
            break;
        case 3:
            strcpy(school[i].language, "GERMAN");
            school[i].level = i;
            school[i].numberEnrolled = 7;
            for (int j = 0; j < school[i].numberEnrolled; j++)
            {
                sprintf(school[i].students[j].name, "Name%d%d\0", i, j);
                sprintf(school[i].students[j].surname, "Surname%d%d\0", i, j);
                school[i].students[j].age = (rand() % (60 - 20 + 1)) + 20;
                printf("%d: age %d\t", i, school[i].students[j].age);
            }
            break;
        }
    }
}
