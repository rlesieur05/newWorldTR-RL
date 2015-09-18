/**
 * @author Robin Lesieur
 * @date 11/08/2015
 *
 *
 *
 **/

#include <QSqlRecord>
#include <QTextCodec>
#include <QDebug>
#include <QSqlQuery>
#include <QApplication>
#include <QSqlDatabase>
#include <QtGui/QPrinter>
#include <QtGui/QPainter>
#include <QVector>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

    QSqlDatabase * maBase=new QSqlDatabase(db);

    maBase->setHostName("172.16.63.111");
    maBase->setDatabaseName("dbtrouxNewWorld");
    maBase->setUserName("troux");
    maBase->setPassword("PscX57Q16");
    bool ok = maBase->open();
    if(!ok)
    {
        cout<<"Connection impossible"<<endl;
    }
    else
    {
        cout<<"Connection réussie"<<endl;
    }



    if(false){
        QApplication a(argc, argv);
        QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
        printer.setFullPage(QPrinter::A4);
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setOutputFileName("/home/troux/Documents/ppe/groupPdf/test.pdf");
        QPainter painter;
        painter.begin(&printer);
        painter.setFont(QFont("Tahoma",8));
        painter.drawText(200,200,"HELOOOO");
        painter.end();
    }

    return 0;
}
