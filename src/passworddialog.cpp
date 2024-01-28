#include "passworddialog.h"
#include "ui_passworddialog.h"
#include "mainwindow.h"
#include <QDialogButtonBox>
#include <QPushButton>

PasswordDialog::PasswordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PasswordDialog)
{
    ui->setupUi(this);
}

void PasswordDialog::ok()
{
    mw->passphrase = ui->psph->text();
    close();
    if (showMw) mw->setup();
}

void PasswordDialog::cancel()
{
    close();
}

PasswordDialog::~PasswordDialog()
{
    delete ui;
}
