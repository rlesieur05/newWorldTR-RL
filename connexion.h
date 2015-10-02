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

private :
    QSqlQuery req;
};

#endif // CONNEXION_H
