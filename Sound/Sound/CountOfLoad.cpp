
#include "CountOfLoad.h"

using namespace Security;

bool CountOfLoad::set_str_file(std::string &data) {
	std::fstream out_f; //�������� �������� ������� �����
	for (int i = 0; i < size_arr; i++) {
		out_f.open(safe_file[i], std::ofstream::out | std::ofstream::trunc); //��������� ��� ������ ��� ����� ������������
		if (!out_f.is_open()) { return false; }; //���� ���� ������� �� ������� - ������ ��������
		out_f << data.substr(i * size_file, size_file);
		out_f.close();
	}

	return true;
}

bool CountOfLoad::get_date_file(std::string& decrypt, const char* way, int param) {
	FILETIME time;
	HANDLE fH; //�������� ����������� ����� ��� ������ � ����������
			   //��������� ����������� ����������� ������ �������� �����
	fH = CreateFile(way, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fH != INVALID_HANDLE_VALUE) //�������� �� ������������ ����������� ����
	{
		if (1 == param) {
			GetFileTime(fH, &time, 0, 0); //�������� ���� �������� �����
		}
		else if (0 == param)
		{
			GetFileTime(fH, 0, 0, &time); //�������� ��������� ���� ��������� �����
		}
		else { return false; }
		CloseHandle(fH); //��������� ���������� �����
	}
	else { return false; }

	//������� ������ - ���� �����
	decrypt = std::to_string(time.dwLowDateTime) + std::to_string(time.dwHighDateTime);
	decrypt = decrypt.substr(0, size_arr*size_file);
	return true;
}

bool CountOfLoad::CheckLicence(void)
{
	/*
	��������� ������������� ���� �������� ����� � ���� ����� = 
	to_string(time.dwLowDateTime) + to_string(time.dwHighDateTime)
	*/
	std::string date_create;

	/* ����� �����, ������� ���������, ������� �������� �������� */
	int file_number = -1;

	/* �������� ������, ������������� � ������ - ���� �������� n-�� ����� ������������ */
	if (!get_str_file(date_create)) { return false; }

	/* ���� �������� */
	std::string key_licence;
	std::cout << "������� ���� �������� (��� ������ ����� ������, ���� ���� ����������) : " << std::endl;
	std::cin >> key_licence;

	/* ���� �� ������ �������� */
	if (lic != key_licence) {
		/* ���������� ������ - ������� � �������� ��� */
		date_create = decrypt(date_create);

		/* ����� �����, ���� �������� �������� ���� date_create */
		for (int i = 0; i < size_arr - 1; i++) {
			std::string sup_date;
			if (!get_date_file(sup_date, safe_file[i], 1)) { return false; }
			if (sup_date == date_create) { file_number = i; break; }
		}

		/* �����, ���� �������� ���� ������ 4 ��� ��� ������-�� �������� � ������������ ����� �������� */
		if (-1 == file_number) { std::cout << "���������� ����������� �� �������� )="; system("pause"); return false; }

		/* ������� �������� �������� */
		std::cout << "� ��� ��������(��)" + std::to_string(size_arr - 2 - file_number) + " ������(a)(��)" << std::endl;

		/* ��������� ����� ���� ��� ������ */
		if (!get_date_file(date_create, safe_file[file_number + 1], 1)) { return false; }

		/* �������� ����� ���� */
		date_create = encrypt(date_create);

		/* ��������� ������ �������� ���� ����������� */
		for (int i = 0; i < size_arr; i++) {
			if (!get_date_file(time[i], safe_file[i])) { return false; }
		}

		/* ������ �� ��� ����� ������ ���� */
		if (!set_str_file(date_create)) { return false; };

		/* ��������� ���� ����������� �� ������ �������� */
		for (int i = 0; i < size_arr; i++) {
			if (!set_date_modif(time[i], safe_file[i])) { return false; }
		}
	}
	else { bool bl = count_refresh(); }
	return true;
}

bool CountOfLoad::get_str_file(std::string &data) {
	std::ifstream inp_f; //�������� ��������� ������ ������
	data.clear();
	for (int i = 0; i < size_arr; i++) {
		std::string buff;
		inp_f.open(safe_file[i], std::ifstream::in); //��������� ��� ������ ��� ����� ������������
		if (!inp_f.is_open()) { return false; }; //���� ���� ������� �� ������� - ������ ��������
		inp_f >> buff;
		data = data + buff; //������������ ������ �� ������
		inp_f.close();
	}
	return true;
};

bool CountOfLoad::set_date_modif(FILETIME& time, const char* way) {
	HANDLE fH; //�������� ����������� ����� ��� ������ � ����������
			   //��������� ����������� ����������� �������� �������� �����
	fH = CreateFile(way, GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); //�������������
	if (fH != INVALID_HANDLE_VALUE) //�������� �� ������������ ����������� ����
	{
		SetFileTime(fH, 0, 0, &time); //��������� ������ ���� ��������� �����
		CloseHandle(fH); //��������� ���������� �����
	}
	else { return false; }
	return true;
}

bool CountOfLoad::get_date_file(FILETIME& inp, const char* way) {
	HANDLE fH; //�������� ����������� ����� ��� ������ � ����������
			   //��������� ����������� ����������� ������ �������� �����
	fH = CreateFile(way, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (fH != INVALID_HANDLE_VALUE) //�������� �� ������������ ����������� ����
	{
		GetFileTime(fH, 0, 0, &inp); //�������� ���� ����������� �����
		CloseHandle(fH); //��������� ���������� �����
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
