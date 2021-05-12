#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    //QObject::connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::createButtons);
    nDate= QDate::currentDate();
    //read data saved in file
    ToFile.fileTermOpen();
    ToFile.read_from_file(DateMap);
    ToFile.file_close(ToFile.FileReadDes);

    //print about current day
    strDate=QDate::currentDate().toString("yyyy/M/dd");
    ui->label_2->setText(strDate);
    if (DateMap[QDate::currentDate().toString("yyyy/M/dd")].isReserved==false){
            ui->label_3->setText("Termin możliwy do rejestracji");
    }
    else { ui->label_3->setText("Termin został zarezerwowany");}

    QDir cat;
    FilePath=cat.currentPath();//take current directory


   //sms
    ui->lineEdit->setText(strDate +" rezerwuje" );
    SmsR.smstext=ui->lineEdit->text();
  // database
  DBase.DatabaseConnect(FilePath);
  DBase.DatabaseInit();


}



MainWindow::~MainWindow()
{
    //save to file
    ToFile.fileTermOpen();
    ToFile.write_to_file(DateMap);
    ToFile.file_close(ToFile.FileReadDes);
    delete ui;

}

void MainWindow::on_calendarWidget_selectionChanged()
{

   ui->label_4->setText("");
   nDate=ui->calendarWidget->selectedDate();//nDate for selected on calender day
   strDate=nDate.toString("yyyy/M/dd");

   if (!(DateMap.contains(strDate))||(DateMap[strDate].isReserved==false)){
           ui->label_3->setText("Termin możliwy do rejestracji");
   }
   else { ui->label_3->setText("Termin został zarezerwowany");}

   QMapIterator<QString,rdata>Iter(DateMap);
   while(Iter.hasNext()){ Iter.next(); qDebug()<<Iter.key()<<" "<<Iter.value().isReserved;};

   ui->label_2->setText(strDate);

}
//----

void MainWindow::createButtons(){//used in the future
    qDebug()<<"create";
  
  /*  QVBoxLayout *layout=new QVBoxLayout();
   layout=ui->verticalLayout;
    QString buttontext=tr("Buttont: #%1").arg(layout->count());
    QPushButton *przyc =new QPushButton(buttontext, ui->frame_2);
    layout->insertWidget(0,przyc);
    przyc->show();
    QObject::connect( przyc,&QPushButton::clicked,this,&MainWindow::onRemoveWidget);
//zrobic layout nf veritivcal i pole textowe

*/

}
void MainWindow::onRemoveWidget(){//use in the future

    QPushButton* przyc =  qobject_cast<QPushButton*>(sender());
    delete przyc;

}

void MainWindow::on_pushButton_clicked()
{

    if (DateMap[strDate].isReserved==false){
        DateMap[strDate].isReserved=true;
        ui->label_4->setText("Zarezerwowales ten termin");
    }
    else { ui->label_4->setText("Nie możesz ponownie zarezerwować");}

}

void MainWindow::on_pushButton_2_clicked()
{

    if (DateMap[strDate].isReserved==true){
      DateMap[strDate].isReserved=false;
      ui->label_4->setText("Odwołałeś ten termin");
    }
    else { ui->label_4->setText("Nie masz jeszcze rezerwacji ");}

}

void MainWindow::on_commandLinkButton_clicked()//button with months
{

    arrowDate=nDate.addMonths(1);//one month later
    ui->calendarWidget->setSelectedDate(arrowDate);
    QString strMonth=arrowDate.toString("M");
    bool ok;
    int k = strMonth.toInt(&ok);
    if (ok ==false) {qDebug()<<"notconverted";}
    strMonth= QDate::longMonthName(k);
    ui->label->setText(strMonth);
}
void MainWindow::on_commandLinkButton_2_clicked()
{

    arrowDate=nDate.addMonths(-1);//one month earlier
    ui->calendarWidget->setSelectedDate(arrowDate);
    QString strMonth=arrowDate.toString("M");
    bool ok;
    int k = strMonth.toInt(&ok);
    if (ok ==false) {qDebug()<<"notconverted";}
    strMonth= QDate::longMonthName(k);
    ui->label->setText(strMonth);
    //MainWindow::createButtons();//use later
}






void MainWindow::on_pushButton_4_clicked()
{

 SmsR.smstext=ui->lineEdit->text();
 QString strDate= SmsR.smstext.left(9);
 QString Rezor = SmsR.smstext.mid(10,17);
 if(Rezor=="rezerwuje"){

     if (DateMap[strDate].isReserved==false){
         DateMap[strDate].isReserved=true;
         ui->label_4->setText("Zarezerwowales ten termin");
     }
     else { ui->label_4->setText("Nie możesz ponownie zarezerwować");}
  }
 if(Rezor=="odwołuje"){
     if (DateMap[strDate].isReserved==true)
     {
       DateMap[strDate].isReserved=false;
       ui->label_4->setText("Odwołałeś ten termin");
     }
     else { ui->label_4->setText("Nie masz jeszcze rezerwacji ");}

 }


 qDebug()<<strDate<<Rezor;
}

void MainWindow::on_save_to_file_clicked()
{
    //write to file
        ToFile.fileTermOpen();
        ToFile.write_to_file(DateMap);
        ToFile.file_close(ToFile.FileReadDes);
        ui->label_4->setText("Zapisano dane do pliku");
}

void MainWindow::on_read_from_file_clicked()
{
    //read data saved in file
    ToFile.fileTermOpen();
    ToFile.read_from_file(DateMap);
    ToFile.file_close(ToFile.FileReadDes);
    ui->label_4->setText("Odczytano dane  z pliku ");
}

void MainWindow::on_pushButton_save_to_bd_clicked()
{

    DBase.Databasewrite(DateMap);
    ui->label_4->setText("Zapisano do bazy danych");

}

void MainWindow::on_pushButton_read_from_bd_clicked()
{

    DBase.Databaseread(DateMap);
    ui->label_4->setText("");
}
