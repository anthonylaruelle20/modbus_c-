#include "cmodbusapplication.h"

CModbusApplication::CModbusApplication()
{
    Decalage=0;
    DebutConfirmation=0;
}

void CModbusApplication::ConstruireRequeteReadInputRegisters(unsigned short Adresse, unsigned short NbMots)
{
    TrameRequete=new TOctet[300];

    TrameRequete[0+Decalage]=0x03;
    TrameRequete[1+Decalage]=Adresse>>8;
    TrameRequete[2+Decalage]=Adresse&0x00FF;
    TrameRequete[3+Decalage]=NbMots>>8;
    TrameRequete[4+Decalage]=NbMots&0x00FF;

    LongueurTrameRequete=5+Decalage;
}

void CModbusApplication::GetTrameRequete(TOctet *Trame_Requete, unsigned short *NbOctets)
{
    int i;
    i=0;

    while(i<LongueurTrameRequete)
    {

    Trame_Requete[i]=TrameRequete[i];
    i=i+1;

    }

 (*NbOctets=LongueurTrameRequete);
}


void CModbusApplication::SetTrameConfirmation(TOctet Trame_Confirmation[], unsigned short NbOctets)
{
   int j;
    LongueurTrameConfirmation=NbOctets;
   TrameConfirmation=new  TOctet[NbOctets];

   j=0;

   while(j<=NbOctets)
   {
   TrameConfirmation[j]=Trame_Confirmation[j];
   j=j+1;
   }


}

void CModbusApplication::AnalyserConfirmationReadInputRegisters(unsigned short Mots[], unsigned short *NombreMots)
{

 int i;
 int j;

 i=0;
 j=2;
LongueurTrameConfirmation=TrameConfirmation[1+DebutConfirmation]/2;

 while (i<LongueurTrameConfirmation)
     {

     Mots[i]=(TrameConfirmation[j+DebutConfirmation]<<8)|TrameConfirmation[j+1+DebutConfirmation];
     i=i+1;
     j=j+2;
     }
 (*NombreMots=LongueurTrameConfirmation);

}



CModbusApplication::~CModbusApplication()
{
    delete[]TrameRequete;
    delete[]TrameConfirmation;
}











