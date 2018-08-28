#include <System\System.h>
#include <System\ResourcesManager.h>
#include <Graphics\Models\Mesh.h>
#include <Graphics\Models\Model.h>
#include <Graphics\Scene.h>
#include <Graphics\Camera.h>
#include <Graphics\Level\Level.h>
#include <Graphics\Light\LightManager.h>
#include <System\Logger.h>

class Game : public le::BasicApplication
{
public:
	Game( le::System& System ) : le::BasicApplication( System )
	{
		le::ResourcesManager::SetErrorTexture( "../textures/Error.png" );

		Scene = new le::Scene();
		GBuffer = &Scene->GetGBuffer();

		ActiveCamera = new le::Camera( System );
		Scene->SetCamera( "Player2", *ActiveCamera );
		Cameras.push_back( ActiveCamera );

		ActiveCamera = new le::Camera( System );
		Scene->SetCamera( "Player1", *ActiveCamera );
		Cameras.push_back( ActiveCamera );

		Level = new le::Level( System );
		Level->LoadLevel( "../maps/testbed_c0a0.bsp" );
		Level->AddToScene( *Scene );

		glm::vec3 Position, LightRotation;
		string Name;
		vector<int> LightColor;
		vector<float> Rotation;
		vector<le::BaseEntity*>* LevelEntitys = &Level->GetAllEntitys();

		for ( size_t IdEntity = 0; IdEntity < LevelEntitys->size(); IdEntity++ )
		{
			le::BaseEntity* Entity = LevelEntitys->at( IdEntity );

			if ( Entity->ClassName == "info_player_start" )
			{
				Cameras[ 0 ]->SetPosition( Entity->Position );
				Cameras[ 1 ]->SetPosition( Entity->Position );
			}
		}

		//	if ( it->GetNameEntity() == "info_static_prop" )
		//	{
		//		string ModelName = it->GetValueString( "ModelName" );
		//		Name = it->GetValueString( "Name" );
		//		string AnimationName = it->GetValueString( "AnimationName" );
		//		Rotation = it->GetVelueVectorFloat( "Rotation" );
		//		Position = it->GetPosition();

		//		le::Model* Model = new le::Model();
		//		Model->LoadModel( Name, "../models/" + ModelName + ".lmd" );
		//		Model->GetAnimationManager()->Play( AnimationName, true );
		//		Model->SetPosition( Position );

		//		if ( !Rotation.empty() )
		//		Model->SetRotation( glm::vec3( Rotation[ 0 ], Rotation[ 1 ], Rotation[ 2 ] ) );

		//		Scene->AddModel( Model );
		//		Models.push_back( Model );
		//	}

		LightManager.AddSpotLight( "spot", 300, 300, glm::vec3( 0, -90, 0 ), glm::vec3(), glm::vec4( 164.f, 126.f, 0, 255.f ), 2.f );
		Spot = LightManager.GetSpotLight( "spot" );

		LightManager.AddPointLight( "point", 300, glm::vec3(), glm::vec4( 164.f, 126.f, 0, 255.f ), 2.f );
		Point = LightManager.GetPointLight( "point" );

		LightManager.AddLightsToScene( *Scene );

		Count = 0.f;
		MoveRight = true;
	}

	~Game()
	{
		delete Scene;
		delete Level;

		for ( size_t i = 0; i < Models.size(); i++ )
			delete Models[ i ];

		for ( size_t i = 0; i < Cameras.size(); i++ )
			delete Cameras[ i ];
	}

