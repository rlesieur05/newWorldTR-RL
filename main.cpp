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

#include "connexion.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    Connexion co;

    int nbUser = co.getNbUser();




    for(int comp=0; comp<nbUser; comp++)
    {
        QString userNom = co.getUserNom(comp);
        QString userPrenom = co.getUserPrenom(comp);
        QVector<int> numPDV = co.getUserTabPointDeVente(comp);
        QVector<QString> nomPDV;
        for(int compPDV=0; compPDV<nomPDV.size(); comp++)
        {
            int noPDV = numPDV[compPDV];
            nomPDV.push_back(co.getNomPDV(noPDV));
        }
        QVector<QString> nomProduit;

        QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
        printer.setFullPage(QPrinter::A4);
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setOutputFileName("/home/troux/Documents/ppe/groupPdf/"+ QString::number(comp) +".pdf");

        QPainter painter;
        painter.begin(&printer);
        painter.setFont(QFont("Arial",30));
        painter.drawText(3500,200,"New World");
        painter.setFont(QFont("Arial",15));
        painter.drawText(0,1000,"Bienvenue sur votre catalogue personnalisé "+ userNom +" "+ userPrenom);
        painter.setFont(QFont("Arial",12));
        painter.drawText(0,1500,"Nous vous invitons dès à présent à regarder les produits disponibles dans le(s) lieu(x) suivant(s):");

        for(int compPDV=0; compPDV<numPDV.size(); compPDV++)
        {

            QVector<int> tabProd = co.getProdByPDV(compPDV);
            for(int compProd=0; compProd<tabProd.size(); compProd++)
            {
                int noProd = tabProd[compProd];
                nomProduit.push_back(co.getProdName(noProd));
            }
        }

        int decalage = 2000;
        for(int compVPDV=0; compVPDV<nomPDV.size(); compVPDV++)
        {
            painter.drawText(0, decalage, nomPDV[compVPDV]);
            decalage += 200;
            for(int compVProduit=0; compVProduit<nomProduit.size(); compVProduit++)
            {
                painter.drawText(1000, decalage, nomProduit[compVProduit]);
                decalage += 200;
            }
        }

        painter.end();
        cout<<endl;
    }


    return 0;
}
