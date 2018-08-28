﻿#include <Graphics\Models\Skeleton.h>

//-------------------------------------------------------------------------//

bool le::Skeleton::LoadSkeleton( TiXmlElement* Skeleton )
{
	Logger::Log( Logger::Info, "Loading Skeleton Mesh" );

	// ****************************
	// Загружаем матрицу биндинга
	// ****************************

	TiXmlElement* BindShapeMatrix;
	BindShapeMatrix = Skeleton->FirstChildElement( "bindShapeMatrix" );

	if ( BindShapeMatrix == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"bindShapeMatrix\"" );
		return false;
	}

	stringstream StrStream( BindShapeMatrix->GetText() );
	string TempString;
	glm::vec4 TempVector4;

	for ( int id = 0, axis = 1; id < 4, !StrStream.eof(); axis++ )
	{
		StrStream >> TempString;

		switch ( axis )
		{
		case 1: // x
			TempVector4.x = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
			break;

		case 2: // y
			TempVector4.y = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
			break;

		case 3: // z
			TempVector4.z = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
			break;

		case 4: // w
			TempVector4.w = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
			BindShape[ id ] = TempVector4;

			id++;
			axis = 0;
			break;
		}

		TempString.clear();
	}

	// ****************************
	// Считываем веса костей
	// ****************************

	TiXmlElement* WeightsBones;
	WeightsBones = Skeleton->FirstChildElement( "weightsBones" );

	if ( WeightsBones == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"weightsBones\"" );
		return false;
	}

	vector<float> Weights;

	StrStream.clear();
	StrStream.str( WeightsBones->GetText() );

	while ( !StrStream.eof() )
	{
		StrStream >> TempString;
		Weights.push_back( NUMBER_TO_FLOAT( atof( TempString.c_str() ) ) );
		TempString.clear();
	}

	// ****************************
	// Загружаем имена суставов
	// ****************************

	TiXmlElement* Joints;
	Joints = Skeleton->FirstChildElement( "Joints" );

	if ( Joints == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"Joints\"" );
		return false;
	}

	vector<string> vJoints;

	StrStream.clear();
	StrStream.str( Joints->GetText() );

	while ( !StrStream.eof() )
	{
		StrStream >> TempString;
		vJoints.push_back( TempString );
		TempString.clear();
	}

	// ****************************
	// Загружаем иерархию костей
	// ****************************

	TiXmlElement* MainNode;
	MainNode = Skeleton->FirstChildElement( "mainNode" );

	if ( MainNode == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"mainNode\"" );
		return false;
	}

	TiXmlElement* Node;
	Node = MainNode->FirstChildElement( "node" );

	while ( Node )
	{
		Bone TempBone;
		ReadingBone( Node, &TempBone );
		Bones.push_back( TempBone );

		Node = Node->NextSiblingElement();
	}

	// ****************************
	// Востанавливаем id предков
	// ****************************

	for ( size_t i = 0; i < Bones.size(); i++ )
	{
		Bone* bone = &Bones[ i ];

		if ( bone->ParentName != "" )
			bone->IdParent = GetIdBone( bone->ParentName );
		else
			IdRootBones.push_back( i );
	}

	// ****************************
	// Считывем кол-во костей на одну вершину
	// ****************************

	TiXmlElement* VCount;
	VCount = Skeleton->FirstChildElement( "vcount" );

	if ( VCount == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"vcount\"" );
		return false;
	}

	vector<int> TmpIdVertexs;

	StrStream.clear();
	StrStream.str( VCount->GetText() );

	while ( !StrStream.eof() )
	{
		StrStream >> TempString;
		TmpIdVertexs.push_back( atoi( TempString.c_str() ) );
		TempString.clear();
	}

	// ****************************
	// Считывем id кости и вес
	// ****************************

	TiXmlElement* IdBoneWeihgt;
	IdBoneWeihgt = Skeleton->FirstChildElement( "IdBoneWeihgt" );

	if ( IdBoneWeihgt == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"IdBoneWeihgt\"" );
		return false;
	}

	StrStream.clear();
	StrStream.str( IdBoneWeihgt->GetText() );

	Bone* TmpBone;
	int NumBones = 0;
	int TempNumBones = 0;
	int IdVertex = -1;
	int IdBone = 0;

	// даный масив содержит отсорт. массив костей 
	// по такому типу: вершина - какие кости на нее 
	// действуют, и с каким весом

	map<int, vector<pair<Bone*, float>>>	VertexBonesById;
	vector<pair<Bone*, float>>*				VertexBones;
	pair<Bone*, float>						VertexBone;

	for ( int id = 1; !StrStream.eof(); id++ )
	{
		StrStream >> TempString;

		switch ( id )
		{
		case 1: // id кости
			TmpBone = GetBone( vJoints[ atoi( TempString.c_str() ) ] );
			break;

		case 2: // вес
			if ( TempNumBones == 0 )
			{
				IdVertex++;
				NumBones = TmpIdVertexs[ IdVertex ];

				if ( NumBones != 1 )
					TempNumBones = NumBones - 1;
			}
			else
				TempNumBones--;

			VertexBones = &VertexBonesById[ IdVertex ];

			// Проверяем чтобы не было 
			// повторений костей в массиве

			bool IsFind = false;
			for ( size_t i = 0; i < VertexBones->size(); i++ )
				if ( ( *VertexBones )[ i ].first == TmpBone )
				{
					IsFind = true;
					break;
				}

			if ( !IsFind )
			{
				VertexBone.first = TmpBone;
				VertexBone.second = Weights[ atoi( TempString.c_str() ) ];
				VertexBones->push_back( VertexBone );
			}

			id = 0;
			break;
		}

		TempString.clear();
	}

	// ****************************
	// Убираем лишнии кости чтобы на одну вершину
	// припадало макс. 4х кости
	// ****************************

	for ( auto it = VertexBonesById.begin(); it != VertexBonesById.end(); it++ )
	{
		// Сортируем веса костей по уменьшению
		// чтобы можно было взять четыре кости
		// с наиболее высоким весом

		float MaxWeight = it->second[ 0 ].second;
		for ( size_t i = 0; i < it->second.size() - 1; i++ )
			if ( it->second[ i ].second > MaxWeight )
			{
				float TmpWeight = it->second[ i ].second;
				it->second[ i ].second = it->second[ i + 1 ].second;
				it->second[ i + 1 ].second = TmpWeight;
				i = -1;
			}

		// Нормализовываем веса костей
		// чтобы в сумме они давали 1

		float accumInv = 0.0f;

		for ( size_t i = 0; i < 4 && i < VertexBones->size(); i++ ) // 4 - макс. кол-во костей на вершину
			accumInv += it->second[ i ].second;

		accumInv = 1.0f / accumInv;

		for ( size_t i = 0; i < 4 && i < VertexBones->size(); i++ )
			it->second[ i ].first->Weights[ it->first ] = it->second[ i ].second * accumInv;
	}

	// ****************************
	// Инициализирываем кости скелета
	// ****************************

	for ( size_t i = 0; i < Bones.size(); i++ )
		InitMatrixBone( Bones[ i ] );

	Logger::Log( Logger::Info, "Loaded Skeleton Mesh" );

	return true;
}

