/******************************************************************************
* Title: ABCU Course Advising Program
* Author: Conor Steward
* Date: 10/17/24
* Version: 1.0
* 
* Description:
* This program implements a course advising system for ABCU. It allows users
* to load course data from a CSV file, print an alphanumerically sorted list
* of all courses, and search for individual course details including
* prerequisites. The program uses a hash table (unordered_map) to store and
* manage course information efficiently.
*
* Known Issues:
* - Assumes the input CSV file is correctly formatted.
* - Does not handle potential memory allocation issues.
******************************************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Course structure to hold information about each course
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};

// Function prototypes
void loadFileData(unordered_map<string, Course>& courses);
void printCoursesSorted(const unordered_map<string, Course>& courses);
void printCourseDetails(const unordered_map<string, Course>& courses);
void displayMenu();

int main() {
    unordered_map<string, Course> courses;  // Hash table to store all courses
    bool fileLoaded = false;  // Flag to check if file has been loaded
    int choice;

    // Main program loop
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                loadFileData(courses);
                fileLoaded = true;
                break;
            case 2:
                if (fileLoaded) {
                    printCoursesSorted(courses);
                } else {
                    cout << "Error: You must load the file data first." << endl;
                }
                break;
            case 3:
                if (fileLoaded) {
                    printCourseDetails(courses);
                } else {
                    cout << "Error: You must load the file data first." << endl;
                }
                break;
            case 9:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid option. Please choose a valid option." << endl;
        }
    } while (choice != 9);

    return 0;
}

// Function to display the main menu
void displayMenu() {
    cout << "\nWelcome to the ABCU Course Advising Program" << endl;
    cout << "1. Load file data into the data structure" << endl;
    cout << "2. Print alphanumerically ordered list of all courses" << endl;
    cout << "3. Print course title and prerequisites for an individual course" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to load course data from CSV file into the hash table
void loadFileData(unordered_map<string, Course>& courses) {
    ifstream file("CS 300 ABCU_Advising_Program_Input.csv");
    if (!file.is_open()) {
        cout << "Error opening file. Make sure the file exists in the correct location." << endl;
        return;
    }

    courses.clear();  // Clear existing data
    string line;
    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        stringstream ss(line);
        string token;
        Course course;

        // Parse course number and name
        if (getline(ss, course.courseNumber, ',') &&
            getline(ss, course.courseName, ',')) {
            
            // Parse prerequisites
            while (getline(ss, token, ',')) {
                if (!token.empty()) {
                    course.prerequisites.push_back(token);
                }
            }

            courses[course.courseNumber] = course;
            cout << "Loaded course: " << course.courseNumber << endl;
        } else {
            cout << "Error parsing line " << lineCount << ": " << line << endl;
        }
    }

    file.close();
    cout << "Finished loading courses. Total courses loaded: " << courses.size() << endl;
}

// Function to print courses sorted alphanumerically
void printCoursesSorted(const unordered_map<string, Course>& courses) {
    vector<pair<string, string>> sortedCourses;
    // Copy courses to a vector for sorting
    for (const auto& pair : courses) {
        sortedCourses.push_back({pair.second.courseNumber, pair.second.courseName});
    }
    // Sort courses based on course number
    sort(sortedCourses.begin(), sortedCourses.end());

    // Print sorted courses
    for (const auto& course : sortedCourses) {
        cout << course.first << ", " << course.second << endl;
    }
}

// Function to print details of a specific course
void printCourseDetails(const unordered_map<string, Course>& courses) {
    string searchCourseNumber;
    cout << "Enter the course number: ";
    cin >> searchCourseNumber;

    // Search for the course in the hash table
    auto it = courses.find(searchCourseNumber);
    if (it != courses.end()) {
        const Course& course = it->second;
        cout << "Course Number: " << course.courseNumber << endl;
        cout << "Course Name: " << course.courseName << endl;
        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        } else {
            cout << "Prerequisites: None" << endl;
        }
    } else {
        cout << "Course not found." << endl;
    }
}