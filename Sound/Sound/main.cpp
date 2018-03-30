#include "stdafx.h" 

#include "Voice_Maker.h"
#include "CountOfLoad.h"

using namespace std; 

/* ���� � �������� �������� */
const string way = "../AudioTracks/" ;
/* ������ ������ */
const string format = ".wav";
/* �������� ������ ������ �� 0 �� 2 (1 - ����������) */
const float speed = 1;
/* ��������� ����� �� 0 �� 1 */
const float volume = 10;


int main(void){
	/* ��������� ������� ����������� � ������� 1251 - ����� ������� �������� ��������� */
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	{ /* �������� ������������ */
		Security::CountOfLoad security = Security::CountOfLoad();
		if ( !security.CheckLicence() ) { return false; };
	}

	/* ������ �������� ����� */
	SpeechSynthesizer::Voice_Maker Speaker(way, format, speed, volume);
	string str;
	cout << "������� ������ �� ������� ����� ��� ������� \n ����� ��������� �����������, ���������� ������� ������" << endl;
	while (true)
	{
		getline(cin, str);
		Speaker.Play(str);
	}

}