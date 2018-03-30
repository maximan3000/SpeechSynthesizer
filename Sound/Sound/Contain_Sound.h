#pragma once

#include "stdafx.h"

/* Для заполнения базы букв */
#include "Sound.h"
#include "Soglasn.h"
#include "Soglasn2.h"
#include "Glasn2.h"
#include "Glasn.h"
#include "Znak.h"
#include "NoLetter.h"

namespace SpeechSynthesizer
{
	/* создание имени-заменителя для типа std::queue<std::string> */
	typedef std::queue<std::string> myqueue;

	/* класс = русский алфавит */
	class Contain_Sound
	{
	private:
		/* получение соответствующего указателя на базу звуков по букве inp */
		Sound* get_sound(std::string& inp);
		/* приведение char к string - воспомогательная для конструктора */
		std::string ToStr(char );
		/* перевод русской строки в нижний регистр - воспомогательная для транскрипта */
		void To_Low(std::string& );
		/* Проверка, есть ли символ (1) в строке (2) - для перевода русской строки в нижний регистр. 
		если есть, позиция будет в int (3) 
		*/
		bool Is_in_str(std::string&, const std::string&, int&);


	protected:
		/*
		размер массива звуков
		*/
		const int size;

		/* база всех букв */
		Sound** base;

		/* пустой звук - пауза */
		Sound* Noltr;

	public:
		Contain_Sound();
		~Contain_Sound();

		/* получение транскрипции строки */
		myqueue Transcript(std::string&);
	};



}