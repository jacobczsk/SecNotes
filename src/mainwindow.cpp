#include "mainwindow.h"
#include "passworddialog.h"
#include "files/filehandling.h"
#include "ui_mainwindow.h"
#include "mrichtextedit.h"

#define MODE_HTML 0
#define MODE_PLAINTEXT 1

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::newNote()
{
    lastNew++;
    Note empty("New note " + to_string(lastNew), "");
    notes.push_back(empty);
    ui->listWidget->addItem(tr(empty.title.c_str()));
}

void MainWindow::activate(bool activate)
{
    ui->actionPlain_text->setEnabled(activate);
    ui->actionRich_text_HTML->setEnabled(activate);
    ui->textEdit->setEnabled(activate);
    ui->noteName->setEnabled(activate);
    ui->actionSaveNote->setEnabled(activate);
    ui->actionDelete->setEnabled(activate);
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
        activate(false);
        return;
    }
    activate(true);
    ui->noteName->setText(tr(gNote->title.c_str()));
    if (gNote->html) {
        changeMode(MODE_HTML);
        ui->textEdit->document()->setHtml(QString::fromStdString(gNote->contents));
    } else {
        changeMode(MODE_PLAINTEXT);
        ui->textEdit->document()->setPlainText(QString::fromStdString(gNote->contents));
    }
}

void MainWindow::saveNote()
{
    if (active == nullptr) return;
    if (active->html) {
        active->contents = ui->textEdit->toHtml().remove("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">").toStdString();
    } else {
        active->contents = ui->textEdit->toPlainText().toStdString();
    }
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

void MainWindow::modeHtml()
{
    changeMode(MODE_HTML);
}

void MainWindow::modePlain()
{
    changeMode(MODE_PLAINTEXT);
}

void MainWindow::changeMode(int mode)
{
    if (mode == MODE_HTML) {
        ui->actionRich_text_HTML->setChecked(true);
        ui->actionPlain_text->setChecked(false);
        active->html = true;
    } else if (mode == MODE_PLAINTEXT) {
        ui->actionRich_text_HTML->setChecked(false);
        ui->actionPlain_text->setChecked(true);
        active->html = false;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
