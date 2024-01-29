#ifndef NOTE_H
#define NOTE_H

#include <string>

using namespace std;

class Note
{
public:
    Note(string title, string contents);
    string contents, title;
    bool html = true;
};

#endif // NOTE_H
