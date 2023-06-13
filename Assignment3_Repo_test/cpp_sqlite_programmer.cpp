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

	// Start of functions menu
	while (user_opt != 0) {
		cout << endl << "1 - Search" << endl;
		cout << "2 - Insert" << endl;
		cout << "3 - Print" << endl;
		cout << "4 - Create Table" << endl;
		cout << "5 - Update" << endl;
		cout << "6 - Remove" << endl;
		cout << "0 - Exit" << endl;

		cin >> user_opt;
		int search_opt;

		// Search table option
		if (user_opt == 1) {
			cout << "1 - Search course" << endl;
			cout << "2 - Search instructor" << endl;
			cout << "3 - Search student" << endl;
			cin >> search_opt;

			if (search_opt == 1) {
				string course_name;
				cin >> course_name;
				string search_course = ("SELECT * FROM COURSES WHERE Title = '" + course_name + "';");
				cout << search_course << endl;
				exit = sqlite3_exec(DB, search_course.c_str(), callback, NULL, NULL);

			}
			else if (search_opt == 2) {
				string prof_name;
				cin >> prof_name;
				string search_prof = ("SELECT * FROM INSTRUCTOR WHERE NAME = '" + prof_name + "';");
				exit = sqlite3_exec(DB, search_prof.c_str(), callback, NULL, NULL);
			}
			else if (search_opt == 3) {
				string student_name;
				cin >> student_name;
				string search_student = "SELECT * FROM STUDENT WHERE NAME = '" + student_name + "';";
				exit = sqlite3_exec(DB, search_student.c_str(), callback, NULL, NULL);
			}
			else cout << "Invalid Input" << endl;
			/*
			if (exit != SQLITE_OK) {
				cout << "Search Error" << endl;
			}
			else cout << "Search Success" << endl; */
		}

		// Insert element option
		else if (user_opt == 2) {
			int insert_opt;
			cout << "1 - Insert course\n2 - Insert student\n3 - Insert instructor\n4 - Insert admin" << endl;
			cout << "Enter your option: ";
			cin >> insert_opt;

			if (insert_opt == 1) {
				string CRN, time, year, credit;
				string course_name, dept, day, semester;
				cin.ignore();
				cout << "Enter CRN, course name, department, time, day, semester, year and credit" << endl;
				cin >> CRN >> course_name >> dept >> time >> day >> semester >> year >> credit;

				string courseInsert = ("INSERT INTO COURSES VALUES(" + CRN + ",'" + course_name + "','" + dept + "'," + time + ",'" + day + "'," + semester + "," + year + "," + credit + ");");
				//cout << courseInsert << endl;
				sqlite3_exec(DB, courseInsert.c_str(), callback, NULL, NULL);
			}
			else if (insert_opt == 2) {
				string id, name, surname, grad_year, major, email;
				cin.ignore();
				cout << "Enter ID, Name, Surname, Grad Year, Major and email of the student seperate by spaces: " << endl;
				cin >> id >> name >> surname >> grad_year >> major >> email;

				string studentInsert = ("INSERT INTO STUDENT VALUES(" + id + ", '" + name + "', '" + surname + "', " + grad_year + ",'" + major + "', '" + email + "'); ");
				cout << studentInsert << endl;
				sqlite3_exec(DB, studentInsert.c_str(), callback, NULL, NULL);
			}
			else if (insert_opt == 3) {
				string id, prof_name, surname, title, hire_year, dept, email;
				cout << "Enter ID, Name, Surname, Hire Year, Department and Email of the Instructor seperated by spaces:" << endl;
				cin >> id >> prof_name >> surname >> hire_year >> dept >> email;
				cout << "Enter your Title: " << endl;
				cin.ignore();
				getline(cin, title);
				string profInsert = ("INSERT INTO INSTRUCTOR VALUES(" + id + ", '" + prof_name + "', '" + surname + "', '" + title + "', " + hire_year + ", '" + dept + "', '" + email + "');");
				cout << profInsert << endl;
				sqlite3_exec(DB, profInsert.c_str(), callback, NULL, NULL);
			}
			else if (insert_opt == 4) {
				string id, name, surname, title, office, email;
				cin.ignore();
				cout << "Enter ID, Name, Surname, Title, Office, and Email of the admin by spaces:" << endl;
				cin >> id >> name >> surname >> title >> office >> email;

				string adminInsert = ("INSERT INTO ADMIN VALUES(" + id + ", '" + name + "', '" + surname + "', '" + title + "', '" + office + "', '" + email + "');");
				cout << adminInsert << endl;
				sqlite3_exec(DB, adminInsert.c_str(), callback, NULL, NULL);
			}
			else cout << "Invalid Input" << endl;

		}

		// Print table option
		else if (user_opt == 3) {
			int print_opt;
			cout << "1 - Print Course Table\n2 - Print Student Table\n3 - Print Instructor Table\n4 - Print Admin Table\n5 - Print All" << endl;
			cout << "Enter your option: ";
			cin >> print_opt;
			if (print_opt == 1) {
				string print_course = "SELECT * FROM COURSES;";
				//cout << print_all << endl;
				sqlite3_exec(DB, print_course.c_str(), callback, NULL, NULL);
			}
			else if (print_opt == 2) {
				string print_student = "SELECT * FROM STUDENT;";
				sqlite3_exec(DB, print_student.c_str(), callback, NULL, NULL);
			}
			else if (print_opt == 3) {
				string print_prof = "SELECT * FROM INSTRUCTOR;";
				sqlite3_exec(DB, print_prof.c_str(), callback, NULL, NULL);
			}
			else if (print_opt == 4) {
				string print_admin = "SELECT * FROM ADMIN;";
				sqlite3_exec(DB, print_admin.c_str(), callback, NULL, NULL);
			}
			else if (print_opt == 5) {
				string print_all = "SELECT * FROM COURSES; SELECT * FROM STUDENT;  SELECT * FROM INSTRUCTOR; SELECT * FROM ADMIN;";
				sqlite3_exec(DB, print_all.c_str(), callback, NULL, NULL);
				//cout << print_all << endl;
			}
			else cout << "Invalid Input" << endl;
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

		// Update attribute option
		else if (user_opt == 5) {
			string sql_query, temp, usr_tbl, usr_attr, usr_id, usr_update; // inputs from user
			cin.ignore();	// clears pending cin buffer
			cout << "Which table would you like to update?" << endl;
			getline(cin, usr_tbl);
			sql_query = "UPDATE " + usr_tbl;
			cout << "What is the element you would like to change?" << endl;
			getline(cin, usr_attr);
			cout << "What do you want to change it to?" << endl;
			getline(cin, usr_update);
			cout << "Is the element a TEXT or INTEGER?" << endl;
			getline(cin, temp);
			// if text use single quotes else don't
			if (temp == "INTEGER") {
				sql_query = sql_query + " SET " + usr_attr + " = " + usr_update;
			}
			else if (temp == "TEXT") {
				sql_query = sql_query + " SET " + usr_attr + " = " + "'" + usr_update + "'";
			}
			cout << "What is the CRN/ID of the object you would like to change?" << endl;
			getline(cin, usr_id);
			// checks if table is courses since it is the only table without ID as primary key
			if (usr_tbl == "COURSES") {
				sql_query = sql_query + " WHERE CRN = " + usr_id + ";";
			}
			else {
				sql_query = sql_query + " WHERE ID = " + usr_id + ";";
			}
			// prints final sql_query string
			cout << sql_query << endl;
			exit = sqlite3_exec(DB, sql_query.c_str(), NULL, 0, &messageError);	// calls callback since there could be multiple rows

			if (exit != SQLITE_OK)
			{
				std::cerr << "Error" << std::endl;
				sqlite3_free(messageError);
			}
			else {
				cout << "Success" << std::endl;
			}
		}
		// Delete object option
		else if (user_opt == 6) {
			string usr_tbl, usr_id;	// user inputs
			string sql_query; // final sql_query
			cin.ignore();	// clears pending cin buffer
			cout << "Which table would you like to delete from?" << endl;
			getline(cin, usr_tbl);
			sql_query = "DELETE FROM " + usr_tbl;
			cout << "What is the ID/CRN of the object you want to delete" << endl;
			getline(cin, usr_id);
			if (usr_tbl == "COURSES") {
				sql_query = sql_query + " WHERE CRN = " + usr_id + ";";
			}
			else {
				sql_query = sql_query + " WHERE ID = " + usr_id + ";";
			}
			cout << sql_query << endl;
			exit = sqlite3_exec(DB, sql_query.c_str(), NULL, 0, &messageError);	// calls callback since there could be multiple rows

			if (exit != SQLITE_OK)
			{
				std::cerr << "Error" << std::endl;
				sqlite3_free(messageError);
			}
			else {
				cout << "Success" << std::endl;
			}
		}
		else if (user_opt == 0) {
			cout << "Exit success!" << endl;
			break;
		}
		else {
			cout << "Invalid Choice!" << endl;
		}
	}

	/* 
	Linking courses to instructor
	Will add this as an option in final integration
	Separate test for now 
	*/

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


