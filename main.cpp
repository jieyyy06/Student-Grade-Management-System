#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip> 

using namespace std;

// Define student data structure
struct Student {
    string id;
    string name;
    int score;
};

void addStudent(vector<Student>& students);
void listStudents(const vector<Student>& students);
void sortByScore(vector<Student>& students);
void searchById(const vector<Student>& students);
void showStatistics(const vector<Student>& students);
bool compareByScore(const Student& a, const Student& b);

int main() {
    vector<Student> students;
    int choice;

    while (true) {
        cout << "\n===== Student Data Management System =====" << endl;
        cout << "1. Add student " << endl;
        cout << "2. List all students " << endl;
        cout << "3. Sort by score " << endl;
        cout << "4. Search by id " << endl;
        cout << "5. Show statistics " << endl;
        cout << "0. Exit " << endl;
        cout << "請輸入選項 (0-5): ";
        
        if (!(cin >> choice)) {
            cout << "Error! Please enter a valid numeric option!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (choice == 0) {
            cout << "Thank you for using this system. The system has ended." << endl;
            break;
        }

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                listStudents(students);
                break;
            case 3:
                sortByScore(students);
                break;
            case 4:
                searchById(students);
                break;
            case 5:
                showStatistics(students);
                break;
            default:
                cout << "Invalid option, please enter again!" << endl;
        }
    }
    return 0;
}

// Function 1: Add new student information (including duplicate student ID check)
void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "\n--- Add student data ---" << endl;
    cout << "Please enter your student ID: ";
    cin >> newStudent.id;

    // Check if the student ID number already exists.
    for (const auto& s : students) {
        if (s.id == newStudent.id) {
            cout << "Error message: Student ID " << newStudent.id << " Existing, no new additions allowed!" << endl;
            return;
        }
    }

    cout << "Please enter your name: ";
    cin >> newStudent.name;
    cout << "Please enter your score (0-100): ";
    cin >> newStudent.score;

    if (newStudent.score < 0 || newStudent.score > 100) {
        cout << "Error: Score must be between 0 and 100! Addition failed." << endl;
        return;
    }

    students.push_back(newStudent);
    cout << "Student information added successfully!" << endl;
}

// Function 2: List all students
void listStudents(const vector<Student>& students) {
    cout << "\n--- List of all students ---" << endl;
    if (students.empty()) {
        cout << "There is currently no student information." << endl;
        return;
    }

    cout << left << setw(12) << "Student ID" << setw(15) << "Name" << setw(6) << "Score" << endl;
    cout << "-----------------------------------" << endl;
    for (const auto& s : students) {
        cout << left << setw(12) << s.id << setw(15) << s.name << setw(6) << s.score << endl;
    }
}

// Function 3: Sort by score (from highest to lowest)
void sortByScore(vector<Student>& students) {
    if (students.empty()) {
        cout << "\nThere are currently no student records available for sorting." << endl;
        return;
    }

    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
    });

    cout << "\nSorting complete! The scores have been sorted from highest to lowest." << endl;
    listStudents(students); 
}

// Function 4: Search for students
void searchById(const vector<Student>& students) {
    cout << "\n--- Searching for student information ---" << endl;
    if (students.empty()) {
        cout << "There is currently no student information." << endl;
        return;
    }

    string searchId;
    cout << "Please enter the student ID you wish to query: ";
    cin >> searchId;

    for (const auto& s : students) {
        if (s.id == searchId) {
            cout << "\nStudent information found:" << endl;
            cout << "Student ID: " << s.id << endl;
            cout << "Name: " << s.name << endl;
            cout << "Score: " << s.score << endl;
            return;
        }
    }
    cout << "Message: Student ID: " << searchId << " could not be found." << endl;
}

// Function 5: Statistics of Results
void showStatistics(const vector<Student>& students) {
    cout << "\n--- Class Grade Statistics ---" << endl;
    if (students.empty()) {
        cout << "There is currently no student data, so statistics cannot be compiled." << endl;
        return;
    }

    int totalScore = 0;
    int maxScore = students[0].score;
    int minScore = students[0].score;
    int passCount = 0;
    int failCount = 0;

    for (const auto& s : students) {
        totalScore += s.score;
        
        if (s.score > maxScore) maxScore = s.score;
        if (s.score < minScore) minScore = s.score;
        
        if (s.score >= 60) {
            passCount++;
        } else {
            failCount++;
        }
    }

    double average = static_cast<double>(totalScore) / students.size();

    cout << "Total number of students in the class： " << students.size()  << endl;
    cout << "Class average： " << fixed << setprecision(2) << average  << endl;
    cout << "Highest score： " << maxScore  << endl;
    cout << "minimum score： " << minScore  << endl;
    cout << "Number of people who passed： " << passCount  << endl;
    cout << "Number of students who failed：" << failCount  << endl;
}