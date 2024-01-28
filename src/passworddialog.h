#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class PasswordDialog;
}

class PasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordDialog(QWidget *parent = nullptr);
    ~PasswordDialog();
    MainWindow *mw = nullptr;
    bool showMw;

public slots:
    void ok();
    void cancel();

private:
    Ui::PasswordDialog *ui;
};

#endif // PASSWORDDIALOG_H
