#include "cddatabase.h"

cdDatabase::cdDatabase(QObject *parent) : QObject(parent)
{
    QString inCDname;
    QString inAutor;
    QString inYear;
    QString inGenre;
    QString inpictureAddres;
    QString inSong;
    int id = 0;

    QMessageBox warning;
    warning.setText(tr("Can't find data.txt"));
    warning.setInformativeText(tr("Couldn't find data.txt. If you have such file please move it into same directory as this program. If not, new file data.txt will be created."));

    QDir imageFolder("thumbs");

    if(!imageFolder.exists())imageFolder.mkpath(".");
    QFile inputFile("data.txt");

    if (inputFile.open(QIODevice::ReadOnly)){
        if(inputFile.readLine().contains("#cdDatabase")){

            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                inCDname = in.readLine();
                inAutor = in.readLine();
                inYear = in.readLine();
                inGenre = in.readLine();
                inpictureAddres = in.readLine();

                fillDb(inCDname,inAutor,inYear.toInt(),inGenre,inpictureAddres);

                inSong = in.readLine();
                while(!inSong.contains("#####"))
                {
                    addSong(id,inSong);
                    inSong = in.readLine();
                }

                id++;
            }

            inputFile.close();

        }else{
            warning.setText(tr("Incompatible data.txt file"));
            warning.setInformativeText(tr("You might have provided wrong data.txt file. Please check program directory if included file is the right one."));
            warning.exec();
            inputFile.close();
        }

    }else {
        warning.exec();
        inputFile.close();
    }
}

cdDatabase::~cdDatabase()
{
    QFile outputFile("data.txt");
    outputFile.remove();

    if(outputFile.open(QIODevice::WriteOnly)){
        QTextStream stream(&outputFile);

        stream << "#cdDatabase manual edits not recommended" << endl;
        for(int i = 0; i < getCount();i++){

            stream << getCDName(i) << endl;
            stream << getAutorName(i) << endl;
            stream << getYear(i) << endl;
            stream << getType(i) << endl;
            stream << getPicture(i) << endl;

            int songsAmount = getNumberOfSongs(i);

            if(songsAmount > 0){
                for(int j = 0;j < songsAmount;j++){
                    stream << getSongs(i,j) << endl;
                }

            }

            stream << "#####" << endl;
        }
    }

    outputFile.close();
    CD.clear();
}

QList<QString> cdDatabase::getAllSongs(int id) //const
{
    return CD.at(id)->getSongs();
}

QString cdDatabase::getCDName(int id) const
{
    return CD.at(id)->getCDName();
}

QString cdDatabase::getAutorName(int id) const
{
    return CD.at(id)->getAutorName();
}

QString cdDatabase::getYear(int id) const
{
    QString str = QString::number(CD.at(id)->getYear());
    return str;
}

QString cdDatabase::getType(int id) const
{
    return CD.at(id)->getType();
}

QString cdDatabase::getSongs(int id,int songID) const
{
    return CD.at(id)->getSong(songID);
}

QString cdDatabase::getPicture(int id) const
{
    return CD.at(id)->getPicture();
}

int cdDatabase::getNumberOfSongs(int id) const
{
    return CD.at(id)->getNumberOfSongs();
}

int cdDatabase::getCount() const
{
    return CD.count();
}

void cdDatabase::fillDb(QString CDName, QString Autor, int Year, QString Genre, QString Picture)
{
    cdData *newCD = new cdData;

    if(CDName.isEmpty())CDName.append("---");
    if(Autor.isEmpty())Autor.append("---");
    if(Genre.isEmpty())Genre.append("---");

    newCD->setAutorName(Autor);
    newCD->setCDName(CDName);
    newCD->setType(Genre);
    newCD->setYear(Year);
    if(QFileInfo(Picture).exists())newCD->setPicture(Picture);
    else newCD->setPicture(":/images/none.png");

    CD.append(newCD);

}

void cdDatabase::fillDb(QString CDName, QString Autor, int Year, QString Genre)
{
    cdData *newCD = new cdData;

    newCD->setAutorName(Autor);
    newCD->setCDName(CDName);
    newCD->setType(Genre);
    newCD->setYear(Year);
    newCD->setPicture(":/images/none.png");

    CD.append(newCD);
}

void cdDatabase::editDB(int id,QString CDName, QString Autor, int Year, QString Genre, QString Picture)
{
    CD.at(id)->setCDName(CDName);
    CD.at(id)->setAutorName(Autor);
    CD.at(id)->setYear(Year);
    CD.at(id)->setType(Genre);
    CD.at(id)->setPicture(Picture);

}

void cdDatabase::addSong(int id, QString songName)
{
    CD.at(id)->addSong(songName);
}

void cdDatabase::removeCD(int id)
{
    CD.removeAt(id);

}

void cdDatabase::clearSongs(int id)
{
    CD.at(id)->clearSongs();
}

void cdDatabase::dbClear()
{
    CD.clear();
}
