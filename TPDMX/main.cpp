//*********************************************************************************************
//* Programme : main.cpp											date : 09/11/2021
//*---------------------------------------------------------------------------------------------------------
//* dernière mise a jour : 09/11/2021
//*
//*Programmeurs : BERTHIER Thomas										classe : BTSSN2
//*				  BOUCHER Louis
//*				  CAUET Clément
//*--------------------------------------------------------------------------------------------------------
//* BUT : Instancie une connexion a l'interface USB-DMX et lance l'application
//*Programmes associés : AUCUN
//*********************************************************************************************

#include "DMXUSB.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	DMXUSB dmx;
    
	dmx.show();
	
    return a.exec();
}
