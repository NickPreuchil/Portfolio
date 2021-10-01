﻿/*****************************************************************//**
 * \file   Global.h
 * \brief Заголовочный файл с объявлениями, используемыми во всех остальных модулях программы.
 * \author Преучиль Н.А.
 * \date   12 January 2021
 *********************************************************************/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DEBUG
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace std;

#pragma pack(push, 1)							
// Необходимо для того, чтобы размеры структур не округлялись до 
// значения, кратного размеру максимального поля (для корректного побитового считывания ).


/**
* \struct BITMAPFILEHEADER "Global.h"
* \brief Заголовок bmp-файла.
* \details Структура содержит основные данные о файле. Эта структура записана в самом начале каждого файла.
*/
struct BITMAPFILEHEADER {
	char bfType[2];								///<  Массив для хранения сигнатуры BMP файла (по умолчанию - ASCII символы 'B' и 'M').
	int bfSize;									///<  Размер всего bmp-файла в байтах.
	short int bfReserved1;						///<  Зарезервированное поле 1 (Должно быть равно 0)
	short int bfReserved2;						///<  Зарезервированное поле 2 (Должно быть равно 0)
	int bfOffBit;								///<  Смещение (в байтах) массива пикселов от начала файла
};
/**
* \struct BITMAPINFOHEADER "Global.h"
* \brief Описание формата изображения.
* \details Структура содержит основные данные об изображении. Записывается после заголовка в каждый файл.
*/
struct BITMAPINFOHEADER {
	int biSize;									///<  Размер структуры BITMAPINFOHEADER в байтах. Всегда равен 40.
	int biWidth;								///<  Ширина картинки в пикселях.
	int biHeight;								///<  Высота картинки в пикселях.
	short int biPlan;							///<  Количество цветовых плоскостей. В рамках ИЗ всегда равно 1.
	short int biBitCount;						///<  Количество битов на 1 пиксел. В рамках ИЗ всегда равно 8.
	int biCompression;							///<  В рамках ИЗ не используется. Всегда равно 0.
	int biSizeImg;								///<  Размер массива пикселов в байтах.
	int biXPelsPerMeter;						///<  В рамках ИЗ не используется. Всегда равно 0.
	int biYPelsPerMeter;						///<  В рамках ИЗ не используется. Всегда равно 0.
	int biClrUsed;								///<  \brief Количество цветов в палитре. 
												///<  \details В рамках ИЗ всегда равно 0, что
												///< означает, что используется максимальное количество цветов
												///< (256) для 8 - битового представления одного пиксела.
	int biClrImportant;							///<  \brief Количество цветов в палитре, необходимых для отображения
												///< изображения. 
												///<  \details В рамках ИЗ всегда равно 0, что означает, что
												///< используется максимальное количество цветов (256) для 
												///< 8-ми битового представления одного пиксела
};
/**
* \struct RGBQUAD "Global.h"
* \brief Элемент палитры.
* \details  Палитра будет представлять собой массив 256-и структур RGBQUAD 
* (в рамках ИЗ, палитра - константное содержимое каждого файла);
* Первые три битовых поля i-го элемента будут равны i;
*/
struct RGBQUAD {

	unsigned int rgbBlue : 8;
	unsigned int rgbGreen : 8;
	unsigned int rgbRed : 8;
	unsigned int rgbReserved : 8;
};
/**
* \struct Line "Global.h"
* \brief Структура описывающая строку растровой развёртки изображения (строку массива пикселей).
*/
struct Line {
	unsigned char ColourIndex[1002];			///<  Массив однобайтовых переменных, в которых будут храниться цветовые индексы пикселей.
};

#pragma pack(pop)								//  Настройки компилятора по умолчанию.


/**
* \struct Pic "Global.h"
* \brief Изображение
* \details Структура объеденяющая все свойства одного изображения. Создана для хранения множества изображений в массиве.
*/
struct Pic {
	BITMAPFILEHEADER File;						///< Переменная с заголовком изображения.						
	BITMAPINFOHEADER Info;						///< Переменная с описанием формата изображения.
	RGBQUAD* ptr_pal;							///< Указатель на палитру.
	Line* ptr_lin;								///< Указатель на массив строк с растровой развёрткой
	int PadBytes;								///< Количество байтов, которые необходимо добавить к длине строки, чтобы она была кратна 4 (обязательное условие хранения bmp файла).
};
/**
* \struct QueueElement "Global.h"
* \brief Элемент очереди команд
* \details Структура содержащая название и аргументы функции, а также массив с номерами изображений, к которым будут применяться команды.
*/
struct QueueElement {
	char CommName[10];							///< Название команды.
	char CommArgue[10];							///< Аргументы команды.
	int CommPics[100];							///< Изображения, к которым будут применяться команды.
	int CommPicsCount;							///< Количество изображений, к которым будут применяться команды.
};



const char ZeroBite = 0; ///< Переменная для добавления нулевых байтов к линиям изображения до длины кратной 4.

