#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>

class Connexion
{
public:
    Connexion();

private :
 QSqlDatabase * maBase;
};

#endif // CONNEXION_H
