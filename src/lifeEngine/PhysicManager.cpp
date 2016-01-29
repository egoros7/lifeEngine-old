﻿#include "PhysicManager.h"

le::PhysicManager::PhysicManager( float& fTime )
{
    this->fTime = &fTime;
    sNameEntityCollided = "";
}

le::PhysicManager::~PhysicManager()
{
}

void le::PhysicManager::UpdatePhysic( vector<Object> obj , vector<BasicEntity*> vEntity , FloatRect& RectEntity , int num )
{
    if ( num == 0 )
    {
        if ( !bOnGround ) fDy += 0.0005 * *fTime;
        bOnGround = false;
    }

    // Check colision for objects in level
    for ( int i = 0; i < obj.size(); i++ )
    {
        if ( RectEntity.intersects( obj[ i ].rect ) )
        {
            if ( obj[ i ].type == "solid" )
            {
                if ( fDx < 0 && num == 0 )  RectEntity.left = obj[ i ].rect.left + obj[ i ].rect.width;
                if ( fDx > 0 && num == 0 )  RectEntity.left = obj[ i ].rect.left - RectEntity.width;
                if ( fDy < 0 && num == 1 ) { RectEntity.top = obj[ i ].rect.top + RectEntity.height; fDy = 0; }
                if ( fDy > 0 && num == 1 ) { RectEntity.top = obj[ i ].rect.top - RectEntity.height; bOnGround = true; fDy = 0; }
            }
        }
    }

    // Check colision for entity
    for ( int i = 0; i < vEntity.size(); i++ )
    {
        if ( RectEntity.intersects( vEntity[ i ]->GetRect() ) )
            if ( RectEntity != vEntity[ i ]->GetRect() )
            {
                if ( fDx < 0 && num == 0 )  RectEntity.left = vEntity[ i ]->GetRect().left + vEntity[ i ]->GetRect().width;
                if ( fDx > 0 && num == 0 )  RectEntity.left = vEntity[ i ]->GetRect().left - RectEntity.width;
                if ( fDy < 0 && num == 1 ) { RectEntity.top = vEntity[ i ]->GetRect().top + RectEntity.height; fDy = 0; }
                if ( fDy > 0 && num == 1 ) { RectEntity.top = vEntity[ i ]->GetRect().top - RectEntity.height; bOnGround = true; fDy = 0; }
                sNameEntityCollided = vEntity[ i ]->GetNameEntity();
            }
    }

}

string le::PhysicManager::GetNameEntityCollided() const
{
    return sNameEntityCollided;
}

void le::PhysicManager::Option()
{
    fDx = fDy = 0;
    bOnGround = false;
}