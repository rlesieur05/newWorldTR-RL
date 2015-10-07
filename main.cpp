
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
        QVector< QVector < QVector<int> > > market = co.getMarket(numProduit, numRayon, numCategorie);//produit par rayon par catégorie (tableau[C][R][P])

        /*for(int test=0; test<numProduit.size(); test++)
        {
            cout<<numProduit[test]<<" ";
        }
        cout<<endl;
        for(int compC=0; compC<market.size(); compC++)
        {
            for(int compR=0; compR<market[compC].size(); compR++)
            {
                for(int compP=0; compP<market[compC][compR].size(); compP++)
                {
                    cout<<market[compC][compR][compP]<<" ";
                }
            }
        }
        cout<<endl;*/

        QPrinter printer(QPrinter::HighResolution); //create your QPrinter (don't need to be high resolution, anyway)
        printer.setFullPage(QPrinter::A4);
        printer.setOutputFormat(QPrinter::NativeFormat);
        printer.setOutputFileName("/home/troux/sources-build-desktop-Qt_4_8_2_in_PATH__System__Debug/"+ QString::number(idUser[comp]) +".pdf");

        QPainter painter;
        painter.begin(&printer);
        painter.setFont(QFont("Arial",30));
        painter.setFont(QFont("Arial",15));
        painter.drawText(0,1500,"Bienvenue sur votre catalogue personnalisé "+ userNom +" "+ userPrenom);
        painter.setFont(QFont("Arial",12));
        painter.drawText(0,2000,"Nous vous invitons dès à présent à regarder les produits disponibles dans le(s) lieu(x) suivant(s):");

        int decalage = 2500;
        /*for(int compC=0; compC<market.size(); compC++)
        {
            for(int compR=0; compR<market[compC].size(); compR++)
            {
                for(int compP=0; compP<market[compC][compR].size(); compP++)
                {
                    cout<<market[compC][compR][compP]<<endl;
                    painter.drawText(0,decalage, co.getProdName(market[compC][compR][compP]));
                    decalage += 200;
                }
            }
        }*/

        /*QPen monPen;
        monPen.setWidth(50);
        monPen.setColor(Qt::blue);
        painter.setPen(monPen);
        painter.drawRect(0,0, 1000, 1000);*/

        QRectF rectangle(0,-100,1000,900);
        QImage monImage;
        monImage.load("images/logoNw.jpg");
        painter.drawImage(rectangle, monImage);

        QRectF rectangle2(500,-100,8000,1000);
        QImage monImage2;
        monImage2.load("images/ecritureNw.png");
        painter.drawImage(rectangle2, monImage2);

        painter.end();
        cout<<userNom.toStdString()<<" "<<userPrenom.toStdString()<<"("<<comp+1<<"/"<<nbUser<<")"<<endl;
    }


    return 0;
}
