#include "note.h"

Note::Note(string title, string contents)
{
    this->title = title;
    this->contents = contents;
}

string Note::getTitle() { return title; }
void Note::setTitle(string title) { this->title = title; }

string Note::getContents() { return contents; }
void Note::setContents(string contents) { this->contents = contents; }
