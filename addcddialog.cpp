#include "addcddialog.h"

addCdDialog::addCdDialog(QWidget *parent) : QDialog(parent)
{
    imageLocation.clear();
    somethingIsEmpty = true;
    setupUi(this);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

QString addCdDialog::getCDName() const
{
    return dialogCdName->text();
}

QString addCdDialog::getAutor() const
{
    return dialogAutor->text();
}

int addCdDialog::getYear() const
{
    return dialogYear->text().toInt();
}

QString addCdDialog::getGener() const
{
    return dialogGenre->text();
}

QString addCdDialog::getSong(int id) const
{
    return songs.at(id);
}

int addCdDialog::getSongCount() const
{
    return songs.count();
}

QString addCdDialog::getImage() const
{
    return imageLocation;
}

void addCdDialog::passData(QString CDName, QString Autor, QString Year, QString Genre, QString Picture, QList<QString> outSongs)
{
    thumb = Picture;
    imageLocation = Picture;
    songs = outSongs;
    songsForShow.clear();

    for(int i = 0; i < songs.count(); i++){
        if(i % 5 == 0) songsForShow.append("\n");
        else songsForShow.append(" ");
        songsForShow.append(songs.at(i));
    }
    songListLabel->setText(songsForShow);

    dialogCdName->setText(CDName);
    dialogAutor->setText(Autor);
    dialogGenre->setText(Genre);
    dialogYear->setText(Year);
    thumbImage->setPixmap(thumb);
}


void addCdDialog::on_addLineButton_clicked()
{
    songs.append(dialogAddSong->text());
    songsForShow.clear();

    for(int i = 0; i < songs.count(); i++){
        if(i % 5 == 0) songsForShow.append("\n");
        else songsForShow.append(" ");
        songsForShow.append(songs.at(i));
    }

    songListLabel->setText(songsForShow);
}

void addCdDialog::on_removeLineButton_clicked()
{
    songsForShow.clear();
    songs.clear();
    songListLabel->setText("");
}

void addCdDialog::on_changeImageButton_clicked()
{
    QString newName;
    QString oldName;
    imageLocation = QFileDialog::getOpenFileName(this,tr("Chose picture"),"",tr("Images (*.png *.bmp *.jpg *.jpeg)"));
    if (!imageLocation.isEmpty()){
        oldName = imageLocation;

        while(imageLocation.contains("/"))
        {
            imageLocation.remove(0,1);
        }

        newName.append("thumbs/");
        newName.append(imageLocation);

        QFile::copy(oldName,newName);

        thumb.load(newName);
        thumbImage->setPixmap(thumb);

        imageLocation = newName;
    }
}
