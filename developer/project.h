#ifndef PROJECT_H
#define PROJECT_H
#include <qstring.h>

class Project {
    public:
        Project();
        Project(QString name, QString desc, int totalHours);
        QString GetName() const;
        QString GetDesc() const;
        int GetTotalHours() const;
    private:
        QString name;
        QString desc;
        int totalHours;
};

#endif
