#pragma once
#include <iostream>
#include <iomanip>
#include <cstring>
#include "structs.h"

using namespace std;

enum Menu
{
	CREATE_LIST = 1,
	ADD_STUDENT,
	DELETE_STUDENT,
	SHOW_ALL_STUDENTS,
	FIND_STUDENT,
	EDIT_STUDENT,
	SORT_BY_NAME,
	SORT_BY_AVERAGE,
	DELETE_ALL,
	EXIT
};

void showMenu()
{
	cout << "\n================= ГОЛОВНЕ МЕНЮ =================\n";
	cout << " " << CREATE_LIST       << " -> Створити новий список студентів\n";
	cout << " " << ADD_STUDENT         << " -> Додати нового студента до списку\n";
	cout << " " << DELETE_STUDENT      << " -> Видалити студента за ID\n";
	cout << " " << SHOW_ALL_STUDENTS   << " -> Показати всіх студентів\n";
	cout << " " << FIND_STUDENT        << " -> Знайти студента за ID\n";
	cout << " " << EDIT_STUDENT        << " -> Редагувати дані студента\n";
	cout << " " << SORT_BY_NAME        << " -> Сортувати за ім'ям\n";
	cout << " " << SORT_BY_AVERAGE     << " -> Сортувати за середнім балом\n";
	cout << " " << DELETE_ALL          << " -> Очистити весь список\n";
	cout << " " << EXIT                << " -> Вийти з програми\n";
	cout << "================================================\n";
}

