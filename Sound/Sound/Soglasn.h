#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* ����� ��������� ������ � 1 ������ ( � � � � � � ) */
	class Soglasn : public Sound
	{
	public:
		/* ����������� ����������� - 1 ����� 1 ���� */
		Soglasn(std::string snd, std::string bukv) : Sound(snd,bukv) {}
		/* ����������� ����������� - ������� ���� */
		Soglasn() : Sound() {}
		/* ���������� ��� ����� - ��������� */
		short MyName() { return name_soglasn; } 
	};
}
