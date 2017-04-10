#include "cmodbusligneseriertu.h"

CModbusLigneSerieRTU::CModbusLigneSerieRTU():CModbusApplication()
{
    Decalage=1;
    DebutConfirmation=1;
}

void CModbusLigneSerieRTU::ConstruireRequeteReadInputRegisters(TOctet NumeroSeeveur, unsigned short AdresseModbusServeur, unsigned short NombreMots)
{

    unsigned short CRC;
    CModbusApplication::ConstruireRequeteReadInputRegisters(AdresseModbusServeur,NombreMots);
    TrameRequete[0]=NumeroSeeveur;


    CRC=CalculerCRC16(TrameRequete,LongueurTrameRequete);

    TrameRequete[LongueurTrameRequete]=(CRC&0x00FF);
    TrameRequete[LongueurTrameRequete+Decalage]=(CRC)>>8;


    LongueurTrameRequete=LongueurTrameRequete+2;


}

unsigned short CModbusLigneSerieRTU::CalculerCRC16(TOctet Trame[], int NombreOctets)
{
  int index=0;
  int n;
  int retenue=0;
  unsigned short CRC=0xffff;

  do
  {
      CRC=Trame[index]^CRC;
      n=0;

      do{
          retenue=(CRC&0x0001);
          CRC=CRC>>1;
          if(retenue==0x0001)
          {
              CRC=CRC^0xA001;
          }
          n=n+1;
      }while (!(n>7));
      index=index+1;

  }while(!(index==NombreOctets));

  return CRC;

}

int CModbusLigneSerieRTU::AnalyserConfirmationReadInputRegisters(unsigned short Mots[], unsigned short *NombreMots)
{

    unsigned short verifCRC=CalculerCRC16(TrameConfirmation,LongueurTrameConfirmation);

    if(verifCRC==0)
    {
        qDebug()<<"\n";
        qDebug()<<"CRC ok";
        CModbusApplication::AnalyserConfirmationReadInputRegisters(Mots,NombreMots);
    }

    else
    {
        qDebug()<<"erreur CRC";
    }
}


unsigned short CModbusLigneSerieRTU::CalculerCRC16r(TOctet Trame, int NombreOctets)
{

}














