
#include "CountOfLoad.h"

using namespace Security;

bool CountOfLoad::set_str_file(std::string &data) {
	std::fstream out_f; //открытие файловых потоков ввода
	for (int i = 0; i < size_arr; i++) {
		out_f.open(safe_file[i], std::ofstream::out | std::ofstream::trunc); //открываем для записи все файлы безопасности
		if (!out_f.is_open()) { return false; }; //если файл открыть не удалось - провал проверки
		out_f << data.substr(i * size_file, size_file);
		out_f.close();
	}

	return true;
}

bool CountOfLoad::get_date_file(std::string& decrypt, const char* way, int param) {
	FILETIME time;
	HANDLE fH; //создание обработчика файла для работы с атрибутами
			   //добавляем обработчику возможность читать атрибуты файла
	fH = CreateFile(way, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fH != INVALID_HANDLE_VALUE) //проверка на корректность предыдущего шага
	{
		if (1 == param) {
			GetFileTime(fH, &time, 0, 0); //получаем дату создания файла
		}
		else if (0 == param)
		{
			GetFileTime(fH, 0, 0, &time); //получаем последнюю дату изменения файла
		}
		else { return false; }
		CloseHandle(fH); //закрываем обработчик файла
	}
	else { return false; }

	//создаем строку - дата файла
	decrypt = std::to_string(time.dwLowDateTime) + std::to_string(time.dwHighDateTime);
	decrypt = decrypt.substr(0, size_arr*size_file);
	return true;
}

bool CountOfLoad::CheckLicence(void)
{
	/*
	получение суммированной даты создания файла в виде числа = 
	to_string(time.dwLowDateTime) + to_string(time.dwHighDateTime)
	*/
	std::string date_create;

	/* номер файла, который указывает, сколько запусков осталось */
	int file_number = -1;

	/* получаем строку, зашифрованную в файлах - дата создания n-го файла безопасности */
	if (!get_str_file(date_create)) { return false; }

	/* ключ лицензии */
	std::string key_licence;
	std::cout << "введите ключ лицензии (или просто любой символ, если ключ неизвестен) : " << std::endl;
	std::cin >> key_licence;

	/* ключ не прошел проверку */
	if (lic != key_licence) {
		/* дешифрация строки - перевод в числовой тип */
		date_create = decrypt(date_create);

		/* поиск файла, дата создание которого есть date_create */
		for (int i = 0; i < size_arr - 1; i++) {
			std::string sup_date;
			if (!get_date_file(sup_date, safe_file[i], 1)) { return false; }
			if (sup_date == date_create) { file_number = i; break; }
		}

		/* выход, если запусков было больше 4 или еще каакие-то проблемы с определением числа запусков */
		if (-1 == file_number) { std::cout << "Достигнуто ограничение по запускам )="; system("pause"); return false; }

		/* сколько осталось запусков */
		std::cout << "у вас осталось(ся)" + std::to_string(size_arr - 2 - file_number) + " запуск(a)(ов)" << std::endl;

		/* получение новой даты для записи */
		if (!get_date_file(date_create, safe_file[file_number + 1], 1)) { return false; }

		/* шифровка новой даты */
		date_create = encrypt(date_create);

		/* сохраняем старое значение даты модификации */
		for (int i = 0; i < size_arr; i++) {
			if (!get_date_file(time[i], safe_file[i])) { return false; }
		}

		/* запись во все файлы нового кода */
		if (!set_str_file(date_create)) { return false; };

		/* изменение даты модификации на старое значение */
		for (int i = 0; i < size_arr; i++) {
			if (!set_date_modif(time[i], safe_file[i])) { return false; }
		}
	}
	else { bool bl = count_refresh(); }
	return true;
}

bool CountOfLoad::get_str_file(std::string &data) {
	std::ifstream inp_f; //открытие файлового потока вывода
	data.clear();
	for (int i = 0; i < size_arr; i++) {
		std::string buff;
		inp_f.open(safe_file[i], std::ifstream::in); //открываем для чтения все файлы безопасности
		if (!inp_f.is_open()) { return false; }; //если файл открыть не удалось - провал проверки
		inp_f >> buff;
		data = data + buff; //суммирование данных из файлов
		inp_f.close();
	}
	return true;
};

bool CountOfLoad::set_date_modif(FILETIME& time, const char* way) {
	HANDLE fH; //создание обработчика файла для работы с атрибутами
			   //добавляем обработчику возможность изменять атрибуты файла
	fH = CreateFile(way, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); //инициализация
	if (fH != INVALID_HANDLE_VALUE) //проверка на корректность предыдущего шага
	{
		SetFileTime(fH, 0, 0, &time); //оставляем старую дату изменения файла
		CloseHandle(fH); //закрываем обработчик файла
	}
	else { return false; }
	return true;
}

bool CountOfLoad::get_date_file(FILETIME& inp, const char* way) {
	HANDLE fH; //создание обработчика файла для работы с атрибутами
			   //добавляем обработчику возможность читать атрибуты файла
	fH = CreateFile(way, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fH != INVALID_HANDLE_VALUE) //проверка на корректность предыдущего шага
	{
		GetFileTime(fH, 0, 0, &inp); //получаем дату модификации файла
		CloseHandle(fH); //закрываем обработчик файла
	}
	else { return false; }
	return true;
}

std::string CountOfLoad::encrypt(std::string& inp) {
	std::string out;
	for (int i = 0; i < inp.size(); i++) {
		int sup = inp[i] - '0';
		out = out + encrypt_table[sup];
	}
	return out;
}

std::string CountOfLoad::decrypt(std::string& inp) {
	std::string out;
	for (int i = 0; i < inp.size(); i++) {
		for (int j = 0; j < 10; j++) {
			if (encrypt_table[j] == inp[i]) { out = out + std::to_string(j); break; }
		}
	}
	return out;
}

bool CountOfLoad::count_refresh(void)
{
	for (int i = 0; i < size_arr; i++) {
		if (!get_date_file(time[i], safe_file[i])) { return false; }
	}
	std::string str_sup;
	if (!get_date_file(str_sup, safe_file[0], 1)) { return false; }
	str_sup = encrypt(str_sup);
	if (!set_str_file(str_sup)) { return false; };
	for (int i = 0; i < size_arr; i++) {
		if (!set_date_modif(time[i], safe_file[i])) { return false; }
	}
	return true;
}
