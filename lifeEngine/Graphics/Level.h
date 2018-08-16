﻿//////////////////////////////////////////////////////////////////////////
// 
//			*** lifeEngine (Двигатель Жизни) ***
//					Copyright (C) 2017
//
// Связь со мной:		https://vk.com/zombihello
// Репозиторий движка:  https://github.com/zombihello/lifeEngine
// 
//////////////////////////////////////////////////////////////////////////

#ifndef LEVEL_H
#define LEVEL_H

#define COMPILING_LIBRARY
#include <DllGlobal.h>

//////////////////
// LIFEENGINE
//////////////////
#include <System\VAO.h>
#include <System\Bitset.h>
#include <Graphics\Skybox.h>
#include <Graphics\Plane.h>
#include <Graphics\Entity.h>

namespace le
{
	//-------------------------------------------------------------------------//

	class LightManager;
	class Scene;

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура заголовка BSP файла
	//////////////////////////////////////////////////////////////////////
	struct BSPHeader
	{
		char		StrID[ 4 ];		///< Это всегда должно быть 'LBSP'
		int			Version;		///< Версия формата (на данный момент версия - 0x10)
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура одного куска BSP файла
	//////////////////////////////////////////////////////////////////////
	struct BSPLump
	{
		int			Offset;			///< Смещение в файле до начала этого куска
		int			Length;			///< Длина в байтах для этого куска	
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура вершин BSP файла
	//////////////////////////////////////////////////////////////////////
	struct BSPVertex
	{
		glm::vec3		Position;			///< Позиция вершины
		glm::vec2		TextureCoord;		///< Текстурные координаты
		glm::vec2		LightmapCoord;		///< Координаты светокарты (lightmap)
		glm::vec3		Normal;				///< Нормаль вершины
		byte			Color[ 4 ];			///< RGBA цвет для вершин

		bool operator==( BSPVertex& Vertex );
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура фейсов BSP файла
	//////////////////////////////////////////////////////////////////////
	struct BSPFace
	{
		int			TextureID;			///< Идентификатор текстуры
		int			Effect;				///< Индекс эффектов (-1 = n/a)
		int			Type;				///< Тип фейса (1 = полигон, 2 = патч, 3 = меш, 4 = билборд)
		int			StartVertIndex;		///< Начальный индекс первой вершины
		int			NumOfVerts;			///< Количество вершин
		int			StartIndex;			///< Начальный индекс в массиве индексов
		int			NumOfIndices;		///< Количество индексов в фейсе
		int			LightmapID;			///< Идентификатор карты освещения
		int			LMapCorner[ 2 ];	///< Угол света в изображении фейса
		int			LMapSize[ 2 ];		///< Размер секции световой карты
		glm::vec3	LMapPos;			///< Позиция световой карты.
		glm::vec3	LMapVecs[ 2 ];		///< 3D-пространство для S и T единичных векторов
		glm::vec3	Normal;				///< Нормаль фейса
		int			Size[ 2 ];			///< Габаритные размеры безье
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура текстуры BSP файла
	//////////////////////////////////////////////////////////////////////
	struct BSPTexture
	{
		char	StrName[ 64 ];				///< Название текстуры без расширения
		int		Flags;						///< Поверхностные флаги
		int		Contents;					///< Флаги содержимого
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура карт освещения BSP файла
	//////////////////////////////////////////////////////////////////////
	struct BSPLightmap
	{
		byte	ImageBits[ 128 ][ 128 ][ 3 ];		///< Данные в формате RGB разрешения 128x128
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура хранит ветки BSP дерева
	//////////////////////////////////////////////////////////////////////
	struct BSPNode
	{
		int				Plane;					///< Индекс в массиве плоскостей
		int				Front;					///< Дочерний индекс для передней ветки
		int				Back;					///< Дочерний индекс для задней ветки
		glm::ivec3		Min;					///< Ограничивающее тело (бокс) минимальная позиция
		glm::ivec3		Max;					///< Ограничивающее тело (бокс) максимальная позиция
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура хранит листья (конечную ветку) в BSP дереве
	//////////////////////////////////////////////////////////////////////
	struct BSPLeaf
	{
		int				Cluster;			///< Видимый кластер
		int				Area;				///< Зона портала
		glm::ivec3		Min;				///< Ограничивающее тело (бокс) минимальная позиция
		glm::ivec3		Max;				///< Ограничивающее тело (бокс) максимальная позиция
		int				LeafFace;			///< Первый индекс в массиве фейсов
		int				NumOfLeafFaces;		///< Количество фейсов для этого листа
		int				LeafBrush;			///< Первый индекс в массиве брашей
		int				NumOfLeafBrushes;		///< Количество брашей для этого листа
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура хранит разделяющую плоскость в BSP дереве
	//////////////////////////////////////////////////////////////////////
	struct BSPPlane
	{
		glm::vec3		Normal;			///< Нормаль плоскости
		float			Distance;		///< Плоское расстояние от источника
	};

