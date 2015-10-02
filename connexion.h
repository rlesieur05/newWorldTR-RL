#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QObject>

class Connexion
{
public:
    Connexion();
    int getNbUser();
    QString getUserNom(int noUser);
    QString getUserPrenom(int noUser);
    QVector<int> getUserTabPointDeVente(int noUser);
    QString getNomPDV(int noPDV);
    QVector<int> getProdByPDV(int noPDV);
    QString getProdName(int noProd);
    int getRayonByProd(int noProd);
    int getCategorieByRayon(int noRayon);
    QVector<int> getTabRayon(QVector<int> numProduit);
    QVector<int> getTabCategorie(QVector<int> numRayon);
    QVector< QVector < QVector<int> > > getMarket(QVector<int> numProduit);

private :
    QSqlQuery req;
};

#endif // CONNEXION_H
