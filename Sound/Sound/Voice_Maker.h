#pragma once

#include "stdafx.h"

/* для наследования(база букв со звуками) */
#include "Contain_Sound.h"

namespace SpeechSynthesizer{

	/* класс, озвучивающий тексты при помощи библиотеки звука irrKlang. Содержит в себе набор звуков из Contain_Sound*/
	class Voice_Maker : public Contain_Sound
	{
	private:
		/* звуковой движок */
		irrklang::ISoundEngine* engine;
		/* параметры движка
			1) путь до звуковых дорожек
			2) расширение звуковых файлов
			3) скорость произношения
			4) громкость произношения
		*/
		const 
			std::string way, // 1
			format; // 2
		const float 
			speed, // 3
			volume; // 4

	public:
		/*
			в конструкторе вводятся:
			указатель на звуковой движок irrklang::ISoundEngine*,
			путь до звуковых дорожек в формате "../AudioTracks/",
			затем расширение этих дорожек в формате ".wav", 
			затем скорость произношения в виде вещественного множителя (0.5 - в 2 раза медленнее),
			затем громкость в виде вещественного числа в интервале от 0 до 1
		*/
		Voice_Maker(std::string , std::string , float, float );
		~Voice_Maker();

		/* озвучивание входящей строки */
		void Play(std::string);
	};
}