#include "cddata.h"

cdData::cdData(QObject *parent) : QObject(parent)
{
    mSongName = new QList<QString>;
    mCDName = new QString;
    mAutorName = new QString;
    mYear = new int;
    mType = new QString;
    mPicture = new QString;
    mNumberOfSongs = new int;
    mNumberOfSongs = 0;

}

cdData::~cdData()
{
    mSongName->clear();
    delete mSongName;
    delete mCDName;
    delete mAutorName;
    delete mYear;
    delete mType;
    delete mPicture;
    delete mNumberOfSongs;
}

QString cdData::getCDName() const
{
    return *mCDName;
}

QString cdData::getAutorName() const
{
    return *mAutorName;
}

int cdData::getYear() const
{
    return *mYear;
}

int cdData::getNumberOfSongs() const
{
    return mSongName->count();
}

QString cdData::getType() const
{
    return *mType;
}

QString cdData::getSong(int id) const
{
    return mSongName->at(id);
}

QString cdData::getPicture() const
{
    return *mPicture;
}

QList<QString> cdData::getSongs() const
{
    return *mSongName;
}

void cdData::setCDName(QString CDName)
{
    *mCDName = CDName;
}

void cdData::setAutorName(QString autorName)
{
    *mAutorName = autorName;
}

void cdData::setYear(int year)
{
    *mYear = year;
}

void cdData::setType(QString genre)
{
    *mType = genre;
}

void cdData::addSong(QString songName)
{
    mSongName->append(songName);
    mNumberOfSongs++;
}

void cdData::setPicture(QString pictureAddr)
{
    *mPicture = pictureAddr;
}

void cdData::clearSongs()
{
    mSongName->clear();
}

