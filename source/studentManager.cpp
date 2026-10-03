#include "studentManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

StudentManager::StudentManager(const std::string& path) : dbPath(path) {}

bool StudentManager::loadFromFile() {
    std::ifstream file(dbPath);
    if (!file.is_open()) return false;

    students.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nameStr, idStr, midStr, secStr, finStr, taskStr, absStr;

        if (std::getline(ss, nameStr, ',') && std::getline(ss, idStr, ',') &&
            std::getline(ss, midStr, ',') && std::getline(ss, secStr, ',') &&
            std::getline(ss, finStr, ',') && std::getline(ss, taskStr, ',') &&
            std::getline(ss, absStr, ',')) {
            
            try {
                Student s(std::stoi(idStr), nameStr, std::stof(midStr), 
                          std::stof(secStr), std::stof(finStr), 
                          std::stof(taskStr), std::stoi(absStr));
                students.push_back(s);
            } catch (...) {
                // Bozuk satırları atla
                continue;
            }
        }
    }
    file.close();
    return true;
}

bool StudentManager::saveToFile() const {
    std::ofstream file(dbPath, std::ios::trunc);
    if (!file.is_open()) return false;

    for (const auto& student : students) {
        file << student.toCsvLine() << "\n";
    }
    file.close();
    return true;
}

void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
    saveToFile(); 
}

bool StudentManager::deleteStudent(int id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getId() == id) {
            students.erase(it); 
            saveToFile();
            return true;
        }
    }
    return false;
}

bool StudentManager::updateStudent(int id, float newMid, float newSec, float newFin, float newTask) {
    for (auto& student : students) {
        if (student.getId() == id) {
            Student updated(id, student.getName(), newMid, newSec, newFin, newTask, student.getAbsences());
            student = updated;
            saveToFile();
            return true;
        }
    }
    return false;
}

const std::vector<Student>& StudentManager::getAllStudents() const {
    return students;
}

std::vector<Student> StudentManager::getPassedStudents() const {
    std::vector<Student> passed;
    for (const auto& s : students) {
        if (s.isPassed()) passed.push_back(s);
    }
    return passed;
}

std::vector<Student> StudentManager::getFailedStudents() const {
    std::vector<Student> failed;
    for (const auto& s : students) {
        if (!s.isPassed()) failed.push_back(s);
    }
    return failed;
}

Student const* StudentManager::findStudentById(int id) const {
    for (const auto& s : students) {
        if (s.getId() == id) return &s;
    }
    return nullptr;
}

std::vector<Student> StudentManager::getStudentsByGradeRange(float minGrade, float maxGrade) const {
    std::vector<Student> filteredList;
    for (const auto& student : students) {
        float avg = student.calculateAverage();
        if (avg >= minGrade && avg <= maxGrade) {
            filteredList.push_back(student);
        }
    }
    return filteredList;
}