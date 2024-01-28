#include "startupdialog.h"
#include "mainwindow.h"
#include "ui_startupdialog.h"
#include "passworddialog.h"
#include <QFileDialog>

StartupDialog::StartupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog), mw(new MainWindow), pd(new PasswordDialog)
{
    pd->mw = mw;
    pd->showMw = true;
    ui->setupUi(this);
}

void StartupDialog::selectFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open notebook", "/", "SecNotes (*.secn)");
    if (path == "") return;
    close();
    mw->path = path;
    mw->create = false;
    pd->show();
}

void StartupDialog::newNotebook()
{
    QString path = QFileDialog::getSaveFileName(this, "New notebook", "/", "SecNotes (*.secn)");
    if (path == "") return;
    close();
    mw->path = path;
    mw->create = true;
    pd->show();
}

StartupDialog::~StartupDialog()
{
    delete ui;
}
