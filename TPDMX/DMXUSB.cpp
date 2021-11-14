//*********************************************************************************************
//* Programme : DMXUSB.cpp											date : 09/11/2021
//*---------------------------------------------------------------------------------------------------------
//* dernière mise a jour : 09/11/2021
//*
//*Programmeurs : BERTHIER Thomas										classe : BTSSN2
//*				  BOUCHER Louis
//*				  CAUET Clément
//*--------------------------------------------------------------------------------------------------------
//* BUT : Gérer les couleurs et la luminosité des lampes saber spot RGBW.
//*Programmes associés : main.cpp
//*********************************************************************************************

#include "DMXUSB.h"
#include <qdebug.h>
#include <qtimer.h>

DMXUSB::DMXUSB(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//Charge la DLL et effectue le connexion à la carte
	g_dasusbdll = LoadLibrary(L"DasHard2006.dll");

	if (g_dasusbdll)
		DasUsbCommand = (DASHARDCOMMAND)::GetProcAddress((HMODULE)g_dasusbdll, "DasUsbCommand");
	interface_open = DasUsbCommand(DHC_INIT, 0, NULL);
	interface_open = DasUsbCommand(DHC_OPEN, 0, 0);
	//Réinitialisation des lampes
	for (int i = 0; i < DMX_MAXCHANNEL + 1; i++) {
		dmxBlock[i] = 0;
		SendTrame();
	}

	timer = new QTimer(this);

}

DMXUSB::~DMXUSB()
{
}
//Envoie une trame a l'interface USB-DMX
void DMXUSB::SendTrame()
{
	if (interface_open > 0)
	{
		DasUsbCommand(DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock);
	}
}

//Récupére la valeur du curseur en parametre et change la couleur rouge de la lampe 1 en fonction de celle-ci
void DMXUSB::red(int newRedValue)
{
	dmxBlock[0] = newRedValue; //rouge
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur verte de la lampe 1 en fonction de celle-ci
void DMXUSB::green(int newGreenValue)
{
	dmxBlock[1] = newGreenValue; //vert
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur bleue de la lampe 1 en fonction de celle-ci
void DMXUSB::blue(int newBlueValue)
{
	dmxBlock[2] = newBlueValue; //bleu
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur blanche de la lampe 1 en fonction de celle-ci
void DMXUSB::white(int newWhiteValue)
{
	dmxBlock[3] = newWhiteValue; //blanc
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur rouge de la lampe 2 en fonction de celle-ci
void DMXUSB::red2(int newRedValue)
{
	dmxBlock[4] = newRedValue; //rouge
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur verte de la lampe 2 en fonction de celle-ci
void DMXUSB::green2(int newGreenValue)
{
	dmxBlock[5] = newGreenValue; //vert
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur bleue de la lampe 2 en fonction de celle-ci
void DMXUSB::blue2(int newBlueValue)
{
	dmxBlock[6] = newBlueValue; //bleu
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur blanche de la lampe 2 en fonction de celle-ci
void DMXUSB::white2(int newWhiteValue)
{
	dmxBlock[7] = newWhiteValue; //blanc
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur rouge de la lampe 3 en fonction de celle-ci
void DMXUSB::red3(int newRedValue)
{
	dmxBlock[8] = newRedValue; //rouge
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur verte de la lampe 3 en fonction de celle-ci
void DMXUSB::green3(int newGreenValue)
{
	dmxBlock[9] = newGreenValue; //vert
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur bleue de la lampe 3 en fonction de celle-ci
void DMXUSB::blue3(int newBlueValue)
{
	dmxBlock[10] = newBlueValue; //bleu
	SendTrame();
}

//Récupére la valeur du curseur en parametre et change la couleur blanche de la lampe 3 en fonction de celle-ci
void DMXUSB::white3(int newWhiteValue)
{
	dmxBlock[11] = newWhiteValue; //blanc
	SendTrame();
}

//Lorsque le bouton StartAuto est cliqué, réinitialise les trois premières lampes et lance un timer
void DMXUSB::startAuto()
{
	for (int i = 0; i < 12; i++)
	{
		dmxBlock[i] = 0;
	}
	SendTrame();
	
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(loop()));
	timer->start(1);
}

//Lorsque le bouton StopAuto est cliqué, arrete le défilement automatique des couleurs
void DMXUSB::stopAuto()
{
	stop = true;
	QObject::disconnect(timer, SIGNAL(timeout()), this, SLOT(loop()));
}

//Effectue le changement automatique des couleurs a chaque fin de timer
void DMXUSB::loop()
{
	//state 0 = rouge
	if (state == 0)
	{
		if (i < 256 && limit == false)
		{
			SendTrame();
			dmxBlock[0] = i;
			dmxBlock[4] = i;
			dmxBlock[8] = i;
			i++;
			if (i == 256)
				limit = true;
			
		}
		if (i > 0 && limit == true)
		{
			i--;
			dmxBlock[0] = i;
			dmxBlock[4] = i;
			dmxBlock[8] = i;
			SendTrame();
		}
		if (i == 0)
		{
			state++;
			i = 1;
			limit = false;
		}
	}
	//state 1 = vert
	if (state == 1)
	{
		if (i < 256 && limit == false)
		{
			SendTrame();
			dmxBlock[1] = i;
			dmxBlock[5] = i;
			dmxBlock[9] = i;
			i++;
			if (i == 256)
				limit = true;
			
		}
		if (i > 0 && limit == true)
		{
			i--;
			dmxBlock[1] = i;
			dmxBlock[5] = i;
			dmxBlock[9] = i;
			SendTrame();
		}
		if (i == 0)
		{
			state++;
			i = 1;
			limit = false;
		}
	}
	//state 2 = bleu
	if (state == 2)
	{
		if (i < 256 && limit == false)
		{
			SendTrame();
			dmxBlock[2] = i;
			dmxBlock[6] = i;
			dmxBlock[10] = i;
			i++;
			if (i == 256)
				limit = true;
			
		}
		if (i > 0 && limit == true)
		{
			i--;
			dmxBlock[2] = i;
			dmxBlock[6] = i;
			dmxBlock[10] = i;
			SendTrame();
		}
		if (i == 0)
		{
			state++;
			i = 1;
			limit = false;
		}
	}
	//state 3 = blanc
	if (state == 3)
	{
		if (i < 256 && limit == false)
		{
			SendTrame();
			dmxBlock[3] = i;
			dmxBlock[7] = i;
			dmxBlock[11] = i;
			i++;
			if (i == 256)
				limit = true;
			
		}
		if (i > 0 && limit == true)
		{
			i--;
			dmxBlock[3] = i;
			dmxBlock[7] = i;
			dmxBlock[11] = i;
			SendTrame();
		}
		if (i == 0)
			if (i == 0)
			{
				state = 0;
				i = 1;
				limit = false;
			}
	}
}



