//============================================================================
// Name        : ABCU.cpp
// Author      : Fernando Balen
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Course {
public:
    std::string code;
    std::string name;

    Course(std::string code, std::string name) : code(code), name(name) {}
};

void loadCoursesFromCSV(const std::string& filePath, std::vector<Course>& courses) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    // Read course codes
    std::getline(file, line);
    std::istringstream codesStream(line);
    std::vector<std::string> codes;
    std::string code;
    while (std::getline(codesStream, code, ',')) {
        codes.push_back(code);
    }

    // Read course names
    std::getline(file, line);
    std::istringstream namesStream(line);
    std::vector<std::string> names;
    std::string name;
    while (std::getline(namesStream, name, ',')) {
        names.push_back(name);
    }

    // Create Course objects
    for (size_t i = 0; i < codes.size(); ++i) {
        courses.emplace_back(codes[i], names[i]);
    }

    file.close();
}

void printMenu() {
    std::cout << "1. Load Data Structure.\n";
    std::cout << "2. Print Course List.\n";
    std::cout << "3. Print Course.\n";
    std::cout << "9. Exit\n";
    std::cout << "Select an option: ";
}

void printCourses(const std::vector<Course>& courses) {
    for (const auto& course : courses) {
        std::cout << "Code: " << course.code << ", Name: " << course.name << std::endl;
    }
}

void printCourseInfo(const std::vector<Course>& courses, const std::string& code) {
    for (const auto& course : courses) {
        if (course.code == code) {
            std::cout << "Code: " << course.code << ", Name: " << course.name << std::endl;
            return;
        }
    }
    std::cout << "Course not found.\n";
}

int main() {
    std::vector<Course> courses;
    int choice = 0;

    while (true) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string filePath;
                std::cout << "Enter the path to the CSV file: ";
                std::cin >> filePath; // Ask the user for the file path
                loadCoursesFromCSV(filePath, courses);
                std::cout << "Courses loaded successfully.\n";
                break;
            }
            case 2:
                printCourses(courses);
                break;
            case 3: {
                std::string code;
                std::cout << "Enter course code: ";
                std::cin >> code;
                printCourseInfo(courses, code);
                break;
            }
            case 9:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid option. Please try again.\n";
                break;
        }
    }

    return 0;
}

