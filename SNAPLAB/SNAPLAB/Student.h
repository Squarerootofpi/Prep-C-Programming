#ifndef STUDENT_H
#define STUDENT_H

#include<string>
#include<vector>
#include<iostream>
#include<iomanip>
#include<limits>
#include<fstream>
#include<sstream>

//standard setters, getters, and toString
//This .h file is included in everything else, so
//all the #includes are in this file for brevity

using namespace std;

class Student
{
public:
	Student(int studentID = -1) 
	{
		setStudentID(studentID);
	}
	~Student(){}
	virtual string const toString() = 0;

	int getStudentID()
	{
		return studentID;
	};

private:
	int studentID;

	void setStudentID(int studentID)
	{
		this->studentID = studentID;
	};

};

#endif