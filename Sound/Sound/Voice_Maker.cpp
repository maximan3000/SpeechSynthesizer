/* ��� ������������ ���� � ������� */
#include "Voice_Maker.h"

 

using namespace SpeechSynthesizer;

Voice_Maker::Voice_Maker(std::string way, std::string format, float speed, float volume) :
	Contain_Sound(), way(way), format(format), speed(speed), volume(volume) 
{
	engine = irrklang::createIrrKlangDevice();

	/* ������ ��������� �� ������ */
	if (!engine) MessageBox(
		NULL,
		"������!!!",
		"�� ���� ������� ����������� ���������� (������ ������)",
		MB_YESNO | // ��/��� (������)
		MB_DEFBUTTON1 | //��������� ������
		MB_ICONEXCLAMATION | //��� ������
		MB_DEFAULT_DESKTOP_ONLY);
}

Voice_Maker::~Voice_Maker()
{
	/* �������� ������ */
	engine->drop(); // delete engine 
}

void Voice_Maker::Play(std::string str)
{
		myqueue To_Speak = this->Transcript(str);
		
		while (!(To_Speak.empty()))
		{
			std::string way_to_file = way + To_Speak.front() + format;
			To_Speak.pop();
			irrklang::ISound* music = engine->play3D(way_to_file.c_str(), irrklang::vec3df(0,0,0), false, false, true);

			music->setPlaybackSpeed(speed);
			music->setVolume(volume);

			int time_play = music->getPlayLength();
			Sleep(time_play);
			//if (music) music->drop();
		}
}

