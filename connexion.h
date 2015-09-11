#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QObject>

class connexion
{
public:
    connexion();

private :
 QSqlDatabase * maBase;
};

#endif // CONNEXION_H
