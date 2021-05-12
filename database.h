#include <QDebug>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>




class DataBase{
public:

void DatabaseConnect(QString FilePathtoDb){

    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(FilePathtoDb+"/tables");

        if(!db.open())
            qWarning() << "MainWindow::DatabaseConnect - ERROR: " << db.lastError().text();
        else qWarning()<<"DataBase opened";
    }
    else
        qWarning() << "MainWindow::DatabaseConnect - ERROR: no driver " << DRIVER << " available";

}

void DatabaseInit()
{
     QSqlQuery query("CREATE TABLE IF NOT EXISTS Reservation4 (DATE TEXT PRIMARY KEY, reserv TEXT)");
     if(!query.isActive())
        qWarning() << "MainWindow::DatabaseInit - ERROR: " << query.lastError().text();

}


void Databasewrite(QMap<QString,rdata> &ReservedMap)
{
    QSqlQuery query;

    QString strDate,Resfort;
    QDate qdate;
    QMapIterator<QString,rdata>Iter(ReservedMap);

    if(!query.exec("DELETE FROM Reservation4"))
        qWarning() << "MainWindow::DatabasePopulate - delete: " << query.lastError().text();

    while(Iter.hasNext()){
          Iter.next();
         // qDebug()<<"zapisuje do  BD: "<<Iter.key()<<" "<<Iter.value().isReserved;
          strDate=Iter.key();
          if(strDate!=""){//if empty somehow
              if(ReservedMap[strDate].isReserved)Resfort="true";
              else Resfort="false";
              if(!query.exec("INSERT INTO Reservation4(DATE, reserv) VALUES('"+strDate+"','"+Resfort+"')"))
                qWarning() << "MainWindow::DatabasePopulate - ERROR: " << query.lastError().text();
          }


    }
    qWarning()<<"zapisano dane do bazy danych";




}

void Databaseread(QMap<QString,rdata> &ReservedMap)
{
    QSqlQuery query;
   //to implement
}
};



