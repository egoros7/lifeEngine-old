﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
#pragma warning( push )

#pragma warning( disable: 4251 ) 

#define COMPILING_LIBRARY
#include <DllGlobal.h>

///////////////////////////
// СИСТЕМНЫЕ БИБЛИОТЕКИ
///////////////////////////
#include <vector>
using namespace std;

//////////////
// OPENGL
//////////////
#include <glew\glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>

////////////////
// LIFEENGINE
///////////////
#include <Graphics\Frustum.h>
#include <System\Query.h>

namespace le
{
	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс ограничивающего тела (прямоугольный параллелепипед)
	///
	/// Данный класс используеться для оптимального (быстрого) отсичения
	/// невидимой геометрии
	//////////////////////////////////////////////////////////////////////
	class DLL_API BoundingBox
	{
	public:
		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		//////////////////////////////////////////////////////////////////////
		BoundingBox();

		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор копирывания
		//////////////////////////////////////////////////////////////////////
		BoundingBox( BoundingBox& Copy );

		//////////////////////////////////////////////////////////////////////
		/// \brief Деструктор
		//////////////////////////////////////////////////////////////////////
		~BoundingBox();

		//////////////////////////////////////////////////////////////////////
		/// \brief Инициализировать ограничивающее тело
		///		
		/// \param[in] MinVertex Минимальная вершина
		/// \param[in] MaxVertex Максимальная вершина
		//////////////////////////////////////////////////////////////////////
		void InitBox( const glm::vec3& MinVertex, const glm::vec3& MaxVertex );

		//////////////////////////////////////////////////////////////////////
		/// \brief Инициализировать ограничивающее тело
		///		
		/// \param[in] Vertexs Массив вершин (макс. 8)
		//////////////////////////////////////////////////////////////////////
		void InitBox( const vector<glm::vec3>& Vertexs );

		//////////////////////////////////////////////////////////////////////
		/// \brief Инициализировать ограничивающее тело
		///		
		/// \param[in] Size Размер куба
		//////////////////////////////////////////////////////////////////////
		void InitBox( const glm::vec3& Size );

		//////////////////////////////////////////////////////////////////////
		/// \brief Провести тест на перекртие объекта
		//////////////////////////////////////////////////////////////////////
		void QueryTest();

		//////////////////////////////////////////////////////////////////////
		/// \brief Отрендерить объект
		//////////////////////////////////////////////////////////////////////
		void RenderBox();

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать позицию объекта
		///		
		/// \param[in] Position Позиция
		//////////////////////////////////////////////////////////////////////
		void SetPosition( const glm::vec3& Position );

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать угол поворота объекта
		///		
		/// \param[in] Rotation Угол поворота
		//////////////////////////////////////////////////////////////////////
		void SetRotation( const glm::vec3& Rotation );

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать угол поворота конуса
		///		
		/// \param[in] Rotation Угол поворота
		//////////////////////////////////////////////////////////////////////
		void SetRotation( const glm::quat& Rotation );

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать масштаб
		///		
		/// \param[in] Scale Масштаб
		//////////////////////////////////////////////////////////////////////
		void SetScale( const glm::vec3& Scale );

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать трансформацию ограничивающего тела
		///
		/// \param[in] Transformation Трансформация
		/// \param[in] Position Позиция
		/// \param[in] Rotation Поворот кватернионом
		/// \param[in] Scale Масштаб
		//////////////////////////////////////////////////////////////////////
		void SetTransformation( const glm::mat4& Transformation, const glm::vec3& Position, const glm::quat& Rotation, const glm::vec3& Scale );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить матрицу трансформации
		///		
		/// \return  glm::mat4&
		//////////////////////////////////////////////////////////////////////
		glm::mat4& GetTransformation();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить позицию
		///		
		/// \return  glm::vec3&
		//////////////////////////////////////////////////////////////////////
		glm::vec3& GetPosition();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить поворот
		///		
		/// \return  glm::quat&
		//////////////////////////////////////////////////////////////////////
		glm::quat& GetRotation();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить вершины
		///
		/// \return glm::vec3*
		//////////////////////////////////////////////////////////////////////
		glm::vec3* GetVertexs();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить самую низкую вершину
		///
		/// \return glm::vec3*
		//////////////////////////////////////////////////////////////////////
		glm::vec3& GetMaxVertex();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить самую высокую вершину
		///
		/// \return glm::vec3*
		//////////////////////////////////////////////////////////////////////
		glm::vec3& GetMinVertex();

		BoundingBox& operator=( const BoundingBox& Copy );

		Query				Query; ///< Объект для проверки перекрытия

	private:

		GLuint				ArrayBuffer; ///< VAO буффер
		GLuint				VertexBuffer; ///< Вершиный буффер
		GLuint				IndexBuffer; ///< Индексный буффер

		glm::vec3			LocalVertexs[ 8 ]; ///< Массив вершин в локальной СК
		glm::vec3			GlobalVertexs[ 8 ]; ///< Массив вершин в глобальной СК
		glm::vec3			MinVertex; ///< Самая низка вершина
		glm::vec3			MaxVertex; ///< Самая высокая вершина
		glm::vec3			Position; ///< Позиция	
		glm::vec3			Scale; /// < Масштаб
		glm::quat			Rotation; ///< Поворот
		glm::mat4			MatrixPosition; ///< Матрица позиции
		glm::mat4			MatrixRotation; ///< Матрица поворота
		glm::mat4			MatrixScale; ///< Матрица масштаба
		glm::mat4			Transformation; ///< Матрица трансформации
	};

	//-------------------------------------------------------------------------//
}

#pragma warning( pop )
#endif // BOUNDING_BOX_H

