#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "project.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void InitializeDb();            //initialize database
        void SearchDb();                //search the database

        //HOME
        void on_hb_view_clicked();      //button view calendar clicked

        //CALENDAR
        void UpdateCalendarTable();     //update calendar with current hour
        void UpdateProjectsTable();     //update projects table
        void on_cb_set_clicked();       //button add clicked
        void on_cb_add_clicked();       //button add clicked
        void on_cb_back_clicked();      //button back clicked

        //SET HOURS
        void UpdateComboBox();          //updates hours in combo boxes
        void on_sb_apply_clicked();     //button apply clicked
        void on_sb_back_clicked();      //button back clicked

        //ADD TASK
        bool isNumber(const QString& str);
        void on_ab_add_clicked();       //button add clicked
        void on_ab_back_clicked();      //button back clicked

    private:
        Ui::MainWindow *ui;             //ui elements
        QSqlDatabase db;                //database
        QTimer *timer;                  //time to auto-update

        QList <Project> projectList;    //project list (contains project objects)

        QString dayStr;                 //string of day: "Mon", "Tue", etc.
        int countHrs;                   //used in calculation for counting hours
        int curDay;                     //current day int: 0=Mon, 1-Tue, etc.
        int prevDay;                    //previous day int: 0=Mon, 1-Tue, etc.
        int curTotalHours;              //total hours currently from start of week
        int prevTotalHours;             //total hours of previous update from start of week
        int daysPassed;                 //days passed between previous update and now
        int hoursPassed;                //hours passed between previous update and now
};

#endif // MAINWINDOW_H
