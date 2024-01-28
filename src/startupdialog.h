#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "passworddialog.h"

namespace Ui {
class LoginDialog;
}

class StartupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartupDialog(QWidget *parent = nullptr);
    ~StartupDialog();

public slots:
    void selectFile();
    void newNotebook();

private:
    Ui::LoginDialog *ui;
    MainWindow *mw;
    PasswordDialog *pd = nullptr;

};

#endif // STARTUPDIALOG_H
