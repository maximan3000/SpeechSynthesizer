#pragma once

#include "stdafx.h"

/* ��� ���������� ���� ���� */
#include "Sound.h"
#include "Soglasn.h"
#include "Soglasn2.h"
#include "Glasn2.h"
#include "Glasn.h"
#include "Znak.h"
#include "NoLetter.h"

namespace SpeechSynthesizer
{
	/* �������� �����-���������� ��� ���� std::queue<std::string> */
	typedef std::queue<std::string> myqueue;

	/* ����� = ������� ������� */
	class Contain_Sound
	{
	private:
		/* ��������� ���������������� ��������� �� ���� ������ �� ����� inp */
		Sound* get_sound(std::string& inp);
		/* ���������� char � string - ���������������� ��� ������������ */
		std::string ToStr(char );
		/* ������� ������� ������ � ������ ������� - ���������������� ��� ����������� */
		void To_Low(std::string& );
		/* ��������, ���� �� ������ (1) � ������ (2) - ��� �������� ������� ������ � ������ �������. 
		���� ����, ������� ����� � int (3) 
		*/
		bool Is_in_str(std::string&, const std::string&, int&);


	protected:
		/*
		������ ������� ������
		*/
		const int size;

		/* ���� ���� ���� */
		Sound** base;

		/* ������ ���� - ����� */
		Sound* Noltr;

	public:
		Contain_Sound();
		~Contain_Sound();

		/* ��������� ������������ ������ */
		myqueue Transcript(std::string&);
	};



}