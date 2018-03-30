#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{ 
	/* ����� ������� � 1� ������ (� � � � � �) */
	class Glasn : public Sound
	{
	public:
		/* ����������� ����������� - 1 ����� 1 ���� */
		Glasn(std::string snd, std::string bukv) : Sound(snd, bukv) {}
		/* ����������� ����������� - ������� ���� */
		Glasn() : Sound() {}
		/* ���������� ��� ����� - ���������, �������, ������� � 2 �������, ��������� � 2 ������� */
		short MyName() { return name_glasn; } 
	};

}