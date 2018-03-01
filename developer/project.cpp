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
}


/*****************************************************************************
 * Project
 *____________________________________________________________________________
 * This method will initialize the class with user-defined values.
 *****************************************************************************/
Project::Project(QString name, QString desc, int totalHours) {
    this->name = name;
    this->desc = desc;
    this->totalHours = totalHours;
    this->remHours = totalHours;
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
