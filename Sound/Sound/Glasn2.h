#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* ����� ������� � 2�� ������� (� � � �) */
	class Glasn2 : public Sound
	{
	protected:
		/* ����������� ������� ����� */
		std::string snd_second;
	public:
		/* ����������� = ������� ���� � ����� ( ����������� ����������� ) + ������ ���� ( snd_second )*/
		Glasn2(std::string snd_first, std::string snd_second, std::string book) : Sound(snd_first, book), snd_second(snd_second) {} 
		/* ����������� ����������� - ������� ���� */
		Glasn2() : Sound(), snd_second() {}
		/* ���������� ��� ����� - ������� � 2 �������*/
		short MyName() { return name_glasn2; } 
		/* ���������� ������ ���� ����� */
		std::string return_second_sound() { return snd_second; }; 
	};

}