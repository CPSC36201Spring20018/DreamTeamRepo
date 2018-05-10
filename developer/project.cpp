#include "project.h"
/*****************************************************************************
 * Project
 *____________________________________________________________________________
 * This method will initialize the class with default values
 *****************************************************************************/
Project::Project() {
    name = "";
    desc = "";
    totalHours = 0;
    remHours = 0;
    dateDue = "";
}


/*****************************************************************************
 * Project
 *____________________________________________________________________________
 * This method will initialize the class with user-defined values.
 *****************************************************************************/
Project::Project(QString name, int totalHours, int remHours, QString desc) {
    this->name = name;
    this->totalHours = totalHours;
    this->remHours = remHours;
    this->desc = desc;
    dateDue = "";
}


/*****************************************************************************
 * Project
 *____________________________________________________________________________
 * This method will initialize the class with user-defined values.
 *****************************************************************************/
Project::Project(QString name, int totalHours, QString desc) {
    this->name = name;
    this->totalHours = totalHours;
    this->remHours = totalHours;
    this->desc = desc;
    dateDue = "";
}


/*****************************************************************************
 * GetName
 *____________________________________________________________________________
 * This method will return the name.
 *****************************************************************************/
QString Project::GetName() const {
    return name;
}


/*****************************************************************************
 * GetDesc
 *____________________________________________________________________________
 * This method will return the description.
 *****************************************************************************/
QString Project::GetDesc() const {
    return desc;
}


/*****************************************************************************
 * GetTotalHours
 *____________________________________________________________________________
 * This method will return the total hours.
 *****************************************************************************/
int Project::GetTotalHours() const {
    return totalHours;
}


/*****************************************************************************
 * GetRemHours
 *____________________________________________________________________________
 * This method will return the remaining hours left on the project.
 *****************************************************************************/
int Project::GetRemHours() const {
    return remHours;
}


/*****************************************************************************
 * GetDateDue
 *____________________________________________________________________________
 * This method will return the date due on the project.
 *****************************************************************************/
QString Project::GetDateDue() const {
    int d = due;
    QString temp;

    switch(d){
    case 0:
        return "Monday";
        break;
    case 1:
        return "Tuesday";
        break;
    case 2:
        return "Wednesday";
        break;
    case 3:
        return "Thursday";
        break;
    case 4:
        return "Friday";
        break;
    case 5:
        return "Saturday";
        break;
    case 6:
        return "Sunday";
        break;
    }

    return dateDue;
}


/*****************************************************************************
 * SetName
 *____________________________________________________________________________
 * This method will set the name.
 *****************************************************************************/
void Project::SetName(QString name) {
    this->name = name;
}


/*****************************************************************************
 * SetDesc
 *____________________________________________________________________________
 * This method will set the description.
 *****************************************************************************/
void Project::SetDesc(QString desc) {
    this->desc = desc;
}


/*****************************************************************************
 * SetTotalHours
 *____________________________________________________________________________
 * This method will set the total hours.
 *****************************************************************************/
void Project::SetTotalHours(int totalHours) {
    this->totalHours = totalHours;
}


/*****************************************************************************
 * SetRemHours
 *____________________________________________________________________________
 * This method will set the remaining hours.
 *****************************************************************************/
void Project::SetRemHours(int remHours) {
    this->remHours = remHours;
}


/*****************************************************************************
 * SetDateDue
 *____________________________________________________________________________
 * This method will set the date due.
 *****************************************************************************/
void Project::SetDateDue(QString date) {
    this->dateDue = date;
}


/*****************************************************************************
 * DecRemHours
 *____________________________________________________________________________
 * This method will decrement the remaining hours.
 *****************************************************************************/
void Project::DecRemHours() {
    remHours--;
}

/*****************************************************************************
 * setDue
 *____________________________________________________________________________
 * This method will set an integer due date.
 *****************************************************************************/
void Project::setDue(int due){
    this->due = due;
}