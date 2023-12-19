#ifndef PROJETO2_AUXILIAR_H
#define PROJETO2_AUXILIAR_H


class Auxiliar {
public:
    static void readClassesPerUc(Course& course);
    static void readStudentsClasses(Course& course);
    static void readClasses(Course& course);

    static void loadRequestRecord(std::queue<Request*> &pastRequests);
    static void saveRequestRecord(std::stack<Request*> requestRecord);
};


#endif //PROJETO2_AUXILIAR_H
