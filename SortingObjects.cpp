//Brendan Li

//include necessary libraries
#include <string>
#include <iostream>
#include <fstream> //Required for ifstream, ofstream
#include <stdexcept>
using namespace std;



//Person Class
class Person {
private: //declaring private variables
    string fullname; //last name followed by first
    string address;
    int age;
public:
    //no constructor necessary
    //this function reads Person attributes from text file
    void readPersonInfo(ifstream* pf){
        string tempS;//temp for conversions of data
        try {
            getline(*pf, fullname);//get name from first line
            getline(*pf, address);//get address from first line
            getline(*pf, tempS); age = stoi(tempS); //get age, convert string to a int
        }
        //failure message
        catch (ifstream::failure e) {
            cerr << "Error: File does not have enough data\n";//error message
            exit(1);
        }
        //no data message
        catch (invalid_argument e) { //if stoi or stof cannot convert tempS to a number
            cerr << "Error: File contains invalid data\n";//error message
            exit(1);
        }

    }
    //this function displays the attributes of a person
    //tabs are used for tabular format
    void printPersonInfo(){
        cout <<"\t"<< fullname<<"\t\t"<<address<<"\t\t"<<age<<"\t\t";
    }
    //this function returns the person object's age
    int personAGE(){return age;}
    //this function returns the person object's fullname
    string personName(){return fullname;}
};



//Student class; derived from Person class
class Student : public Person {
private://declaring private attributes of student class
    string ID;
    string major;
    float gpa;
public:
    //this function allows user to input Student attributes; invokes readPersonInfo function
    void readStudentInfo(ifstream* sf){
        Person::readPersonInfo(sf);//invoke printPersonInfo function
        //temp string for readings
        string tempS;
        try {
            getline(*sf, ID);//read ID, string
            getline(*sf, major);//read major
            getline(*sf, tempS); gpa = stof(tempS); //read GPA, convert string to a float
        }
        //failure message
        catch (ifstream::failure e) {
            cerr << "Error: File does not have enough data\n";//error message
            exit(1);
        }
        //no data message
        catch (invalid_argument e) { //if stoi or stof cannot convert tempS to a number
            cerr << "Error: File contains invalid data\n";//error message
            exit(1);
        }
        //cout<<"worked Student";
    }
    //this function prints the Student info
    void printStudentInfo(){
        Person::printPersonInfo();//invoke printPersonInfo function
        cout <<ID<<"\t"<<major<<"\t\t"<<gpa<<endl;//tabs are again used for tabular format
    }
    //this function returns the GPA of a student object
    float studentGPA(){return gpa;}
};



//The Course Class
class Course{
private://private attributs of Course class
    string ID;
    string title;
    int credits;
public:
    //Made a default constructor however it was not necessary for this assignment
    Course(){
        ID="";
        title="";
        credits=0;
    }
    //Constructor that took arguments for the Course objects attributes
    Course(string courseID, string courseTitle, int courseCredits){
        ID=courseID;//assigns given values to private attributes
        title=courseTitle;
        credits=courseCredits;
    }
    //This function just prints the course object's information
    void printCourseInfo(){
        cout << "Course ID: " << ID <<endl;//not tabular format
        cout << "Course Title: " << title <<endl;
        cout << "Course Credits: " << credits <<endl;
    }
};




//This is the CourseSection class; derived from Course class
class CourseSection : public Course {
private://private attributes of CourseSection class
    int sectionSize;//for sizes of dynamic rosters
    Student *roster; //dynamic array for class roster
    Student* *sortedNames;//double pointers to the roster array
    Student* *sortedAges;
    Student* *sortedGPAs;

    //this function sorts the pointers of sortedNames into alphabetical order
    void sortNames() {
        //temporary pointer for swap
        Student *temp;
        //double loops to sort, algorithm
        for (int j = 0; j < sectionSize - 1; j++) {
            for (int i = 0; i < sectionSize - 1 - j; i++) {
                if (sortedNames[i]->personName() > sortedNames[i + 1]->personName()) {//if names aren't in order, swap
                    temp = sortedNames[i];//set temp
                    sortedNames[i] = sortedNames[i + 1];//change first
                    sortedNames[i + 1] = temp;//change second to temp
                }
            }
        }
    }

    //this function sorts the pointers of sortedAges into numerical order of ages (least to greatest)
    void sortAges() {
        //temporary pointer for swap
        Student *temp;
        //double loops to sort, algorithm
        for (int j = 0; j < sectionSize - 1; j++) {
            for (int i = 0; i < sectionSize - 1 - j; i++) {
                if (sortedAges[i]->personAGE() > sortedAges[i + 1]->personAGE()) {//if ages aren't in order, swap
                    temp = sortedAges[i];//set temp, change values
                    sortedAges[i] = sortedAges[i + 1];
                    sortedAges[i + 1] = temp;
                }
            }
        }
    }

