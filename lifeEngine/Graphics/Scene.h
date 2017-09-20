﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef SCENE_H
#define SCENE_H

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

//////////////////
// SFML
//////////////////
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
using namespace sf;

////////////////
// LIFEENGINE
///////////////
#include <System\System.h>

namespace le
{
	//-------------------------------------------------------------------------//

	class Model;
	class BoundingBox;
	class Level;
	class Camera;
	class Frustum;
	class Skeleton;

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс для работы со сценой
	///
	/// Данный класс необходим для рендера графики на экран
	//////////////////////////////////////////////////////////////////////
	class DLL_API Scene
	{
	public:

		//-------------------------------------------------------------------------//

		//////////////////////////////////////////////////////////////////////
		/// \brief Структура хранения меша для сцены
		//////////////////////////////////////////////////////////////////////
		struct DLL_API InfoMesh
		{
			//////////////////////////////////////////////////////////////////////
			/// \brief Конструктор
			//////////////////////////////////////////////////////////////////////
			InfoMesh();

			int					CountIndexs; ///< Количество индексов вершин

			GLuint				VertexArray; ///< VAO
			Skeleton*			Skeleton; ///< Скелет меша
			BoundingBox*		BoundingBox; ///< Ограничивающее тело меша
			glm::mat4*			MatrixTransformation; ///< Матрица трансформации меша
		};

		//-------------------------------------------------------------------------//

		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		//////////////////////////////////////////////////////////////////////
		Scene( System& System );

		//////////////////////////////////////////////////////////////////////
		/// \brief Деструктор
		//////////////////////////////////////////////////////////////////////
		~Scene();

		//////////////////////////////////////////////////////////////////////
		/// \brief Добавить модель на сцену
		///		
		/// \param[in] Model Указатель на модель
		//////////////////////////////////////////////////////////////////////
		void AddModelToScene( Model* Model );

		//////////////////////////////////////////////////////////////////////
		/// \brief Удалить модель с сцены
		///		
		/// \param[in] Model Указатель на модель
		//////////////////////////////////////////////////////////////////////
		void RemoveModelFromScene( Model* Model );

		//////////////////////////////////////////////////////////////////////
		/// \brief Добавить уровень на сцену
		///		
		/// \param[in] Level Указатель на уровень
		//////////////////////////////////////////////////////////////////////
		void AddLevelToScene( Level* Level );

		//////////////////////////////////////////////////////////////////////
		/// \brief Удалить уровень с сцены
		///		
		/// \param[in] Level Указатель на уровень
		//////////////////////////////////////////////////////////////////////
		void RemoveLevelFromScene( Level* Level );

		//////////////////////////////////////////////////////////////////////
		/// \brief Убрать камеру со сцены
		//////////////////////////////////////////////////////////////////////
		void RemoveCamera();

		//////////////////////////////////////////////////////////////////////
		/// \brief Отрендерить сцену
		//////////////////////////////////////////////////////////////////////
		void RenderScene();

		//////////////////////////////////////////////////////////////////////
		/// \brief Очистить сцену
		//////////////////////////////////////////////////////////////////////
		void ClearScene();

		//////////////////////////////////////////////////////////////////////
		/// \brief Задать камеру
		///		
		/// \param[in] Camera Камера
		//////////////////////////////////////////////////////////////////////
		void SetCamera( Camera& Camera );

	private:

		Shader								AnimationModelsRender; ///< Шейдер рендера анимируемых моделей
		Shader								StaticModelsRender; ///< Шейдер рендера статичных моделей
		Shader								LevelRender; ///< Шейдер рендера уровня
		glm::mat4*							ViewMatrix; ///< Матрица вида
		glm::mat4*							ProjectionMatrix; ///< Матрица проекции
		Frustum*							Frustum; ///< Пирамида усечения

		Level*								LevelInScene; ///< Уровень который нах. на сцене
		vector<Model*>						ModelsInScene; ///< Массив моделей которые нах. на сцене

		map<GLuint, vector<InfoMesh*>>		RenderBuffer_AnimationModels; ///< Буффер рендера анимируемых моделей
		map<GLuint, vector<InfoMesh*>>		RenderBuffer_StaticModels; ///< Буффер рендера статичных моделей
		map<GLuint, vector<InfoMesh*>>		RenderBuffer_Level; ///< Буффер рендера уровня
	};

	//-------------------------------------------------------------------------//
}

#endif // SCENE_H