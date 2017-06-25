#include "..\..\3D\ModelMesh.h"
#include "..\..\System\MaterialManager.h"
#include <HaffmanCode.h>

//-------------------------------------------------------------------------//

bool le::VBO_ModelVertex::operator==( le::VBO_ModelVertex& VBO_ModelVertex )
{
	return Position == VBO_ModelVertex.Position &&
		Normal == VBO_ModelVertex.Normal &&
		TextureCoord == VBO_ModelVertex.TextureCoord &&
		VertexColor == VBO_ModelVertex.VertexColor;
}

//-------------------------------------------------------------------------//

le::ModelMesh::~ModelMesh()
{
	Clear();
}

//-------------------------------------------------------------------------//

bool le::ModelMesh::LoadMesh( string route )
{
	TiXmlDocument LMD;

	vector<string>	 vNameTextures;
	vector<Vector3f> vVertexPosition;
	vector<Vector3f> vVertexNormal;
	vector<Color>	 vVertexColor;
	vector<Vector2f> vTextureCoords;

	string routeTmp = route;
	routeTmp.erase( 0, routeTmp.find_last_of( '.' ) + 1 );

	if ( routeTmp == "lmd" )
	{
		// ���������� ������
		HaffmanCode haffmanCode;
		string sModel = haffmanCode.DecompressedFromFile( route );

		if ( sModel == "ERROR" )
		{
			cout << "Error: Model [" << route << "] Not Found\n";
			return false;
		}

		LMD.Parse( sModel.c_str() );
	}
	else if ( routeTmp == "xlmd" )
	{
		if ( !LMD.LoadFile( route.c_str() ) )
		{
			cout << "Error: Model [" << route << "] Not Found\n";
			return false;
		}
	}
	else
	{
		cout << "Error: Model [" << route << "] Not Correct Format\n";
		return false;
	}

	// �������� � ����������� model
	TiXmlElement *model;
	model = LMD.FirstChildElement( "model" );

	// �������� � ����������� textures
	TiXmlElement *textures;
	TiXmlElement *img;

	textures = model->FirstChildElement( "textures" );

	if ( textures != NULL )
	{
		img = textures->FirstChildElement( "image" );

		while ( img )
		{
			string route = img->Attribute( "src" );
			route.erase( 0, route.find_last_of( '/' ) + 1 );
			
			string nameTexture = route;
			nameTexture.erase( 0, nameTexture.find_last_of( '\\' ) + 1 );

			MaterialManager::LoadGLTexture( nameTexture, route );
			vNameTextures.push_back( nameTexture );
			img = img->NextSiblingElement();
		}
	}
	
	// �������� � ����������� geometries
	TiXmlElement *geometries;
	TiXmlElement *point;

	geometries = model->FirstChildElement( "geometries" );

	TiXmlElement *position_point;
	position_point = geometries->FirstChildElement( "position_point" );
	point = position_point->FirstChildElement( "point" );

	while ( point )
	{
		Vector3f Vertex;

		Vertex.x = atof( point->Attribute( "x" ) );
		Vertex.y = atof( point->Attribute( "y" ) );
		Vertex.z = atof( point->Attribute( "z" ) );

		vVertexPosition.push_back( Vertex );
		point = point->NextSiblingElement();
	}

	TiXmlElement *Normals;
	Normals = geometries->FirstChildElement( "normals" );
	point = Normals->FirstChildElement( "point" );

	while ( point )
	{
		Vector3f Normal;

		Normal.x = atof( point->Attribute( "x" ) );
		Normal.y = atof( point->Attribute( "y" ) );
		Normal.z = atof( point->Attribute( "z" ) );

		vVertexNormal.push_back( Normal );
		point = point->NextSiblingElement();
	}

	TiXmlElement *UV;
	UV = geometries->FirstChildElement( "UV" );
	point = UV->FirstChildElement( "point" );

	while ( point )
	{
		Vector2f TexCoord;

		TexCoord.x = atof( point->Attribute( "x" ) );
		TexCoord.y = atof( point->Attribute( "y" ) );

		vTextureCoords.push_back( TexCoord );
		point = point->NextSiblingElement();
	}

	TiXmlElement *VertexColors;
	VertexColors = geometries->FirstChildElement( "VertexColors" );

	if ( VertexColors != NULL )
	{
		point = VertexColors->FirstChildElement( "point" );

		while ( point )
		{
			Color VertexColor;

			VertexColor.r = atof( point->Attribute( "r" ) );
			VertexColor.g = atof( point->Attribute( "g" ) );
			VertexColor.b = atof( point->Attribute( "b" ) );
			VertexColor.a = atof( point->Attribute( "a" ) );

			vVertexColor.push_back( VertexColor );
			point = point->NextSiblingElement();
		}
	}

	TiXmlElement *polygons;
	TiXmlElement *texture;
	TiXmlElement *p;

	polygons = geometries->FirstChildElement( "polygons" );
	texture = polygons->FirstChildElement( "texture" );

	while ( texture )
	{
		p = texture->FirstChildElement( "p" );
		int idTexture = atoi( texture->Attribute( "id" ) );
		int idVertex = 0;

		vector<unsigned int> vIdVertex;
		VBO_ModelVertex VBO_ModelVertex;
		ModelVertex ModelVertex;

		while ( p )
		{
			string sTmp = string( p->GetText() );
			istringstream iss( sTmp );

			for ( int id = 1; !iss.eof(); id++ )
			{
				string _tmp;
				iss >> _tmp;

				switch ( id )
				{
				case 1: // ����������			
					idVertex = atoi( _tmp.c_str() );
					VBO_ModelVertex.Position = vVertexPosition[idVertex];
					ModelVertex.Position = VBO_ModelVertex.Position;
					break;

				case 2: // �������
					VBO_ModelVertex.Normal = vVertexNormal[atoi( _tmp.c_str() )];
					break;

				case 3: // ��������
					VBO_ModelVertex.TextureCoord = vTextureCoords[atoi( _tmp.c_str() )];


					if ( vVertexColor.empty() )
					{
						bool isFind = false;
						for ( int i = 0; i < vVBO_Vertexs.size(); i++ )
						if ( vVBO_Vertexs[i] == VBO_ModelVertex )
						{
							vIdVertex.push_back( i );
							isFind = true;
							break;
						}

						if ( !isFind )
						{
							if ( mVertexs.find( idVertex ) != mVertexs.end() )
							{
								if ( mVertexs[idVertex].Position == VBO_ModelVertex.Position )
									mVertexs[idVertex].vIdVBO_Vertex.push_back( vVBO_Vertexs.size() );
							}
							else
							{
								mVertexs[idVertex] = ModelVertex;

								if ( mVertexs[idVertex].Position == VBO_ModelVertex.Position )
									mVertexs[idVertex].vIdVBO_Vertex.push_back( vVBO_Vertexs.size() );
							}

							vIdVertex.push_back( vVBO_Vertexs.size() );
							vVBO_Vertexs.push_back( VBO_ModelVertex );
						}

						id = 0;
					}

					break;

				case 4: // ���� �������
					VBO_ModelVertex.VertexColor = vVertexColor[atoi( _tmp.c_str() )];

					bool isFind = false;
					for ( int i = 0; i < vVBO_Vertexs.size(); i++ )
					if ( vVBO_Vertexs[i] == VBO_ModelVertex )
					{
						vIdVertex.push_back( i );
						isFind = true;
						break;
					}

					if ( !isFind )
					{
						if ( mVertexs.find( idVertex ) != mVertexs.end() )
						{
							if ( mVertexs[idVertex].Position == VBO_ModelVertex.Position )
								mVertexs[idVertex].vIdVBO_Vertex.push_back( vVBO_Vertexs.size() );
						}
						else
						{
							mVertexs[idVertex] = ModelVertex;

							if ( mVertexs[idVertex].Position == VBO_ModelVertex.Position )
								mVertexs[idVertex].vIdVBO_Vertex.push_back( vVBO_Vertexs.size() );
						}

						vIdVertex.push_back( vVBO_Vertexs.size() );
						vVBO_Vertexs.push_back( VBO_ModelVertex );
					}

					id = 0;

					id = 0;
					break;
				}
			}

			p = p->NextSiblingElement();
		}

		mIdIndexs[vNameTextures[idTexture]] = vIdVertex;;
		mCountIndexs[vNameTextures[idTexture]] = vIdVertex.size();

		texture = texture->NextSiblingElement();
	}

	// �������� � ����������� skeleton
	TiXmlElement *skeleton;
	skeleton = model->FirstChildElement( "skeleton" );

	if ( skeleton != NULL )
	{
		Skeleton.LoadSkeleton( skeleton, mVertexs );
		Skeleton.InitMesh( mVertexs, vVBO_Vertexs );
	}

	// �������� � ����������� animations
	TiXmlElement *animations;
	animations = model->FirstChildElement( "animations" );

	if ( animations != NULL )
	{
		AnimationManager3D.SetSkeleton( Skeleton );
		AnimationManager3D.LoadAnimations( animations );
	}
}

//-------------------------------------------------------------------------//

void le::ModelMesh::Clear()
{
	mCountIndexs.clear();
	vVBO_Vertexs.clear();
	mIdIndexs.clear();
	mVertexs.clear();
}

//-------------------------------------------------------------------------//