#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "cddatabase.h"
#include "addcddialog.h"
#include <QPixmap>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
class addCdDialog;
class addSongDialog;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_listViewAlba_clicked(const QModelIndex &index);

    void on_pushButtonAdd_clicked();

    void updateData();

    void on_pushButtonRemove_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonClear_clicked();

private:

    void searchTerm(QString search);

    Ui::MainWindow *ui;
    QStandardItemModel *model;
    cdDatabase *database;
    addCdDialog *addDialog;
    int globalIndex;
    QPixmap myDefault;
    QPixmap myPixmap;
};

#endif // MAINWINDOW_H
