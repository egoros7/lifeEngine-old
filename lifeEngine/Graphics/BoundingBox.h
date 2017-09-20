﻿#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

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

////////////////
// LIFEENGINE
///////////////
#include <Graphics\Frustum.h>

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
		/// \brief Получить вершины
		///
		/// \return glm::vec3*
		//////////////////////////////////////////////////////////////////////
		glm::vec3* GetVertexs();

	private:

		glm::vec3			Vertexs[ 8 ]; ///< Массив вершин (мин и макс)
	};

	//-------------------------------------------------------------------------//
}

#endif // BOUNDING_BOX_H
