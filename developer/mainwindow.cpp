#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

/*****************************************************************************
 * MainWindow
 *____________________________________________________________________________
 * This method will initialize the database. It also creates a timer that will
 * automatically update the database.
 *****************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Smart Calendar");
    isFree = true;

    //Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/database.sqlite");

    if(db.open())
        qDebug() << "Database connected\n";
    else
        qDebug() << "Database NOT connected\n";

    //Initialize database
    InitializeDb();

    //Initializes free hours combo boxes
    UpdateComboBox();

    //Updates (un)scheduled projects from database
    UpdateUnscheduledDb();
    UpdateScheduledDb();

    row = -1;
    col = -1;
    notScheduled = false;

    //Decrements remaining hours of the top project in the scheduled list using hoursPassed variable
    //When remaining time is 0, post message saying project is complete, then remove project from unscheduled list.
    //Also, remove project name from calendar up to current hour (if "Current" is on a project hour, then that hour is decremented)
    if (scheduledList.size() > 0) {
        QSqlQuery query(db);
        QMessageBox msgBox;

        for (int i = 0; i < countHrs; i++) {
            if (scheduledList.at(0).GetRemHours() > 0) {
                scheduledList[0].DecRemHours();
                query.exec("UPDATE scheduled SET left='" + QString::number(scheduledList.at(0).GetRemHours()) + "' WHERE name='" + scheduledList.at(0).GetName() + "'");
            }
            else {
                msgBox.setText("The " + scheduledList.at(0).GetName() + " project has been completed!");
                msgBox.exec();

                query.exec("DELETE FROM scheduled WHERE name='" + scheduledList.at(0).GetName() + "'");
                scheduledList.removeAt(0);
            }
        }
        UpdateCalendarTable();
    }

    //Creates a timer to auto-update InitializeDb function
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(InitializeDb()));
    timer->start(60000); //time specified in ms (60 seconds)
}

MainWindow::~MainWindow() {
    delete ui;
}


/*****************************************************************************
 * InitializeDb
 *____________________________________________________________________________
 * This method will initialize the database. It will find a "1" in the
 * database, then create another "1" for the current hour. It will then count
 * how many hours passed between the first 1 and the current 1. (hoursPassed)
 *****************************************************************************/
void MainWindow::InitializeDb() {
    QSqlQuery query(db);                                           //initial query
    curDayStr = QDate::currentDate().toString().mid(0,3);          //current day name (Mon, Tue...Sun)
    curHour = QTime::currentTime();                                //current hour (12,13...23)
    curTotalHours = 0;
    prevTotalHours = 0;
    hoursPassed = -1;

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

    //Checks if there is an 'X' in the table on the current hour
    UpdateCalendarTable();
    if (ui->ct_table->model()->data(ui->ct_table->model()->index(curHour.hour(),curDay)).toString() == "X" ||
        ui->ct_table->model()->data(ui->ct_table->model()->index(curHour.hour(),curDay)).toString() == "X/Current")
        isFree = false;

    //Searches for the ealier "Current", then updates the hour to how many hours passed, the dayStr to ealier day,
    SearchDb();

    curTotalHours += curHour.hour();

    //First time running program
    if (prevTotalHours == 168) {
        prevTotalHours = curTotalHours;
        prevDay = curDay;
    }

    daysPassed = curDay-prevDay;
    countHrs = curTotalHours-prevTotalHours;

    qDebug() << "Current Day: "  << curDay << "\n"
             << "Previous Day: " << prevDay << "\n"
             << "Current Total Hours: " << curTotalHours << "\n"
             << "Previous Total Hours: " << prevTotalHours << "\n"
             << "Days Passed: " << daysPassed << "\n"
             << "Hours Passed: " << countHrs << "\n";

    //Removes "Current" from ealier hour
    query.exec("UPDATE calendar SET '" + dayStr + "'='' WHERE hour=" + QString::number(prevTotalHours-hoursPassed+1));

    //Finds amount of hours passed between ealier hour and current hour (hoursPassed)
    hoursPassed = countHrs + 24*daysPassed;

    //If previous day is after current day, then count a week's worth of hours.
    if (daysPassed < 0)
        hoursPassed = 168+hoursPassed;

    countHrs = hoursPassed;

    qDebug() << "Hours Passed Since Last Update: " << hoursPassed;

    //Updates a cell from the database. Selects the current day, then to current hour, then sets cell to "Current"
    query.prepare("SELECT * FROM calendar ORDER BY hour");



if (ui->ct_table->model()->data(ui->ct_table->model()->index(curTotalHours,curDay)).toString() == "X")
            qDebug() << "testing5";

    if (isFree) {
        query.exec("UPDATE calendar SET '" + curDayStr + "'='Current' WHERE hour=" + QString::number(curHour.hour()+1));
    }
    else
        query.exec("UPDATE calendar SET '" + curDayStr + "'='X/Current' WHERE hour=" + QString::number(curHour.hour()+1));

    //Updates time in upper left corner of calendar page
    ui->ct_time->setText(QDateTime::currentDateTime().toString());

    SearchDb();
}


