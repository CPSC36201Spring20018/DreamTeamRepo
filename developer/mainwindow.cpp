#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/database.sqlite");

    if(db.open())
        qDebug() << "Database connected\n";
    else
        qDebug() << "Database NOT connected\n";

    InitializeDb();
}

MainWindow::~MainWindow() {
    delete ui;
}


/*****************************************************************************
 * InitializeDb
 *____________________________________________________________________________
 * This method will initialize the database. It will find a "1" in the
 * database, then create another "1" for the current hour. It will then count
 * how many hours passed between the first 1 and the current 1. (countHrs)
 *****************************************************************************/
void MainWindow::InitializeDb() {
    QSqlQuery query(db);                                        //initial query
    QString curDayStr = QDate::currentDate().toString().mid(0,3);  //current day name (Mon, Tue...Sun)
    QTime curHour = QTime::currentTime();                       //current hour (12,13...23)
    prevHour = 0;
    countHrs = -1;

    //Gets current day as a number
    if (curDayStr == "Mon")
        curDay = 1;
    else if (curDayStr == "Tue")
        curDay = 2;
    else if (curDayStr == "Wed")
        curDay = 3;
    else if (curDayStr == "Thu")
        curDay = 4;
    else if (curDayStr == "Fri")
        curDay = 5;
    else if (curDayStr == "Sat")
        curDay = 6;
    else
        curDay = 7;

    //Searches for the ealier "1", then updates the hour to how many hours passed, the dayStr to ealier day,
    SearchDb();

    curTotalHours += curHour.hour();
    daysPassed = curDay-prevDay;
    hoursPassed = curTotalHours-prevHour;

    qDebug() << "Current Day: "  << curDay << "\n"
             << "Previous Day: " << prevDay << "\n"
             << "Current Total Hours: " << curTotalHours << "\n"
             << "Previous Total Hours: " << prevHour << "\n"
             << "Days Passed: " << daysPassed << "\n"
             << "Hours Passed: " << hoursPassed << "\n";

    //Removes 1 from ealier hour
    query.exec("UPDATE database SET '" + dayStr + "'=0 WHERE hour=" + QString::number(prevHour-countHrs));

    //Finds amount of hours passed between ealier hour and current hour (countHrs)
    countHrs = hoursPassed + 24*daysPassed;

    //If previous day is after current day, then count a week's worth of hours.
    if (daysPassed < 0)
        countHrs = 168+countHrs;

    qDebug() << "Hours Passed Since Last Update: " << countHrs;

    //Updates a cell from the database. Selects the current day, then to current hour, then sets cell to 1
    query.exec("UPDATE database SET '" + curDayStr + "'=1 WHERE hour=" + QString::number(curHour.hour()));
}


/*****************************************************************************
 * SearchDb
 *____________________________________________________________________________
 * This method will search the database for a "1" integer.
 *      hour = how many hours passed
 *      dayStr = ealier day
 *****************************************************************************/
void MainWindow::SearchDb() {
    QSqlQuery query(db);                                        //initial query

    //Checks for where "1" is in the database.
    query.prepare("SELECT * FROM database ORDER BY hour");

    //First checks for previous 1 (from ealier update). Once it has place of 1, then counts each hour until current hour.
    for (prevDay = 1; prevDay <= 7; prevDay++) {
        if(query.exec()) {
            while(query.next()) {\
                if (query.value(prevDay).toInt() == 1) {
                    qDebug() << "Found";

                    switch(prevDay) {
                        case 1 : dayStr = "Mon"; curTotalHours = 0; countHrs = 0;
                            break;
                        case 2 : dayStr = "Tue"; curTotalHours = 24; countHrs = 24;
                            break;
                        case 3 : dayStr = "Wed"; curTotalHours = 48; countHrs = 48;
                            break;
                        case 4 : dayStr = "Thu"; curTotalHours = 72; countHrs = 72;
                            break;
                        case 5 : dayStr = "Fri"; curTotalHours = 96; countHrs = 96;
                            break;
                        case 6 : dayStr = "Sat"; curTotalHours = 120; countHrs = 120;
                            break;
                        default: dayStr = "Sun"; curTotalHours = 144; countHrs = 144;
                            break;
                    }

                    return;
                }
                prevHour++;
            }
        }
    }
}

//H O M E   P A G E
void MainWindow::on_hb_view_clicked() {
    UpdateCalendarTable();
    ui->stackedWidget->setCurrentIndex(1);
}


//C A L E N D A R   P A G E
void MainWindow::UpdateCalendarTable() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM database ORDER BY hour");

    ui->ct_table->setRowCount(24);
    ui->ct_table->setColumnCount(8);

    ui->ct_table->setHorizontalHeaderItem(0, new QTableWidgetItem("Hour"));
    ui->ct_table->setHorizontalHeaderItem(1, new QTableWidgetItem("Monday"));
    ui->ct_table->setHorizontalHeaderItem(2, new QTableWidgetItem("Tuesday"));
    ui->ct_table->setHorizontalHeaderItem(3, new QTableWidgetItem("Wednesday"));
    ui->ct_table->setHorizontalHeaderItem(4, new QTableWidgetItem("Thursday"));
    ui->ct_table->setHorizontalHeaderItem(5, new QTableWidgetItem("Friday"));
    ui->ct_table->setHorizontalHeaderItem(6, new QTableWidgetItem("Saturday"));
    ui->ct_table->setHorizontalHeaderItem(7, new QTableWidgetItem("Sunday"));

    ui->ct_table->setItem(0, 0, new QTableWidgetItem("12 AM"));

    if(query.exec()) {
        for(int i = 0; i < 24; i++) {
            query.next();

            if (i < 12)
                ui->ct_table->setItem(i+1, 0, new QTableWidgetItem(QString::number(i+1) + " AM"));
            else
                ui->ct_table->setItem(i+1, 0, new QTableWidgetItem(QString::number(i-11) + " PM"));

            for (int j = 1; j <= 7; j++)
                ui->ct_table->setItem(i, j, new QTableWidgetItem(QString::number(query.value(j).toInt())));

            ui->ct_table->setVerticalHeaderItem(i, new QTableWidgetItem(""));
        }
    }

    ui->ct_table->resizeColumnsToContents();
}

void MainWindow::on_cb_back_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_cb_add_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}


//A D D   T A S K   P A G E
void MainWindow::on_ab_back_clicked() {
    UpdateCalendarTable();
    ui->stackedWidget->setCurrentIndex(1);
}


