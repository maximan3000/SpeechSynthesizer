#pragma once

#include "Sound.h"

namespace SpeechSynthesizer
{
	/* Класс пустого звука - которого не существует ( # ) */
	class NoLetter : public Sound
	{
	public:
		/* наследуемый конструктор - 1 буква 1 звук, которые всегда равны # */
		NoLetter() : Sound("#","#") {}
		/* возвращает тип буквы - данный символ не является буквой русского алфавита */
		short MyName() { return name_not_a_letter; }
	};
}