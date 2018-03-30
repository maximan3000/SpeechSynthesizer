#include "stdafx.h" 

#include "Voice_Maker.h"
#include "CountOfLoad.h"

using namespace std; 

/* путь к звуковым дорожкам */
const string way = "../AudioTracks/" ;
/* формат файлов */
const string format = ".wav";
/* скорость чтения текста от 0 до 2 (1 - нормальная) */
const float speed = 1;
/* громкость звука от 0 до 1 */
const float volume = 10;


int main(void){
	/* установка русской локализации в консоли 1251 - номер кодовой страницы кириллицы */
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	{ /* проверка безопасности */
		Security::CountOfLoad security = Security::CountOfLoad();
		if ( !security.CheckLicence() ) { return false; };
	}

	/* запуск основной проги */
	SpeechSynthesizer::Voice_Maker Speaker(way, format, speed, volume);
	string str;
	cout << "Введите строку на русском языке для озвучки \n после окончания озвучивания, повторяйте сколько влезет" << endl;
	while (true)
	{
		getline(cin, str);
		Speaker.Play(str);
	}

}