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
#include <QTextDocument>
#include "connexion.h"


int main(int argc, char *argv[])
{
    Connexion maCo;

    QApplication a(argc, argv);
    QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
    printer.setFullPage(QPrinter::A4);
    printer.setOutputFormat(QPrinter::NativeFormat);
    printer.setOutputFileName("/home/troux/Document/ppe/test.pdf");
    QPainter painter;
    painter.begin(&printer);
    painter.setFont(QFont("Tahoma",8));
    painter.drawText(200,200,"HELOOOO");
    painter.end();

    return 0;


    /*QTextDocument doc;
    doc.setHtml("<h1>hello, I'm an head</h1>");
    QPrinter printer;
    printer.setOutputFileName("/home/troux/Documents/ppe/file.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    printer.newPage();*/
}
