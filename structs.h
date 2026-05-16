#pragma once

typedef unsigned int uint;
typedef unsigned short ushort;

struct Date
{
	ushort day;
	ushort month;
	ushort year;
};

struct Student
{
	char* name = nullptr;
	Date birthdayDate{ 0, 0, 0 };
	uint id = 0;
	float average = 0.0f;
};
