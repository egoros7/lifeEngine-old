﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#define COMPILING_LIBRARY
#include <DllGlobal.h>

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

namespace le
{
	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс отвечающий за работу с конфиг-файлами
	///
	/// Данный класс предназначен для загрузки и сохранения конфиг-файлов
	//////////////////////////////////////////////////////////////////////
	class DLL_API ConfigFile
	{
	public:
		//////////////////////////////////////////////////////////////////////
		/// \brief Загрузка конфигураций с файла
		///		
		/// \param[in] RouteToFile Путь к файлу
		/// \return true если все прошло успешно, иначе false
		//////////////////////////////////////////////////////////////////////
		bool LoadFromFile( const string& RouteToFile );

		//////////////////////////////////////////////////////////////////////
		/// \brief Сохранить данные в файл конфигураций
		/// \details Метод сохраняет данные которые были введены
		/// с помощью WriteValue/WriteComent/WriteGroup, после чего буффер
		/// очиститься (SaveBuffer)
		///		
		/// \param[in] RouteToFile Путь к файлу
		//////////////////////////////////////////////////////////////////////
		void SaveInFile( const string& RouteToFile );

		//////////////////////////////////////////////////////////////////////
		/// \brief Написать строку в буффер сохранения
		///		
		/// \param[in] NameValue Название значение
		/// \param[in] Value Значение
		//////////////////////////////////////////////////////////////////////
		void WriteValue( const string& NameValue, const string& Value );

		//////////////////////////////////////////////////////////////////////
		/// \brief Написать целое число в буффер сохранения
		///		
		/// \param[in] NameValue Название значение
		/// \param[in] Value Значение
		//////////////////////////////////////////////////////////////////////
		void WriteValue( const string& NameValue, const int& Value );

		//////////////////////////////////////////////////////////////////////
		/// \brief Написать дробное число в буффер сохранения
		///		
		/// \param[in] NameValue Название значение
		/// \param[in] Value Значение
		//////////////////////////////////////////////////////////////////////
		void WriteValue( const string& NameValue, const float& Value );

		//////////////////////////////////////////////////////////////////////
		/// \brief Написать логическую переменную в буффер сохранения
		///		
		/// \param[in] NameValue Название значение
		/// \param[in] Value Значение
		//////////////////////////////////////////////////////////////////////
		void WriteValue( const string& NameValue, const bool& Value );

		//////////////////////////////////////////////////////////////////////
		/// \brief Написать коментарий в буффер сохранения
		///		
		/// \param[in] Coment Коментарий
		//////////////////////////////////////////////////////////////////////
		void WriteComent( const string& Coment );

		//////////////////////////////////////////////////////////////////////
		/// \brief Написать группу в буффер сохранения
		///		
		/// \param[in] NameGroup Имя группы
		//////////////////////////////////////////////////////////////////////
		void WriteGroup( const string& NameGroup );

		//////////////////////////////////////////////////////////////////////
		/// \brief Очистить буффер сохранения
		//////////////////////////////////////////////////////////////////////
		void ClearSaveBuffer();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить значение конфигурации в виде строки
		///		
		/// \param[in] NameValue Тег/имя значения
		/// \return значение в виде строки
		//////////////////////////////////////////////////////////////////////
		string GetValueString( const string& NameValue );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить значение конфигурации в виде целого числа
		///		
		/// \param[in] NameValue Тег/имя значения
		/// \return значение в виде целого числа
		//////////////////////////////////////////////////////////////////////
		int GetValueInt( const string& NameValue );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить значение конфигурации в виде дробного числа
		///		
		/// \param[in] NameValue Тег/имя значения
		/// \return значение в виде дробного числа
		//////////////////////////////////////////////////////////////////////
		float GetValueFloat( const string& NameValue );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить значение конфигурации в виде логической переменной
		///		
		/// \param[in] NameValue Тег/имя значения
		/// \return значение в виде логической переменной
		//////////////////////////////////////////////////////////////////////
		bool GetValueBool( const string& NameValue );

	private:

		stringstream				SaveBuffer; ///< Буффер для записи конфигураций в файл
		map<string, string>			Values; ///< Массив считаных значений
	};

	//-------------------------------------------------------------------------//
}

#endif // CONFIG_FILE_H