/*****************************************************************************
 * SearchDb
 *____________________________________________________________________________
 * This method will search the database for a "Current" string
 *      hour = how many hours passed
 *      dayStr = ealier day
 *****************************************************************************/
void MainWindow::SearchDb() {
    QSqlQuery query(db);        //initial query
    int count = 1;

    //Checks for where "Current" is in the database.
    query.prepare("SELECT * FROM calendar ORDER BY hour");

    //First checks for previous "Current" (from ealier update). Once it has place of "Current",
    //then counts each hour until current hour.
    for (prevDay = 1; prevDay <= 7; prevDay++) {
        if(query.exec()) {
            while(query.next()) {
                switch(prevDay) {
                    case 1 : dayStr = "Mon"; curTotalHours = 0; hoursPassed = 0;
                        break;
                    case 2 : dayStr = "Tue"; curTotalHours = 24; hoursPassed = 24;
                        break;
                    case 3 : dayStr = "Wed"; curTotalHours = 48; hoursPassed = 48;
                        break;
                    case 4 : dayStr = "Thu"; curTotalHours = 72; hoursPassed = 72;
                        break;
                    case 5 : dayStr = "Fri"; curTotalHours = 96; hoursPassed = 96;
                        break;
                    case 6 : dayStr = "Sat"; curTotalHours = 120; hoursPassed = 120;
                        break;
                    default: dayStr = "Sun"; curTotalHours = 144; hoursPassed = 144;
                        break;
                }
                if (query.value(prevDay).toString() == "Current" || query.value(prevDay).toString() == "X/Current" )
                    return;
                else if (query.value(prevDay).toString() != "" && query.value(prevDay).toString() != "X")
                    query.exec("UPDATE calendar SET '" + dayStr + "'='' WHERE hour=" + QString::number(count));

                if (count < 24)
                    count++;
                else
                    count = 1;

                prevTotalHours++;
            }
        }
    }
}



//H O M E   P A G E
void MainWindow::on_hb_view_clicked() {
    UpdateCalendarTable();
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_hb_exit_clicked() {
    QApplication::quit();
}



//C A L E N D A R   P A G E
/*****************************************************************************
 * UpdateCalendarTable
 *____________________________________________________________________________
 * This method update the calendar table with values from the database.
 *****************************************************************************/
void MainWindow::UpdateCalendarTable() {
    QSqlQuery query(db);

    query.prepare("SELECT * FROM calendar ORDER BY hour");

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
                ui->ct_table->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));

            ui->ct_table->setVerticalHeaderItem(i, new QTableWidgetItem(""));
        }
    }

    ui->ct_table->resizeColumnsToContents();

    UpdateUnscheduledTable();
    UpdateScheduledTable();
}


