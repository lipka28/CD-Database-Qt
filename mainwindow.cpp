#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myDefault.load(":/images/none.png");
    database = new cdDatabase(this);
    model = new QStandardItemModel(1,1,this);

    this->setGeometry(QStyle::alignedRect(
                          Qt::LeftToRight,
                          Qt::AlignCenter,
                          this->size(),
                          qApp->desktop()->availableGeometry()
                          )
                      );

    ui->setupUi(this);
    ui->listViewAlba->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->songListChangeable->setReadOnly(true);

    updateData();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listViewAlba_clicked(const QModelIndex &index)
{
    if(model->item(index.row())->isEnabled()){
    globalIndex = index.row();
    myPixmap.load(database->getPicture(index.row()));
    ui->cdNameChangable->setText(database->getCDName(index.row()));
    ui->autorChangable->setText(database->getAutorName(index.row()));
    ui->rokChangable->setText(database->getYear(index.row()));
    ui->zanrChangable->setText(database->getType(index.row()));
    ui->thumbImage->setPixmap(myPixmap);

    QString songs;
    for(int i = 0; i < database->getNumberOfSongs(index.row());i++){
    songs.append(database->getSongs(index.row(),i)+"\n");
    }

    ui->songListChangeable->setText(songs);
    }

}

void MainWindow::on_pushButtonAdd_clicked()
{
    addDialog = new addCdDialog(this);

    if(addDialog->exec()){
    database->fillDb(addDialog->getCDName(),addDialog->getAutor(),addDialog->getYear(),addDialog->getGener(),addDialog->getImage());
    for(int i = 0; i < addDialog->getSongCount();i++){
        database->addSong(database->getCount()-1,addDialog->getSong(i));
    }

    updateData();}

    delete addDialog;
}

void MainWindow::updateData()
{
    model->clear();

    for( int i=0; i<database->getCount(); i++ )
        {
                QStandardItem *item = new QStandardItem(database->getCDName(i));
                model->setItem(i, item);
        }

    ui->listViewAlba->setModel(model);

    ui->thumbImage->setPixmap(myDefault);
    ui->songListChangeable->setText("");
    ui->autorChangable->setText("");
    ui->cdNameChangable->setText("");
    ui->zanrChangable->setText("");
    ui->rokChangable->setText("");

    globalIndex = -1;

}

void MainWindow::on_pushButtonRemove_clicked()
{
    database->removeCD(globalIndex);
    updateData();
}

void MainWindow::on_pushButtonEdit_clicked()
{
    if(globalIndex >= 0){
    addDialog = new addCdDialog(this);

    addDialog->passData(database->getCDName(globalIndex),database->getAutorName(globalIndex),database->getYear(globalIndex),database->getType(globalIndex),database->getPicture(globalIndex),database->getAllSongs(globalIndex));

    if(addDialog->exec()){
    database->editDB(globalIndex,addDialog->getCDName(),addDialog->getAutor(),addDialog->getYear(),addDialog->getGener(),addDialog->getImage());
    database->clearSongs(globalIndex);
    for(int i = 0; i < addDialog->getSongCount();i++){
        database->addSong(globalIndex,addDialog->getSong(i));
    }

    updateData();}

    delete addDialog;
    }
}

void MainWindow::on_pushButtonSearch_clicked()
{
    searchTerm(ui->searchLine->text());
}

void MainWindow::searchTerm(QString search)
{
    model->clear();
    //int index =0;


    for( int i=0; i<database->getCount(); i++ )
    { if(database->getAutorName(i).contains(search,Qt::CaseInsensitive)){
            QStandardItem *item = new QStandardItem(database->getCDName(i));
            model->setItem(i, item);
            //index++;

        }else if(database->getType(i).contains(search,Qt::CaseInsensitive)){
            QStandardItem *item = new QStandardItem(database->getCDName(i));
            model->setItem(i, item);

        }else if(database->getYear(i).contains(search,Qt::CaseInsensitive)){
            QStandardItem *item = new QStandardItem(database->getCDName(i));
            model->setItem(i, item);
        }else{
            QStandardItem *item = new QStandardItem(database->getCDName(i));
            //item->setEnabled(false);
            model->setItem(i, item);
            model->item(i)->setEnabled(false);
        }

      }

    ui->listViewAlba->setModel(model);

    ui->thumbImage->setPixmap(myDefault);
    ui->songListChangeable->setText("");
    ui->autorChangable->setText("");
    ui->cdNameChangable->setText("");
    ui->zanrChangable->setText("");
    ui->rokChangable->setText("");

    globalIndex = INT_MAX;

}

void MainWindow::on_pushButtonClear_clicked()
{
    updateData();
}
