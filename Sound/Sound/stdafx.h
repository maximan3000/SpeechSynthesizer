#pragma once

/* Программа озвучки текста (звуковые эффекты не поддерживаются) */

/* Для работы с консолью */
#include <iostream>

/* Для русской локализации */
#include <clocale>

/* Для работы с файлами (ограничение запусков) */
#include <fstream>

/* Для работы со строками */
#include <string>

/* Для класса очередь */
#include <queue>

/* Для функции Sleep */
#include <windows.h>

/* Подключение библиотеки звука */
#pragma comment(lib, "irrKlang.lib") // Дает понять, где искать lib файл, ссылающийся на dll (link with irrKlang.dll)
#include <irrklang.h> //подключение функций библиотеки звука


