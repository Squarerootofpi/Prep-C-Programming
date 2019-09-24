#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

int studentIDSize = 0; //you use this later in the classes for setfill
					   //and when the studentID is 0000 or 00000. 

#include "Student.h"
#include "SNAP.h"
#include "CDH.h"
#include "CSG.h"
#include "CR.h"
#include "Course.h"

//All other macros are in Student.h


//Allows you to check if any issues with the inputfile.
const string readInCheck(string toCheck)
{
	exception ex;
	try
	{
		if (!(2 <= toCheck.find('(') && toCheck.find('(') <= 5))
		{
			throw ex;
		}
	}
	catch (out_of_range)
	{
		cout << "Out of range!" << endl;
		//system("Pause");
		return "**Error: ";
	}
	catch (std::exception) //if something fails in outside function;
	{
		cout << "Standard exception: " << ex.what() << endl;
		//system("Pause");
		return "**Error: ";

	}
	catch (...)
	{
		cout << "Unknown function exception." << endl;
		//system("Pause");
		return "**Error: ";
	}
	string returnString = "none";
	return returnString;
}

//finds which class each line is, so line an be parsed appropriately.
const string checkClass(string toCheck)
{
	if (readInCheck(toCheck) == "**Error: ") 
	{
		return "**Error: ";
	}
	string testString = toCheck.substr(0, toCheck.find('('));
		string classType;
		if ("snap" == testString) { classType = "SNAP"; }
		else if (testString == "cdh") { classType = "CDH"; }
		else if (testString == "csg") { classType = "CSG"; }
		else if (testString == "cr") { classType = "CR"; }
		else { classType = "**Error: "; }

	return classType;
}


