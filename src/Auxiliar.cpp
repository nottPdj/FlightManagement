#include "Auxiliar.h"
#include <sstream>
#include <fstream>
#include "Auxiliar.h"

void Auxiliar::readClassesPerUc(Course& course){
    std::ifstream file("../classes_per_uc.csv");
    std::string line;
    std::string ucCode, classCode;

    getline(file, line); // ignorar header
    while (std::getline(file, line)){
        std::istringstream ss(line);
        getline(ss, ucCode, ',');
        getline(ss, classCode, '\r');
        course.addUC(ucCode);
        course.addClass(classCode, ucCode);
    }

}

void Auxiliar::readStudentsClasses(Course& course){
    std::ifstream file("../students_classes.csv");
    std::string line;
    std::string studentCode, studentName, ucCode, classCode;

    getline(file, line); // ignorar header
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        getline(ss, studentCode, ',');
        getline(ss, studentName, ',');
        getline(ss, ucCode, ',');
        getline(ss, classCode, '\r');
        course.addStudent(studentCode, studentName, ucCode, classCode);

    }
}

void Auxiliar::readClasses(Course& course) {
    std::ifstream file("../classes.csv");
    std::string line;
    std::string classCode, ucCode, type, weekday, startHour, duration;
    float startHourF, durationF;

    getline(file, line); // ignorar header
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        getline(ss, classCode, ',');
        getline(ss, ucCode, ',');
        getline(ss, weekday, ',');
        getline(ss, startHour, ',');
        getline(ss, duration, ',');
        getline(ss, type, '\r');

        startHourF = std::stof(startHour);
        durationF = std::stof(duration);
        course.addLecture(classCode, ucCode, type, weekday, startHourF, durationF);
    }
}

void Auxiliar::loadRequestRecord(std::queue<Request *> &pastRequests) {
    std::ifstream file("../request_history.txt");
    std::string line;
    std::string reqType;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        getline(ss, reqType, ',');
        if (reqType == "Join"){
            std::string studentCode, ucCode;
            getline(ss, studentCode, ',');
            getline(ss, ucCode);
            JoinRequest* newReq = new JoinRequest(studentCode, ucCode);
            pastRequests.push(newReq);
        }
        else if (reqType == "Leave"){
            std::string studentCode, ucCode;
            getline(ss, studentCode, ',');
            getline(ss, ucCode);
            LeaveRequest* newReq = new LeaveRequest(studentCode, ucCode);
            pastRequests.push(newReq);
        }
        else if (reqType == "SwitchUc"){
            std::string studentCode, ucCodeCurrent, ucCodeNext;
            getline(ss, studentCode, ',');
            getline(ss, ucCodeCurrent, ',');
            getline(ss, ucCodeNext);
            SwitchUcRequest* newReq = new SwitchUcRequest(studentCode, ucCodeCurrent, ucCodeNext);
            pastRequests.push(newReq);
        }
        else if (reqType == "SwitchClass"){
            std::string studentCode, ucCode, classCodeCurrent, classCodeNext;
            getline(ss, studentCode, ',');
            getline(ss, ucCode, ',');
            getline(ss, classCodeCurrent, ',');
            getline(ss, classCodeNext);
            SwitchClassRequest* newReq = new SwitchClassRequest(studentCode, ucCode, classCodeCurrent, classCodeNext);
            pastRequests.push(newReq);
        }
    }
}

/**
 * @brief Save the requests into a file
 * @param requestRecord
 * @details Time Complexity O(n) n = number of requests
 */
void Auxiliar::saveRequestRecord(std::stack<Request *> requestRecord) {
    /*
     JOIN        studentCode, ucCode
     LEAVE       studentCode, ucCode
     SWITCHUC    studentCode, ucCodeCurrent, ucCodeNext
     SWITCHCLASS studentCode, ucCode,        classCodeCurrent, classCodeNext
     */
    std::ofstream file("../request_history.txt");
    std::stack<Request *> reversedRecord;
    while (!requestRecord.empty()){
        reversedRecord.push(requestRecord.top());
        requestRecord.pop();
    }

    while (!reversedRecord.empty()){
        Request* request =  reversedRecord.top();
        if (JoinRequest* joinReq = dynamic_cast<JoinRequest*>(request)) {
            file << "Join," << joinReq->getStudentCode() << "," << joinReq->getUcCode() << "\n";
        }
        else if (LeaveRequest* leaveReq = dynamic_cast<LeaveRequest*>(request)) {
            file << "Leave," << leaveReq->getStudentCode() << "," << leaveReq->getUcCode() << "\n";
        }
        else if (SwitchUcRequest* switchUcReq = dynamic_cast<SwitchUcRequest*>(request)) {
            file << "SwitchUc," << switchUcReq->getStudentCode() << "," << switchUcReq->getUcCodeCurrent() << "," << switchUcReq->getUcCodeNext() << "\n";
        }
        else if (SwitchClassRequest* switchClassReq = dynamic_cast<SwitchClassRequest*>(request)) {
            file<< "SwitchClass,"  << switchClassReq->getStudentCode() << "," << switchClassReq->getUcCode() << "," << switchClassReq->getClassCodeCurrent() << "," << switchClassReq->getClassCodeNext() << "\n";
        }
        reversedRecord.pop();
    }
}