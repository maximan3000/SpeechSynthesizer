#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* ����� � � � ����� */
	class Znak : public Sound
	{
	public:
		/* ����������� ����������� - ������� ���� � 1 ����� */
		Znak(std::string bukv) : Sound("", bukv) {}
		/* ����������� ����������� - ������� ���� */
		Znak() : Sound() {}
		/* ���������� ��� ����� - ���������, �������, ������� � 2 �������, ��������� � 2 ������� */
		short MyName() { return name_znak; } 
	};
}
