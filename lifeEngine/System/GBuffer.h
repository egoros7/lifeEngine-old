﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef GBUFFER_H
#define GBUFFER_H

#define COMPILING_LIBRARY
#define GBUFFER_NUM_TEXTURES 3
#include <DllGlobal.h>

//////////////
// OPENGL
//////////////
#include <glew\glew.h>
#include <glm/glm.hpp>

//////////////////
// LIFEENGINE
//////////////////
#include <System\Logger.h>

namespace le
{
	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс для работы с G-Буффером
	///
	/// Данный класс необходим для работы с G-Буффером
	//////////////////////////////////////////////////////////////////////
	class DLL_API GBuffer
	{
	public:

		//-------------------------------------------------------------------------//

		enum TypeTexture
		{
			Position,
			Textures,
			Normal
		};

		//-------------------------------------------------------------------------//

		enum TypeBind
		{
			RenderBuffers,
			RenderLight,
			RenderSkybox
		};

		//-------------------------------------------------------------------------//

		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		//////////////////////////////////////////////////////////////////////
		GBuffer();

		//////////////////////////////////////////////////////////////////////
		/// \brief Деструктор
		//////////////////////////////////////////////////////////////////////
		~GBuffer();

		//////////////////////////////////////////////////////////////////////
		/// \brief Инициализировать G-Буффер
		///
		/// \param[in] WindowWidth Длина окна
		///	\param[in] WindowHeight Высота окна
		/// \return true - если все прошло успешно, иначе false
		//////////////////////////////////////////////////////////////////////
		bool InitGBuffer( const float& WindowWidth, const float& WindowHeight );

		//////////////////////////////////////////////////////////////////////
		/// \brief Инициализировать G-Буффер
		///
		/// \param[in] SizeWindow Размер окна
		/// \return true - если все прошло успешно, иначе false
		//////////////////////////////////////////////////////////////////////
		bool InitGBuffer( const glm::vec2& SizeWindow );

		//////////////////////////////////////////////////////////////////////
		/// \brief Очистить финальный кадр
		//////////////////////////////////////////////////////////////////////
		void ClearFrame();

		//////////////////////////////////////////////////////////////////////
		/// \brief Отрендерить финальный кадр
		//////////////////////////////////////////////////////////////////////
		void RenderFrame();

		//////////////////////////////////////////////////////////////////////
		/// \brief Отрендерить буффер
		///
		/// \param[in] TypeBufferRender Буффер для рендера
		//////////////////////////////////////////////////////////////////////
		void RenderFrame( TypeTexture TypeBufferRender );

		//////////////////////////////////////////////////////////////////////
		/// \brief Отрендерить финальный кадр
		///
		/// \param[in] SizeWindow Размер окна
		//////////////////////////////////////////////////////////////////////
		void RenderFrame( const glm::vec2& SizeWindow );

		//////////////////////////////////////////////////////////////////////
		/// \brief Привязать G-Буффер для рендера
		///
		/// \param[in] TypeBind Тип рендера
		//////////////////////////////////////////////////////////////////////
		void Bind( TypeBind TypeBind );

		//////////////////////////////////////////////////////////////////////
		/// \brief Отвязать G-Буффер от рендера
		//////////////////////////////////////////////////////////////////////
		void Unbind();

		//////////////////////////////////////////////////////////////////////
		/// \brief Показать отладачную информацию
		//////////////////////////////////////////////////////////////////////
		void ShowDebug();

		//////////////////////////////////////////////////////////////////////
		/// \brief Показать отладачную информацию
		///
		/// \param[in] SizeWindow Размер окна
		//////////////////////////////////////////////////////////////////////
		void ShowDebug( const glm::vec2& SizeWindow );

	private:

		bool			IsInit; ///< Инициализирован ли G-Буффер

		glm::vec2		SizeWindow; ///< Размер окна под который создан G-Буффер

		GLuint			FrameBuffer; ///< Буффер кадра
		GLuint			FinalFrame; ///< Финальный кадр
		GLuint			DepthBuffer; ///< Буффер глубины
		GLuint			Buffers[ GBUFFER_NUM_TEXTURES ]; ///< Буфферы (нормалей, позиций вершин и т.д)
		GLenum			DrawBuffers[ GBUFFER_NUM_TEXTURES ]; ///< Типы буфферов
	};

	//-------------------------------------------------------------------------//
}

#endif // GBUFFER_H
