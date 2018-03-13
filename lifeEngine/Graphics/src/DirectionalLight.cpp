﻿#include <System\System.h>
#include <System\VAO.h>
#include "..\DirectionalLight.h"

//-------------------------------------------------------------------------//

le::DirectionalLight::DirectionalLight()
{
	Logger::Log( Logger::Info, "Creating Directional Light" );
	Logger::Log( Logger::None, "  Intensivity: " + to_string( Intensivity ) );
	Logger::Log( Logger::None, "  Position: " + to_string( Position.x ) + " " + to_string( Position.y ) + " " + to_string( Position.z ) );
	Logger::Log( Logger::None, "  Color: " + to_string( Color.x ) + " " + to_string( Color.y ) + " " + to_string( Color.z ) + " " + to_string( Color.w ) );
	Logger::Log( Logger::None, "  Specular: " + to_string( Specular.x ) + " " + to_string( Specular.y ) + " " + to_string( Specular.z ) + " " + to_string( Specular.w ) );

	Position.w = 0;
	Quad.InitQuad( 1.f );

	Logger::Log( Logger::Info, "Created Directional Light" );
}

//-------------------------------------------------------------------------//

le::DirectionalLight::DirectionalLight( const glm::vec3& Position, const glm::vec4& Color, float Intensivity, const glm::vec4& Specular )
{
	Logger::Log( Logger::Info, "Creating Directional Light" );
	Logger::Log( Logger::None, "  Intensivity: " + to_string( Intensivity ) );
	Logger::Log( Logger::None, "  Position: " + to_string( Position.x ) + " " + to_string( Position.y ) + " " + to_string( Position.z ) );
	Logger::Log( Logger::None, "  Color: " + to_string( Color.x ) + " " + to_string( Color.y ) + " " + to_string( Color.z ) + " " + to_string( Color.w ) );
	Logger::Log( Logger::None, "  Specular: " + to_string( Specular.x ) + " " + to_string( Specular.y ) + " " + to_string( Specular.z ) + " " + to_string( Specular.w ) );

	this->Position = glm::vec4( Position, 0.0f );
	this->Color = Color / 255.f;
	this->Specular = Specular / 255.f;
	this->Intensivity = Intensivity;

	Quad.InitQuad( 1 );

	Logger::Log( Logger::Info, "Created Directional Light" );
}

//-------------------------------------------------------------------------//

le::DirectionalLight::DirectionalLight( const DirectionalLight& Copy )
{
	CopyBaseLight( Copy );

	Quad = Copy.Quad;
}

//-------------------------------------------------------------------------//

le::DirectionalLight::~DirectionalLight()
{}

//-------------------------------------------------------------------------//

void le::DirectionalLight::SetPosition( const glm::vec3& Position )
{
	this->Position = glm::vec4( Position, 0.0f );
}

//-------------------------------------------------------------------------//

le::DirectionalLight& le::DirectionalLight::operator=( const DirectionalLight& Copy )
{
	CopyBaseLight( Copy );

	Quad = Copy.Quad;

	return *this;
}

//-------------------------------------------------------------------------//