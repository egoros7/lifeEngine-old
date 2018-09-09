﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#define COMPILING_LIBRARY
#include <DllGlobal.h>

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <vector>
#include <map>
using namespace std;

//////////////
// OPENGL
//////////////
#include <glew\glew.h>
#include <glm\glm.hpp>

//////////
// XML
//////////
#include <tinyxml.h>

//////////////////
// LIFEENGINE
//////////////////
#include <System\System.h>

namespace le
{
	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс для хранения энтити-объектов карты
	///
	/// Данный класс необходим для хранения энтити-объектов карты, например
	/// точка старта игрока, спавн npc и т.д
	//////////////////////////////////////////////////////////////////////
	class DLL_API BaseEntity
	{
	public:
		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		///
		/// \param[in] ClassName Название класса энтити
		//////////////////////////////////////////////////////////////////////
		BaseEntity( const string& ClassName );

		//////////////////////////////////////////////////////////////////////
		/// \brief Обновить энтити-объект
		//////////////////////////////////////////////////////////////////////
		virtual void Update();

		//////////////////////////////////////////////////////////////////////
		/// \brief Выполнить действие энтити-объекта
		//////////////////////////////////////////////////////////////////////
		virtual void Action();
	
		string					ClassName;			///< Название класса энтити
		glm::vec3				Position;			///< Позиция энтити в мире
		glm::mat4				Transformation;		///< Матрица трансформации

	protected:

		//////////////////////////////////////////////////////////////////////
		/// \brief Преобразовать строку в логическую переменную
		///
		/// \param[in] Value Значение
		/// \return Логическая переменная
		//////////////////////////////////////////////////////////////////////
		bool ValueToBoolean( const string& Value );

		//////////////////////////////////////////////////////////////////////
		/// \brief Преобразовать строку в число
		///
		/// \param[in] Value Значение
		/// \return Число 
		//////////////////////////////////////////////////////////////////////
		template <typename T> T StringToNumber( const string &Value, T DefValue = T() );

		//////////////////////////////////////////////////////////////////////
		/// \brief Преобразовать строку в 3D вектор
		///
		/// \param[in] Value Значение
		/// \return 3D вектор
		//////////////////////////////////////////////////////////////////////
		glm::vec3 ValueToVec3( const string& Value );

		//////////////////////////////////////////////////////////////////////
		/// \brief Преобразовать строку в 4D вектор
		///
		/// \param[in] Value Значение
		/// \return 4D вектор
		//////////////////////////////////////////////////////////////////////
		glm::vec4 ValueToVec4( const string& Value );
	};

	//-------------------------------------------------------------------------//

	template<typename T> inline T BaseEntity::StringToNumber( const string& Value, T DefValue )
	{
		stringstream		Stringstream;
		T					Result;

		for ( auto It = Value.begin(); It != Value.end(); ++It )
			if ( isdigit( *It ) || *It == 'e' || *It == '-' || *It == '+' || *It == '.' )
				Stringstream << *It;
		
		return Stringstream >> Result ? Result : DefValue;
	}

	//-------------------------------------------------------------------------//
}

#endif // BASE_ENTITY_H