	void Update()
	{
		if ( Keyboard::isKeyPressed( Keyboard::F1 ) )
			ActiveCamera = Scene->SetActiveCamera( "Player1" );

		if ( Keyboard::isKeyPressed( Keyboard::F2 ) )
			ActiveCamera = Scene->SetActiveCamera( "Player2" );

		if ( MoveRight )
		{
			Point->SetPosition( glm::vec3( Point->Position.x + 1.f * Configuration->Time, Point->Position.y, Point->Position.z ) );
			Count += 1.f;
		}
		else
		{
			Point->SetPosition( glm::vec3( Point->Position.x - 1.f * Configuration->Time, Point->Position.y, Point->Position.z ) );
			Count -= 1.f;
		}

		if ( Count > 100 )
			MoveRight = false;
		else if ( Count < -100 )
			MoveRight = true;

		if ( Keyboard::isKeyPressed( Keyboard::W ) )
			ActiveCamera->Move( le::Camera::Forward, 5.25f * Configuration->Time );

		if ( Keyboard::isKeyPressed( Keyboard::S ) )
			ActiveCamera->Move( le::Camera::Back, 5.25f * Configuration->Time );

		if ( Keyboard::isKeyPressed( Keyboard::A ) )
		{
			ActiveCamera->Move( le::Camera::Left, 3.25f * Configuration->Time );

			if ( ActiveCamera->GetInclinationCamera() > -5 )
				ActiveCamera->TiltCamera( -0.2f );
		}

		if ( Keyboard::isKeyPressed( Keyboard::D ) )
		{
			ActiveCamera->Move( le::Camera::Right, 3.25f * Configuration->Time );

			if ( ActiveCamera->GetInclinationCamera() < 5 )
				ActiveCamera->TiltCamera( 0.2f );
		}

		if ( Keyboard::isKeyPressed( Keyboard::Q ) )
			le::System::SetWireframeRender( true );
		else
			le::System::SetWireframeRender( false );

		if ( Keyboard::isKeyPressed( Keyboard::Z ) )
			Spot->SetPosition( ActiveCamera->GetPosition() );

		if ( Keyboard::isKeyPressed( Keyboard::X ) )
			Point->SetPosition( ActiveCamera->GetPosition() );

		if ( !Keyboard::isKeyPressed( Keyboard::A ) && !Keyboard::isKeyPressed( Keyboard::D ) )
		{
			if ( ActiveCamera->GetInclinationCamera() + 0.5f < 0 )
				ActiveCamera->TiltCamera( 0.5f );
			else if ( ActiveCamera->GetInclinationCamera() - 0.5f > 0 )
				ActiveCamera->TiltCamera( -0.5f );
		}

		for ( size_t Id = 0; Id < Models.size(); Id++ )
		{
			le::Model* Model = Models[ Id ];

			if ( Keyboard::isKeyPressed( Keyboard::Left ) )
				Model->Move( glm::vec3( 1.f * Configuration->Time, 0, 0 ) );

			if ( Keyboard::isKeyPressed( Keyboard::Right ) )
				Model->Move( glm::vec3( -1.5f * Configuration->Time, 0, 0 ) );

			if ( Keyboard::isKeyPressed( Keyboard::Up ) )
				Model->Move( glm::vec3( 0, 0, 1.f * Configuration->Time ) );

			if ( Keyboard::isKeyPressed( Keyboard::Down ) )
				Model->Move( glm::vec3( 0, 0, -1.f * Configuration->Time ) );

			Model->GetAnimationManager()->Update();
		}

		ActiveCamera->UpdateTargetPoint();
		Scene->Render();

		if ( Keyboard::isKeyPressed( Keyboard::E ) )
			GBuffer->ShowDebug();
	}

	bool MoveRight;
	float Count;

	le::Scene*					Scene;
	le::Camera*					ActiveCamera;
	le::Level*					Level;
	le::GBuffer*				GBuffer;
	le::LightManager			LightManager;
	le::SpotLight*				Spot;
	le::PointLight*				Point;

	vector<le::Model*>			Models;
	vector<le::Camera*>			Cameras;
};

int main( int argc, char** argv )
{
	le::System System( argc, argv, "../config.cfg", "../" ENGINE ".log" );
	System.WindowCreate( ENGINE " | " ENGINE_VERSION, Style::Default );

	Game Game( System );
	System.MainLoop( Game );

	return 0;
}