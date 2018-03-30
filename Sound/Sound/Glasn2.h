#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* Класс гласных с 2мя звуками (я е ё ю) */
	class Glasn2 : public Sound
	{
	protected:
		/* обозначение второго звука */
		std::string snd_second;
	public:
		/* конструктор = простой звук и буква ( наследуемый конструктор ) + второй звук ( snd_second )*/
		Glasn2(std::string snd_first, std::string snd_second, std::string book) : Sound(snd_first, book), snd_second(snd_second) {} 
		/* наследуемый конструктор - никакой звук */
		Glasn2() : Sound(), snd_second() {}
		/* возвращает тип буквы - гласная с 2 звуками*/
		short MyName() { return name_glasn2; } 
		/* возвращает второй звук буквы */
		std::string return_second_sound() { return snd_second; }; 
	};

}