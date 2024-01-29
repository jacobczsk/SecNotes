#include "mainwindow.h"
#include "passworddialog.h"
#include "files/filehandling.h"
#include "ui_mainwindow.h"
#include "mrichtextedit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->noteName->setDisabled(true);
    ui->textEdit->setDisabled(true);
}

void MainWindow::newNote()
{
    lastNew++;
    Note empty("New note " + to_string(lastNew), "");
    notes.push_back(empty);
    ui->listWidget->addItem(tr(empty.title.c_str()));
}

void MainWindow::loadNote(QListWidgetItem *item)
{
    Note *gNote = nullptr;
    for (Note &note : notes)
    {
        if (note.title == item->text().toStdString())
        {
            gNote = &note;
            active = &note;
            break;
        }
    }
    if (gNote == nullptr) {
        ui->textEdit->setDisabled(true);
        ui->noteName->setDisabled(true);
        return;
    }
    ui->textEdit->setDisabled(false);
    ui->noteName->setDisabled(false);
    ui->noteName->setText(tr(gNote->title.c_str()));
    ui->textEdit->document()->setHtml(tr(gNote->contents.c_str()));
}

void MainWindow::saveNote()
{
    if (active == nullptr) return;
    active->contents = ui->textEdit->toHtml().toStdString();
}

void MainWindow::saveNotebook()
{
    if (passphrase == tr(""))
    {
        PasswordDialog pd;
        pd.mw = this;
        pd.show();
        return;
    }
    FileHandling::writeNotebook(notes, path.toStdString(), passphrase.toStdString());
}

void MainWindow::changeNoteTitle()
{
    std::string newTitle = ui->noteName->text().toStdString();
    for (Note &note : notes) if (note.title == newTitle) return;
    active->title = newTitle;
    updateNotesList();
}

void MainWindow::updateNotesList()
{
    ui->listWidget->clear();
    for (Note &note : notes) {
        ui->listWidget->addItem(tr(note.title.c_str()));
    }
}

void MainWindow::deleteNote()
{
    vector<Note> newNotes;
    for (Note &note : notes)
        if (note.title != active->title) newNotes.push_back(note);
    notes = newNotes;
    updateNotesList();
}

void MainWindow::setup()
{
    show();
    if (!create) {
        notes = FileHandling::parseNotebook(path.toStdString(), passphrase.toStdString());
        updateNotesList();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
