#include <iostream>
#include <sqlite3.h>
#include <string>
#include <stdio.h>

using namespace std;

/*************************************************************************************************
 The callback() function is invoked for each result row coming out of the evaluated SQL statement
 1st argument - the 4th argument provided by sqlite3_exec() and is typically not used
 2nd argument - number of columns in the result
 3rd argument - an array of strings containing the fields in that row
 4th argument - an array of strings containing the names of the columns
*************************************************************************************************/
static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

int main(int argc, char** argv)
{
	sqlite3* DB;

	int exit = 0;

	exit = sqlite3_open("assignment3.db", &DB); // open the database
	if (exit != SQLITE_OK) {
		cout << "error";
	}
	else {
		cout << "open success";
	}
	char* messageError;
	string query;
	
	int user_opt = 10;

	while (user_opt != 0) {
		cout << "1 - Search" << endl;
		cout << "2 - Insert" << endl;
		cout << "3 - Print All" << endl;
		cout << "4 - Create Table" << endl;
		cout << "5 - Update" << endl;
		cout << "6 - Remove" << endl;

		if (user_opt == 1) {
			cout << "Search for: ";

		}
	}
	/*Call command course queries the database for the list of class names and corresponding times*/

	string course = "SELECT Title, time FROM COURSES;";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following is the courses and the corresponding times: " << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for courses under the BSCO dept*/

	course = "SELECT Title FROM COURSES WHERE department = 'BSCO';";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following courses are taught in BSCO" << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for instructors' names that can teach the above courses (linking)*/

	course = "SELECT NAME, SURNAME FROM INSTRUCTOR WHERE DEPT = 'BSCO'; ";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following instructors can teach those courses: " << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for courses under the BSEE dept*/

	course = "SELECT Title FROM COURSES WHERE department = 'BSEE';";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following courses are taught in BSEE" << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for instructors' names that can teach the above courses (linking)*/

	course = "SELECT NAME, SURNAME FROM INSTRUCTOR WHERE DEPT = 'BSEE'; ";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following instructors can teach those courses: " << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}
	

	sqlite3_close(DB);		// closes the database
	return 0;
}
