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

    row = -1;

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
    QString curDayStr = QDate::currentDate().toString().mid(0,3);  //current day name (Mon, Tue...Sun)
    QTime curHour = QTime::currentTime();                          //current hour (12,13...23)
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

    qDebug() << "Hours Passed Since Last Update: " << hoursPassed;

    //Updates a cell from the database. Selects the current day, then to current hour, then sets cell to 1
    query.exec("UPDATE calendar SET '" + curDayStr + "'='Current' WHERE hour=" + QString::number(curHour.hour()+1));

    //Updates time in upper left corner of calendar page
    ui->ct_time->setText(QDateTime::currentDateTime().toString());

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

    //Checks for where "Current" is in the database.
    query.prepare("SELECT * FROM calendar ORDER BY hour");

    //First checks for previous "Current" (from ealier update). Once it has place of "Current",
    //then counts each hour until current hour.
    for (prevDay = 1; prevDay <= 7; prevDay++) {
        if(query.exec()) {
            while(query.next()) {\
                if (query.value(prevDay).toString() == "Current") {
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

                    return;
                }
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

    connect(ui->ct_unscheduled, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onUnscheduledClicked(const QModelIndex &)));
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
        qDebug() << scheduledList.at(i).GetName();
        ui->ct_scheduled->setItem(i, 0, new QTableWidgetItem(scheduledList.at(i).GetName()));
        ui->ct_scheduled->setItem(i, 1, new QTableWidgetItem(QString::number(scheduledList.at(i).GetTotalHours())));
        ui->ct_scheduled->setItem(i, 2, new QTableWidgetItem(QString::number(scheduledList.at(i).GetRemHours())));
        ui->ct_scheduled->setItem(i, 3, new QTableWidgetItem(scheduledList.at(i).GetDesc()));
    }

    ui->ct_scheduled->resizeColumnsToContents();
}


void MainWindow::onUnscheduledClicked(const QModelIndex& value) {
    row = value.row();
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

    if (row >= 0) {
        QSqlQuery query(db);
        query.exec("DELETE FROM unscheduled WHERE priority=" + QString::number(row+1));
        query.exec("INSERT INTO scheduled (NAME, HOURS, LEFT, DESC) "
                   "VALUES ('" + unscheduledList.at(row).GetName() +
                   "', '" + QString::number(unscheduledList.at(row).GetTotalHours()) +
                   "', '" + QString::number(unscheduledList.at(row).GetRemHours()) +
                   "', '" + unscheduledList.at(row).GetDesc() + "')");

        scheduledList.append(unscheduledList.at(row));
        unscheduledList.removeAt(row);
        row--;

        UpdateCalendarTable();
    }
    else {
        msgBox.setText("ERROR - Must select an unscheduled project!");
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
void MainWindow::UpdateFreeDatabase(QComboBox* from, QComboBox* to, QString day) {
    QSqlQuery query(db);
    query.exec("UPDATE freeTime SET '" + day + "'='" + from->itemText(from->currentIndex()) + "' WHERE FROM_TO=1");
    query.exec("UPDATE freeTime SET '" + day + "'='" + to->itemText(to->currentIndex()) + "' WHERE FROM_TO=2");

    //Updates calendar database with "Open"
    if (from->currentIndex() != to->currentIndex()) {
        for (int count = from->currentIndex(); count <= to->currentIndex(); count++) {
            query.exec("UPDATE calendar SET '" + day + "'='OPEN' WHERE hour=" + QString::number(count));
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
    if (CheckFreeHours(ui->sc_monFrom, ui->sc_monTo, "Monday")    &&
        CheckFreeHours(ui->sc_tueFrom, ui->sc_tueTo, "Tuesday")   &&
        CheckFreeHours(ui->sc_wedFrom, ui->sc_wedTo, "Wednesday") &&
        CheckFreeHours(ui->sc_thuFrom, ui->sc_thuTo, "Thursday")  &&
        CheckFreeHours(ui->sc_friFrom, ui->sc_friTo, "Friday")    &&
        CheckFreeHours(ui->sc_satFrom, ui->sc_satTo, "Saturday")  &&
        CheckFreeHours(ui->sc_sunFrom, ui->sc_sunTo, "Sunday")) {

        //Updating
        UpdateFreeDatabase(ui->sc_monFrom, ui->sc_monTo, "MON");
        UpdateFreeDatabase(ui->sc_tueFrom, ui->sc_tueTo, "TUE");
        UpdateFreeDatabase(ui->sc_wedFrom, ui->sc_wedTo, "WED");
        UpdateFreeDatabase(ui->sc_thuFrom, ui->sc_thuTo, "THU");
        UpdateFreeDatabase(ui->sc_friFrom, ui->sc_friTo, "FRI");
        UpdateFreeDatabase(ui->sc_satFrom, ui->sc_satTo, "SAT");
        UpdateFreeDatabase(ui->sc_sunFrom, ui->sc_sunTo, "SUN");

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
 * isNumber
 *____________________________________________________________________________
 * This method checks of string is a positive whole number.
 *****************************************************************************/
bool MainWindow::isNumber(const QString& str) {
    QRegExp re("\\d*");
    return re.exactMatch(str);
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

    if (setHours == "0") {
        msgBox.setText("ERROR - Hours should be at least 1!");
        msgBox.exec();
    }
    else if (!isNumber(setHours) || setHours == "") {
        msgBox.setText("ERROR - Hours should be numerical and positive!");
        msgBox.exec();
    }
    else {
        Project project(setName, setDesc, setHours.toInt());
        unscheduledList.append(project);

        QSqlQuery query(db);
        query.exec("INSERT INTO unscheduled (NAME, HOURS, DESC) "
                   "VALUES ('" + setName + "', '" + setHours + "', '" + setDesc + "')");

        UpdateCalendarTable();
        ui->stackedWidget->setCurrentIndex(1);
    }
}


void MainWindow::on_ab_back_clicked() {
    UpdateCalendarTable();
    ui->stackedWidget->setCurrentIndex(1);
}

