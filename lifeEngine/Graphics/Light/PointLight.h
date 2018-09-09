﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#define COMPILING_LIBRARY
#include <DllGlobal.h>

//////////////
// OPENGL
//////////////
#include <glew\glew.h>
#include <glm\glm.hpp>

////////////////
// LIFEENGINE
///////////////
#include <Graphics\Light\BaseLight.h>
#include <Graphics\Bounding Volume\BoundingSphere.h>

namespace le
{
	//-------------------------------------------------------------------------//

	class Scene;

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс точечного света
	///
	/// Данный класс необходим для работы точечного света
	//////////////////////////////////////////////////////////////////////
	class DLL_API PointLight : public BaseLight
	{
	public:
		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		//////////////////////////////////////////////////////////////////////
		PointLight();
		
		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор копирования
		//////////////////////////////////////////////////////////////////////
		PointLight( const PointLight& Copy );
		
		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		///
		/// \param[in] Radius Радиус света
		/// \param[in] Position Позиция света
		/// \param[in] Color Цвет света
		/// \param[in] Intensivity Интенсивность света
		/// \param[in] Specular Отражение света
		//////////////////////////////////////////////////////////////////////
		PointLight( float Radius, const glm::vec3& Position, const glm::vec4& Color, float Intensivity = 1.f, const glm::vec4& Specular = glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
		
		//////////////////////////////////////////////////////////////////////
		/// \brief Деструктор
		//////////////////////////////////////////////////////////////////////
		~PointLight();

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать радиус света
		///		
		/// \param[in] Radius Радиус света
		//////////////////////////////////////////////////////////////////////
		void SetRadius( float Radius );

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать позицию света
		///		
		/// \param[in] Position Позиция света
		//////////////////////////////////////////////////////////////////////
		void SetPosition( const glm::vec3& Position );

		le::PointLight& operator=( const PointLight& Copy );

		float					Radius; ///< Радиус света
		BoundingSphere			LightSphere; ///< Сфера света
	};

	//-------------------------------------------------------------------------//
}

#endif // POINT_LIGHT_H