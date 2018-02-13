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
    QString curDay = QDate::currentDate().toString().mid(0,3);  //current day name (Mon, Tue...Sun)
    QTime curHour = QTime::currentTime();                       //current hour (12,13...23)
    hour = 0;
    countHrs = -1;

    //Searches for the ealier "1", then updates the hour to how many hours passed, the dayStr to ealier day,
    SearchDb();

    qDebug() << day << " - " << hour << " - " << dayStr << " - " << countHrs << " - " << (hour-countHrs);

    //Removes 1 from ealier hour
    query.exec("UPDATE database SET '" + dayStr + "'=0 WHERE hour=" + QString::number(hour-countHrs));

    //Finds amount of hours passed between ealier hour and current hour (countHrs)
    if (countHrs != -1)
        countHrs += curHour.hour() - hour;
    //If countHrs is -1, then that means program is running for first time.
    else
        countHrs = 0;

    qDebug() << "Hours Passed Since Last Update: " << countHrs;

    //Updates a cell from the database. Selects the current day, then to current hour, then sets cell to 1
    query.exec("UPDATE database SET '" + curDay + "'=1 WHERE hour=" + QString::number(curHour.hour()));
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
    for (day = 1; day <= 7; day++) {
        qDebug() << "\nNEXT DAY\n";
        if(query.exec()) {
            while(query.next()) {
                qDebug() << query.value(day).toInt();
                if (query.value(day).toInt() == 1) {
                    qDebug() << "Found";

                    switch(day) {
                        case 1 : dayStr = "Mon"; countHrs = 0;
                            break;
                        case 2 : dayStr = "Tue"; countHrs = 24;
                            break;
                        case 3 : dayStr = "Wed"; countHrs = 48;
                            break;
                        case 4 : dayStr = "Thu"; countHrs = 72;
                            break;
                        case 5 : dayStr = "Fri"; countHrs = 96;
                            break;
                        case 6 : dayStr = "Sat"; countHrs = 120;
                            break;
                        default: dayStr = "Sun"; countHrs = 144;
                            break;
                    }
                    return;
                }
                hour++;
            }
        }
    }
}

//H O M E   P A G E
void MainWindow::on_hb_view_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}


//C A L E N D A R   P A G E
void MainWindow::on_cb_back_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_cb_add_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}


//A D D   T A S K   P A G E
void MainWindow::on_ab_back_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
}


