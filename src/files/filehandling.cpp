#include "filehandling.h"
#include "note.h"
#include "../okcrypt/okcrypt.h"
#include <pugixml.hpp>
#include <pugiconfig.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>

using namespace std;
using namespace pugi;

vector<Note> FileHandling::parseNotebook(string path, string passphrase)
{
    xml_document doc;

    if (!(doc.load_file(path.c_str()))) {
        vector<Note> empty;
        return empty;
    }

    vector<Note> result;

    int okStart = 0;
    for (xml_node xmlNote : doc.child("Notebook").children("Note")) {
        string title = OKCrypt::decrypt(xmlNote.child("Title").text().as_string(), passphrase, okStart);
        okStart += title.length();
        string content = OKCrypt::decrypt(xmlNote.child("Content").text().as_string(), passphrase, okStart);
        okStart += content.length();
        Note note(title, content);
        result.push_back(note);
    }

    return result;
}

void FileHandling::writeNotebook(vector<Note> notes, string path, string passphrase)
{
    xml_document doc;
    xml_node notebook = doc.append_child("Notebook");
    int okStart = 0;
    for (Note &note : notes) {
        xml_node xmlNote = notebook.append_child("Note");
        xmlNote.append_child("Title").append_child(node_pcdata).set_value(OKCrypt::encrypt(note.title, passphrase, okStart).c_str());
        okStart += note.title.length();
        xmlNote.append_child("Content").append_child(node_pcdata).set_value(OKCrypt::encrypt(note.contents.c_str(), passphrase, okStart).c_str());
        okStart += note.contents.length();
    }
    doc.save_file(path.c_str());
}
