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
    QVector<int> getTabIdUser();
    QString getUserNom(int noUser);
    QString getUserPrenom(int noUser);
    QVector<int> getUserTabPointDeVente(int noUser);
    QString getNomPDV(int noPDV);
    QVector<int> getProdByPDV(int noPDV);
    QString getProdName(int noProd);
    int getRayonByProd(int noProd);
    int getCategorieByRayon(int noRayon);
    QVector<int> getTabRayon(QVector<int> numProduit);
    QString getRayonName(int idRayon);
    QVector<int> getTabCategorie(QVector<int> numRayon);
    QString getCategorieName(int idCategorie);
    QVector< QVector < QVector<int> > > getMarket(QVector<int> numProduit, QVector<int> numRayon, QVector<int> numCategorie);


private :
    QSqlQuery req;
};

#endif // CONNEXION_H
