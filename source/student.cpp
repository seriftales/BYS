#include "student.h"
#include <sstream>

Student::Student(int id, const std::string& name, float mid, float sec, float fin, float task, int abs)
    : id(id), name(name), midtermScore(mid), secondTermScore(sec), finalScore(fin), taskScore(task), absences(abs) {}

int Student::getId() const { return id; }
std::string Student::getName() const { return name; }
float Student::getMidterm() const { return midtermScore; }
float Student::getSecond() const { return secondTermScore; }
float Student::getFinal() const { return finalScore; }
float Student::getTask() const { return taskScore; }
int Student::getAbsences() const { return absences; }

float Student::calculateAverage() const {
    return (midtermScore * MIDTERM_WEIGHT) + 
           (secondTermScore * SECOND_WEIGHT) + 
           (taskScore * TASK_WEIGHT) + 
           (finalScore * FINAL_WEIGHT);
}

bool Student::isPassed() const {
    return calculateAverage() >= 50.0f;
}

std::string Student::toCsvLine() const {
    std::stringstream ss;
    ss << name << "," << id << "," << midtermScore << "," 
       << secondTermScore << "," << finalScore << "," 
       << taskScore << "," << absences;
    return ss.str();
}