
#include <iostream>
#include<cstring>
#include<vector>
#include<fstream>
#include<string.h>
#include<cstring>
#include<filesystem>
#include <cstdio>
#include <cstdlib>



using namespace std;

void clrscr(){
	cout << "\x1B[2J\x1B[H"; //clears screen
}

void pause(int cond) //just a function for pausing 
{
	cout<<endl; 
	if (cond == 1){cout<<"NO SUCH FILE"<<endl;}
	if (cond == 2) {cout<<"Enter valid A-F letter grade."<<endl;}
	if (cond == 3) {cout<<"Enter valid O/G/S/F letter grade."<<endl;}
	if (cond == 4) {cout<<"Enter only a numerical value."<<endl;}
	if (cond == 5) {cout<<"Enter a valid Y/N value"<<endl;}
	cout<<"Press ENTER To Continue.";
	cin.ignore();
	cin.ignore();
	clrscr();
}


//-----------TABULATES GRADE INTO O/G/S format----------------
string tabulate(int final){
	
	string final1;
	if (final >= 85) {final1 = "Outstanding";} //PUTS FINAL GRADE INTO O/G/S FORMAT
	if (final <= 84.99 && final >= 75) {final1 = "Good";}
	if (final <= 74.9 && final >= 60) {final1 = "Satisfactory";}
	if (final <= 59.9) {final1 = "Unsatisfactory";}
	
   return final1;
}

//----------------THIS FUNCTION IS FOR DISPLAYING A SHEET----------------

void disp_sheet(vector<string> pickle){
	string data;
	int c = 0; //A counter to label rows
	int len = pickle.size();
	
	int c1 = 0;
	
	for (int i = 0; i < len; i++){ //packs pickle into data string
		data += pickle[i];
		
	}
	
	int len1 = data.size();
	
	for (int i = 0; i < len1; i++){ //FORMATTING
		
		//----------TOP ROW ONLY------------
		if (i == 0 && c == 0 && data[i] != ',') {cout<<"      "<<data[i];} //indents first line and first line only/ 8 SPACES
		if (c == 0 && data[i] == ',') {cout<<"|";} //To make table more readable. Single bars for top row
		if (c == 0 && data[i] == '\n') {c++;}
		if (c == 0 && i > 0 && data[i] != ',') {cout<<data[i];}
		
		if (c == 1) {cout<<endl; for (int c1 = 0; c1 < 25; c1++){cout<<"-";}} //adds horizontal bar of letters
		
		//		---------ALL SUBSEQUENT ROWS------------
		
		if (c > 0 && data[i] == ',' && c1 == 0) {cout<<"||";}
		if (c > 0 && data[i] != ',') {cout<<data[i];}
		
		
		if (data[i] == '\n' && c != 0) {c++; cout<<c-1<<"| ";}//if a new line is encountered, c will increment and label it..
		
		//-----------THIS LINE GIVES THE STUDENT NAME ITS OWN LINE---------------
		if (data[i] == '\n' && c != 0) {c1 = 1;}
		if (c1 == 1 && data[i] == ',') {cout<<endl; cout<<"      "; c1 = 0;} 
		
	} 
}


//---------------FUNCTION THAT TRANSFORMS GRADES INTO NUMERICAL VALUE-----------------
#include<algorithm>
int getgrade(string a, string b) //THIS FUNCTION COMPUTES THE GRADES
{
	
	int len = a.size();
	int len1 = b.size();
	char a1, b1;
	
	//CONVERTS TO UPPER CASE
		a1 = a[0];
		a1 = toupper(a1);
		a[0] = a1;
		
	 //CONVERTS TO UPPER CASE
		b1 = b[0];
		b1 = toupper(b1);
		b[0] = b1;

	
	float result = 0; //ASSIGNMENT RESULT
	float result1 = 0; //DISCUSSION RESULT
	float final = 0; //FINAL SCORE RESULT + RESULT / NUMBER OF ASSIGNMENTS
	
	//for (int i = 0; i < sizeof(a,b); i++) {
	if (a == "A") {result = 100;}
	if (a == "A-") {result = 85;}
	
	if (a == "B+") {result = 84.9;}
	if (a == "B") {result = 80;}
	if (a == "B-") {result = 75;}
	
	if (a == "C+") {result = 74.9;}
	if (a == "C") {result = 70;}
	if (a == "C-") {result = 65;}
	
	if (a == "D+") {result = 64.9;}
	if (a == "D") {result = 52;}
	if (a == "D-") {result = 60;}
	
	if (a == "F") {result = 0;}
	if (a == "-") {result = '-';}
	
	if (b == "O") {result1 = 100;}
	if (b == "G") {result1 = 70;}
	if (b == "S") {result1 = 50;}
	final = result + result1;
	return final;
}


