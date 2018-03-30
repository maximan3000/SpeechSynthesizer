#pragma once
#include "Sound.h"

namespace SpeechSynthesizer
{
	/* Класс согласных звуков с 1 звуком ( ж й ц ч ш щ ) */
	class Soglasn : public Sound
	{
	public:
		/* наследуемый конструктор - 1 буква 1 звук */
		Soglasn(std::string snd, std::string bukv) : Sound(snd,bukv) {}
		/* наследуемый конструктор - никакой звук */
		Soglasn() : Sound() {}
		/* возвращает тип буквы - согласная */
		short MyName() { return name_soglasn; } 
	};
}
