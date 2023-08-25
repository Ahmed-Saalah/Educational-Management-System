#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Assignment; // Forward declaration

class Person {
protected:
    string name;
    int id;
    int age;

public:
    Person(const string &_name, int _id, int _age) : name(_name), id(_id), age(_age) {}

    // Getter and setter methods
    void setName(const string &_name) {
        name = _name;
    }

    string getName() const {
        return name;
    }

    void setID(int _id) {
        id = _id;
    }

    int getID() const {
        return id;
    }

    void setAge(int _age) {
        age = _age;
    }

    int getAge() const {
        return age;
    }

    virtual void displayInfo() const = 0; // Pure virtual function for abstraction
};
class Assignment {
private:
    string title;
    string description;
    bool submitted;
    int grade;

public:
    Assignment(const string &_title, const string &_description)
        : title(_title), description(_description), submitted(false), grade(-1) {}

    string getTitle() const {
        return title;
    }

    string getDescription() const {
        return description;
    }

    bool isSubmitted() const {
        return submitted;
    }

    int getGrade() const {
        return grade;
    }

    void submit() {
        submitted = true;
    }

    void gradeAssignment(int _grade) {
        grade = _grade;
    }
};

class Student : public Person 
{
private:
    vector<Assignment> assignments;
public:
    Student(int _id, const string &_name, int _age) : Person(_name, _id, _age) {}

    void addAssignment(const Assignment &assignment) 
    {  
        assignments.push_back(assignment);
    }

    void submitAssignment(const string &title) {
        for (Assignment &assignment : assignments) {
            if (assignment.getTitle() == title) {
                assignment.submit();
                cout << "Assignment submitted successfully." << endl;
                return;
            }
        }
        cout << "Assignment not found." << endl;
    }

    void viewGrades() const {
        cout << left << setw(20) << "Title" << setw(20) << "Submitted" << setw(10) << "Grade" << endl;
        for (const Assignment &assignment : assignments) {
            cout << left << setw(20) << assignment.getTitle() << setw(20) << (assignment.isSubmitted() ? "Yes" : "No")
                 << setw(10) << assignment.getGrade() << endl;
        }
    }
    
    // Public method to allow Professor to access assignments
    vector<Assignment>& getAssignments() {
        return assignments;
    }

    void displayInfo() const override {
        cout << left << setw(20) << name << setw(10) << id << setw(10) << age << endl;
    }
};

class Professor : public Person 
{
private:
    string expertise;

public:
    Professor(const string &_name, int _age, const string &_expertise) : Person(_name, _age, _age), expertise(_expertise) {}

    void gradeAssignment(Student &student, const string &assignmentTitle, int grade) {
        vector<Assignment> &studentAssignments = student.getAssignments();
        for (Assignment &assignment : studentAssignments) {
            if (assignment.getTitle() == assignmentTitle) {
                assignment.gradeAssignment(grade);
                cout << "Assignment graded successfully." << endl;
                return;
            }
        }
        cout << "Assignment not found for this student." << endl;
    }

    void displayInfo() const override 
    {
        cout << left << setw(20) << name << setw(10) << expertise << setw(10) << age << endl;
    }
};

class Course {
private:
    string courseName;
    string courseCode;
    Professor *professor; 

public:
    Course(const string &_courseName, const string &_courseCode ,Professor *_professor) : courseName(_courseName), courseCode(_courseCode) ,professor(_professor) {}

    void displayInfo() const {
        cout << left << setw(20) << courseName;
        professor->displayInfo();
    }
};


