#pragma once

#include "Sound.h"

namespace SpeechSynthesizer
{
	/* ����� ������� ����� - �������� �� ���������� ( # ) */
	class NoLetter : public Sound
	{
	public:
		/* ����������� ����������� - 1 ����� 1 ����, ������� ������ ����� # */
		NoLetter() : Sound("#","#") {}
		/* ���������� ��� ����� - ������ ������ �� �������� ������ �������� �������� */
		short MyName() { return name_not_a_letter; }
	};
}