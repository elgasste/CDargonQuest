#include "renderer.h"
#include "window.h"
#include "render_config.h"
#include "diagnostics_renderer.h"
#include "dialog_renderer.h"
#include "title_renderer.h"
#include "overworld_renderer.h"
#include "battle_renderer.h"
#include "transition_renderer.h"
#include "game.h"

void dqRenderer_Init()
{
   dqDiagnosticsRenderer_Init();
   dqDialogRenderer_Init();
   dqTitleRenderer_Init();
   dqOverworldRenderer_Init();
   dqBattleRenderer_Init();
   dqTransitionRenderer_Init();
}

void dqRenderer_Cleanup()
{
   dqTransitionRenderer_Cleanup();
   dqBattleRenderer_Cleanup();
   dqOverworldRenderer_Cleanup();
   dqTitleRenderer_Cleanup();
   dqDialogRenderer_Cleanup();
   dqDiagnosticsRenderer_Cleanup();
}

void dqRenderer_Render()
{
   dqWindow_Clear( dqWindow, dqRenderConfig->windowClearColor );

   switch ( dqGame->state )
   {
      case dqStateTitle:
         dqTitleRenderer_Render();
         break;
      case dqStateOverworld:
         dqOverworldRenderer_RenderMap();
         dqOverworldRenderer_RenderEntities();
         break;
      case dqStateOverworldTransition:
         dqOverworldRenderer_RenderMap();
         dqOverworldRenderer_RenderEntities();
         dqTransitionRenderer_Render( sfTrue ); // black
         break;
      case dqStateBattleTransitionIn:
         if ( dqTransitionRenderer->fadingIn )
         {
            dqBattleRenderer_Render();  
         }
         else
         {
            dqOverworldRenderer_RenderMap();
            dqOverworldRenderer_RenderEntities();
         }
         dqTransitionRenderer_Render( sfFalse ); // white
         break;
      case dqStateBattleTransitionOut:
         if ( dqTransitionRenderer->fadingOut )
         {
            dqBattleRenderer_Render();
         }
         else
         {
            dqOverworldRenderer_RenderMap();
            dqOverworldRenderer_RenderEntities();
         }
         dqTransitionRenderer_Render( sfTrue ); // black
         break;
      case dqStateBattle:
         dqBattleRenderer_Render();
         break;
   }

   if ( dqRenderConfig->showDiagnostics )
   {
      dqDiagnosticsRenderer_Render();
   }

   dqWindow_Display();
}
