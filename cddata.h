#ifndef CDDATA_H
#define CDDATA_H

#include <QObject>
#include <QList>
#include <QString>

class cdData : public QObject
{
    Q_OBJECT
public:
    explicit cdData(QObject *parent = nullptr);
    ~cdData();

    QString getCDName() const;
    QString getAutorName() const;
    int getYear() const;
    int getNumberOfSongs() const;
    QString getType() const;
    QString getSong(int id) const;
    QString getPicture() const;
    QList<QString> getSongs() const;

    void setCDName(QString CDName);
    void setAutorName(QString autorName);
    void setYear(int year);
    void setType(QString genre);
    void addSong(QString songName);
    void setPicture(QString pictureAddr);
    void clearSongs();


private:
    int *mNumberOfSongs;
    QString *mCDName;
    QString *mAutorName;
    int *mYear;
    QString *mType;
    QList<QString> *mSongName;
    QString *mPicture;


signals:

public slots:
};

#endif // CDDATA_H