/*****************************************************************************
 * UpdateUnscheduledTable
 *____________________________________________________________________________
 * This method will update the unscheduled projects table with the name,
 * hours, and description of all the added projects.
 *****************************************************************************/
void MainWindow::UpdateUnscheduledTable() {
    ui->ct_unscheduled->setRowCount(unscheduledList.count());
    ui->ct_unscheduled->setColumnCount(3);

    ui->ct_unscheduled->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->ct_unscheduled->setHorizontalHeaderItem(1, new QTableWidgetItem("Hours"));
    ui->ct_unscheduled->setHorizontalHeaderItem(2, new QTableWidgetItem("Desc."));

    for (int i = 0; i < unscheduledList.count(); i++) {
        ui->ct_unscheduled->setItem(i, 0, new QTableWidgetItem(unscheduledList.at(i).GetName()));
        ui->ct_unscheduled->setItem(i, 1, new QTableWidgetItem(QString::number(unscheduledList.at(i).GetTotalHours())));
        ui->ct_unscheduled->setItem(i, 2, new QTableWidgetItem(unscheduledList.at(i).GetDesc()));
    }

    ui->ct_unscheduled->resizeColumnsToContents();

    //Whenever data is changed on this table, run function onDataChangedUnscheduled
    connect(ui->ct_unscheduled->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChangedUnscheduled(const QModelIndex&)));
}


/*****************************************************************************
 * UpdateScheduledTable
 *____________________________________________________________________________
 * This method will update the scheduled projects table with the name, hours,
 * and description of all the added projects.
 *****************************************************************************/
void MainWindow::UpdateScheduledTable() {
    ui->ct_scheduled->setRowCount(scheduledList.count());
    ui->ct_scheduled->setColumnCount(4);

    ui->ct_scheduled->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->ct_scheduled->setHorizontalHeaderItem(1, new QTableWidgetItem("Hours"));
    ui->ct_scheduled->setHorizontalHeaderItem(2, new QTableWidgetItem("Left"));
    ui->ct_scheduled->setHorizontalHeaderItem(3, new QTableWidgetItem("Desc."));

    for (int i = 0; i < scheduledList.count(); i++) {
        ui->ct_scheduled->setItem(i, 0, new QTableWidgetItem(scheduledList.at(i).GetName()));
        ui->ct_scheduled->setItem(i, 1, new QTableWidgetItem(QString::number(scheduledList.at(i).GetTotalHours())));
        ui->ct_scheduled->setItem(i, 2, new QTableWidgetItem(QString::number(scheduledList.at(i).GetRemHours())));
        ui->ct_scheduled->setItem(i, 3, new QTableWidgetItem(scheduledList.at(i).GetDesc()));
    }

    ui->ct_scheduled->resizeColumnsToContents();

    //Whenever data is changed on this table, run function onDataChangedScheduled
    connect(ui->ct_scheduled->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChangedScheduled(const QModelIndex&)));
}


/*****************************************************************************
 * UpdateUnscheduledDb
 *____________________________________________________________________________
 * This method will update the unscheduled projects table using values from
 * the database.
 *****************************************************************************/
void MainWindow::UpdateUnscheduledDb() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM unscheduled");

    if(query.exec()) {
        while(query.next()) {
            Project project(query.value(0).toString(), query.value(1).toInt(), query.value(2).toString());
            unscheduledList.append(project);
        }
    }
}


/*****************************************************************************
 * UpdateScheduledDb
 *____________________________________________________________________________
 * This method will update the scheduled projects table using values from
 * the database.
 *****************************************************************************/
void MainWindow::UpdateScheduledDb() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM scheduled");

    if(query.exec()) {
        while(query.next()) {
            Project project(query.value(0).toString(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toString());
            scheduledList.append(project);
        }
    }
}


/*****************************************************************************
 * on_ct_unscheduled_cellClicked
 *____________________________________________________________________________
 * This method will record the exact cell (row and column) that was clicked
 * on the unscheduled table.
 *****************************************************************************/
