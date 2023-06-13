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
		cout << "open success" << endl;
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
		cout << "0 - Exit" << endl;

		cin >> user_opt;

		if (user_opt == 1) {
			cout << "Search for: ";

		}
		// Create table option
		else if (user_opt == 4) {
			string title;
			string table;
			string sql_query;
			int attr = 0;
			int usr_attr;
			// Inquires User how many attributes they want their table to have
			cout << "How many attributes does your table have?" << endl;
			cin >> usr_attr;
			cout << "What is the title of your table?" << endl;
			cin >> title;
			table = "CREATE TABLE " + title + "(";
			// Asks users to input attributes with corresponding inputs until attribute size is reached
			while (attr < usr_attr) {
				// temp and temp_d are temporary variables storing user inputs
				string temp;
				string temp_d;
				cout << "Enter an attribute: " << endl;
				// On first iteration clear the pending buffer from previous cins
				if (attr == 0) {
					cin.ignore();
				}
				getline(cin, temp);
				// starts building sql command starting with attribute name
				sql_query = temp;
				temp = "";
				cout << "Enter data type(INTEGER,TEXT): " << endl;
				getline(cin, temp);
				sql_query = sql_query + " " + temp;
				cout << "Primary Key?(Y/N): " << endl;
				getline(cin, temp_d);
				// asks if is primary key
				if (temp_d == "Y") {
					sql_query = sql_query + " PRIMARY KEY,";
				}
				else if (temp_d == "N") {
					cout << "NULL or NOT NULL? " << endl;
					getline(cin, temp);
					// checks if it is last attribute to terminate the table string with right bracket
					if (attr == usr_attr - 1) {
						sql_query = sql_query + " " + temp + "); ";
					}
					else {
						sql_query = sql_query + " " + temp + ", ";
					}
				}				
				attr++;
				// clear temp variables
				temp = "";
				temp_d = "";
				// add current sql attribute to table 
				table = table + sql_query;
			}
			// prints final table string
			cout << table << endl;
			exit = sqlite3_exec(DB, table.c_str(), NULL, 0, &messageError);	// calls callback since there could be multiple rows

			if (exit != SQLITE_OK)
			{
				std::cerr << "Error Create Table" << std::endl;
				sqlite3_free(messageError);
			}
			else {
				cout << "Table created Successfully" << std::endl;
			}
			/*
			for (int i = 0; i < attr_num; i++) {
				string temp_element;
				cout << "Enter the number " << i + 1 << "element" << endl;
				cin >> temp_element;
				attr[i] = temp_element;
			}
			*/

		}
		else if (user_opt == 5) {

		}
		else if (user_opt == 6) {

		}
		else {
			cout << "Invalid Choice!" << endl;
		}
	}
	/*
	/*Call command course queries the database for the list of class names and corresponding times

	string course = "SELECT Title, time FROM COURSES;";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following is the courses and the corresponding times: " << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for courses under the BSCO dept

	course = "SELECT Title FROM COURSES WHERE department = 'BSCO';";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following courses are taught in BSCO" << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for instructors' names that can teach the above courses (linking)

	course = "SELECT NAME, SURNAME FROM INSTRUCTOR WHERE DEPT = 'BSCO'; ";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following instructors can teach those courses: " << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for courses under the BSEE dept

	course = "SELECT Title FROM COURSES WHERE department = 'BSEE';";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following courses are taught in BSEE" << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}

	/*Call command course queries the database for instructors' names that can teach the above courses (linking)

	course = "SELECT NAME, SURNAME FROM INSTRUCTOR WHERE DEPT = 'BSEE'; ";
	cout << endl
		<< "SQL Command: " << course << endl;
	cout << "The following instructors can teach those courses: " << endl;
	exit = sqlite3_exec(DB, course.c_str(), callback, NULL, NULL);		// calls callback since there could be multiple rows
	if (exit != SQLITE_OK) {
		cout << "error";
	}
	*/

	sqlite3_close(DB);		// closes the database
	return 0;
}
