﻿#ifndef SKELETON_H
#define SKELETON_H

#define COMPILING_LIBRARY
#include "../../DllGlobal.h"

////////////////
/// LIFEENGINE
///////////////
#include "../System.h"
#include <Matrix.h>

namespace le
{
	//-------------------------------------------------------------------------//

	struct Mesh;
	struct Vertex;

	//-------------------------------------------------------------------------//

	struct DLL_API Bone
	{
		Bone();

		Matrixf				StartMatrix;
		Matrixf				InvertMatrix;
		Matrixf				Realese;

		vector<Bone*>		vChild;

		Bone*				Perent;
		string				name;
	};

	//-------------------------------------------------------------------------//

	class DLL_API Skeleton
	{
	public:
		/////////////////
		/// КОНСТРУКТОР
		/////////////////
		Skeleton( Mesh& Mesh );

		/////////////////
		/// ДЕСТРУКТОР
		/////////////////
		~Skeleton();

		//////////////////////
		/// ЗАГРУЗИТЬ СКЕЛЕТ
		/////////////////////
		void LoadSkeleton( TiXmlElement *skeleton );

		//////////////////////////////////
		/// ИНИЦИАЛИЗАЦИЯ ПОЗИЦИИ ВЕРШИН
		/////////////////////////////////
		void InitMesh();

		//////////////////////////////
		/// ДОБАВИТЬ КОСТЬ СКЕЛЕТУ
		//////////////////////////////
		void AddBone( Bone* bone );

		///////////////////////////////////////////////////
		/// ЗАДАТЬ ТРАНСФОРМАЦИЮ МОДЕЛИ ПЕРЕД БИНДИНГОМ 
		///////////////////////////////////////////////////
		void SetBindShape( Matrixf bindShape );

		///////////////////////////////////
		/// ЗАДАТЬ МАТРИЦУ ДЛЯ КОСТИ
		//////////////////////////////////
		void SetMatrixBone( string nameBone, Matrixf matrix );

		///////////////////////////////////////////////////
		/// ПОЛУЧИТЬ ТРАНСФОРМАЦИЮ МОДЕЛИ ПЕРЕД БИНДИНГОМ 
		///////////////////////////////////////////////////
		float* GetBindShape();

		/////////////////////////////////
		/// ПОЛУЧИТЬ ВСЕ КОСТИ СКЕЛЕТА
		////////////////////////////////
		vector<Bone*> GetAllBones();

		////////////////////////////////////////
		/// ПОЛУЧИТЬ КОСТЬ СКЕЛЕТА ПО ИМЕНИ
		////////////////////////////////////////
		Bone* GetBone( string NameBone );

		//////////////////////////////////
		/// ПОЛУЧИТЬ КОСТЬ СКЕЛЕТА ПО ID
		/////////////////////////////////
		int	GetIdBone( string NameBone );

		///////////////////////
		/// НАРИСОВАТЬ СКЕЛЕТ
		//////////////////////
		void DrawSkeleton( vector<Bone*> bones );

	private:
		////////////////////////////////////////////
		/// СЧИТЫВАНИЕ КОСТЕЙ [РЕКУРСИВНЫЙ МЕТОД]
		///////////////////////////////////////////
		void ReadingBone( TiXmlElement* node , Bone* bone );

		//////////////////////////////////
		/// ИНИЦИАЛИЗАЦИЯ КОСТЕЙ СКЕЛЕТА
		//////////////////////////////////
		void InitBone();

		//////////////////////////////////
		/// ИНИЦИАЛИЗАЦИЯ МАТРИЦ КОСТЕЙ
		//////////////////////////////////
		void InitMatrixBone( Bone& bone );

		Mesh*				Mesh;
		Matrixf				BindShape;
		vector<Bone*>		vBone;
	};

	//-------------------------------------------------------------------------//
}

#endif // SKELETON_H
