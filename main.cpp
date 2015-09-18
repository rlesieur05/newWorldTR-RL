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
#include <iostream>
#include <QtGui/QPrinter>
#include <QtGui/QPainter>
#include "connexion.h"

using namespace std;

int main(int argc, char *argv[])
{
    Connexion maCo;



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
