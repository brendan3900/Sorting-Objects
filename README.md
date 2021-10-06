# Sorting-Objects-Cplusplus
Creating classes, class inheritance, reading data from external text files, sorting lists of pointers, dynamic memory allocation, displaying data in tabular format.

section01.txt is the text file being read by the program.

Summary of Approach


///////Class Person
•	To begin this class, the private variables were declared, including two strings and an int (fullname, address, and age).
•	Next, all the public functions were created. A class constructor was unnecessary because C++ automatically generates a default constructor when no other constructors are created. 
•	The first function created was a void function called readPersonInfo which takes an ifstream* as the only argument; this function reads the person’s three private attributes from the text file through the file stream pointer pf.
•	The second function was a void function called printPersonInfo; this displays the private attributes of a Person object. 
•	The third function was a function called personAGE; this returns the age of a Person object. 
•	The final function was a function called personName; this returns the fullname of a Person object. A deconstructor was not necessary for this class because there was no dynamic memory allocation.

//////Class Student
•	Next, the Student class was created, which is a derived class of the base class Person. Three private variables were declared, including two strings and a float (ID, major, and gpa).
•	Then the public functions were created. Again, a class constructor was unnecessary because of the default constructor which was automatically created. 
•	The first function created was a void function called readStudentInfo which takes an ifstream* as the only argument; this function calls the function readPersonInfo from the base class and then reads the student’s three private attributes from the text file through the file stream pointer sf. 
•	The second function was a void function called printStudentInfo; this function invokes the function printPersonInfo from the base class and then prints the Student class’s private attributes. 
•	The final function was a function called studentGPA; this function returned a Student object’s GPA attribute. A deconstructor was not necessary for this class because there was no dynamic memory allocation.

//////Class Course
•	Next, the Course class was created. At the beginning of this class, three private variables were declared, including two strings and an int (ID, title, and credits). 
•	Then all the public functions were created. First, a class constructor was made that is used to fill the data of the class’s three private attributes. 
•	Finally, a void function called printCourseInfo was created; this function displays the three private attributes of the class.

//////Class CourseSection
•	Lastly, the CourseSection class was made; this is a derived class of the Course class. To begin, 5 private variables were declared, including an int, a Student object pointer, and three Student object double pointers (sectionSize, *roster, **sortedNames, **sortedAges, **sortedGPAs). 
•	Moreover, three private functions were created, including sortNames, sortAges, and sortGPAs. The sortNames function sorts the pointers in sortedNames to access the students’ records in an alphabetical order of their name. The sortAges function sorts the pointers in sortedAges to access the students’ records in an ascending order of their age. The sortGPAs function sorts the pointers in sortedGPAs to access the students’ records in a descending order of their GPA.
•	Next, all the public functions were created. First, a class constructor was made; this constructor takes (as arguments) the three attributes of the Course that the section belongs to along with the section size. This constructor invokes the base class’s constructor with the three Course attributes and then dynamically creates the roster, sortedNames, sortedAges, and sortedGPAs using the sectionSize attribute. 
•	A void function called fillRosterInfo was created; this function reads the info of all the students in the section from the text file through its file stream pointer rf by invoking the readStudentInfo inside of a for loop. Then it inserts each Student object into the roster list. This function also fills sortedNames, sortedAges, and sortedGPAs, with pointers to the students’ objects that were inserted in the roster using for loops. Finally, this invokes the functions sortNames, sortAges, and sortGPAs.
•	A void function called printSectionInfoByName was created; this function prints the section’s information, including course information and the information of each student in alphabetical order by name. The information of each student was printed, in a tabular format, by invoking the printStudentInfo inside of a for loop for the pointers in the sortedNames array.
•	A void function called printSectionInfoByAge was created; this function prints the section’s information, including course information and the information of each student in ascending order of age. The information of each student was printed, in a tabular format, by invoking the printStudentInfo inside of a for loop for the pointers in the sortedAges array.
•	A void function called printSectionInfoByGPA was created; this function prints the section’s information, including course information and the information of each student in descending order of GPA. The information of each student was printed, in a tabular format, by invoking the printStudentInfo inside of a for loop for the pointers in the sortedGPAs array.
•	Lastly, a destructor was created to delete the dynamically allocated memory (roster, sortedNames, sortedAges, sortedGPAs).
