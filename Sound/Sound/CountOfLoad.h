#pragma once

#include "stdafx.h"

namespace Security 
{
	/* �����, ��������������� ��� �������� ����� �������� � �������� 
		�������� �������� � �������� ��� �������
	*/
	class CountOfLoad
	{
	public:
		CountOfLoad() { time = new FILETIME[size_arr]; }
		~CountOfLoad() { delete[] time; }

		/* �������� �������� � ����� �������� */
		bool CheckLicence(void);

	private:

	#pragma region Data

		/* ������� ��� ���������� ���� ������� � 0 � �� 9 */
		const char encrypt_table[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
		/* �������� */
		const std::string lic = "maks";
		/* ����� ������������ - ����� ����� � ������� ������������� ����� �������� */
		const char* safe_file[5] = { "../Debug/base.dll", "../kek.sdf", "../lib/force.lib", "../AudioTracks/snd.mp3", "../Debug/engine.dll" };
		/* ������ ������� ����� = ����� ������ */
		const int size_arr = sizeof(safe_file) / sizeof(const char*);
		/* ����� �������� � ������ */
		const int size_file = 3;
		/* ��� �������� �������� ���� ����������� */
		FILETIME* time = new FILETIME[size_arr];

	#pragma endregion

	#pragma region Methods

		/* ��������� ������������������� ����������� ����� (!����� ������) ������ ������������ */
		bool get_str_file(std::string&);

		/* ��������� ���� ��������� ����� (param=0) ��� ���� �������� (param=1) �� ��� ���� */
		bool get_date_file(std::string&, const char*, int param);

		/* ���������� ��� ��������� ���� � �������� ������� */
		bool get_date_file(FILETIME&, const char*);

		/* ������� ���� ��������� ����� �� ��������������� �������� */
		bool set_date_modif(FILETIME&, const char*);

		/* ��������� ����� ������ � ����� ������������ */
		bool set_str_file(std::string&);

		/* ���������� ������ */
		std::string encrypt(std::string&);

		/* ������������ ������ */
		std::string decrypt(std::string&);

		/* ���������� �������� */
		bool count_refresh(void);

	#pragma endregion

	};
}