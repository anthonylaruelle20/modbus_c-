#ifndef CMODBUSLIGNESERIERTU_H
#define CMODBUSLIGNESERIERTU_H
#include<cmodbusapplication.h>
#include<QDebug>
class CModbusLigneSerieRTU :public CModbusApplication
{
public:
    CModbusLigneSerieRTU();
    void ConstruireRequeteReadInputRegisters(TOctet NumeroSeeveur,unsigned short AdresseModbusServeur,unsigned short NombreMots);
    int AnalyserConfirmationReadInputRegisters(unsigned short Mots[], unsigned short *NombreMots);
    unsigned short CalculerCRC16r(TOctet Trame,int NombreOctets);
    unsigned short CalculerCRC16(TOctet Trame[],int NombreOctets);
private: TOctet*CRCPoidsFort[2];
         TOctet*CRCPoidsFaible[2];

};

#endif // CMODBUSLIGNESERIERTU_H