//------------GETS USER INPUT FOR GRADES--------------
vector<string> fetch_grade(vector<string> pickle, int students, int weeks){
	
			
	//vector<string> pickle; //define a vector to store all grades
	char q[2],d[2];//student discussion and question grades
	float final;
	string final1;
	string name;
			
	//------TWO ARRAYS OF VALID VALUES-------------
	string valid_input[25] = {"A","A-","B+","B","B-","C+","C","C-","D+","D","D-","a","a-","b+","b","b-","c+","c","c-","d+","d","d-","F","f","-"};
	string valid_input1[9] = {"O","G","S","o","g","s","F","f","-"};	
	int cond = 0;
	
	//---------GRADING BLOCK----------
		
	for (int s = 0; s != students; s++){ //this loop covers the students
		final = 0; //reset final grade for each student
		final1.clear(); //clear string for next round
		
		cout << "\x1B[2J\x1B[H"; //clears screen
		
		cout<<"Student "<<s+1<<" Name: "<<endl;
		cin>>name; 
		
		pickle.push_back(name); //ADDS NAME AND COMMA TO PICKLE
		pickle.push_back(",");
		
		
	//THIS LOOP COVERS THE AMOUNT OF WEEKS IN COURSE
	for (int w = 1; w <= weeks; w++){ //this loop covers the assignments
		clrscr();
		
		/*The next two WHILE loops are for ensuring user input is valid*/
		
		while (cond == 0){
			cout << "\x1B[2J\x1B[H"; //clears screen
			cout<<"Grade for Week "<<w<<" STUDY question. '-' for N/A."<<endl;
			cout<<"Student: "<<name<<endl; 
			cin>>q;
			
			
			   //DOES INPUT AGREE WITH VALID INPUTS?
				for (int i = 0; i < 25; i++){
					if (q == valid_input[i]) {cond = 1; break;}
					else if (i == 24 && cond == 0) {pause(2);} 
					
				}}
			
			cond = 0; //Reset COND for next loop.
			
		while (cond != 1){
			cout << "\x1B[2J\x1B[H"; //clears screen
			cout<<"Grade for Week "<<w<< " DISCUSSION. '-' for N/A."<<endl;
			cout<<"Student: "<<name<<endl;
			cin>>d;
				
				//DOES INPUT AGREE WITH VALID INPUTS?
			    for (int i = 0; i < 9; i++){
					if (d == valid_input1[i]) {cond = 1; break;}
					if (i == 8 && cond == 0) {pause(3);}
					
				}}
			
		cond = 0; //Reset COND for next time around.	
			
			final += getgrade(q,d); //gets the numerical grade for each student
			pickle.push_back(q); //adds inputs to pickle, plus comma.
			pickle.push_back(",");
			pickle.push_back(d);
			pickle.push_back(",");
			
		}
			
		final /= (weeks * 2); //The final grade is a result of the grade divided by weeks.
		final1 = tabulate(final); //finally, get grade in official format
		
		
		//------------ADDS FINISHING TOUCHES TO PICKLE-----------
		pickle.push_back(final1);
		pickle.push_back("/");
		pickle.push_back(to_string(final));
		pickle.push_back("\n"); //new line will not be added if end of students.
		if (s == students-1) {pickle.pop_back();}
	}
		return pickle;

}

#include<string.h>
#include<stdio.h>
//----------------FILE HANDLING FUNCTION------------------
FILE* open_file(string fname, char cond){ //this function gets a file and returns data
	//----------THIS BLOCK IS FOR FILE HANDLING--------------
	clrscr();
	
	FILE *f;
	//char fname1[fname.size()+5];
	
	fname += ".csv";
	
	if (cond == 'r'){f = fopen(fname.c_str(),"r");} //opens in read mode
	if (cond == 'w'){f = fopen(fname.c_str(),"w");} //opens in write mode
	
	
	
	return f;
fclose(f);
}


using namespace std;


//------------DUMPS VECTOR INTO FILE---------------
void can_file(string data, string fname){
	
	//----------THIS BLOCK IS FOR FILE HANDLING--------------
	
	
	ofstream f;
	f.open(fname+".csv");
    f<<data;
	f.close();
	
	cout<<"FILE SAVED AS <<"<<fname<<".csv"<<endl; 
	pause(0);
}



