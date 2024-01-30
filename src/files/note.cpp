#include "note.h"

Note::Note(string title, string contents, bool html)
{
    this->title = title;
    this->contents = contents;
    this->html = html;
}
