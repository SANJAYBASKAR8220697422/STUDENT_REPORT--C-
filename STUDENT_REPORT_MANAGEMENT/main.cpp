#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <algorithm>
#include <iomanip>

using namespace std;

// Function to validate grade input
bool isValidGrade(char grade) {
    grade = toupper(grade);
    return (grade >= 'A' && grade <= 'F');
}

class Student {
private:
    string name;
    char grade;
    int mark;

public:
    Student(const string& n, char g, int m) : name(n), grade(toupper(g)), mark(m) {}

    string getName() const {
        return name;
    }

    char getGrade() const {
        return grade;
    }

    int getMarks() const {
        return mark;
    }
};

class ClassReport {
private:
    multimap<string, Student> classData;
    string className;
    string fileName;

public:
    ClassReport(const string& clsName, const string& file) : className(clsName), fileName(file) {
        loadFromFile();
    }

    void loadFromFile() {
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            string name;
            char grade;
            int marks;
            while (inFile >> name >> grade >> marks) {
                classData.insert(make_pair(name, Student(name, grade, marks)));
            }
            inFile.close();
            cout << "Data loaded from file successfully.\n";
        } else {
            cout << "File not found or unable to open.\n";
        }
    }


    void saveToFile() {
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            for (auto& entry : classData) {
                outFile << entry.second.getName() << " " << entry.second.getGrade() << " " << entry.second.getMarks() << "\n";
            }
            outFile.close();
            cout << "Data saved to file successfully.\n";
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

    void addStudent() {
        string name;
        char grade;
        int marks;
        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter student grade (A-F): ";
        cin >> grade;
        grade = toupper(grade);
        if(isValidGrade(grade)) {
            cout << "Enter student marks: ";
            cin >> marks;
            classData.insert(make_pair(name, Student(name, grade, marks)));
            saveToFile();
        } else {
            cout << "Invalid grade. Please enter a grade between A and F.\n";
        }
    }

    void removeStudent() {
        string name;
        cout << "Enter student name to remove: ";
        cin >> name;
        auto it = classData.find(name);
        if(it != classData.end()) {
            classData.erase(it);
            saveToFile();
            cout << "Student " << name << " removed successfully.\n";
        } else {
            cout << "Student " << name << " not found.\n";
        }
    }

    void displayStudents() {
        cout << "\nStudent Report for Class " << className << ":\n";
        cout << "---------------------------------------------\n";
        cout << "|   Name   |   Grade   |   Marks   |\n";
        cout << "---------------------------------------------\n";
        for(auto& entry : classData) {
            cout << "| " << setw(8) << left << entry.second.getName() << " | ";
            cout << setw(9) << left << entry.second.getGrade() << " | ";
            cout << setw(8) << left << entry.second.getMarks() << " |\n";
        }
        cout << "---------------------------------------------\n";
    }

    void start() {
        int choice;
        string ascii;
//        string classascii = R"(
//   _____ _1

//  / ____| |
// | |    | | __ _ ___ ___
// | |    | |/ _` / __/ __|
// | |____| | (_| \__ \__ \
//  \_____|_|\__,_|___/___/
//
//
//)";
        if (className == "A") {
            ascii = R"(
     /\
    /  \
   / /\ \
  / ____ \
 /_/    \_\


)";
        } else if (className == "B") {
            ascii = R"(
  ____
 |  _ \
 | |_) |
 |  _ <
 | |_) |
 |____/


)";
        } else if (className == "C") {
            ascii = R"(
   _____
  / ____|
 | |
 | |
 | |____
  \_____|


)";
        } else {
            cout << ".........\n";
        }

        do {
            cout <<"             "<< ascii << "\n";
            cout << "                      =====================================\n";
            cout << "                        =>1. Add Student\n";
            cout << "                        =>2. Remove Student\n";
            cout << "                        =>3. Display Students\n";
            cout << "                        =>4. Go Back to Class Selection\n";
            cout << "                        =>5. Exit\n";
            cout << "                      =====================================\n";
            cout << "Enter your choice   { 1 / 2 / 3 / 4 / 5 } : ";
            cin >> choice;

            switch(choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    removeStudent();
                    break;
                case 3:
                    displayStudents();
                    break;
                case 4:
                    return; // Return to class selection
                case 5:
                    cout << "==================================\n";
                    cout << "Thank you for your Feed.Exiting...\n";
                    exit(0);
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                    break;
            }

        } while(choice != 4);
    }
};

int main() {
    int classChoice;
    string header = R"(
  _______              _                      _____               _        _____                       _
 |__   __|            | |                    / ____|             | |      |  __ \                     | |
    | | ___  __ _  ___| |__   ___ _ __ ___  | |  __ _ __ __ _  __| | ___  | |__) |___ _ __   ___  _ __| |_
    | |/ _ \/ _` |/ __| '_ \ / _ \ '__/ __| | | |_ | '__/ _` |/ _` |/ _ \ |  _  // _ \ '_ \ / _ \| '__| __|
    | |  __/ (_| | (__| | | |  __/ |  \__ \ | |__| | | | (_| | (_| |  __/ | | \ \  __/ |_) | (_) | |  | |_
    |_|\___|\__,_|\___|_| |_|\___|_|  |___/  \_____|_|  \__,_|\__,_|\___| |_|  \_\___| .__/ \___/|_|   \__|
                                                                                     | |
                                                                                     |_|

)";
    std::cout<<header<<"\n";
    while (true) {
        cout << "                     Welcome to the Teachers grade report System\n";
        cout << "---------------------------------------------------------------------------------------------------\n";
        cout << " Choose the class you want to manage:\n";
        cout << "                      =====================================\n";
        cout << "                          =>1. Class A----------( 1 )\n";
        cout << "                          =>2. Class B----------( 2 )\n";
        cout << "                          =>3. Class C----------( 3 )\n";
        cout << "                          =>4. Exit-------------( 4 )\n";
        cout << "                      =====================================\n";
        cout << "                      =>Enter your choice { 1 / 2 / 3 / 4 }:- ";
        cin >> classChoice;

        switch(classChoice) {
            case 1: {
                ClassReport classA("A", "classA_data.txt");
                classA.start();
                break;
            }
            case 2: {
                ClassReport classB("B", "classB_data.txt");
                classB.start();
                break;
            }
            case 3: {
                ClassReport classC("C", "classC_data.txt");
                classC.start();
                break;
            }
            case 4: {
                cout << "Exiting...\n";
                exit(0);
            }
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4.\n";
                break;
        }
    }

    return 0;
}
