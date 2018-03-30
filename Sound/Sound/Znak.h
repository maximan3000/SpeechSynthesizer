#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* Класс ь и ъ знака */
	class Znak : public Sound
	{
	public:
		/* наследуемый конструктор - никакой звук и 1 буква */
		Znak(std::string bukv) : Sound("", bukv) {}
		/* наследуемый конструктор - никакой звук */
		Znak() : Sound() {}
		/* возвращает тип буквы - согласная, гласная, гласная с 2 звуками, согласная с 2 звуками */
		short MyName() { return name_znak; } 
	};
}