void MainWindow::on_ct_unscheduled_cellClicked(int row1, int col1) {
    row = row1;
    col = col1;
    notScheduled = true;
}


/*****************************************************************************
 * on_ct_scheduled_cellClicked
 *____________________________________________________________________________
 * This method will record the exact cell (row and column) that was clicked
 * on the scheduled table.
 *****************************************************************************/
void MainWindow::on_ct_scheduled_cellClicked(int row1, int col1) {
    row = row1;
    col = col1;
    notScheduled = false;
}


/*****************************************************************************
 * onDataChangedUnscheduled
 *____________________________________________________________________________
 * This method, upon detecting data that was changed, will update the database
 * with the new value in the unscheduled table.
 *****************************************************************************/
void MainWindow::onDataChangedUnscheduled(const QModelIndex& value) {
    QMessageBox msgBox;
    QString dataStr = value.data(Qt::DisplayRole).toString();
    int dataInt = value.data(Qt::DisplayRole).toInt();

    if (row != -1) {
        QSqlQuery query(db);

        switch(col) {
            case 0 : if (IsUnique(dataStr,unscheduledList, scheduledList)) {
                        query.exec("UPDATE unscheduled SET name='" + dataStr + "' WHERE name='" + unscheduledList.at(row).GetName() + "'");
                        unscheduledList[row].SetName(dataStr);
                     }
                     else {
                        msgBox.setText("ERROR - Name must be unique!");
                        msgBox.exec();
                     }
                break;
            case 1 : {
                     if (dataStr == "0") {
                         msgBox.setText("ERROR - Hours must be at least 1!");
                         msgBox.exec();
                     }
                     else if (!IsNumber(dataStr) || dataStr == "") {
                         msgBox.setText("ERROR - Hours must be numerical and positive!");
                         msgBox.exec();
                     }
                     else {
                         unscheduledList[row].SetTotalHours(dataInt);
                         query.exec("UPDATE unscheduled SET hours='" + QString::number(dataInt) + "' WHERE name='" + unscheduledList.at(row).GetName() + "'");
                         unscheduledList[row].SetRemHours(dataInt);
                     }}
                break;
            case 2 : unscheduledList[row].SetDesc(dataStr);
                     query.exec("UPDATE unscheduled SET desc='" + dataStr + "' WHERE name='" + unscheduledList.at(row).GetName() + "'");
                break;
            default :
                break;
        };
        row = -1;
    }
}


/*****************************************************************************
 * onDataChangedScheduled
 *____________________________________________________________________________
 * This method, upon detecting data that was changed, will update the database
 * with the new value in the scheduled table.
 *****************************************************************************/
