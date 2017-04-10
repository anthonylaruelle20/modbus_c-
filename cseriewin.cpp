#include "cseriewin.h"
#include<stdio.h>
#include"windows.h"
#include <winbase.h>

wchar_t *cseriewin::GetWC(const char *c)
{
    const size_t cSize=strlen(c)+1;
    wchar_t* wc=new wchar_t[cSize];
    mbstowcs(wc,c,cSize);
    return wc;

}

cseriewin::cseriewin(char portID[], int Baudrate, int NbBitParite, int NbBitsDonnees, int NbStopBit)
{
    bool state=false;
    char caractere;
    state=this->OuvrirPortComm(portID, Baudrate, NbBitParite, NbBitsDonnees, NbStopBit);
    while(state!=true)
    {
        printf("echec veuillez reessayez (O/n)");
        scanf("c", &caractere);
        if(caractere=='O')

        {
            state=this->OuvrirPortComm(portID, Baudrate, NbBitParite, NbBitsDonnees, NbStopBit);
        }
    }
}

  bool cseriewin::OuvrirPortComm(char portID[], int Baudrate, int NbBitParite, int NbBitsDonnees, int NbStopBit)
{

 wchar_t*port=this->GetWC(portID);
 this->hcomm=::CreateFile(port, GENERIC_ALL,0,0,OPEN_EXISTING,0,0);

 if((GetCommState(this->hcomm, &(this->config))==0))
{
         printf("Impossible d'acceder au port\n ");
         return false;

}

         this->config.BaudRate=Baudrate;
         this->config.StopBits=NbStopBit;
         this->config.Parity=NbBitParite;
         this->config.ByteSize=NbBitsDonnees;


         if(!SetCommState(this->hcomm, &this->config))
 {


         printf("Impossible d'utiliser le port");
         return false;
  }

         else
{
  printf("Les parametres sont:\n Vitesse de transmission %d Vitesse Bauds\n Parite %d, bits(s)\n taille des octets %d bits\n bit(s) de stop %d bits(s)\n\n", this->config.BaudRate, this->config.Parity,this->config.ByteSize,this->config.StopBits);
  printf("le port est ouvert\n\n");
  return true;
  }
  }





         unsigned short cseriewin::EcrireNOctets(unsigned char*pListeOctets, unsigned short NbOctets)
 {
         DWORD dwBytesWritten=NbOctets;
         unsigned short write;

         write=WriteFile(this->hcomm, pListeOctets, (DWORD) NbOctets, &dwBytesWritten, NULL);
         return write;


  }

unsigned short cseriewin::LireNOctets(unsigned char *pListeOctets, unsigned short *NbOctets)
{
  COMSTAT EtatComm;
  DWORD Octetslus;
  int retour;


  ClearCommError(this->hcomm, NULL,&EtatComm);
  printf("Nombre de caracteres a lire:%ld\n",EtatComm.cbInQue);
  retour=ReadFile(this->hcomm, pListeOctets,EtatComm.cbInQue, &Octetslus,NULL);


  *NbOctets = EtatComm.cbInQue;
  return retour;
}



         void cseriewin::FermerPort(HANDLE)

         {

             CloseHandle(hcomm);

         }





















