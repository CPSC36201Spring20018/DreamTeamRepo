#ifndef PROJECT_H
#define PROJECT_H
#include <qstring.h>

class Project {
    public:
        Project();
        Project(QString name, int totalHours, int remHours, QString desc);
        Project(QString name, int totalHours, QString desc);
        QString GetName() const;
        QString GetDesc() const;
        int GetTotalHours() const;
        int GetRemHours() const;
        QString GetDateDue() const;

        void SetName(QString name);
        void SetDesc(QString desc);
        void SetTotalHours(int totalHours);
        void SetRemHours(int remHours);
        void SetDateDue(QString date);
        void setDue(int due);

        void DecRemHours();
    private:
        QString name;
        QString desc;
        int totalHours;
        int remHours;
        QString dateDue;
        int due;
};

#endif
