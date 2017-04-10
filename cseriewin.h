#ifndef CSERIEWIN_H
#define CSERIEWIN_H
#include"ccommunication.h"
#include"windows.h"
#include"winbase.h"

class cseriewin
{

private:
    HANDLE hcomm;
    DCB config;
    wchar_t *GetWC(const char *c);
    bool OuvrirPortComm(char portID[], int Baudrate, int NbBitParite, int NbBitsDonnees, int NbStopBit);
    void FermerPort(HANDLE);

public:

    cseriewin(char portID[], int Baudrate, int NbBitParite, int NbBitsDonnees, int NbStopBit );
    unsigned short EcrireNOctets(unsigned char *pListeOctets, unsigned short NbOctets);
    unsigned short LireNOctets(unsigned char*pListeOctets, unsigned short *NbOctets);


};

#endif // CSERIEWIN_H
