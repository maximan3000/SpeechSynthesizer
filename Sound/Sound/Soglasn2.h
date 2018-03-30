#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* Класс согласных с 2 звуками ( б в г д з к л м н п р с т ф х ) */
	class Soglasn2 : public Sound
	{
	protected:
		/* обозначение второго звука */
		std::string snd_second;
	public:
		/* конструктор = простой звук и буква ( наследуемый Sound(,) ) + второй звук ( snd_second )*/
		Soglasn2(std::string snd_first, std::string snd_second, std::string book) : Sound(snd_first, book), snd_second(snd_second) {}
		/* пустой конструктор */
		Soglasn2() : Sound(), snd_second() {}
		/* возвращает тип буквы - согласная, гласная, гласная с 2 звуками, согласная с 2 звуками */
		short MyName() { return name_soglasn2; } 
		/* возвращает второй звук буквы */
		std::string return_second_sound() { return snd_second; }; 
	};
}