int main(int arc, char* argv[])
{
	VS_MEM_CHECK               // enable memory leak check

	//Apply Input and Output files

	std::ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		std::cout << "input opening error" << std::endl;
		return 1;
	}
	std::ofstream outputFile(argv[2]);
	if (!outputFile)
	{
		std::cout << "output opening error" << std::endl;
		return 1;
	}

	outputFile << "Input Strings:" << endl;

	vector<CR> crs;
	vector<SNAP> snaps;
	vector<CDH> cdhs;
	vector<CSG> csgs;

	while (!inputFile.eof()) 
	{
		string tempString = "";
		getline(inputFile, tempString);

		string construct = checkClass(tempString);

		if (construct == "**Error: ")
		{
			outputFile << construct << tempString << endl;
		}
		else outputFile << tempString << endl;
		
			// Read until EOF 
	
		if ("cr(" == tempString.substr(0, 3))
		{
			// cr('CS101','Turing Aud.').
			string course = tempString.substr(3, tempString.find(',') - 3);
			tempString = tempString.substr(tempString.find(',') + 1);
			string room = tempString.substr(0, tempString.find(')'));
			crs.push_back(CR(course, room));
		}
		else if ("snap(" == tempString.substr(0, 5))
		{
			string sStudentID = tempString.substr(5, tempString.find(',') - 5);
			studentIDSize = sStudentID.size(); //Need to store this, use it later in code
			int studentID = stoi(sStudentID);
			tempString = tempString.substr(tempString.find(',') + 1);
			string name = tempString.substr(0, tempString.find(','));
			tempString = tempString.substr(tempString.find(',') + 1);
			string address = tempString.substr(0, tempString.find(','));
			tempString = tempString.substr(tempString.find(',') + 1);
			string phone = tempString.substr(0, tempString.find(')'));
			snaps.push_back(SNAP(studentID, name, address, phone));
		}
		else if ("csg(" == tempString.substr(0, 4))
		{
			string course = tempString.substr(4, tempString.find(',') - 4);
			tempString = tempString.substr(tempString.find(',') + 1);
			string tempStudentID = tempString.substr(0, tempString.find(','));
			int studentID = stoi(tempStudentID);
			tempString = tempString.substr(tempString.find(',') + 1);
			string grade = tempString.substr(0, tempString.find(')'));
			csgs.push_back(CSG(course, studentID, grade));
		}
		else if ("cdh(" == tempString.substr(0, 4))
		{
			string course = tempString.substr(4, tempString.find(',') - 4);
			tempString = tempString.substr(tempString.find(',') + 1);
			string day = tempString.substr(0, tempString.find(','));
			tempString = tempString.substr(tempString.find(',') + 1);
			string hour = tempString.substr(0, tempString.find(')'));
			cdhs.push_back(CDH(course, day, hour));
		}
	}

	outputFile << endl << "Vectors:" << endl;
	
	for (int i = 0; i < snaps.size(); ++i)
	{
		outputFile << snaps.at(i) << endl;
	}
	for (int i = 0; i < csgs.size(); ++i)
	{
		outputFile << csgs.at(i) << endl;
	}
	for (int i = 0; i < cdhs.size(); ++i)
	{
		outputFile << cdhs.at(i) << endl;
	}
	for (int i = 0; i < crs.size(); ++i)
	{
		outputFile << crs.at(i) << endl;
	}

	outputFile << endl << "Course Grades:" << endl;

	for (int i = 0; i < crs.size(); ++i)
	{
		for (int x = 0; x < csgs.size(); ++x)
		{
			if (crs.at(i).getCourse() == csgs.at(x).getCourse())
			{
				string tempStudentName;
				//bool studentIDToName = false;
				for (int f = 0; f < snaps.size(); ++f)
				{
					if (csgs.at(x).getStudentID() == snaps.at(f).getStudentID())
					{
						tempStudentName = snaps.at(f).getName();
					}
					/*if (studentIDToName = true) 
					{ 
						tempStudentName = snaps.at(f).getName(); 
					}*/
				}
				
				
				outputFile << crs.at(i).getCourse()
					<< "," << tempStudentName << ","
					<< csgs.at(x).getGrade() << endl;
			}


		}

		outputFile << endl;


	}



	vector<string> allDays;
	//Calculate all days class is on, store in vector of strings
	for (int i = 0; i < crs.size(); ++i) //go through each class
	{
		string tempAllDays = "";
		for (int h = 0; h < cdhs.size(); ++h)
		{
			if (cdhs.at(h).getCourse() == crs.at(i).getCourse())
			{
				tempAllDays = tempAllDays.append(cdhs.at(h).getDay());
			}
		}
		allDays.push_back(tempAllDays);
	}



	outputFile << "Student Schedules:" << endl;

	for (int f = 0; f < snaps.size(); ++f)
	{
		outputFile << snaps.at(f).getName() << ", "
			<< setw(studentIDSize) << setfill('0') << snaps.at(f).getStudentID()
			<< ", "	<< snaps.at(f).getAddress() << ", "
			<< snaps.at(f).getPhone() << endl;

		for (int x = 0; x < csgs.size(); ++x) //go through each course for each student
		{
			if (csgs.at(x).getStudentID() == snaps.at(f).getStudentID()) //if student is in the class
			{
				
				string tempCourseAddress;	
				string allCourseDays;
				for (int i = 0; i < crs.size(); ++i)
				{
					if (csgs.at(x).getCourse() == crs.at(i).getCourse()) //store each course's address
					{
						tempCourseAddress = crs.at(i).getRoom();
						allCourseDays = allDays.at(i);
						break;
					}
					//store alldaystring into string
				}


				string tempHour;
				for (int h = 0; h < cdhs.size(); ++h)
				{
					if (cdhs.at(h).getCourse() == csgs.at(x).getCourse())
					{
						tempHour = cdhs.at(h).getHour();
						break;
					}
				}

				//output all the information


				outputFile << "  " << csgs.at(x).getCourse()
					<< " " << allCourseDays << " " << tempHour
					<< ", " << tempCourseAddress << endl;

			}

		}

		outputFile << endl;

	}



	inputFile.close();
	outputFile.close();
	return 0;
}