void MainWindow::onDataChangedScheduled(const QModelIndex& value) {
    QMessageBox msgBox;
    QString dataStr = value.data(Qt::DisplayRole).toString();
    int dataInt = value.data(Qt::DisplayRole).toInt();

    if (row != -1) {
        QSqlQuery query(db);

        switch(col) {
            case 0 : if (IsUnique(dataStr, unscheduledList, scheduledList)) {
                            query.exec("UPDATE scheduled SET name='" + dataStr + "' WHERE name='" + scheduledList.at(row).GetName() + "'");
                            scheduledList[row].SetName(dataStr);
                        }
                        else {
                           msgBox.setText("ERROR - Name must be unique!");
                           msgBox.exec();
                        }
                break;
            case 1 : {if (dataStr == "0") {
                         msgBox.setText("ERROR - Total hours must be at least 1!");
                         msgBox.exec();
                     }
                     else if (!IsNumber(dataStr) || dataStr == "") {
                         msgBox.setText("ERROR - Total hours must be numerical and positive!");
                         msgBox.exec();
                     }
                     else if (dataInt < scheduledList[row].GetRemHours()) {
                         msgBox.setText("ERROR - Total hours must be greater than or equal to remaining hours!");
                         msgBox.exec();
                     }
                     else {
                         scheduledList[row].SetTotalHours(dataInt);
                         query.exec("UPDATE scheduled SET hours='" + QString::number(dataInt) + "' WHERE name='" + scheduledList.at(row).GetName() + "'");
                     }}
                break;
            case 2 : {
                 if (dataStr == "0") {
                     msgBox.setText("ERROR - Remaining hours must be at least 1!");
                     msgBox.exec();
                 }
                 else if (!IsNumber(dataStr) || dataStr == "") {
                     msgBox.setText("ERROR - Remaining hours must be numerical and positive!");
                     msgBox.exec();
                 }
                 else if (dataInt > scheduledList[row].GetTotalHours()) {
                     msgBox.setText("ERROR - Remaining hours must be less than or equal to total hours!");
                     msgBox.exec();
                 }
                 else {
                     scheduledList[row].SetRemHours(dataInt);
                     query.exec("UPDATE scheduled SET left='" + QString::number(dataInt) + "' WHERE name='" + scheduledList.at(row).GetName() + "'");
                 }}
                break;
            case 3 : scheduledList[row].SetDesc(dataStr);
                     query.exec("UPDATE scheduled SET desc='" + dataStr + "' WHERE name='" + scheduledList.at(row).GetName() + "'");
                break;
            default :
                break;
        };
        row = -1;
    }
}


void MainWindow::on_cb_set_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_cb_add_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
}


/*****************************************************************************
 * on_cb_schedule_clicked
 *____________________________________________________________________________
 * This method will activate when the user clicks an unscheduled project on
 * the unscheduled project list and clicks the "Schedule" button. This will
 * transfer the selected project into the scheduled project list. From there,
 * it will automatically schedule the project onto the calendar by looking at
 * the time remaining on the project.
 *****************************************************************************/
void MainWindow::on_cb_schedule_clicked() { 
    QMessageBox msgBox;

    if (row >= 0 && notScheduled) {
        disconnect(ui->ct_unscheduled->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChangedUnscheduled(const QModelIndex&)));
        disconnect(ui->ct_scheduled->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChangedScheduled(const QModelIndex&)));

        QSqlQuery query(db);
        query.exec("DELETE FROM unscheduled WHERE name='" + unscheduledList.at(row).GetName() + "'");
        query.exec("INSERT INTO scheduled (NAME, HOURS, LEFT, DESC) "
                   "VALUES ('" + unscheduledList.at(row).GetName() +
                   "', '" + QString::number(unscheduledList.at(row).GetTotalHours()) +
                   "', '" + QString::number(unscheduledList.at(row).GetRemHours()) +
                   "', '" + unscheduledList.at(row).GetDesc() + "')");

        scheduledList.append(unscheduledList.at(row));
        unscheduledList.removeAt(row);
        row--;

        //Updates calendar database with the project name for the # of the project's hours
        QString dayTemp = curDayStr;                    //string of day
        int max = scheduledList.last().GetRemHours();   //remaining time on project
        int current = curHour.hour()+1;                 //current hour
        int tempDay = curDay;                           //current day (int)

        for (int i = 0; i < max; i++) {
            if (current+i <= 24) {
                if (ui->ct_table->model()->data(ui->ct_table->model()->index(current+i,tempDay)).toString() == "") {
                    query.exec("UPDATE calendar SET '" + dayTemp + "'='" + scheduledList.last().GetName() + "' WHERE hour=" + QString::number(current+i+1));
                }
                else
                    max++;
            }
            else {
                if (dayTemp == "Mon")
                    dayTemp = "Tue";
                else if (dayTemp == "Tue")
                    dayTemp = "Wed";
                else if (dayTemp == "Wed")
                    dayTemp = "Thu";
                else if (dayTemp == "Thu")
                    dayTemp = "Fri";
                else if (dayTemp == "Fri")
                    dayTemp = "Sat";
                else if (dayTemp == "Sat")
                    dayTemp = "Sun";
                else {
                    dayTemp = "Mon";
                    tempDay = 0;
                }

                tempDay++;
                max -= i-2;
                current = -1;
                i = 0;
            }
        }

        UpdateCalendarTable();
    }
    else {
        msgBox.setText("ERROR - Must select an unscheduled project!");
        msgBox.exec();
    }
}


