#ifndef ADDCDDIALOG_H
#define ADDCDDIALOG_H

#include <QDialog>
#include "ui_dialog.h"
#include <QFileDialog>

class addCdDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT
public:
    explicit addCdDialog(QWidget *parent = nullptr);
    bool somethingIsEmpty;

    QString getCDName() const;
    QString getAutor() const;
    int getYear() const;
    QString getGener() const;
    QString getSong(int id) const;
    int getSongCount() const;
    QString getImage() const;

    void passData(QString CDName, QString Autor, QString Year, QString Genre, QString Picture, QList<QString> outSongs);

private:
    QList<QString> songs;
    QString songsForShow;
    QString imageLocation;
    QPixmap thumb;


signals:

public slots:
private slots:

    void on_addLineButton_clicked();
    void on_removeLineButton_clicked();
    void on_changeImageButton_clicked();
};

#endif // ADDCDDIALOG_H
