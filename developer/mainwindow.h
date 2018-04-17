#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "project.h"

/*****************************************************************************
 * Smart Calendar
 *____________________________________________________________________________
 * This project will create a smart calendar for the user.
 *
 * TO DO:
 *      1: When adding free time to calendar, place mark each cell that is not
 *         free time with an "X" (reverse of what we have now)
 *      2: When the current hour lands on an OPEN cell, change to "Current/OPEN".
 *         Fix all connections to detecting a current cell.
 *         When Current hour is removed, replace with OPEN again
 *      3: When current hour lands on "X" free time, don't decrement remaining hrs
 *      4: On Free Time page, make so the combo boxes read from database.
 *
 * KNOWN BUGS:
 *      1: When the user adds a task, then edits free hours, this can create
 *         one or more open cells in the calendar before the added task. If
 *         the user adds another project, it will place project hours before
 *         the first added project. When the program decrements remaining
 *         hours, it will decrement from the 1st task instead of the 2nd.
 *         Look at page 50 in mainwindow.cpp to fix.
 *****************************************************************************/

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
        void on_hb_exit_clicked();      //button exit clicked

        //CALENDAR
        void UpdateCalendarTable();     //update calendar with current hour
        void UpdateUnscheduledTable();  //update unscheduled projects table
        void UpdateScheduledTable();    //update scheduled projects table

        void UpdateUnscheduledDb();     //updates unscheduled table from the database
        void UpdateScheduledDb();       //updates scheduled table from the database

        void on_ct_unscheduled_cellClicked(int row1, int col1);   //on unscheduled table cell click, record row and column
        void on_ct_scheduled_cellClicked(int row1, int col1);     //on scheduled table cell click, record row and column
        void onDataChangedUnscheduled(const QModelIndex& value);  //on unscheduled cell data change, update db
        void onDataChangedScheduled(const QModelIndex& value);    //on scheduled cell data change, update db

        void on_cb_set_clicked();       //button add clicked
        void on_cb_add_clicked();       //button add clicked
        void on_cb_schedule_clicked();  //button auto-schedule clicked
        void on_cb_deleteUn_clicked();  //button delete unscheduled task clicked
        void on_cb_deleteSc_clicked();  //button delete scheduled task clicked
        void on_cb_back_clicked();      //button back clicked

        //SET HOURS
        void UpdateComboBox();                   //updates hours in combo boxes
        bool CheckFreeHours(QComboBox* from,
                            QComboBox* to,
                            QString comboDay);   //checks the free hours combo boxes
        void UpdateFreeDatabase(QComboBox* from,
                                QComboBox* to,
                                QString day,
                                int dayNum);     //updates that free hours database
        void on_sb_apply_clicked();     //button apply clicked
        void on_sb_back_clicked();      //button back clicked

        //ADD TASK
        bool IsNumber(const QString& str);           //if string is a number over 0
        bool IsUnique(const QString& str,
                      const QList<Project>& list1,
                      const QList<Project>& list2);  //if string is unique
        void on_ab_add_clicked();       //button add clicked
        void on_ab_back_clicked();      //button back clicked

    private:
        Ui::MainWindow *ui;             //ui elements
        QSqlDatabase db;                //database
        QTimer *timer;                  //time to auto-update
        QString curDayStr;              //current day name (Mon, Tue...Sun)
        QTime curHour;                  //current hour (12,13...23)

        QList<Project> unscheduledList; //project list (contains unscheduled project objects)
        QList<Project> scheduledList;   //project list (contains scheduled project objects)

        QString dayStr;                 //string of day: "Mon", "Tue", etc.
        int countHrs;                   //used in calculation for counting hours
        int curDay;                     //current day int: 0=Mon, 1-Tue, etc.
        int prevDay;                    //previous day int: 0=Mon, 1-Tue, etc.
        int curTotalHours;              //total hours currently from start of week
        int prevTotalHours;             //total hours of previous update from start of week
        int daysPassed;                 //days passed between previous update and now
        int hoursPassed;                //hours passed between previous update and now

        int row;                        //row selected on table
        int col;                        //column selected on table
        bool notScheduled;              //false if scheduled project list is selected
        bool isFree;                    //false if current hour is not on free time
};

#endif // MAINWINDOW_H
