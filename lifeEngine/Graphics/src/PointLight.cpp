﻿#include <System\System.h>
#include <Graphics\Scene.h>
#include "..\PointLight.h"

//-------------------------------------------------------------------------//

le::PointLight::PointLight() :
	Radius( 25 )
{
	Logger::Log( Logger::Info, "Creating Point Light" );
	Logger::Log( Logger::None, "  Radius: " + to_string( Radius ) );
	Logger::Log( Logger::None, "  Intensivity: " + to_string( Intensivity ) );
	Logger::Log( Logger::None, "  Position: " + to_string( Position.x ) + " " + to_string( Position.y ) + " " + to_string( Position.z ) );
	Logger::Log( Logger::None, "  Color: " + to_string( Color.x ) + " " + to_string( Color.y ) + " " + to_string( Color.z ) + " " + to_string( Color.w ) );
	Logger::Log( Logger::None, "  Specular: " + to_string( Specular.x ) + " " + to_string( Specular.y ) + " " + to_string( Specular.z ) + " " + to_string( Specular.w ) );

	LightSphere.InitSphere( Radius );
	LightSphere.SetPosition( Position );

	glm::vec3 TempPosition = Position;
	LightProjection = glm::perspective( glm::radians( 90.f ), NUMBER_TO_FLOAT( SHADOWMAP_SIZE / SHADOWMAP_SIZE ), 1.f, Radius );

	LightTransforms =
	{
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( -1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, 1, 0 ), glm::vec3( 0, 0, 1 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, -1, 0 ), glm::vec3( 0, 0, -1 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) )
	};

	Logger::Log( Logger::Info, "Created Point Light" );
}

//-------------------------------------------------------------------------//

le::PointLight::PointLight( const PointLight& Copy )
{
	CopyBaseLight( Copy );

	Radius = Copy.Radius;
	LightSphere = Copy.LightSphere;
}

//-------------------------------------------------------------------------//

le::PointLight::PointLight( float Radius, const glm::vec3& Position, const glm::vec4& Color, float Intensivity, const glm::vec4& Specular )
{
	Logger::Log( Logger::Info, "Creating Point Light" );
	Logger::Log( Logger::None, "  Radius: " + to_string( Radius ) );
	Logger::Log( Logger::None, "  Intensivity: " + to_string( Intensivity ) );
	Logger::Log( Logger::None, "  Position: " + to_string( Position.x ) + " " + to_string( Position.y ) + " " + to_string( Position.z ) );
	Logger::Log( Logger::None, "  Color: " + to_string( Color.x ) + " " + to_string( Color.y ) + " " + to_string( Color.z ) + " " + to_string( Color.w ) );
	Logger::Log( Logger::None, "  Specular: " + to_string( Specular.x ) + " " + to_string( Specular.y ) + " " + to_string( Specular.z ) + " " + to_string( Specular.w ) );

	this->Position = glm::vec4( Position, 1.0f );
	this->Color = Color / 255.f;
	this->Specular = Specular / 255.f;
	this->Radius = Radius;
	this->Intensivity = Intensivity;

	LightSphere.InitSphere( Radius );
	LightSphere.SetPosition( Position );

	LightProjection = glm::perspective( glm::radians( 90.f ), NUMBER_TO_FLOAT( SHADOWMAP_SIZE / SHADOWMAP_SIZE ), 1.f, Radius );

	LightTransforms =
	{
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( -1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, 1, 0 ), glm::vec3( 0, 0, 1 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, -1, 0 ), glm::vec3( 0, 0, -1 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) )
	};

	Logger::Log( Logger::Info, "Created Point Light" );
}

//-------------------------------------------------------------------------//

le::PointLight::~PointLight()
{}

//-------------------------------------------------------------------------//

void le::PointLight::SetRadius( float Radius )
{
	this->Radius = Radius;
	LightSphere.SetRadius( Radius );

	glm::vec3 TempPosition = Position;
	LightProjection = glm::perspective( glm::radians( 90.f ), NUMBER_TO_FLOAT( SHADOWMAP_SIZE / SHADOWMAP_SIZE ), 1.f, Radius );

	LightTransforms =
	{
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( -1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, 1, 0 ), glm::vec3( 0, 0, 1 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, -1, 0 ), glm::vec3( 0, 0, -1 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( TempPosition, TempPosition + glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) )
	};
}

//-------------------------------------------------------------------------//

void le::PointLight::SetPosition( const glm::vec3& Position )
{
	this->Position = glm::vec4( Position, 1.0f );
	LightSphere.SetPosition( Position );

	LightTransforms =
	{
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( -1, 0, 0 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, 1, 0 ), glm::vec3( 0, 0, 1 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, -1, 0 ), glm::vec3( 0, 0, -1 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, 0, 1 ), glm::vec3( 0, 1, 0 ) ),
		LightProjection * glm::lookAt( Position, Position + glm::vec3( 0, 0, -1 ), glm::vec3( 0, 1, 0 ) )
	};
}

//-------------------------------------------------------------------------//

le::PointLight& le::PointLight::operator=( const PointLight& Copy )
{
	CopyBaseLight( Copy );

	Radius = Copy.Radius;
	LightSphere = Copy.LightSphere;

	return *this;
}

//-------------------------------------------------------------------------//