/*****************************************************************************
 * on_cb_deleteUn_clicked
 *____________________________________________________________________________
 * This method will delete a project from the unscheduled project list from
 * the database.
 *****************************************************************************/
void MainWindow::on_cb_deleteUn_clicked() {
    QMessageBox msgBox;

    if (row >= 0) {
        QSqlQuery query(db);
        query.exec("DELETE FROM unscheduled WHERE name='" + unscheduledList.at(row).GetName() + "'");

        unscheduledList.removeAt(row);
        row--;

        UpdateCalendarTable();
    }
    else {
        msgBox.setText("ERROR - Must select an unscheduled project!");
        msgBox.exec();
    }
}


/*****************************************************************************
 * on_cb_deleteSc_clicked
 *____________________________________________________________________________
 * This method will delete a project from the scheduled project list from
 * the database.
 *****************************************************************************/
void MainWindow::on_cb_deleteSc_clicked() {
    QMessageBox msgBox;

    if (row >= 0) {
        QSqlQuery query(db);
        query.exec("DELETE FROM scheduled WHERE name='" + scheduledList.at(row).GetName() + "'");

        scheduledList.removeAt(row);
        row--;
        col = -1;

        UpdateCalendarTable();
    }
    else {
        msgBox.setText("ERROR - Must select an scheduled project!");
        msgBox.exec();
    }
}


void MainWindow::on_cb_back_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}



//S E T   H O U R S   P A G E
/*****************************************************************************
 * UpdateComboBox
 *____________________________________________________________________________
 * This method will update the combo boxes with the hours of the day.
 *****************************************************************************/
void MainWindow::UpdateComboBox() {
    QStringList hourList;
    hourList << "None" << "12 AM" << "1 AM" << "2 AM" << "3 AM" << "4 AM" << "5 AM" << "6 AM" << "7 AM" << "8 AM"
             << "9 AM" << "10 AM" << "11 AM" << "12 PM" << "1 PM" << "2 PM" << "3 PM" << "4 PM" << "5 PM"
             << "6 PM" << "7 PM" << "8 PM" << "9 PM" << "10 PM " << "11 PM";
    ui->sc_monFrom->insertItems(0,hourList);
    ui->sc_tueFrom->insertItems(0,hourList);
    ui->sc_wedFrom->insertItems(0,hourList);
    ui->sc_thuFrom->insertItems(0,hourList);
    ui->sc_friFrom->insertItems(0,hourList);
    ui->sc_satFrom->insertItems(0,hourList);
    ui->sc_sunFrom->insertItems(0,hourList);

    ui->sc_monTo->insertItems(0,hourList);
    ui->sc_tueTo->insertItems(0,hourList);
    ui->sc_wedTo->insertItems(0,hourList);
    ui->sc_thuTo->insertItems(0,hourList);
    ui->sc_friTo->insertItems(0,hourList);
    ui->sc_satTo->insertItems(0,hourList);
    ui->sc_sunTo->insertItems(0,hourList);
}


/*****************************************************************************
 * CheckFreeHours
 *____________________________________________________________________________
 * This method will check the free hours combo boxe and return whether it
 * passed the checks or failed.
 *      1: If either "to" or "from" is denoted "None", and if one has a time,
 *         then post error.
 *      2: If the "to" hour is higher than the "from" time, then post error.
 *****************************************************************************/
