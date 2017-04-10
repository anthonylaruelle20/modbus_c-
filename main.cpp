#include <QCoreApplication>
#include<cmodbusapplication.h>
#include<cmodbusligneseriertu.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    unsigned short LongueurRequete=0;
    unsigned short LongueurConfirmation=0;

    unsigned short TailleConfirmation=0;

    unsigned short NombreMots=0;
    unsigned short Mots[TailleConfirmation];

    TOctet TrameRequete[LongueurRequete];
    TOctet TrameConfirmation[LongueurConfirmation];
//********************************************************************************Application
 /*

    int i=0;
    int j;
    int k;

    CModbusApplication modbus;

    while(i<3)
    {
    scanf("%02x",&Mots[i]);
    i=i+1;
    }
printf("%02x",Mots[0]);
printf("%02x",Mots[1]);
printf("%02x",Mots[2]);
    modbus.conv(Mots,3);





    modbus.ConstruireRequeteReadInputRegisters(0x220,2);

    modbus.GetTrameRequete(TrameRequete,&LongueurRequete);
printf("Trame Requete: ");
    i=0;
    while(i<LongueurRequete)
    {
        printf("%02x",TrameRequete[i]);
        i=i+1;
    }
    printf("\n");

    printf("Trame Reponse: ");

        TrameConfirmation[0]=0x03;
        TrameConfirmation[1]=0x04;
        TrameConfirmation[2]=0x20;
        TrameConfirmation[3]=0x23;
        TrameConfirmation[4]=0x32;
        TrameConfirmation[5]=0x05;


    LongueurConfirmation=6;

modbus.SetTrameConfirmation(TrameConfirmation,LongueurConfirmation);

j=0;
while(j<LongueurConfirmation)
{
    printf("%02x ",TrameConfirmation[j]);
    j=j+1;
}

modbus.AnalyserConfirmationReadInputRegisters(Mots,&NombreMots);
k=0;
printf("\n");

printf("TrameConfirmation: ");

while(k<NombreMots)
{
    printf("%04x ",Mots[k]);
    k=k+1;
}
*/
//*********************************************************************************//FinApplication

    CModbusLigneSerieRTU modbus;
    int i;
    int m;
    int o;
    unsigned short crc;
    i=0;
    modbus.ConstruireRequeteReadInputRegisters(0x01,0x0220,2);

    modbus.GetTrameRequete(TrameRequete,&LongueurRequete);

    while(i<LongueurRequete)
    {
        printf("%02x ",TrameRequete[i]);
        i=i+1;
    }

    printf("\n");

    TrameConfirmation[0]=0x01;
    TrameConfirmation[1]=0x03;
    TrameConfirmation[2]=0x04;
    TrameConfirmation[3]=0x02;
    TrameConfirmation[4]=0x06;
    TrameConfirmation[5]=0x04;
    TrameConfirmation[6]=0x52;

    LongueurConfirmation=7;

    crc=modbus.CalculerCRC16(TrameConfirmation,LongueurConfirmation);
    TrameConfirmation[7]=crc&0x00FF;
    TrameConfirmation[8]=crc>>8;

    LongueurConfirmation=9;
    modbus.SetTrameConfirmation(TrameConfirmation,LongueurConfirmation);

    m=0;
    while(m<LongueurConfirmation)
    {
        printf("%02x ",TrameConfirmation[m]);
        m=m+1;
    }

    modbus.AnalyserConfirmationReadInputRegisters(Mots,&NombreMots);
    o=0;
    printf("\n");


    while(o<NombreMots)
    {
        printf("%04x ",Mots[o]);
        o=o+1;
    }

    return a.exec();
}
