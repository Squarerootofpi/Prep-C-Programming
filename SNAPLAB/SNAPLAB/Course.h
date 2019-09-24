#ifndef COURSE_H
#define COURSE_H

#include "Student.h" //This is so you can see all the libraries in student

//standard setters, getters, and toString

class Course
{
public:
	Course(string courseName = "none") 
	{
		setCourse(courseName);
	}
	~Course(){}
	virtual string const toString() = 0;

	string getCourse()
	{
		return courseName;
	}

private:
	string courseName;
	void setCourse(string courseName)
	{
		this->courseName = courseName;
	}
};

#endif