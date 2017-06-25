﻿#ifndef MODEL_H
#define MODEL_H

#define COMPILING_LIBRARY
#include "../../DllGlobal.h"

////////////////
/// LIFEENGINE
///////////////
#include "ModelMesh.h"
#include "Skeleton.h"
#include "../System.h"
#include "../../Animation/AnimationManager3D.h"

namespace le
{
	//-------------------------------------------------------------------------//

	class DLL_API Model
	{
	public:
		/////////////////
		/// КОНСТРУКТОР
		/////////////////
		Model( System& System );

		/////////////////
		/// ДЕСТРУКТОР
		/////////////////
		~Model();

		/////////////////////
		/// УДАЛИТЬ МОДЕЛЬ
		/////////////////////
		void DeleteModel();

		//////////////////////
		/// ЗАГРУЗКА МОДЕЛИ
		//////////////////////
		bool LoadModel( string nameModel, string route );
		void LoadModel( ModelMesh ModelMesh );

		////////////////////////////
		/// ЗАДАТЬ ПОЗИЦИЮ МОДЕЛИ
		///////////////////////////
		void SetPosition( Vector3f Position );

		////////////////////////////
		/// ЗАДАТЬ МАСШТАБ МОДЕЛИ
		///////////////////////////
		void SetScale( Vector3f Scale );

		////////////////////////////
		/// ЗАДАТЬ ПОВОРОТ МОДЕЛИ
		///////////////////////////
		void SetRotate( Vector3f Angle );

		////////////////////
		/// СМЕСТИТЬ МОДЕЛЬ
		////////////////////
		void Move( Vector3f FactorMove );

		///////////////////////////
		/// МАСШТАБИРОВАТЬ МОДЕЛЬ
		//////////////////////////
		void Scale( Vector3f FactorScale );

		//////////////////////
		/// ПОВЕРНУТЬ МОДЕЛЬ
		//////////////////////
		void Rotate( Vector3f Angle );

		//////////////////////
		/// ОТРИСОВКА МОДЕЛИ
		//////////////////////
		void RenderModel();

		////////////////////////////////
		/// ПОЛУЧИТЬ МЕНЕДЖЕР АНИМАЦИЙ
		////////////////////////////////
		AnimationManager3D& GetAnimationManager();

		/////////////////////////////
		/// ПОЛУЧИТЬ ПОЗИЦИЮ МОДЕЛИ
		/////////////////////////////
		Vector3f GetPosition();

		////////////////////////////
		/// ПОЛУЧИТЬ МАСШТАБ МОДЕЛИ
		////////////////////////////
		Vector3f GetScale();

		////////////////////////////
		/// ПОЛУЧИТЬ ПОВОРОТ МОДЕЛИ
		////////////////////////////
		Vector3f GetRotate();

		////////////////////////////
		/// ПОЛУЧИТЬ ВЕРШИНЫ МОДЕЛИ
		////////////////////////////
		map<int, ModelVertex>& GetVertexs();

		///////////////////////////////////
		/// ПОЛУЧИТЬ ВЕРШИНЫ МОДЕЛИ В VBO
		///////////////////////////////////
		vector<VBO_ModelVertex>& GetVBO_Vertexs();

		/////////////////////////
		/// ПОЛУЧИТЬ VBO МОДЕЛИ
		////////////////////////
		GLuint& GetVertexBuffer();

	private:

		GLuint							VertexBuffer;

		Vector3f						Position;
		Vector3f						ScaleModel;
		Vector3f						Angle;

		Skeleton						Skeleton;
		AnimationManager3D				AnimationManager3D;
		System*							System;

		vector<VBO_ModelVertex>			vVBO_Vertexs;
		map<string, GLuint>				mIndexBuffers;
		map<string, int>				mCountIndexs;
		map<int, ModelVertex>			mVertexs;

	};

	//-------------------------------------------------------------------------//
}

#endif // MODEL_H