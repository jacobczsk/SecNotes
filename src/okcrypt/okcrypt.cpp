#include "okcrypt.h"
#include <cmath>
#include <string>
#include <QCryptographicHash>
#include <QByteArray>

using namespace std;

int lowestPrimeDivider(int num)
{
    for (int i = 2; i < sqrt(num); i++) {
        if (num % i == 0) return i;
    }
    return 2;
}

int magic(char c, int pos)
{
    int clpd = (lowestPrimeDivider(c) * c);
    return ceil(sqrt(abs(clpd * sin(pos)))) * ceil(abs(2*sin(clpd)));
}

string OKCrypt::encrypt(string data, string passphrase, int start)
{
    string result;
    string passhash = QCryptographicHash::hash(QByteArray::fromStdString(passphrase), QCryptographicHash::Sha512).toHex().toStdString();
    for (int i = 0; i < data.length(); i++) {
        int pos = i;
        if (pos == 0) pos++;
        result += data[i] + magic(passhash[(i + start) % passhash.length()], pos);
    }
    return result;
}

string OKCrypt::decrypt(string data, string passphrase, int start)
{
    string result;
    string passhash = QCryptographicHash::hash(QByteArray::fromStdString(passphrase), QCryptographicHash::Sha512).toHex().toStdString();
    for (int i = 0; i < data.length(); i++) {
        int pos = i;
        if (pos == 0) pos++;
        result += data[i] - magic(passhash[(i + start) % passhash.length()], pos);
    }
    return result;
}
