#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Database/database.sqlite");

    if(db.open())
        qDebug() << "Database connected\n";
    else
        qDebug() << "Database NOT connected\n";

    InitializeCalendar();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::InitializeCalendar() {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM database ORDER BY HOUR");

    if(query.exec()) {
        while(query.next()) {
            qDebug() << query.value(0).toInt();
            qDebug() << query.value(1).toInt();
            qDebug() << query.value(2).toInt();
            qDebug() << query.value(3).toInt();
            qDebug() << query.value(4).toInt();
            qDebug() << query.value(5).toInt();
            qDebug() << query.value(6).toInt();
            qDebug() << query.value(7).toInt();
            qDebug() << query.value(8).toInt();
            qDebug() << query.value(9).toInt();
            qDebug() << query.value(10).toInt();
            qDebug() << query.value(11).toInt();
            qDebug() << query.value(12).toInt();
            qDebug() << query.value(13).toInt();
            qDebug() << query.value(14).toInt();
            qDebug() << query.value(15).toInt();
            qDebug() << query.value(16).toInt();
            qDebug() << query.value(17).toInt();
            qDebug() << query.value(18).toInt();
            qDebug() << query.value(19).toInt();
            qDebug() << query.value(20).toInt();
            qDebug() << query.value(21).toInt();
            qDebug() << query.value(22).toInt();
            qDebug() << query.value(23).toInt();
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