//-------------------------------------------------------------------------//

void le::Skeleton::UpdateMatrixBone( const string& NameBone, const glm::mat4& Matrix )
{
	Bone* Bone = GetBone( NameBone );

	if ( Bone != NULL )
	{
		Bone->InterpolatedMatrix = Matrix;

		if ( Bone->IdParent != -1 )
			Bone->Realese = Matrix * Bones[ Bone->IdParent ].Realese;

		for ( size_t i = 0; i < Bone->IdChild.size(); i++ )
			InitMatrixBone( Bones[ Bone->IdChild[ i ] ] );
	}
}

//-------------------------------------------------------------------------//

void le::Skeleton::UpdateSkeleton()
{
	for ( size_t i = 0; i < Bones.size(); i++ )
	{
		Bone* Bone = &Bones[ i ];
		Bone->TransformMatrix = Bone->InvertMatrix * Bone->Realese;
	}
}

//-------------------------------------------------------------------------//

int le::Skeleton::GetIdBone( const string& NameBone )
{
	for ( size_t i = 0; i < Bones.size(); i++ )
		if ( Bones[ i ].Name == NameBone )
			return NUMBER_TO_INT( i );

	return -1;
}

//-------------------------------------------------------------------------//

int le::Skeleton::GetIdBone( const Bone& Bone )
{
	for ( size_t i = 0; i < Bones.size(); i++ )
		if ( Bones[ i ].Name == Bone.Name )
			return i;

	return -1;
}

