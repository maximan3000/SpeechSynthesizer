#include "Contain_Sound.h"

using namespace SpeechSynthesizer;

Sound* Contain_Sound::get_sound(std::string& inp)
{
	for (int i = 0; i < size; i++) if (base[i]->IsMe(inp))  return base[i];
	return Noltr;
}

inline std::string Contain_Sound::ToStr(char ch)
{
	std::string back;
	back += ch;
	return back;
}


bool Contain_Sound::Is_in_str(std::string& ch, const std::string& str, int& pos)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (ch == ToStr(str[i])) { pos = i; return true; };
	}
	return false;
}

inline void Contain_Sound::To_Low(std::string& str)
{
	/* воспомогательные константы дл€ этой функции - алфавит в верхнем и нижнем регистрах */
	static const std::string alf = "абвгдеЄжзийклмнопрстуфхцчшщъыьэю€";
	static const std::string U_alf = "јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№Ёёя";
	int pos = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (Is_in_str(ToStr(str[i]), U_alf, pos)) str[i] = alf[pos];
	}
}


/* конструктор класса. сразу инициализирует size = 33, так как в русском алфавите 33 буквы */
Contain_Sound::Contain_Sound() : size(33)
{

	//воспомогательные константы дл€ определени€ типа буквы
	const std::string soglsn2 = "бвгдзклмнпрстфх";
	const std::string soglsn = "жйцчшщ";
	const std::string glsn = "эоуаиы";
	const std::string glsn2 = "еЄю€";
	const std::string znk = "ьъ";


	/*
	«аполнение массива указателей на Sound с динамической пам€тью
	ƒл€ соглласных и гласных с 1 звуком всЄ очевидно - звук = буква и звук только один
	ƒл€ согласных с 2 звуками - 1-й звук обозначаетс€ маленькой буквой с м€гким знаком после неЄ и он м€гкий, 
	а второй - просто маленькой буквой и он твердый
	ƒл€ гласных с 2 звуками - 1-й звук есть гласна€ с 1-м звуком, а 2-й звук - 'й'
	*/
	int len1 = soglsn2.length(), 
		len2 = glsn.length() + len1, 
		len3 = glsn2.length() + len2, 
		len4 = soglsn.length() + len3, 
		len5 = znk.length() + len4;
		
		
	base = new Sound*[size];
		
	int i = 0, j = 0;
	while (i < len1)
	{
			
		std::string ch = ToStr(soglsn2[i]);
		Sound* sn2 = new Soglasn2(ch + "ь", ch, ch);
		base[i] = sn2; i++;
	};
	while (i < len2)
	{
		std::string ch = ToStr(glsn[j]);
		Sound* gn = new Glasn(ch, ch);
		base[i] = gn; i++; j++;
	};
	j = 0;
	while (i < len3)
	{
		std::string ch = ToStr(glsn2[j]);
		Sound* gn2 = new Glasn2(ToStr(glsn[j]), "й", ch);
		base[i] = gn2; i++; j++;
	};
	j = 0;
	while (i < len4)
	{
		std::string ch = ToStr(soglsn[j]);
		Sound* sn = new Soglasn(ch, ch);
		base[i] = sn; i++; j++;
	};
	j = 0;
	while (i < len5)
	{
		std::string ch = ToStr(znk[j]);
		Sound* sn = new Znak(ch);
		base[i] = sn; i++; j++;
	};

	Sound* Nl = new NoLetter();
	Noltr = Nl;
}

/* деструктор - освобождение пам€ти */
Contain_Sound::~Contain_Sound()
{
	for (int i = 0; i < size; i++)
	{
		delete base[i];
	}
	delete[] base;
	delete Noltr;
}

/*
получение стека на озвучку через строку (получение еЄ транскрипции)
*/
myqueue Contain_Sound::Transcript(std::string& inp)
{
	To_Low(inp);
	Sound* now, *next, *next_next;
	myqueue To_voice;
	unsigned int i = 0;
	while (i < inp.length())
	{
		now = get_sound(ToStr(inp[i]));
		if (now->MyName() == name_soglasn2)
		{
			next = get_sound(ToStr(inp[i + 1]));
			if (next->MyName() == name_znak)
			{
				next_next = get_sound(ToStr(inp[i + 2]));
				if ((next_next->MyName() == name_glasn) || (next_next->MyName() == name_glasn2))
				{
					To_voice.push(now->return_second_sound()); //добавить твердый звук согласной
					To_voice.push("й"); //добавить й от м€гкого знака и гласной
					To_voice.push(next_next->return_first_sound()); //добавить простую гласную с 1 звуком
					i += 3;
				}
				else
				{
					To_voice.push(now->return_first_sound()); //добавить м€гкую согласную и обойти м€гкий знак
					i += 2;
				}
			}
			else if ((next->MyName() == name_glasn2) || (next->IsMe("и")))
			{
				To_voice.push(now->return_first_sound()); // добавить м€гкую согласную
				To_voice.push(next->return_first_sound()); //добавить простой гласный звук
				i += 2;
			}
			else
			{
				To_voice.push(now->return_second_sound()); //добавить твердый согласный звук
				i += 1;
			}
		}
		else if (now->MyName() == name_glasn)
		{
			next = get_sound(ToStr(inp[i + 1]));
			if (next->MyName() == name_glasn2)
			{
				To_voice.push(now->return_first_sound()); //добавление звука первой гласной
				To_voice.push(next->return_second_sound()); //добавление звука "й"
				To_voice.push(next->return_first_sound()); //добавление звука второй гласной
				i += 2;
			}
			else
			{
				To_voice.push(now->return_first_sound()); //добавление звука первой гласной
				i += 1;
			}
		}
		else if (now->MyName() == name_glasn2)
		{
			if (i == 0) To_voice.push(now->return_second_sound()); //добавоение "й"
			To_voice.push(now->return_first_sound()); //добавление звука гласной
			i += 1;
		}
		else if (now->MyName() == name_soglasn)
		{
			next = get_sound(ToStr(inp[i + 1]));
			if (next->MyName() == name_glasn2)
			{
				To_voice.push(now->return_first_sound()); //добавть звук согласной
				To_voice.push(next->return_first_sound()); //добавить звук гласной
				i += 2;
			}
			else if (next->MyName() == name_znak)
			{
				next_next = get_sound(ToStr(inp[i + 2]));
				if ((next_next->MyName() == name_glasn) || (next_next->MyName() == name_glasn2))
				{
					To_voice.push(now->return_first_sound()); //добавить звук согласной
					To_voice.push("й"); //добавить й от знака и гласной
					To_voice.push(next_next->return_first_sound()); //добавить простую гласную с 1 звуком
					i += 3;
				}
				else
				{
					To_voice.push(now->return_first_sound()); // добавить звук согласной
					i += 2;
				}
			}
			else
			{
				To_voice.push(now->return_first_sound()); //добавить звук согласной
				i += 1;
			}
		}
		else
		{
			To_voice.push(Noltr->return_first_sound());
			i += 1;
		}
	}
	return To_voice;
}