//----------------CREATES NEW SHEET------------------
using namespace std;
void new_sheet(){
  int weeks; //amount of grades
  string name; //student name
  char grade[3]; //student grade
  float final; //computes final grade
  string final1; //for pickling
  int students; //total students
  vector<string> pickle; //define a vector to store all grades
  //vector<string> pickle1;
  string headline;
  char choice;	
  string data;
  int cond;
  string fname;
	
	
	clrscr();
	cout<<"Name of file. (Extension .CSV will be automatically applied.)"<<endl;
	cin>>fname;
	
	clrscr();
		cout<<"How many TOTAL WEEKS?: "<<endl;
		cin>>weeks;
		
	//-------CREATES HEADLINE-----------	
	for (int i = 1; i <= weeks; i++){ //populates the titles of the table, based on WEEKS		
		pickle.push_back("Q");
		pickle.push_back(to_string(i)); //MUST BE CONVERTED TO STRING
		pickle.push_back(",");
		
		pickle.push_back("D");
		pickle.push_back(to_string(i)); //MUST BE CONVERTED TO STRING
		pickle.push_back(",");
	}
	
	pickle.push_back("FINAL");
	pickle.push_back("\n");
	//-------------END OF HEADLINE---------------
	
		cout << "\x1B[2J\x1B[H"; //clears screen
	    cout<<"Total Students: "<<endl;
	    cin>>students;
	
	
		
	//--------------END OF GET GRADE BLOCK-----------
	
	pickle = fetch_grade(pickle,students, weeks); //sends weeks and students to grade tabulator
	
			
	//------------THIS BLOCK PRINTS OUT DATA IN A TABLE FORMAT------------------
	disp_sheet(pickle);
	
	
	//--------------THIS BLOCK TAKES USER CHOICE IF RESULTS ARE GOOD OR NOT------------------
	 cond = 0;
	while (cond != 1){
		cout<<endl;
		
		cout<<"Are you satisfied with these results? [Y/N]"<<endl;
		cin>>choice;
		choice = toupper(choice);
		if (choice == 'Y' || choice == 'N'){cond = 1;} //LOOP TERMINATES ONLY WHEN VALID CHOICE MADE
	}
	
	
	/*----------PACKS PICKLE INTO DATA STRING---------------
	-----------SENDS TO BE CANNED IF SATISFIED-------------*/
	int len = pickle.size();
	if (choice == 'Y') {for (int i = 0; i < len; i++){data += pickle[i];}}

	if (choice == 'Y') {can_file(data,fname);} //can_file dumps to file
	if (choice == 'N') {new_sheet();} //if unsatisfactory, goes to edit_sheet
	
}

void edit_sheet(vector<string> pickle, string fname){ 
	
    char choice;
	int n = 0;
	//vector<string> data;
	string data;
	string data1;
	int c = 0;
	int len = 0;
	int cond = 0;
	int weeks = 0;
	int lines = 0; 
	
	//----------------GET LINES IN VECTOR----------------
	
	for (int i= 0; i < pickle.size();i++){ //gets length.
	
	    if (pickle[i] == "\n"){lines++;}  //if a new line is encountered, lines increments.
	
	}
	//----------------END OF GETTING LINES----------------

	
	do{
        clrscr();		
	    disp_sheet(pickle);
		
		cout<<"Enter line to edit: 'Q' to Quit. 'A' to add student."<<endl; 
		cout<<"Choose between 1-"<<lines-1<<endl;
		cin>>choice;
		
		//this line will not allow a non-int value. or a value exceeding the lines in data.
		if (isdigit(choice) == true && ((int)choice-48) <= lines-1 && (int)choice-48 != 0){cond = 1; break;} //once an integer value is entered, loop breaks.
	}while (toupper(choice) != 'Q' && toupper(choice) != 'A');
	
	if (toupper(choice) == 'A') {cond = 2;} //sends to Add student block
	
	//-------------GET THE AMOUNT OF WEEKS TO PASS TO EDITING--------------
	for (int i = 0; pickle[i] != "\n"; i++){
		data1 += pickle[i];
	}
	
	for (int i = 0; i < data1.size(); i++){
		if (data1[i] == ',') {weeks++;}
	}
	weeks = (weeks /= 2);
	n = (int)choice-47; //converts choice to integer, minus ascii numbers.
		
	//----------------END OF GETTING WEEKS---------------
	 
	switch(cond) {
		
		case 1: ;
			
			pickle.erase(pickle.begin() + n); //DELETE ELEMENT TO BE EDITED
			pickle = fetch_grade(pickle,1, weeks); //sends weeks and students to grade tabulator, ONLY 1 student value.
			cond = 3;
			
		case 2: ;
			pickle = fetch_grade(pickle,1,weeks);
			cond = 3;
	
		
		disp_sheet(pickle);

		case 3: ; //this block only executes if and only if one of the previous two blocks has been executed.
	
	      cond = 0; //reset condition variable
	
	       while (cond != 1){
		     cout<<endl;
		
		     cout<<"Are you satisfied with these results? [Y/N]"<<endl;
		      cin>>choice;
		      choice = toupper(choice);
		      if (choice == 'Y' || choice == 'N'){cond = 1;} //LOOP TERMINATES ONLY WHEN VALID CHOICE MADE
	}
	
	}
	
	
	/*----------PACKS PICKLE INTO DATA STRING---------------
	-----------SENDS TO BE CANNED IF SATISFIED-------------*/
    len = pickle.size();
	if (choice == 'Y') {for (int i = 0; i < len; i++){data += pickle[i];}}
	if (choice == 'Y') {can_file(data,fname);} //can_file dumps to file
	if (choice == 'N') {edit_sheet(pickle, fname);} //if unsatisfactory, goes to edit_sheet
	

}

