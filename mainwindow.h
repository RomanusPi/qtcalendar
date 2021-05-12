#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDate>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCalendarWidget>
#include "data.h"
#include "file.h"
#include "sms.h"
#include "database.h"
#include<QDir>

//class QtextEdit;

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
    void on_commandLinkButton_clicked();
    void on_calendarWidget_selectionChanged();

    void createButtons();//create new buttons (not used yet)
    void onRemoveWidget();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_commandLinkButton_2_clicked();



    void on_pushButton_4_clicked();

    void on_save_to_file_clicked();

    void on_read_from_file_clicked();

    void on_pushButton_save_to_bd_clicked();

    void on_pushButton_read_from_bd_clicked();

private:
    Ui::MainWindow *ui;
    QDate nDate;//selected date for date oparations
    QDate arrowDate;//date for months from arrows
    QMap<QString,rdata> DateMap;//all termins reserved
    QString strDate;//for save string of qdate
    File ToFile;//class to save in the file
    Sms SmsR;
    DataBase DBase;
    friend class database;
    friend class File;//access to privet MainWindow(QMap)
    friend class Sms;
    QString FilePath="";//string to path of project

};

#endif // MAINWINDOW_H


//obsluga bladnej daty
