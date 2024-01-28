#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <vector>
#include "files/note.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString path;
    QString passphrase;
    bool create;
    void setup();

public slots:
    void newNote();
    void loadNote(QListWidgetItem *item);
    void saveNote();
    void saveNotebook();
    void changeNoteTitle();
    void deleteNote();

private:
    Ui::MainWindow *ui;
    vector<Note> notes;
    int lastNew;
    Note *active = nullptr;
    void updateNotesList();

};

#endif // MAINWINDOW_H
