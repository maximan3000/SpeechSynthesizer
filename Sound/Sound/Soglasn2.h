#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* ����� ��������� � 2 ������� ( � � � � � � � � � � � � � � � ) */
	class Soglasn2 : public Sound
	{
	protected:
		/* ����������� ������� ����� */
		std::string snd_second;
	public:
		/* ����������� = ������� ���� � ����� ( ����������� Sound(,) ) + ������ ���� ( snd_second )*/
		Soglasn2(std::string snd_first, std::string snd_second, std::string book) : Sound(snd_first, book), snd_second(snd_second) {}
		/* ������ ����������� */
		Soglasn2() : Sound(), snd_second() {}
		/* ���������� ��� ����� - ���������, �������, ������� � 2 �������, ��������� � 2 ������� */
		short MyName() { return name_soglasn2; } 
		/* ���������� ������ ���� ����� */
		std::string return_second_sound() { return snd_second; }; 
	};
}