	//-------------------------------------------------------------------------//

	//////////////////////////////////////////////////////////////////////
	/// \brief Структура хранит информацию кластеров для PVS'а
	//////////////////////////////////////////////////////////////////////
	struct BSPVisData
	{
		int			NumOfClusters;			///< Количество кластеров
		int			BytesPerCluster;		///< Количество байтов( 8 бит ) в бите кластера
		byte*		Bitsets;				///< Массив байтов, который содержит кластерные биты			
	};

	//////////////////////////////////////////////////////////////////////
	/// \brief Класс для работы с уровнем
	//////////////////////////////////////////////////////////////////////
	class DLL_API Level
	{
	public:

		//-------------------------------------------------------------------------//

		//////////////////////////////////////////////////////////////////////
		/// \brief Перечисление типов кусков BSP файла
		//////////////////////////////////////////////////////////////////////
		enum Lumps
		{
			Entities = 0,				///< Хранит позицию игрока, объекта и т.д
			Textures,					///< Хранит информацию про текстуры
			Planes,						///< Хранит плоскости
			Nodes,						///< Хранит BSP ветки
			Leafs,						///< Хранит листы узлов
			LeafFaces,					///< Хранит индексы листа в фейсах
			LeafBrushes,				///< Хранит индексы листа в брашах
			Models,						///< Хранит информацию о моделях
			Brushes,					///< Хранит информацию о брашах (для коллизии)
			BrushSides,					///< Хранит информацию о поверхностях браша
			Vertices,					///< Хранит вершины уровня
			Indices,					///< Хранит индексы уровня
			Shaders,					///< Хранит файлы шейдеров (смешивание, анимация ..)
			Faces,						///< Хранит фейся уровня
			Lightmaps,					///< Хранит световые карты для уровня
			LightVolumes,				///< Хранит дополнительную информацию о освещении света
			VisData,					///< Хранит PVS и информацию о кластере (видимость)
			MaxLumps					///< Константа для хранения количества кусков
		};

		//-------------------------------------------------------------------------//

		//////////////////////////////////////////////////////////////////////
		/// \brief Конструктор
		//////////////////////////////////////////////////////////////////////
		Level( System& System );

		//////////////////////////////////////////////////////////////////////
		/// \brief Деструктор
		//////////////////////////////////////////////////////////////////////
		~Level();

		//////////////////////////////////////////////////////////////////////
		/// \brief Загрузить карту в формате BSP (Версия Quake 3)
		///
		/// \param[in] Route Путь к файлу
		/// \return true если все прошло успешно, иначе false
		//////////////////////////////////////////////////////////////////////
		bool LoadLevel( const string& Route );

		//////////////////////////////////////////////////////////////////////
		/// \brief Добавить на сцену
		///		
		/// \param[in] Scene Сцена
		//////////////////////////////////////////////////////////////////////
		void AddToScene( Scene& Scene );

		//////////////////////////////////////////////////////////////////////
		/// \brief Удалить с сцены
		//////////////////////////////////////////////////////////////////////
		void RemoveFromScene();

		//////////////////////////////////////////////////////////////////////
		/// \brief Указать сцену (необходима для уничтожения со сцены)
		///		
		/// \param[in] Scene Сцена
		//////////////////////////////////////////////////////////////////////
		void SetScene( Scene* Scene );

		//////////////////////////////////////////////////////////////////////
		/// \brief Очистить уровень
		//////////////////////////////////////////////////////////////////////
		void ClearLevel();

