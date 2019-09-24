#ifndef SNAP_H
#define SNAP_H

#include "Student.h"

//standard setters, getters, and toString

class SNAP :
	public Student
{
public:
	SNAP(int studentID = -1, string name = "none", 
		string address = "none", string phone = "none") 
		: Student(studentID)
	{
		setName(name);
		setAddress(address);
		setPhone(phone);
	}
	~SNAP(){}
	string const toString()
	{
		string returnString = "";
		ostringstream oS;
		oS << "snap(" << setw(studentIDSize) << setfill('0') << getStudentID() 
			<< "," << getName() << "," << getAddress() << "," 
			<< getPhone() << ")";
		returnString = oS.str();
		return returnString;
	}
	const string getName()
	{
		return name;
	}
	const string getAddress()
	{
		return address;
	}
	const string getPhone()
	{
		return phone;
	}
	friend ostream& operator<< (ostream& os, SNAP& thisSnap)
	{
		os << thisSnap.toString();
		return os;
	}

private:
	string name;
	string address;
	string phone;

	void setName(string name)
	{
		this->name = name;
	}
	void setAddress(string address)
	{
		this->address = address;
	}
	void setPhone(string phone)
	{
		this->phone = phone;
	}

};

#endif