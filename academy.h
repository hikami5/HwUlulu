#pragma once
#include "structs.h"

enum MenuChoice {
    EXIT,
    ADD_STUDENT,
    DELETE_STUDENT,
    SHOW_ALL_STUDENTS,
    SORT_BY_NAME,
    SORT_BY_AVERAGE,
    FIND_BY_NAME,
    EDIT_GRADE,
    CLEAR_DATABASE
};

void showMenu();
void runAcademy();
void addStudent(Student*& students, uint& size);
void deleteStudentById(Student*& students, uint& size, uint id);
void sorting(Student* students, uint size, void(*sort)(Student* students, uint size));
void sortByName(Student* students, uint size);
void sortByAverage(Student* students, uint size);
void clear(Student*& students, uint& size);
void findByName(const Student* students, uint size);
void editGrade(Student* students, uint size);