bool MainWindow::CheckFreeHours(QComboBox* from, QComboBox* to, QString comboDay) {
    QMessageBox msgBox;

    if ((to->itemText(from->currentIndex()) == "None"    &&
         to->itemText(to->currentIndex()) != "None") ||
        (to->itemText(to->currentIndex()) == "None"  &&
         to->itemText(from->currentIndex()) != "None")) {
        msgBox.setText("ERROR - Hours must be either all \"None\" or all hours for " + comboDay + "!");
        msgBox.exec();
    }
    else if (from->currentIndex() > to->currentIndex()) {
        msgBox.setText("ERROR - \"From\" hour must be less than \"To\" hour for " + comboDay + "!");
        msgBox.exec();
    }
    else
        return 1;
    return 0;
}


/*****************************************************************************
 * UpdateFreeDatabase
 *____________________________________________________________________________
 * This method will update calendar database by putting "Open" for all hours
 * free. First, start with column Monday (0), then start at row at index of
 * from hour free. Go down column until you hit to hour free, then go to next
 * column.
 *****************************************************************************/
void MainWindow::UpdateFreeDatabase(QComboBox* from, QComboBox* to, QString day, int dayNum) {
    QSqlQuery query(db);
    query.exec("UPDATE freeTime SET '" + day + "'='" + from->itemText(from->currentIndex()) + "' WHERE FROM_TO=1");
    query.exec("UPDATE freeTime SET '" + day + "'='" + to->itemText(to->currentIndex()) + "' WHERE FROM_TO=2");

    //Deletes all previous X's
    for (int i = 1; i <= 24; i++) {
        if (ui->ct_table->model()->data(ui->ct_table->model()->index(i-1,dayNum)).toString() == "X")
            query.exec("UPDATE calendar SET '" + day + "'='' WHERE hour=" + QString::number(i));
        else if (ui->ct_table->model()->data(ui->ct_table->model()->index(i-1,dayNum)).toString() == "X/Current")
            query.exec("UPDATE calendar SET '" + day + "'='Current' WHERE hour=" + QString::number(i));
    }

    //Updates calendar database with "X" on not free time
    if (from->currentIndex() != to->currentIndex()) {
        for (int count = 1; count < from->currentIndex(); count++) {
            if (ui->ct_table->model()->data(ui->ct_table->model()->index(count-1,dayNum)).toString() != "Current") {
                query.exec("UPDATE calendar SET '" + day + "'='X' WHERE hour=" + QString::number(count));
            }
            else if (ui->ct_table->model()->data(ui->ct_table->model()->index(count-1,dayNum)).toString() == "Current") {
                query.exec("UPDATE calendar SET '" + day + "'='X/Current' WHERE hour=" + QString::number(count));
                isFree = false;
            }
        }

        for (int count = to->currentIndex()+1; count <= 24; count++) {
            if (ui->ct_table->model()->data(ui->ct_table->model()->index(count-1,dayNum)).toString() != "Current") {
                query.exec("UPDATE calendar SET '" + day + "'='X' WHERE hour=" + QString::number(count));
            }
            else if (ui->ct_table->model()->data(ui->ct_table->model()->index(count-1,dayNum)).toString() == "Current") {
                query.exec("UPDATE calendar SET '" + day + "'='X/Current' WHERE hour=" + QString::number(count));
                isFree = false;
            }
        }
    }
}


/*****************************************************************************
 * on_sb_apply_clicked
 *____________________________________________________________________________
 * This method, when the apply button is clicked, will first error check the
 * hours for errors. It will then update the user's free time on a seperate
 * database.
 *****************************************************************************/
