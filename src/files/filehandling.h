#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <vector>
#include "note.h"

class FileHandling
{
public:
    static vector<Note> parseNotebook(string path, string passphrase);
    static void writeNotebook(vector<Note> notes, string path, string passphrase);
};

#endif // FILEHANDLING_H
