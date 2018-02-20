#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void InitializeDb();                //Initialize database
        void SearchDb();                    //Search the database

        //HOME
        void on_hb_view_clicked();      //Home page: button view calendar clicked

        //CALENDAR
        void UpdateCalendarTable();     //Update calendar with current hour
        void on_cb_back_clicked();      //Calendar page: button back clicked
        void on_cb_add_clicked();       //Calendar page: button add clicked

        //ADD TASK
        void on_ab_back_clicked();      //Add task page: button back clicked

    private:
        Ui::MainWindow *ui;
        QSqlDatabase db;                //Database
        QTimer *timer;                  //time to auto-update
        QString dayStr;                 //String of day: "Mon", "Tue", etc.
        int countHrs;                   //Used in calculation for counting hours
        int curDay;                     //Current day int: 0=Mon, 1-Tue, etc.
        int prevDay;                    //Previous day int: 0=Mon, 1-Tue, etc.
        int curTotalHours;              //Total hours currently from start of week
        int prevTotalHours;             //Total hours of previous update from start of week
        int daysPassed;                 //Days passed between previous update and now
        int hoursPassed;                //Hours passed between previous update and now
};

#endif // MAINWINDOW_H