		//////////////////////////////////////////////////////////////////////
		/// \brief Посчитать видимые плоскости
		///	
		/// \param[in] Camera Камера игрока
		//////////////////////////////////////////////////////////////////////
		void CalculateVisablePlanes( Camera& Camera );

		//////////////////////////////////////////////////////////////////////
		/// \brief Посчитать видимые плоскости
		///	
		/// \param[in] Position Позиция игрока
		/// \param[in] Frustum Пирамида отсечения
		//////////////////////////////////////////////////////////////////////
		void CalculateVisablePlanes( const glm::vec3& Position, Frustum& Frustum );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить скайбокс уровня
		///		
		/// \return Skybox&.
		//////////////////////////////////////////////////////////////////////
		Skybox& GetSkybox();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить VAO уровня
		///		
		/// \return Массив буфером уровня в OpenGL
		//////////////////////////////////////////////////////////////////////
		GLuint& GetArrayBuffer();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить энтити по названию
		///		
		/// \param[in] NameEntity Название энтити
		/// \return Entity*. Если не нашли энтити,то вернет NULL
		//////////////////////////////////////////////////////////////////////
		Entity* GetEntity( const string& NameEntity );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить буфер видимых плоскостей
		///
		/// \return Буфер видимых плоскостей на уровне
		//////////////////////////////////////////////////////////////////////
		map<GLuint, vector<Plane*> >& GetVisablePlanes();

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить все энтити на уровне
		///		
		/// \return vector<Entity*>&
		//////////////////////////////////////////////////////////////////////
		vector<Entity>& GetAllEntitys();

	private:

		//////////////////////////////////////////////////////////////////////
		/// \brief Изменить уровень гаммы на текстуре
		///		
		/// \param[in] ImageBits Массив байт изображения
		/// \param[in] Size Размер изображения
		/// \param[in] Factor Фактор гаммы
		//////////////////////////////////////////////////////////////////////
		void ChangeGamma( byte *ImageBits, int Size, float Factor );

		//////////////////////////////////////////////////////////////////////
		/// \brief Загрузить в OpenGL карту освещения с памяти
		///		
		/// \param[in] ImageBits Массив байт изображения
		/// \param[in] Width Длина изображения
		/// \param[in] Height Высота изображения
		//////////////////////////////////////////////////////////////////////
		void CreateLightmapTexture( byte *ImageBits, int Width, int Height );

		//////////////////////////////////////////////////////////////////////
		/// \brief Получить индекс листа в котором нах. камера
		///		
		/// \return Индекс листа
		//////////////////////////////////////////////////////////////////////
		int FindLeaf( const glm::vec3& Position );

		//////////////////////////////////////////////////////////////////////
		/// \brief Виден ли тестовый кластер из текущего кластера
		///		
		/// \return True - Виден тестовый кластер из текущего, False - нет
		//////////////////////////////////////////////////////////////////////
		bool IsClusterVisible( int CurrentCluster, int TestCluster );

		Scene*								Scene;				///< Сцена на котором находится уровень
		Skybox*								Skybox;				///< Скайбокс уровня
		Bitset								FacesDrawn;			///< Хранит нарисованные фейсы в битах
		BSPVisData							Сlusters;			///< Кластеры

		GLuint								VertexBuffer;		///< Вершиный буфер
		GLuint								IndexBuffer;		///< Индексный буфер
		GLuint								ArrayBuffer;		///< VAO

		vector<Plane*> 						ArrayPlanes;		///< Массив плоскостей уровня	
		vector<BSPNode>						ArrayNodes;			///< Массив веток BSP дерева
		vector<BSPLeaf>						ArrayLeafs;			///< Массив листьев BSP дерева
		vector<BSPPlane>					ArrayBSPPlanes;		///< Массив секущих плоскостей
		vector<Entity>						ArrayEntitys;		///< Массив энтити-объектов
		vector<int>							ArrayLeafsFaces;	///< Массив индексов фейсов в листе
		vector<GLuint>						ArrayLightmaps;		///< Массив идентификаторов карт освещения

		map<GLuint, vector<le::Plane*> >	VisablePlanes;		///< Буффер видимых плоскостей (обновляется при вызове GetVisablePlanes() )
	};

	//-------------------------------------------------------------------------//
}

#endif //LEVEL_H

