#pragma once

#include "stdafx.h"

namespace Security 
{
	/* класс, предназначенный для проверки числа запусков и лицензии 
		подлежит шифрации и сокрытию при выпуске
	*/
	class CountOfLoad
	{
	public:
		CountOfLoad() { time = new FILETIME[size_arr]; }
		~CountOfLoad() { delete[] time; }

		/* Проверка лицензии и числа запусков */
		bool CheckLicence(void);

	private:

	#pragma region Data

		/* таблица для шифрования цифр начиная с 0 и до 9 */
		const char encrypt_table[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
		/* лицензия */
		const std::string lic = "maks";
		/* файлы безопасности - номер файла в массиве соответствует числу запусков */
		const char* safe_file[5] = { "../Debug/base.dll", "../kek.sdf", "../lib/force.lib", "../AudioTracks/snd.mp3", "../Debug/engine.dll" };
		/* размер массива путей = число файлов */
		const int size_arr = sizeof(safe_file) / sizeof(const char*);
		/* число символов в файлах */
		const int size_file = 3;
		/* для хранения значений даты модификации */
		FILETIME* time = new FILETIME[size_arr];

	#pragma endregion

	#pragma region Methods

		/* получение сконкатенированного содержимого строк (!одной первой) файлов безопасности */
		bool get_str_file(std::string&);

		/* получение даты изменения файла (param=0) или даты создания (param=1) по его пути */
		bool get_date_file(std::string&, const char*, int param);

		/* перегрузка для получение даты в истинном формате */
		bool get_date_file(FILETIME&, const char*);

		/* задание даты изменения файла на соответствующее значение */
		bool set_date_modif(FILETIME&, const char*);

		/* установка новой строки в файлы безопасности */
		bool set_str_file(std::string&);

		/* шифрование строки */
		std::string encrypt(std::string&);

		/* дешифрование строки */
		std::string decrypt(std::string&);

		/* обновление счетчика */
		bool count_refresh(void);

	#pragma endregion

	};
}