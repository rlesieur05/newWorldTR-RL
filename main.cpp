
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


    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

    //maBase=new QSqlDatabase(db);

    db.setHostName("172.16.63.111");
    db.setDatabaseName("dbtrouxNewWorld");
    db.setUserName("troux");
    db.setPassword("PscX57Q16");
    bool ok = db.open();
    if(!ok)
    {
        cout<<"Connection impossible"<<endl;
    }
    else
    {
        cout<<"Connection réussie"<<endl;
    }

    Connexion co;
    QVector<int> idUser = co.getTabIdUser();
    int nbUser = idUser.size();



    for(int comp=0; comp<nbUser; comp++)
    {
        QString userNom = co.getUserNom(idUser[comp]);
        QString userPrenom = co.getUserPrenom(idUser[comp]);
        QVector<int> numPDV = co.getUserTabPointDeVente(idUser[comp]);
        QVector<int> numProduit;
        for(int compPDV=0; compPDV<numPDV.size(); compPDV++)
        {
            QVector<int> tabInstNumProd = co.getProdByPDV(numPDV[compPDV]);
            for(int compProd=0; compProd < tabInstNumProd.size(); compProd++)
            {
                bool uniqueNumProd = true;
                for(int compVerifDoubleProd=0; compVerifDoubleProd < numProduit.size(); compVerifDoubleProd++)
                {
                    if(numProduit[compVerifDoubleProd] == tabInstNumProd[compProd])
                    {
                        uniqueNumProd = false;
                    }
                }
                if(uniqueNumProd){
                    numProduit.push_back(tabInstNumProd[compProd]);
                }
            }
        }
        QVector<int> numRayon = co.getTabRayon(numProduit);
        QVector<int> numCategorie = co.getTabCategorie(numRayon);

        QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
        printer.setFullPage(QPrinter::A4);
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setOutputFileName("pdfClient/"+ QString::number(idUser[comp]) +".pdf");


        int decalage = -100;
        int tailleImage = 2300;
        QPainter painter;
        painter.begin(&printer);
        QRectF rectangle(700, decalage,1000,900);
        QImage monImage;
        monImage.load("images/presentation/logoNw.jpg");
        painter.drawImage(rectangle, monImage);
        QRectF rectangle2(1200, decalage,8000,1000);
        QImage monImage2;
        monImage2.load("images/presentation/ecritureNw.png");
        painter.drawImage(rectangle2, monImage2);
        decalage += 2000;
        painter.setFont(QFont("Arial",15));
        painter.drawText(0, decalage, userNom +" "+ userPrenom +",");
        decalage += 250;
        painter.drawText(0, decalage,"Bienvenue sur votre catalogue personnalisé ");
        decalage += 1000;
        painter.setFont(QFont("Arial",12));
        painter.drawText(0, decalage,"Nous vous proposerons cette semaine "+QString::number(numProduit.size()) +" produits parmi les "+ QString::number(numPDV.size()) +" points de vente choisis.");
        decalage += 650;

        foreach(const int &idCategorie, numCategorie)
        {
            painter.drawText(0, decalage, co.getCategorieName(idCategorie));
            decalage += 200;
            foreach(const int &idRayon, numRayon)
            {
                if(co.getCategorieByRayon(idRayon) == idCategorie)
                {
                    painter.drawText(500,decalage, co.getRayonName(idRayon));
                    decalage += 200;
                    int decalageV = 1000;
                    foreach(const int &idProduit, numProduit)
                    {
                        if(co.getRayonByProd(idProduit) == idRayon)
                        {
                            QRectF rectangle(decalageV, decalage-100, tailleImage, tailleImage);
                            QImage monImage;
                            monImage.load("images/produit/"+ QString::number(idProduit) +".png");
                            painter.drawImage(rectangle, monImage);
                            QPen pen;
                            pen.setColor(Qt::magenta);
                            painter.setPen(pen);
                            painter.setFont(QFont("Arial",10));
                            painter.drawText(decalageV+500, decalage+tailleImage+100, co.getProdName(idProduit));
                            pen.setColor(Qt::black);
                            painter.setPen(pen);
                            painter.setFont(QFont("Arial",12));

                            decalageV += tailleImage+500;

                        }
                    }
                    decalage += tailleImage+500;
                    if(decalage > 11000){
                        printer.newPage();
                        decalage = 0;
                    }
                }
            }
        }

        /*QPen monPen;
        monPen.setWidth(50);
        monPen.setColor(Qt::blue);
        painter.setPen(monPen);
        painter.drawRect(0,0, 1000, 1000);*/



        painter.end();
        cout<<userNom.toStdString()<<" "<<userPrenom.toStdString()<<" ("<<comp+1<<"/"<<nbUser<<")"<<endl;
    }


    return 0;
}