// Function to add a new student
void addNewStudent(vector<Student> &students) {
    int id, age;
    string name;
    cout << "\t\tEnter id: ";
    cin >> id;

    // Check if student already exists
    for (const Student &student : students) {
        if (student.getID() == id) {
            cout << "\t\tStudent already exists." << endl;
            return; // Exit the function early
        }
    }
    cout << "\n\t\tEnter Name: ";
    cin >> name;
    cout << "\n\t\tEnter Age: " ;
    cin >> age;

    Student newStudent(id, name, age);
    students.push_back(newStudent);
    cout << "\t\tStudent added successfully..." << endl;
    
}
// Function to print all Student in the system
void printAllStudent(vector<Student> &students)
{
    cout << left << setw(20) << "Name" << setw(10) << "ID" << setw(10) << "Age" << endl;
        for (int i = 0; i < students.size(); ++i) {
            cout << left << setw(20) << students[i].getName() << setw(10) << students[i].getID() << setw(10) << students[i].getAge() << endl;
        }
}
// Function to search for a student by ID
int searchStudentByID(const vector<Student> &students, int id) {
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].getID() == id) {
            return i; // Return the index of the student if found
        }
    }
    cout << "\t\tNOT FOUND." << endl;
    return -1;
}
void DisplaySaerch(const vector<Student> &students, int id)
{
    int searchIndex = searchStudentByID(students, id);
    if (searchIndex != -1) {
        cout << left << setw(20) << "Name" << setw(10) << "ID" << setw(10) << "Age" << endl;
        cout << left << setw(20) << students[searchIndex].getName() << setw(10) << students[searchIndex].getID() << setw(10) << students[searchIndex].getAge() << endl;
    } else {
         cout << "\t\tStudent not found." << endl;
    }
}
// Function to update student information
void updateStudent(vector<Student> &students) {
    int id;
    cout << "\t\tEnter ID of the student to update: ";
    cin >> id;

    int index = searchStudentByID(students, id);
    if (index != -1) {
        cout << "\t\tEnter new Name: ";
        string newName;
        cin >> newName;
        students[index].setName(newName);

        cout << "\t\tEnter new Age: ";
        int newAge;
        cin >> newAge;
        students[index].setAge(newAge);

        cout << "\t\tStudent updated successfully." << endl;
    } else {
        cout << "\t\tStudent not found." << endl;
    }
}
// Function to delete a student
void deleteStudent(vector<Student> &students) {
    int id;
    cout << "\t\tEnter ID of the student to delete: ";
    cin >> id;

    int index = searchStudentByID(students, id);
    if (index != -1) {
        students.erase(students.begin() + index);
        cout << "\t\tStudent deleted successfully." << endl;
    } else {
        cout << "\t\tStudent not found." << endl;
    }
}
int main() {
    vector<Student> students;
    students.push_back(Student(1, "Ahmed", 21));
    students.push_back(Student(2, "Mohamed", 22));
    students.push_back(Student(3, "Ali", 21));

    vector<Professor> professors;
    professors.push_back(Professor("Dr. Torist", 40, "Computer Science"));
    professors.push_back(Professor("Dr. Jiangly", 46, "Computer Science"));
    professors.push_back(Professor("Dr. Smith", 39, "Computer Science"));
    professors.push_back(Professor("Dr. Benque", 50, "Computer Science"));

    vector<Course> courses;
    courses.push_back(Course("Introduction to Programming", "CS111", &professors[0]));
    courses.push_back(Course("Data Structure", "CS112", &professors[1]));
    courses.push_back(Course("Data Base", "CS113", &professors[2]));
    courses.push_back(Course("OOP", "CS114", &professors[3]));

    char choice;
    do {
        int op;
        cout << "\t\t-----------------------" << endl;
        cout << "\t\tStudent Management System" << endl;
        cout << "\t\t-----------------------" << endl;
        cout << "\t\t1. Add new student" << endl;
        cout << "\t\t2. Display All Students" << endl;
        cout << "\t\t3. Search Student" << endl;
        cout << "\t\t4. Update Student" << endl;
        cout << "\t\t5. Delete Student" << endl;
        cout << "\t\t6. Exit" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> op;

        switch (op) {
            case 1:
                addNewStudent(students);
                break;
            case 2:
                printAllStudent(students);
                break;
            case 3:
                cout << "Enter The ID of the student : ";
                int searchID ; cin >> searchID;
                DisplaySaerch(students , searchID);
                break;
            case 4:
                updateStudent(students);
                break;
            case 5:
                deleteStudent(students);
                break;
            case 6:
                exit(0); // Use 0 to indicate successful termination
            default:
                cout << "\t\tInvalid Number......" << endl;
        }

        cout << "\t\tDo you want to continue (y/n)?: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}