#include "connexion.h"
#include <QSqlRecord>
#include <QTextCodec>
#include <QDebug>
#include <QSqlQuery>
#include <iostream>

using namespace std;

Connexion::Connexion()
{
}

int Connexion::getNbUser()
{
    req.exec("select * from PointDeVenteParUtilisateur group by idUser");
    return req.size();
}

QString Connexion::getUserNom(int noUser)
{
    req.exec("select nom from Utilisateur where no = "+ QString::number(noUser));
    req.next();
    return req.value(0).toString();
}

QString Connexion::getUserPrenom(int noUser)
{
    req.exec("select prenom from Utilisateur where no = "+ QString::number(noUser));
    req.next();
    return req.value(0).toString();
}

QVector<int> Connexion::getUserTabPointDeVente(int noUser)
{
    QVector<int> PDVByUser;
    req.exec("select idPointDeVente from PointDeVenteParUtilisateur where idUser = "+ QString::number(noUser));
    while(req.next())
    {
        PDVByUser.push_back(req.value(0).toInt());
    }
    return PDVByUser;
}

QString Connexion::getNomPDV(int noPDV)
{
    req.exec("select libelle from PointDeVente where no = "+ QString::number(noPDV));
    req.next();
    return req.value(0).toString();
}

QVector<int> Connexion::getProdByPDV(int noPDV)
{
    QVector<int> tabProd;
    req.exec("select lot from Propose where pointDeVente = "+ QString::number(noPDV));
    while(req.next())
    {
       int numLot = req.value(0).toInt();
       QSqlQuery reqLot;
       reqLot.exec("select produit from Lot where no ="+ QString::number(numLot));
       while(reqLot.next())
       {
           tabProd.push_back(reqLot.value(0).toInt());
       }
    }
    return tabProd;
}

QString Connexion::getProdName(int noProd)
{
    req.exec("select libelle from Produit where no ="+ QString::number(noProd));
    req.next();
    return req.value(0).toString();
}
