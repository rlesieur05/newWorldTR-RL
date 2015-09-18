#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>

class Connexion
{
public:
    Connexion();
    QVector<QString> getRequest(QString stringRequest, QString tabType);

private :
 QSqlDatabase * maBase;
};

#endif // CONNEXION_H
