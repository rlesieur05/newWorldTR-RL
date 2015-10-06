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

int Connexion::getRayonByProd(int noProd)
{
    req.exec("select categorie from Produit where no ="+ QString::number(noProd));
    req.next();
    return req.value(0).toInt();
}

int Connexion::getCategorieByRayon(int noRayon)
{
    req.exec("select rayon from TypeProduit where no ="+ QString::number(noRayon));
    req.next();
    return req.value(0).toInt();
}

QVector<int> Connexion::getTabRayon(QVector<int> numProduit)
{
    QVector<int> numRayon;
    for(int comp=0; comp<numProduit.size(); comp++)
    {
        int rayon = getRayonByProd(numProduit[comp]);
        bool uniqueR = true;
        for(int compR=0; compR<numRayon.size(); compR++)
        {
            if(numRayon[compR] == rayon){
                uniqueR = false;
            }
        }
        if(uniqueR){
            numRayon.push_back(rayon);
        }
    }
    return numRayon;
}

QVector<int> Connexion::getTabCategorie(QVector<int> numRayon)
{
    QVector<int> numCategorie;
    for(int comp=0; comp<numRayon.size(); comp++)
    {
        int categorie = getCategorieByRayon(numRayon[comp]);
        bool uniqueC = true;
        for(int compC=0; compC<numCategorie.size(); compC++)
        {
            if(numCategorie[compC] == categorie){
                uniqueC = false;
            }
        }
        if(uniqueC){
            numCategorie.push_back(categorie);
        }
    }
    return numCategorie;
}

QVector< QVector < QVector<int> > > Connexion::getMarket(QVector<int> numProduit, QVector<int> numRayon, QVector<int> numCategorie)
{
    QVector< QVector < QVector<int> > > marketC;
    for(int compC=0; compC<numCategorie.size(); compC++)
    {
        QVector< QVector<int> > marketR;
        for(int compR=0; compR<numRayon.size(); compR++)
        {
            QVector<int> marketP;
            for(int compP=0; compP<numProduit.size(); compP++)
            {
            }
        }
    }
    return marketC;
}
