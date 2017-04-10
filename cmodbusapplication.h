#ifndef CMODBUSAPPLICATION_H
#define CMODBUSAPPLICATION_H
#include<stdio.h>
typedef unsigned char TOctet;


class CModbusApplication
{
public:
    CModbusApplication();
    ~CModbusApplication();

    void conv(unsigned short entier[],int nb);
    void ConstruireRequeteReadInputRegisters(unsigned short Adresse,unsigned short NbMots);
    void GetTrameRequete(TOctet TrameRequete[],unsigned short *NbOctets);
    void SetTrameConfirmation(TOctet Trame_Confirmation[],unsigned short NbOctets);
    void AnalyserConfirmationReadInputRegisters(unsigned short Mots[],unsigned short *NombreMots);

protected:
    unsigned short LongueurTrameRequete;
    unsigned short LongueurTrameConfirmation;
    TOctet*TrameRequete;
    TOctet*TrameConfirmation;
    int Decalage;
    int DebutConfirmation;


};

#endif // CMODBUSAPPLICATION_H
