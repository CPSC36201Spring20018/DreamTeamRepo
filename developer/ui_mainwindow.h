/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *home;
    QPushButton *hb_view;
    QTextEdit *textEdit;
    QPushButton *hb_exit;
    QWidget *calendar;
    QPushButton *cb_add;
    QTableWidget *ct_table;
    QTextBrowser *ct_time;
    QLabel *label;
    QPushButton *cb_set;
    QLabel *label_29;
    QTableWidget *ct_scheduled;
    QPushButton *cb_schedule;
    QPushButton *cb_back;
    QLabel *label_30;
    QTableWidget *ct_unscheduled;
    QPushButton *cb_deleteUn;
    QPushButton *cb_deleteSc;
    QWidget *set;
    QPushButton *sb_back;
    QLabel *sc_label1;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_24;
    QLabel *label_3;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_20;
    QLabel *label_23;
    QLabel *label_22;
    QComboBox *sc_monFrom;
    QLabel *label_18;
    QComboBox *sc_satTo;
    QComboBox *sc_satFrom;
    QComboBox *sc_tueFrom;
    QComboBox *sc_wedFrom;
    QComboBox *sc_sunFrom;
    QComboBox *sc_wedTo;
    QComboBox *sc_thuTo;
    QLabel *label_2;
    QComboBox *sc_thuFrom;
    QComboBox *sc_sunTo;
    QComboBox *sc_tueTo;
    QComboBox *sc_friFrom;
    QLabel *label_25;
    QComboBox *sc_monTo;
    QComboBox *sc_friTo;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_15;
    QLabel *label_14;
    QLabel *label_17;
    QLabel *label_16;
    QPushButton *sb_apply;
    QWidget *add;
    QLabel *label_7;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_26;
    QLabel *label_27;
    QLineEdit *al_name;
    QLineEdit *al_desc;
    QLineEdit *al_hours;
    QLabel *label_28;
    QPushButton *ab_back;
    QPushButton *ab_add;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(950, 470);
        MainWindow->setStyleSheet(QLatin1String("QToolTip\n"
"{\n"
"     border: 1px solid black;\n"
"     background-color: #ffa02f;\n"
"     padding: 1px;\n"
"     border-radius: 3px;\n"
"     opacity: 100;\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QWidget:item:hover\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #ca0619);\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:item:selected\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QMenuBar::item\n"
"{\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected\n"
"{\n"
"    background: transparent;\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QMenuBar::item:pressed\n"
"{\n"
"    background: #444;\n"
"    border: 1px solid #000;\n"
"    background-color: QLinearGradient(\n"
"        x1:0, y1:0,\n"
"        x2:0, y2:1,\n"
"        stop:1 #212121,\n"
"        stop:0.4 #343434/*,\n"
"        stop:0.2 #3"
                        "43434,\n"
"        stop:0.1 #ffaa00*/\n"
"    );\n"
"    margin-bottom:-1px;\n"
"    padding-bottom:1px;\n"
"}\n"
"\n"
"QMenu\n"
"{\n"
"    border: 1px solid #000;\n"
"}\n"
"\n"
"QMenu::item\n"
"{\n"
"    padding: 2px 20px 2px 20px;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"    color: #000000;\n"
"}\n"
"\n"
"QWidget:disabled\n"
"{\n"
"    color: #404040;\n"
"    background-color: #323232;\n"
"}\n"
"\n"
"QAbstractItemView\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0.1 #646464, stop: 1 #5d5d5d);\n"
"}\n"
"\n"
"QWidget:focus\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4d4d4d, stop: 0 #646464, stop: 1 #5d5d5d);\n"
"    padding: 1px;\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"    color: #b1b1b1;\n"
""
                        "    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-width: 1px;\n"
"    border-color: #1e1e1e;\n"
"    border-style: solid;\n"
"    border-radius: 6;\n"
"    padding: 3px;\n"
"    font-size: 12px;\n"
"    padding-left: 5px;\n"
"    padding-right: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"    selection-background-color: #ffaa00;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #565656, stop: 0.1 #525252, stop: 0.5 #4e4e4e, stop: 0.9 #4a4a4a, stop: 1 #464646);\n"
"    border-style: solid;\n"
"    border: 1px solid #1e1e1e;\n"
"    border-radius: 5;\n"
"}\n"
"\n"
"QComboBox:hover,QPushButton:hover\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0,"
                        " y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"\n"
"QComboBox:on\n"
"{\n"
"    padding-top: 3px;\n"
"    padding-left: 4px;\n"
"    background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #2d2d2d, stop: 0.1 #2b2b2b, stop: 0.5 #292929, stop: 0.9 #282828, stop: 1 #252525);\n"
"    selection-background-color: #ffaa00;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView\n"
"{\n"
"    border: 2px solid darkgray;\n"
"    selection-background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"\n"
"QGroupBox:focus\n"
"{\n"
"border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QTextEdit:focus\n"
"{\n"
"    border: 2px solid QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"     border: 1px solid #222222;\n"
"     background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848"
                        ");\n"
"     height: 7px;\n"
"     margin: 0px 16px 0 16px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"      subcontrol-position: right;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      width: 14px;\n"
"     subcontrol-position: left;\n"
"     subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::right-arrow:horizontal, QScrollBar::left-arrow:horizontal\n"
"{\n"
"      border"
                        ": 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QScrollBar:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0.0 #121212, stop: 0.2 #282828, stop: 1 #484848);\n"
"      width: 7px;\n"
"      margin: 16px 0 16px 0;\n"
"      border: 1px solid #222222;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical\n"
"{\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 0.5 #d7801a, stop: 1 #ffa02f);\n"
"      min-height: 20px;\n"
"      border-radius: 2px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffa02f, stop: 1 #d7801a);\n"
"      height: 14px;\n"
"      subcontrol-position: bottom;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
""
                        "QScrollBar::sub-line:vertical\n"
"{\n"
"      border: 1px solid #1b1b19;\n"
"      border-radius: 2px;\n"
"      background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #d7801a, stop: 1 #ffa02f);\n"
"      height: 14px;\n"
"      subcontrol-position: top;\n"
"      subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical\n"
"{\n"
"      border: 1px solid black;\n"
"      width: 1px;\n"
"      height: 1px;\n"
"      background: white;\n"
"}\n"
"\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical\n"
"{\n"
"      background: none;\n"
"}\n"
"\n"
"QTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QPlainTextEdit\n"
"{\n"
"    background-color: #242424;\n"
"}\n"
"\n"
"QHeaderView::section\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #616161, stop: 0.5 #505050, stop: 0.6 #434343, stop:1 #656565);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"}\n"
"\n"
""
                        "QCheckBox:disabled\n"
"{\n"
"color: #414141;\n"
"}\n"
"\n"
"QDockWidget::title\n"
"{\n"
"    text-align: center;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button, QDockWidget::float-button\n"
"{\n"
"    text-align: center;\n"
"    spacing: 1px; /* spacing between items in the tool bar */\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #323232, stop: 0.5 #242424, stop:1 #323232);\n"
"}\n"
"\n"
"QDockWidget::close-button:hover, QDockWidget::float-button:hover\n"
"{\n"
"    background: #242424;\n"
"}\n"
"\n"
"QDockWidget::close-button:pressed, QDockWidget::float-button:pressed\n"
"{\n"
"    padding: 1px -1px -1px 1px;\n"
"}\n"
"\n"
"QMainWindow::separator\n"
"{\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white"
                        ";\n"
"    padding-left: 4px;\n"
"    border: 1px solid #4c4c4c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QMainWindow::separator:hover\n"
"{\n"
"\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #d7801a, stop:0.5 #b56c17 stop:1 #ffa02f);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    border: 1px solid #6c6c6c;\n"
"    spacing: 3px; /* spacing between items in the tool bar */\n"
"}\n"
"\n"
"QToolBar::handle\n"
"{\n"
"     spacing: 3px; /* spacing between items in the tool bar */\n"
"     background: url(:/images/handle.png);\n"
"}\n"
"\n"
"QMenu::separator\n"
"{\n"
"    height: 2px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #161616, stop: 0.5 #151515, stop: 0.6 #212121, stop:1 #343434);\n"
"    color: white;\n"
"    padding-left: 4px;\n"
"    margin-left: 10px;\n"
"    margin-right: 5px;\n"
"}\n"
"\n"
"QProgressBar\n"
"{\n"
"    border: 2px solid grey;\n"
"    border-radius: 5px;\n"
"    text-align: center;\n"
""
                        "}\n"
"\n"
"QProgressBar::chunk\n"
"{\n"
"    background-color: #d7801a;\n"
"    width: 2.15px;\n"
"    margin: 0.5px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    color: #b1b1b1;\n"
"    border: 1px solid #444;\n"
"    border-bottom-style: none;\n"
"    background-color: #323232;\n"
"    padding-left: 10px;\n"
"    padding-right: 10px;\n"
"    padding-top: 3px;\n"
"    padding-bottom: 2px;\n"
"    margin-right: -1px;\n"
"}\n"
"\n"
"QTabWidget::pane {\n"
"    border: 1px solid #444;\n"
"    top: 1px;\n"
"}\n"
"\n"
"QTabBar::tab:last\n"
"{\n"
"    margin-right: 0; /* the last selected tab has nothing to overlap with on the right */\n"
"    border-top-right-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:first:!selected\n"
"{\n"
" margin-left: 0px; /* the last selected tab has nothing to overlap with on the right */\n"
"\n"
"\n"
"    border-top-left-radius: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected\n"
"{\n"
"    color: #b1b1b1;\n"
"    border-bottom-style: solid;\n"
"    margin-top: 3px;\n"
"    background-color: QLinearGradi"
                        "ent(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:.4 #343434);\n"
"}\n"
"\n"
"QTabBar::tab:selected\n"
"{\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    margin-bottom: 0px;\n"
"}\n"
"\n"
"QTabBar::tab:!selected:hover\n"
"{\n"
"    /*border-top: 2px solid #ffaa00;\n"
"    padding-bottom: 3px;*/\n"
"    border-top-left-radius: 3px;\n"
"    border-top-right-radius: 3px;\n"
"    background-color: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:1 #212121, stop:0.4 #343434, stop:0.2 #343434, stop:0.1 #ffaa00);\n"
"}\n"
"\n"
"QRadioButton::indicator:checked, QRadioButton::indicator:unchecked{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked\n"
"{\n"
"    background-color: qradialgradient(\n"
"        cx: 0.5, cy: 0.5,\n"
"        fx: 0.5, fy: 0.5,\n"
"        radius: 1.0,\n"
"        stop: 0.25 #ffaa00,\n"
"        stop: 0.3 #323232\n"
"    );\n"
"}\n"
"\n"
"QCheckBox"
                        "::indicator{\n"
"    color: #b1b1b1;\n"
"    background-color: #323232;\n"
"    border: 1px solid #b1b1b1;\n"
"    width: 9px;\n"
"    height: 9px;\n"
"}\n"
"\n"
"QRadioButton::indicator\n"
"{\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QRadioButton::indicator:hover, QCheckBox::indicator:hover\n"
"{\n"
"    border: 1px solid #ffaa00;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(:/images/checkbox.png);\n"
"}\n"
"\n"
"QCheckBox::indicator:disabled, QRadioButton::indicator:disabled\n"
"{\n"
"    border: 1px solid #444;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 950, 470));
        home = new QWidget();
        home->setObjectName(QStringLiteral("home"));
        hb_view = new QPushButton(home);
        hb_view->setObjectName(QStringLiteral("hb_view"));
        hb_view->setGeometry(QRect(400, 160, 161, 71));
        textEdit = new QTextEdit(home);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(360, 0, 231, 51));
        hb_exit = new QPushButton(home);
        hb_exit->setObjectName(QStringLiteral("hb_exit"));
        hb_exit->setGeometry(QRect(440, 340, 84, 28));
        stackedWidget->addWidget(home);
        calendar = new QWidget();
        calendar->setObjectName(QStringLiteral("calendar"));
        cb_add = new QPushButton(calendar);
        cb_add->setObjectName(QStringLiteral("cb_add"));
        cb_add->setGeometry(QRect(450, 10, 84, 28));
        ct_table = new QTableWidget(calendar);
        ct_table->setObjectName(QStringLiteral("ct_table"));
        ct_table->setGeometry(QRect(10, 50, 531, 411));
        ct_time = new QTextBrowser(calendar);
        ct_time->setObjectName(QStringLiteral("ct_time"));
        ct_time->setGeometry(QRect(110, 10, 191, 31));
        label = new QLabel(calendar);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 91, 20));
        cb_set = new QPushButton(calendar);
        cb_set->setObjectName(QStringLiteral("cb_set"));
        cb_set->setGeometry(QRect(340, 10, 84, 28));
        label_29 = new QLabel(calendar);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(550, 60, 91, 20));
        ct_scheduled = new QTableWidget(calendar);
        ct_scheduled->setObjectName(QStringLiteral("ct_scheduled"));
        ct_scheduled->setGeometry(QRect(545, 80, 221, 291));
        cb_schedule = new QPushButton(calendar);
        cb_schedule->setObjectName(QStringLiteral("cb_schedule"));
        cb_schedule->setGeometry(QRect(720, 10, 91, 28));
        cb_back = new QPushButton(calendar);
        cb_back->setObjectName(QStringLiteral("cb_back"));
        cb_back->setGeometry(QRect(860, 430, 81, 28));
        label_30 = new QLabel(calendar);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(770, 60, 111, 20));
        ct_unscheduled = new QTableWidget(calendar);
        ct_unscheduled->setObjectName(QStringLiteral("ct_unscheduled"));
        ct_unscheduled->setGeometry(QRect(770, 80, 171, 291));
        cb_deleteUn = new QPushButton(calendar);
        cb_deleteUn->setObjectName(QStringLiteral("cb_deleteUn"));
        cb_deleteUn->setGeometry(QRect(820, 380, 84, 28));
        cb_deleteSc = new QPushButton(calendar);
        cb_deleteSc->setObjectName(QStringLiteral("cb_deleteSc"));
        cb_deleteSc->setGeometry(QRect(620, 380, 84, 28));
        stackedWidget->addWidget(calendar);
        set = new QWidget();
        set->setObjectName(QStringLiteral("set"));
        sb_back = new QPushButton(set);
        sb_back->setObjectName(QStringLiteral("sb_back"));
        sb_back->setGeometry(QRect(860, 430, 81, 28));
        sc_label1 = new QLabel(set);
        sc_label1->setObjectName(QStringLiteral("sc_label1"));
        sc_label1->setGeometry(QRect(420, 10, 101, 20));
        gridLayoutWidget = new QWidget(set);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(150, 90, 600, 187));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(gridLayoutWidget);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout->addWidget(label_24, 0, 6, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        label_19 = new QLabel(gridLayoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 0, 1, 1, 1);

        label_21 = new QLabel(gridLayoutWidget);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout->addWidget(label_21, 0, 3, 1, 1);

        label_20 = new QLabel(gridLayoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 0, 2, 1, 1);

        label_23 = new QLabel(gridLayoutWidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout->addWidget(label_23, 0, 5, 1, 1);

        label_22 = new QLabel(gridLayoutWidget);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout->addWidget(label_22, 0, 4, 1, 1);

        sc_monFrom = new QComboBox(gridLayoutWidget);
        sc_monFrom->setObjectName(QStringLiteral("sc_monFrom"));

        gridLayout->addWidget(sc_monFrom, 2, 1, 1, 1);

        label_18 = new QLabel(gridLayoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 2, 0, 1, 1);

        sc_satTo = new QComboBox(gridLayoutWidget);
        sc_satTo->setObjectName(QStringLiteral("sc_satTo"));

        gridLayout->addWidget(sc_satTo, 4, 6, 1, 1);

        sc_satFrom = new QComboBox(gridLayoutWidget);
        sc_satFrom->setObjectName(QStringLiteral("sc_satFrom"));

        gridLayout->addWidget(sc_satFrom, 2, 6, 1, 1);

        sc_tueFrom = new QComboBox(gridLayoutWidget);
        sc_tueFrom->setObjectName(QStringLiteral("sc_tueFrom"));

        gridLayout->addWidget(sc_tueFrom, 2, 2, 1, 1);

        sc_wedFrom = new QComboBox(gridLayoutWidget);
        sc_wedFrom->setObjectName(QStringLiteral("sc_wedFrom"));

        gridLayout->addWidget(sc_wedFrom, 2, 3, 1, 1);

        sc_sunFrom = new QComboBox(gridLayoutWidget);
        sc_sunFrom->setObjectName(QStringLiteral("sc_sunFrom"));

        gridLayout->addWidget(sc_sunFrom, 2, 7, 1, 1);

        sc_wedTo = new QComboBox(gridLayoutWidget);
        sc_wedTo->setObjectName(QStringLiteral("sc_wedTo"));

        gridLayout->addWidget(sc_wedTo, 4, 3, 1, 1);

        sc_thuTo = new QComboBox(gridLayoutWidget);
        sc_thuTo->setObjectName(QStringLiteral("sc_thuTo"));

        gridLayout->addWidget(sc_thuTo, 4, 4, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        sc_thuFrom = new QComboBox(gridLayoutWidget);
        sc_thuFrom->setObjectName(QStringLiteral("sc_thuFrom"));

        gridLayout->addWidget(sc_thuFrom, 2, 4, 1, 1);

        sc_sunTo = new QComboBox(gridLayoutWidget);
        sc_sunTo->setObjectName(QStringLiteral("sc_sunTo"));

        gridLayout->addWidget(sc_sunTo, 4, 7, 1, 1);

        sc_tueTo = new QComboBox(gridLayoutWidget);
        sc_tueTo->setObjectName(QStringLiteral("sc_tueTo"));

        gridLayout->addWidget(sc_tueTo, 4, 2, 1, 1);

        sc_friFrom = new QComboBox(gridLayoutWidget);
        sc_friFrom->setObjectName(QStringLiteral("sc_friFrom"));

        gridLayout->addWidget(sc_friFrom, 2, 5, 1, 1);

        label_25 = new QLabel(gridLayoutWidget);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout->addWidget(label_25, 0, 7, 1, 1);

        sc_monTo = new QComboBox(gridLayoutWidget);
        sc_monTo->setObjectName(QStringLiteral("sc_monTo"));

        gridLayout->addWidget(sc_monTo, 4, 1, 1, 1);

        sc_friTo = new QComboBox(gridLayoutWidget);
        sc_friTo->setObjectName(QStringLiteral("sc_friTo"));

        gridLayout->addWidget(sc_friTo, 4, 5, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 3, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 2, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 3, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 3, 4, 1, 1);

        label_11 = new QLabel(gridLayoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 1, 4, 1, 1);

        label_12 = new QLabel(gridLayoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 3, 5, 1, 1);

        label_13 = new QLabel(gridLayoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 1, 5, 1, 1);

        label_15 = new QLabel(gridLayoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 1, 6, 1, 1);

        label_14 = new QLabel(gridLayoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 3, 6, 1, 1);

        label_17 = new QLabel(gridLayoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 1, 7, 1, 1);

        label_16 = new QLabel(gridLayoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 3, 7, 1, 1);

        sb_apply = new QPushButton(set);
        sb_apply->setObjectName(QStringLiteral("sb_apply"));
        sb_apply->setGeometry(QRect(430, 310, 84, 28));
        stackedWidget->addWidget(set);
        add = new QWidget();
        add->setObjectName(QStringLiteral("add"));
        label_7 = new QLabel(add);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(440, 10, 63, 20));
        formLayoutWidget = new QWidget(add);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(390, 130, 160, 92));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_26 = new QLabel(formLayoutWidget);
        label_26->setObjectName(QStringLiteral("label_26"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_26);

        label_27 = new QLabel(formLayoutWidget);
        label_27->setObjectName(QStringLiteral("label_27"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_27);

        al_name = new QLineEdit(formLayoutWidget);
        al_name->setObjectName(QStringLiteral("al_name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, al_name);

        al_desc = new QLineEdit(formLayoutWidget);
        al_desc->setObjectName(QStringLiteral("al_desc"));

        formLayout->setWidget(1, QFormLayout::FieldRole, al_desc);

        al_hours = new QLineEdit(formLayoutWidget);
        al_hours->setObjectName(QStringLiteral("al_hours"));

        formLayout->setWidget(2, QFormLayout::FieldRole, al_hours);

        label_28 = new QLabel(formLayoutWidget);
        label_28->setObjectName(QStringLiteral("label_28"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_28);

        ab_back = new QPushButton(add);
        ab_back->setObjectName(QStringLiteral("ab_back"));
        ab_back->setGeometry(QRect(860, 430, 84, 28));
        ab_add = new QPushButton(add);
        ab_add->setObjectName(QStringLiteral("ab_add"));
        ab_add->setGeometry(QRect(430, 260, 84, 28));
        stackedWidget->addWidget(add);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        hb_view->setText(QApplication::translate("MainWindow", "View Calendar", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:24pt;\">Smart Calendar</span></p></body></html>", Q_NULLPTR));
        hb_exit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        cb_add->setText(QApplication::translate("MainWindow", "Add Task", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Current Time:", Q_NULLPTR));
        cb_set->setText(QApplication::translate("MainWindow", "Set Hours", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "SCHEDULED:", Q_NULLPTR));
        cb_schedule->setText(QApplication::translate("MainWindow", "Schedule", Q_NULLPTR));
        cb_back->setText(QApplication::translate("MainWindow", "Back", Q_NULLPTR));
        label_30->setText(QApplication::translate("MainWindow", "UNSCHEDULED:", Q_NULLPTR));
        cb_deleteUn->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        cb_deleteSc->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        sb_back->setText(QApplication::translate("MainWindow", "Back", Q_NULLPTR));
        sc_label1->setText(QApplication::translate("MainWindow", "Set Hours Free", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "SAT", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "MON", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "WED", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "TUE", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "FRI", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "THU", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "Hours Free", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "SUN", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "From:", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "To:", Q_NULLPTR));
        sb_apply->setText(QApplication::translate("MainWindow", "Apply", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Add Task", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "Name: ", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "Description", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "Total Hours", Q_NULLPTR));
        ab_back->setText(QApplication::translate("MainWindow", "Back", Q_NULLPTR));
        ab_add->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
