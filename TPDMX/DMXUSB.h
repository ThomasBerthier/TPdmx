//*********************************************************************************************
//* Programme : DMXUSB.h											date : 09/11/2021
//*---------------------------------------------------------------------------------------------------------
//* dernière mise a jour : 09/11/2021
//*
//*Programmeurs : BERTHIER Thomas										classe : BTSSN2
//*				  BOUCHER Louis
//*				  CAUET Clément
//*--------------------------------------------------------------------------------------------------------
//* BUT : Gérer les couleurs et la luminosité des lampes saber spot RGBW.
//*Programmes associés : DMXUSB.cpp
//*********************************************************************************************

#pragma once

#include <QWidget>
#include "ui_DMXUSB.h"
#include "DasHard.h"
#include <Windows.h>
#include <qtimer.h>

#define DMX_MAXCHANNEL 512

class DMXUSB : public QWidget
{
	Q_OBJECT
	HINSTANCE g_dasusbdll;
public:
	DMXUSB(QWidget *parent = Q_NULLPTR);
	~DMXUSB();
	typedef int(*DASHARDCOMMAND)(int, int, unsigned char*);
	DASHARDCOMMAND DasUsbCommand;
	int interface_open;
	unsigned char dmxBlock[512];
	void SendTrame();
	bool stop = false;
	QTimer * timer;
	int state = 0;
	bool limit = false;
	int i = 1;

private:
	Ui::DMXUSB ui;

	public slots:
		void red(int newRedValue);
		void green(int newGreenValue);
		void blue(int newBlueValue);
		void white(int newWhiteValue);

		void red2(int newRedValue);
		void green2(int newGreenValue);
		void blue2(int newBlueValue);
		void white2(int newWhiteValue);

		void red3(int newRedValue);
		void green3(int newGreenValue);
		void blue3(int newBlueValue);
		void white3(int newWhiteValue);

		void startAuto();
		void stopAuto();
		void loop();
};
