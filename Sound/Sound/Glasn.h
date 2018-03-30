#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{ 
	/* класс гласных с 1м звуком (а э о у и ы) */
	class Glasn : public Sound
	{
	public:
		/* наследуемый конструктор - 1 буква 1 звук */
		Glasn(std::string snd, std::string bukv) : Sound(snd, bukv) {}
		/* наследуемый конструктор - никакой звук */
		Glasn() : Sound() {}
		/* возвращает тип буквы - согласная, гласная, гласная с 2 звуками, согласная с 2 звуками */
		short MyName() { return name_glasn; } 
	};

}