void systemPause()
{
	cout << "\nНатисніть Enter, щоб продовжити...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

Student createStudent()
{
	Student std{};
	static uint id = 100;
	std.id = id++;

	const int N = 40;
	char n[N];
	
	cout << "\nВведіть ПІБ студента: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(n, N);
	
	std.name = new char[strlen(n) + 1];
	strcpy_s(std.name, strlen(n) + 1, n);

	cout << "Введіть середній бал: ";
	cin >> std.average;

	cout << "Введіть дату народження (День Місяць Рік через пробіл): ";
	cin >> std.birthdayDate.day >> std.birthdayDate.month >> std.birthdayDate.year;

	return std;
}

void showTableHeader()
{
	cout << "\n" << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
	cout << "| " << setw(5) << left << "ID" 
		 << "| " << setw(25) << left << "ПІБ Студента" 
		 << "| " << setw(12) << left << "Сер. бал" 
		 << "| " << setw(12) << left << "Дата народж." << " |\n";
	cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
}

void showStudentRow(const Student& std)
{
	cout << "| " << setw(5) << left << std.id 
		 << "| " << setw(25) << left << (std.name ? std.name : "Немає імені")
		 << "| " << setw(12) << left << fixed << setprecision(2) << std.average << "| ";
	
	cout << setfill('0') << setw(2) << std.birthdayDate.day << "."
		 << setw(2) << std.birthdayDate.month << "."
		 << setfill(' ') << setw(6) << left << std.birthdayDate.year << " |\n";
}

void showAllStudents(const Student* students, uint size)
{
	if (size == 0 || students == nullptr)
	{
		cout << "\n[!] Список студентів порожній.\n";
		return;
	}

	showTableHeader();
	for (uint i = 0; i < size; i++)
	{
		showStudentRow(students[i]);
	}
	cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
}

void clearNames(Student* students, uint size)
{
	if (students != nullptr)
	{
		for (uint i = 0; i < size; i++)
		{
			delete[] students[i].name;
			students[i].name = nullptr;
		}
	}
}

void clear(Student*& students, uint& size)
{
	clearNames(students, size);
	delete[] students;
	size = 0;
	students = nullptr;
}

void sorting(Student* students, uint size, void(*sortFunc)(Student* students, uint size))
{
	if (size < 2 || students == nullptr)
	{
		cout << "\n[!] Немає чим сортувати (список занадто малий).\n";
		return;
	}
	sortFunc(students, size);
	cout << "\n[+] Сортування успішно виконано!\n";
}

void sortByName(Student* students, uint size)
{
	for (uint i = 0; i < size - 1; i++)
	{
		for (uint j = 0; j < size - 1 - i; j++)
		{
			if (strcmp(students[j].name, students[j + 1].name) > 0)
			{
				swap(students[j], students[j + 1]);
			}
		}
	}
}

void sortByAverage(Student* students, uint size)
{
	for (uint i = 0; i < size - 1; i++)
	{
		for (uint j = 0; j < size - 1 - i; j++)
		{
			if (students[j].average < students[j + 1].average)
			{
				swap(students[j], students[j + 1]);
			}
		}
	}
}

void createStudentsList(Student*& students, uint& size)
{
	if (students != nullptr)
	{
		clear(students, size);
	}
	cout << "Введіть кількість студентів для початкового списку: ";
	cin >> size;
	if (size > 0)
	{
		students = new Student[size];
		for (uint i = 0; i < size; i++)
		{
			cout << "\n--- Студент №" << i + 1 << " ---";
			students[i] = createStudent();
		}
		cout << "\n[+] Список успішно створено!\n";
	}
}

void addStudent(Student*& students, uint& size)
{
	Student* new_students = new Student[size + 1];
	for (uint i = 0; i < size; i++)
	{
		new_students[i] = students[i];
	}
	
	cout << "\n--- Додавання нового студента ---";
	new_students[size] = createStudent();
	
	delete[] students;
	students = new_students;
	size++;
	cout << "\n[+] Студента успішно додано!\n";
}

void deleteStudentById(Student*& students, uint& size, uint id)
{
	int index = -1;
	for (uint i = 0; i < size; i++)
	{
		if (students[i].id == id)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		if (size - 1 == 0)
		{
			clear(students, size);
		}
		else
		{
			Student* new_students = new Student[size - 1];
			delete[] students[index].name;

			for (uint i = 0, k = 0; i < size; i++)
			{
				if (i != (uint)index)
				{
					new_students[k++] = students[i];
				}
			}
			delete[] students;
			students = new_students;
			size--;
		}
		cout << "[+] Студента з ID " << id << " успішно видалено!\n";
	}
	else
	{
		cout << "[-] Студента з ID " << id << " не знайдено.\n";
	}
}

void findStudentById(const Student* students, uint size, uint id)
{
	for (uint i = 0; i < size; i++)
	{
		if (students[i].id == id)
		{
			cout << "\n[+] Студента знайдено:";
			showTableHeader();
			showStudentRow(students[i]);
			cout << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
			return;
		}
	}
	cout << "[-] Студента з ID " << id << " не знайдено.\n";
}

void editStudentById(Student* students, uint size, uint id)
{
	for (uint i = 0; i < size; i++)
	{
		if (students[i].id == id)
		{
			cout << "\nРедагування даних для студента: " << students[i].name << endl;
			cout << "Введіть новий середній бал: ";
			cin >> students[i].average;
			cout << "[+] Дані успішно оновлено!\n";
			return;
		}
	}
	cout << "[-] Студента з ID " << id << " не знайдено.\n";
}

void runAcademy()
{
	uint size = 0;
	Student* students = nullptr;
	int choice;

	do
	{
		showMenu();
		cout << "Зробіть ваш вибір (" << CREATE_LIST << "-" << EXIT << "): ";
		cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "[-] Помилка! Введіть коректне число.\n";
			systemPause();
			continue;
		}

		switch (choice)
		{
		case CREATE_LIST:
			createStudentsList(students, size);
			break;
		case ADD_STUDENT:
			addStudent(students, size);
			break;
		case DELETE_STUDENT:
		{
			if (size == 0) { cout << "Список порожній.\n"; break; }
			uint id;
			cout << "Введіть ID для видалення: ";
			cin >> id;
			deleteStudentById(students, size, id);
			break;
		}
		case SHOW_ALL_STUDENTS:
			showAllStudents(students, size);
			break;
		case FIND_STUDENT:
		{
			if (size == 0) { cout << "Список порожній.\n"; break; }
			uint id;
			cout << "Введіть ID для пошуку: ";
			cin >> id;
			findStudentById(students, size, id);
			break;
		}
		case EDIT_STUDENT:
		{
			if (size == 0) { cout << "Список порожній.\n"; break; }
			uint id;
			cout << "Введіть ID для редагування: ";
			cin >> id;
			editStudentById(students, size, id);
			break;
		}
		case SORT_BY_NAME:
			sorting(students, size, sortByName);
			break;
		case SORT_BY_AVERAGE:
			sorting(students, size, sortByAverage);
			break;
		case DELETE_ALL:
			clear(students, size);
			cout << "[+] Усі дані видалено, список порожній.\n";
			break;
		case EXIT:
			clear(students, size);
			cout << "\nДякуємо за використання програми! Бувай!\n";
			break;
		default:
			cout << "[-] Невірна команда! Спробуйте ще раз.\n";
			break;
		}

		if (choice != EXIT)
		{
			systemPause();
		}

	} while (choice != EXIT);
}