//-------------------------------------------------------------------------//

le::Skeleton::Bone* le::Skeleton::GetBone( const string& NameBone )
{
	for ( size_t i = 0; i < Bones.size(); i++ )
		if ( Bones[ i ].Name == NameBone )
			return &Bones[ i ];

	return NULL;
}

//-------------------------------------------------------------------------//

vector<le::Skeleton::Bone>* le::Skeleton::GetAllBones()
{
	return &Bones;
}

//-------------------------------------------------------------------------//

void le::Skeleton::ReadingBone( TiXmlElement* Node, Bone* Bone )
{
	stringstream StrStream;
	string TempString;
	glm::vec4 TempVector4;

	// ****************************
	// Считываем стартовую матрицу
	// ****************************

	TiXmlElement* StartMatrix;
	const char* TagText = Node->Attribute( "name" );

	if ( TagText != NULL )
		Bone->Name = TagText;

	StartMatrix = Node->FirstChildElement( "startMatrix" );

	if ( StartMatrix == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"startMatrix\"" );
		return;
	}

	TagText = StartMatrix->GetText();

	if ( TagText != NULL )
	{
		StrStream.str( TagText );

		for ( int id = 0, axis = 1; id < 4, !StrStream.eof(); axis++ )
		{
			StrStream >> TempString;

			switch ( axis )
			{
			case 1:
				TempVector4.x = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				break;

			case 2:
				TempVector4.y = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				break;

			case 3:
				TempVector4.z = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				break;

			case 4:
				TempVector4.w = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				Bone->InterpolatedMatrix[ id ] = TempVector4;

				id++;
				axis = 0;
				break;
			}

			TempString.clear();
		}
	}

	// ****************************
	// Загружаем инвертированную матрицу
	// ****************************

	TiXmlElement* InvertMatrix;
	InvertMatrix = Node->FirstChildElement( "invertMatrix" );

	if ( InvertMatrix == NULL )
	{
		Logger::Log( Logger::Error, "Not Correct Format In Skeleton Mesh. Not Found Tag \"invertMatrix\"" );
		return;
	}

	TagText = InvertMatrix->GetText();

	if ( TagText != NULL )
	{
		StrStream.clear();
		StrStream.str( TagText );

		for ( int id = 0, axis = 1; id < 4, !StrStream.eof(); axis++ )
		{
			StrStream >> TempString;

			switch ( axis )
			{
			case 1:
				TempVector4.x = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				break;

			case 2:
				TempVector4.y = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				break;

			case 3:
				TempVector4.z = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				break;

			case 4:
				TempVector4.w = NUMBER_TO_FLOAT( atof( TempString.c_str() ) );
				Bone->InvertMatrix[ id ] = TempVector4;

				id++;
				axis = 0;
				break;
			}

			TempString.clear();
		}
	}

	Bone->Realese = Bone->InterpolatedMatrix;

	Node = Node->FirstChildElement( "node" );

	while ( Node )
	{
		Skeleton::Bone Parent;
		ReadingBone( Node, &Parent );
		Parent.ParentName = Bone->Name;
		Bone->IdChild.push_back( Bones.size() );
		Bones.push_back( Parent );

		Node = Node->NextSiblingElement();
	}
}

//-------------------------------------------------------------------------//

void le::Skeleton::InitMatrixBone( Bone& Bone )
{
	if ( Bone.ParentName != "" )
		Bone.Realese = Bone.InterpolatedMatrix * Bones[ Bone.IdParent ].Realese;

	for ( size_t i = 0; i < Bone.IdChild.size(); i++ )
		InitMatrixBone( Bones[ Bone.IdChild[ i ] ] );
}

//-------------------------------------------------------------------------//