//----------------------DISPLAYS AN EXISTING SHEET---------------------
#include<filesystem>
void view_sheet(){
	clrscr();
	
	string fname;
	
	vector<string> pickle; //define a vector to store all grades
	FILE *f;
	string c;
	string data;
	char choice;
	
	//-----------GETS FILENAME TO OPEN, FROM USER-----------------
	cout<<"Enter file name. *.csv will be added."<<endl;
	do{
		cin>>fname;
	}while (fname == "");
	
    
	
	f = open_file(fname,'r');
	
	if (f == NULL) {pause(1);} //WARNS USER IF FILE DOES NOT EXIST
	if (f == NULL) {view_sheet();}
	
	//----------------PUTS FILE INTO PICKLE------------>>>--
	while (!feof(f)){ //displays file until end of file
	
        c = fgetc(f);
		pickle.push_back(c);
	} 
	
	disp_sheet(pickle); 
	
	cout<<endl;
	
	do{
		cout<<"Would you like to edit this sheet? [Y/N]"<<endl;
		cin>>choice;
		choice = toupper(choice);
		if (choice == 'Y' || choice == 'N') {break;}

		if (choice != 'Y' || choice != 'N') {pause(5);}
			}while (choice != 'Y' || choice != 'N');
	
	clrscr();
	if (choice == 'Y') {edit_sheet(pickle, fname);} //PASSES PICKLE TO EDITING FUNCTION
	

}

//-----------------HELP FUNCTION----------------
void helper(){
	
	clrscr();
	
	cout<<"Student Grader, by Colin Burgess"<<endl;
	cout<<"Please report errors/suggestions to ColinBurgess890@gmail.com"<<endl;
	pause(0);
	cout<<"STEP 1: MENU OPTIONS."<<endl;
	cout<<"'New grade sheet' creates a new data sheet."<<endl;
	cout<<"'View/Edit Sheet' allows for viewing and editing an existing sheet."<<endl;
	pause(0);
	clrscr();
	cout<<"Enter the name of your file. Extension '.CSV' will be applied automatically."<<endl;
	cout<<"Enter the amount of weeks in your course."<<endl;
	cout<<"Then, enter the name for each student and their individual grades."<<endl;
	pause(0);
	clrscr();
	cout<<"ACCEPTED GRADES FOR ASSIGNMENTS"<<endl;
	cout<<"A+,A-,A,B+,B-,B,,C+,C-,C,D+,D-,D,F."<<endl;
	cout<<"'-' for when an assignment is not applicable or not handed in."<<endl;
	cout<<"ACCEPTED GRADES FOR DISCUSSION:"<<endl;
	cout<<"O,G,S (Outstanding, Good, Satisfactory."<<endl;
	cout<<"'-' for when an assignment is not applicable or not handed in."<<endl;
	cout<<"These two grades will be calculated together for a final outcome."<<endl;
	pause(0);
	clrscr();
	cout<<"Once you are satisfied with the results, select [Y] to continue, or [N] to try again."<<endl;
	pause(0);
	clrscr();
	cout<<"EDITING SHEET:"<<endl;
	cout<<"Enter name of file to be edited/viewed."<<endl;
	cout<<"If you are not satisfied with the file, select [N] to edit. "<<endl;
	cout<<"To add a new student, select [A]"<<endl;
	cout<<"Select line to modify"<<endl;
	cout<<"Enter the new values for the line to be edited."<<endl;
	cout<<"Weeks in the class will be assumed based on length of existing file being edited."<<endl;
	pause(0);
	
}

//-----------MAIN PROGRAM------------
void intro(){
	
	char choice; //choice variable
	
	do{ //this loop is the main loop
		//SetConsoleTextAttribute(hConsole, k);
        cout << "\x1B[2J\x1B[H"; //clears screen
		cout<<"GRADE COMPILER"<<endl;
		cout<<"1: New Grade sheet"<<endl;
		cout<<"2: View/Edit Grade sheet"<<endl;
		cout<<"3: Help"<<endl;
		cout<<"4: Quit"<<endl;
		
		cin>>choice;
		
		choice = toupper(choice); //eliminate case sensitivity
		
		if (choice == '1') {new_sheet();}
		if (choice == '2') {view_sheet();}
		if (choice == '3') {helper();}
		if (choice == '4') {}
		
	}while (choice != '4');
	
	
}


using namespace std;
int main() {
	intro();		
	return 0;
}
