#include "../AI.h"

//-------------------------------------------------------------------------//

le::AI::AI( le::System& System )
{
	ViewAI = new le::AI_View( System );
}

//-------------------------------------------------------------------------//

le::AI::~AI()
{
	delete ViewAI;
}

//-------------------------------------------------------------------------//

void le::AI::UpdateAI( vector<BasicPersonages*> vPersonage )
{
	ViewAI->UpdateViewAI( vPersonage );
	Actions();
}

//-------------------------------------------------------------------------//

bool le::AI::IsLook()
{
	return ViewAI->IsLook();
}

//-------------------------------------------------------------------------//

le::BasicPersonages* le::AI::GetLookPersonage()
{
	return ViewAI->GetLookPersonage();
}

//-------------------------------------------------------------------------//

void le::AI::InitAI( le::BasicPersonages* Personage , le::GroupColision GroupColision )
{
	ViewAI->InitViewAI( Personage , GroupColision );
}

//-------------------------------------------------------------------------//