    //this function sorts the pointer of sortedGPAs into numerical order of GPAs (greatest to least)
    void sortGPAs(){
        //temporary pointer for swap
        Student *temp;
        //double loops to sort, algorithm
        for (int j = 0; j < sectionSize - 1; j++) {
            for (int i = 0; i < sectionSize - 1 - j; i++) {
                if (sortedGPAs[i]->studentGPA() < sortedGPAs[i + 1]->studentGPA()) {//if GPAs aren't in order, swap
                    temp = sortedGPAs[i];//set temp, change values
                    sortedGPAs[i] = sortedGPAs[i + 1];
                    sortedGPAs[i + 1] = temp;
                }
            }
        }
    }
public:
    //constructor that fills the course attributes along with allocating memory for roster/other pointer arrays
    CourseSection(string courseID, string courseTitle, int courseCredits, int size):Course(courseID, courseTitle, courseCredits){//call base class constructor
        sectionSize=size;
        roster = new Student[sectionSize];//dynamic allocation
        sortedNames = new Student*[sectionSize];//dynamic allocation
        sortedAges= new Student*[sectionSize];//dynamic allocation
        sortedGPAs = new Student*[sectionSize];//dynamic allocation
    }

    //Fills roster by calling readStudentInfo(), given ifstream
    void fillRosterInfo(ifstream *rf){
        //goes through all students
        for(int i=0; i<sectionSize; i++){
            Student place = Student();//create new students
            place.readStudentInfo(rf);//invoke readStudentInfo function
            roster[i]=place;//update roster
        }
        for (int j = 0; j < sectionSize; j++) { sortedNames[j] = &roster[j]; }//set elements
        for (int j = 0; j < sectionSize; j++) { sortedAges[j] = &roster[j]; }//set elements
        for (int j = 0; j < sectionSize; j++) { sortedGPAs[j] = &roster[j]; }//set elements
        //invoke sort functions to sort sortedNames,Ages,GPAs array
        sortNames();
        sortAges();
        sortGPAs();
    }

    //prints the information of section by alphabetical order
    void printSectionInfoByName(){
        Course::printCourseInfo();//invoke printCourseInfo function
        cout<<"Seq\tName\t\t\tAddress\t\t\tAge\t\tID\t\tMajor\t\tGPA\t"<<endl;//make table column headers
        cout<<"===\t====\t\t\t=======\t\t\t===\t\t==\t\t=====\t\t===\t"<<endl;//underline them
        //for loop to call printStudentInfo() function for all students in sortedNames
        for(int i=0; i<sectionSize; i++){
            cout<<(i+1);//sequence
            sortedNames[i]->printStudentInfo();//printStudentInfo function for each object
            cout<<endl;
        }
    }
    //prints the information of section in order of age
    void printSectionInfoByAge(){
        Course::printCourseInfo();//invoke printCourseInfo fnction
        cout<<"Seq\tName\t\t\tAddress\t\t\tAge\t\tID\t\tMajor\t\tGPA\t"<<endl;//make table column headers
        cout<<"===\t====\t\t\t=======\t\t\t===\t\t==\t\t=====\t\t===\t"<<endl;//underline them
        //for loop to call printStudentInfo() function for all students in sortedAges
        for(int i=0; i<sectionSize; i++){
            cout<<(i+1);//sequence
            sortedAges[i]->printStudentInfo();//printStudentInfo function for each object
            cout<<endl;
        }
    }
    //prints the information of section in order of GPA
    void printSectionInfoByGPA(){
        Course::printCourseInfo();//invoke printCourseInfo fnction
        cout<<"Seq\tName\t\t\tAddress\t\t\tAge\t\tID\t\tMajor\t\tGPA\t"<<endl;//make table column headers
        cout<<"===\t====\t\t\t=======\t\t\t===\t\t==\t\t=====\t\t===\t"<<endl;//underline them
        //for loop to call printStudentInfo() function for all students in sortedGPAs
        for(int i=0; i<sectionSize; i++){
            cout<<(i+1);//sequence
            sortedGPAs[i]->printStudentInfo();//printStudentInfo function for each object
            cout<<endl;
        }
    }
    //class destructor for dynamic memory
    ~CourseSection() {
        if (!roster) delete[] roster;//deletion required for all the dynamic arrays
        if (!sortedGPAs) delete[] sortedGPAs;//avoid memory issues/errors
        if (!sortedAges) delete[] sortedAges;
        if (!sortedNames) delete[] sortedNames; }

};



//Main function
int main(){
    int num,cr;
    string id,tl;

    ifstream inf;
    inf.open("/Users/Student/bli061/Algo/section01.txt");// replace with the exact location where your file is stored
    if (inf.fail()) {//to avoid terminating your program without displaying a message
        cerr << "Error:Could not open input file\n";
        exit(1);
    }
    //activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    cout<<"Course ID? "<<endl;
    cin>>id;
    cin.get();//remove the leftover "new line" character from cin
    cout<<"Course Title? "<<endl;
    getline(cin,tl);
    cout<<"Course Credits? "<<endl;
    cin>>cr;
    cin.get();//remove the leftover "new line" character from cin
    cout<<"How many students in the course section? "<<endl;
    cin>>num;
    cin.get();//remove the leftover "new line" character from cin
    CourseSection sec(id, tl, cr, num);//define sec for CourseSection
    sec.fillRosterInfo(&inf);//ifstream cannot be passed by value
    inf.close();

    cout<<"Section info (course and students info) sorted by students' names:\n";
    sec.printSectionInfoByName();

    cout<<"\nSection info (course and students info) sorted by students' ages:\n";
    sec.printSectionInfoByAge();

    cout<<"\nSection info (course and students info) sorted by students' GPAs:\n";
    sec.printSectionInfoByGPA();

    return 0;
}