#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void InitializeDb();
    void SearchDb();

    //HOME
    void on_hb_view_clicked();

    //CALENDAR
    void UpdateCalendarTable();
    void on_cb_back_clicked();
    void on_cb_add_clicked();

    //ADD TASK
    void on_ab_back_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QString dayStr;
    int curDay;
    int prevDay;
    int daysPassed;
    int prevHour;
    int hoursPassed;
    int curTotalHours;
    int countHrs;
};

#endif // MAINWINDOW_H
