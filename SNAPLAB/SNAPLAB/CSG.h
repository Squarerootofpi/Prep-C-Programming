#ifndef CSG_H
#define CSG_H

#include "Student.h"
#include "Course.h"

//standard setters, getters, and toString

class CSG :
	public Student, public Course
{
public:
	CSG(string course = "none", int student = -1, string grade = "none") 
		: Student(student), Course(course)
	{
		setGrade(grade);
	}
	~CSG(){}
	const string toString()
	{
		string returnString = "";
		ostringstream oS;
		oS << "csg(" << getCourse() << "," << setw(studentIDSize) 
			<< setfill('0') << getStudentID() << ","
			<< getGrade() << ")";
		returnString = oS.str();
		return returnString;
	}
	const string getGrade()
	{
		return grade;
	}
	friend ostream& operator<< (ostream& os, CSG& thisCSG)
	{
		os << thisCSG.toString();
		return os;
	}

private:
	string grade;

	void setGrade(string grade)
	{
		this->grade = grade;
	}

};

#endif