void MainWindow::on_sb_apply_clicked() {
    isFree = true;
    if (CheckFreeHours(ui->sc_monFrom, ui->sc_monTo, "Monday")    &&
        CheckFreeHours(ui->sc_tueFrom, ui->sc_tueTo, "Tuesday")   &&
        CheckFreeHours(ui->sc_wedFrom, ui->sc_wedTo, "Wednesday") &&
        CheckFreeHours(ui->sc_thuFrom, ui->sc_thuTo, "Thursday")  &&
        CheckFreeHours(ui->sc_friFrom, ui->sc_friTo, "Friday")    &&
        CheckFreeHours(ui->sc_satFrom, ui->sc_satTo, "Saturday")  &&
        CheckFreeHours(ui->sc_sunFrom, ui->sc_sunTo, "Sunday")) {

        //Updating
        UpdateFreeDatabase(ui->sc_monFrom, ui->sc_monTo, "MON", 1);
        UpdateFreeDatabase(ui->sc_tueFrom, ui->sc_tueTo, "TUE", 2);
        UpdateFreeDatabase(ui->sc_wedFrom, ui->sc_wedTo, "WED", 3);
        UpdateFreeDatabase(ui->sc_thuFrom, ui->sc_thuTo, "THU", 4);
        UpdateFreeDatabase(ui->sc_friFrom, ui->sc_friTo, "FRI", 5);
        UpdateFreeDatabase(ui->sc_satFrom, ui->sc_satTo, "SAT", 6);
        UpdateFreeDatabase(ui->sc_sunFrom, ui->sc_sunTo, "SUN", 7);

        //Initialize database
        InitializeDb();

        UpdateCalendarTable();
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_sb_back_clicked() {
    UpdateCalendarTable();
    ui->stackedWidget->setCurrentIndex(1);
}


// A D D   H O U R S   P A G E
/*****************************************************************************
 * IsNumber
 *____________________________________________________________________________
 * This method checks of string is a positive whole number.
 *****************************************************************************/
bool MainWindow::IsNumber(const QString& str) {
    QRegExp re("\\d*");
    return re.exactMatch(str);
}


/*****************************************************************************
 * IsUnique
 *____________________________________________________________________________
 * This method checks to see if a string is unique.
 *****************************************************************************/
bool MainWindow::IsUnique(const QString& str, const QList<Project>& list1, const QList<Project>& list2) {
    bool unique = true;

    for (int i = 0; i < list1.length(); i++)
        if (str == list1.at(i).GetName())
            unique = false;

    for (int i = 0; i < list2.length(); i++)
        if (str == list2.at(i).GetName())
            unique = false;

    return unique;
}


/*****************************************************************************
 * on_ab_add_clicked
 *____________________________________________________________________________
 * This method, upon clicking the "Add" button, will first check the number of
 * hours to see if it is indeed numerical and positive. If false, then create
 * an error message. If true, then create a project object, insert the values
 * onto the object, then put that object onto the project list.
 *****************************************************************************/
void MainWindow::on_ab_add_clicked() {
    QMessageBox msgBox;
    QString setName = ui->al_name->text();
    QString setHours = ui->al_hours->text();
    QString setDesc = ui->al_desc->text();

    //Error checks name (must be unique)
    if (IsUnique(setName, unscheduledList, scheduledList)) {
        //Error checks hours (must be numerical above 0)
        if (setHours == "0") {
            msgBox.setText("ERROR - Hours must be at least 1!");
            msgBox.exec();
        }
        else if (!IsNumber(setHours) || setHours == "") {
            msgBox.setText("ERROR - Hours must be numerical and positive!");
            msgBox.exec();
        }
        else {
            Project project(setName, setHours.toInt(), setDesc);
            unscheduledList.append(project);

            QSqlQuery query(db);
            query.exec("INSERT INTO unscheduled (NAME, HOURS, DESC) "
                       "VALUES ('" + setName + "', '" + setHours + "', '" + setDesc + "')");

            col = -1;

            UpdateCalendarTable();
            ui->stackedWidget->setCurrentIndex(1);
        }
    }
    else {
        msgBox.setText("ERROR - Name must be unique!");
        msgBox.exec();
    }
}


void MainWindow::on_ab_back_clicked() {
    UpdateCalendarTable();
    ui->stackedWidget->setCurrentIndex(1);
}

