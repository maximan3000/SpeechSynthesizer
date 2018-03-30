#pragma once

#include "stdafx.h"

/* ��� ������������(���� ���� �� �������) */
#include "Contain_Sound.h"

namespace SpeechSynthesizer{

	/* �����, ������������ ������ ��� ������ ���������� ����� irrKlang. �������� � ���� ����� ������ �� Contain_Sound*/
	class Voice_Maker : public Contain_Sound
	{
	private:
		/* �������� ������ */
		irrklang::ISoundEngine* engine;
		/* ��������� ������
			1) ���� �� �������� �������
			2) ���������� �������� ������
			3) �������� ������������
			4) ��������� ������������
		*/
		const 
			std::string way, // 1
			format; // 2
		const float 
			speed, // 3
			volume; // 4

	public:
		/*
			� ������������ ��������:
			��������� �� �������� ������ irrklang::ISoundEngine*,
			���� �� �������� ������� � ������� "../AudioTracks/",
			����� ���������� ���� ������� � ������� ".wav", 
			����� �������� ������������ � ���� ������������� ��������� (0.5 - � 2 ���� ���������),
			����� ��������� � ���� ������������� ����� � ��������� �� 0 �� 1
		*/
		Voice_Maker(std::string , std::string , float, float );
		~Voice_Maker();

		/* ����������� �������� ������ */
		void Play(std::string);
	};
}