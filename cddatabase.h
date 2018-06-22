#ifndef CDDATABASE_H
#define CDDATABASE_H

#include <QObject>
#include "cddata.h"
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>

class cdDatabase : public QObject
{
    Q_OBJECT
public:
    explicit cdDatabase(QObject *parent = nullptr);
    ~cdDatabase();

    QList<QString> getAllSongs(int id); //const;
    QString getCDName(int id) const;
    QString getAutorName(int id) const;
    QString getYear(int id) const;
    QString getType(int id) const;
    QString getSongs(int id,int songID) const;
    QString getPicture(int id) const;
    int getNumberOfSongs(int id) const;
    int getCount() const;

    void fillDb(QString CDName, QString Autor, int Year, QString Genre, QString Picture);
    void fillDb(QString CDName, QString Autor, int Year, QString Genre);
    void editDB(int id, QString CDName, QString Autor, int Year, QString Genre, QString Picture);

    void addSong(int id,QString songName);
    void removeCD(int id);
    void clearSongs(int id);
    void dbClear();

private:
    QList<cdData*> CD;



signals:

public slots:
};

#endif // CDDATABASE_H
