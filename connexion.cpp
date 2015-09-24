#include "connexion.h"
#include <QSqlRecord>
#include <QTextCodec>
#include <QDebug>
#include <QSqlQuery>
#include <iostream>

using namespace std;

Connexion::Connexion()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

    maBase=new QSqlDatabase(db);

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
}

int Connexion::getNbUser()
{
    req.exec("select * from PointDeVenteParUtilisateur group by idUser");
    return req.size();
}

QString Connexion::getUserNom(int noUser)
{
    req.exec("select nom from Utilisateur where no = "+ noUser);
    req.next();
    return req.value(0).toString();
}

QString Connexion::getUserPrenom(int noUser)
{
    req.exec("select prenom from Utilisateur where no = "+ noUser);
    req.next();
    return req.value(0).toString();
}

QVector<int> Connexion::getUserTabPointDeVente(int noUser)
{
    QVector<int> PDVByUser;
    req.exec("select idPointDeVente from PointDeVenteParUtilisateur where idUser = "+ noUser);
    while(req.next())
    {
        PDVByUser.push_back(req.value(0).toInt());
    }
    return PDVByUser;
}

QString Connexion::getNomPDV(int noPDV)
{
    req.exec("select libelle from PointDeVente where no = "+ noPDV);
    req.next();
    return req.value(0).toString();
}

QVector<int> Connexion::getProdByPDV(int noPDV)
{
    QVector<int> tabProd;
    req.exec("select lot from Propose where pointDeVente = "+ noPDV);
    while(req.next())
    {
       int numLot = req.value(0).toInt();
       QSqlQuery reqLot;
       reqLot.exec("select produit from Lot where no ="+ numLot);
       while(reqLot.next())
       {
           tabProd.push_back(reqLot.value(0).toInt());
       }
    }
    return tabProd;
}

QString Connexion::getProdName(int noProd)
{
    req.exec("select libelle from Produit where no ="+ noProd);
    req.next();
    return req.value(0).toString();
}
