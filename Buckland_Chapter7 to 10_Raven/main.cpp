#pragma warning (disable:4786)
#include <windows.h>
#include <time.h>
#include "constants.h"
#include "misc/utils.h"
#include "Time/PrecisionTimer.h"
#include "Resource.h"
#include "misc/windowutils.h"
#include "misc/Cgdi.h"
#include "debug/DebugConsole.h"
#include "Raven_UserOptions.h"
#include "Raven_Game.h"
#include "lua/Raven_Scriptor.h"


//need to include this for the toolbar stuff
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")



//--------------------------------- Globals ------------------------------
//------------------------------------------------------------------------

char* g_szApplicationName = "Raven";
char*	g_szWindowClassName = "MyWindowClass";


Raven_Game* g_pRaven;


//---------------------------- WindowProc ---------------------------------
//	
//	This is the callback function which handles all the windows messages
//-------------------------------------------------------------------------

LRESULT CALLBACK WindowProc (HWND   hwnd,
                             UINT   msg,
                             WPARAM wParam,
                             LPARAM lParam)
{
 
   //these hold the dimensions of the client window area
	 static int cxClient, cyClient; 

	 //used to create the back buffer
   static HDC		hdcBackBuffer;
   static HBITMAP	hBitmap;
   static HBITMAP	hOldBitmap;

      //to grab filenames
   static TCHAR   szFileName[MAX_PATH],
                  szTitleName[MAX_PATH];


    switch (msg)
    {
	
		//A WM_CREATE msg is sent when your application window is first
		//created
    case WM_CREATE:
      {
         //to get get the size of the client window first we need  to create
         //a RECT and then ask Windows to fill in our RECT structure with
         //the client window size. Then we assign to cxClient and cyClient 
         //accordingly
			   RECT rect;

			   GetClientRect(hwnd, &rect);

			   cxClient = rect.right;
			   cyClient = rect.bottom;

         //seed random number generator
         srand((unsigned) time(NULL));

         
         //---------------create a surface to render to(backbuffer)

         //create a memory device context
         hdcBackBuffer = CreateCompatibleDC(NULL);

         //get the DC for the front buffer
         HDC hdc = GetDC(hwnd);

         hBitmap = CreateCompatibleBitmap(hdc,
                                          cxClient,
                                          cyClient);

			  
         //select the bitmap into the memory device context
			   hOldBitmap = (HBITMAP)SelectObject(hdcBackBuffer, hBitmap);

         //don't forget to release the DC
         ReleaseDC(hwnd, hdc);  
              
         //create the game
         g_pRaven = new Raven_Game();

        //make sure the menu items are ticked/unticked accordingly
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SHOW_NAVGRAPH, UserOptions->m_bShowGraph);
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SHOW_PATH, UserOptions->m_bShowPathOfSelectedBot);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_IDS, UserOptions->m_bShowBotIDs);
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SMOOTH_PATHS_QUICK, UserOptions->m_bSmoothPathsQuick);
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SMOOTH_PATHS_PRECISE, UserOptions->m_bSmoothPathsPrecise);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_HEALTH, UserOptions->m_bShowBotHealth);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_TARGET, UserOptions->m_bShowTargetOfSelectedBot);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_FOV, UserOptions->m_bOnlyShowBotsInTargetsFOV);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_SCORES, UserOptions->m_bShowScore);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_GOAL_Q, UserOptions->m_bShowGoalsOfSelectedBot);
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SHOW_INDICES, UserOptions->m_bShowNodeIndices);
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_SENSED, UserOptions->m_bShowOpponentsSensedBySelectedBot);

      }

      break;

    case WM_KEYUP:
      {
        switch(wParam)
        {
         case VK_ESCAPE:
          {
            SendMessage(hwnd, WM_DESTROY, NULL, NULL);
          }
          
          break;

         case 'P':

           g_pRaven->TogglePause();

           break;

         case '1':

           g_pRaven->ChangeWeaponOfPossessedBot(type_blaster);

           break;

         case '2':

           g_pRaven->ChangeWeaponOfPossessedBot(type_shotgun);

           break;
           
         case '3':

           g_pRaven->ChangeWeaponOfPossessedBot(type_rocket_launcher);

           break;

         case '4':

           g_pRaven->ChangeWeaponOfPossessedBot(type_rail_gun);

           break;

         case 'X':

           g_pRaven->ExorciseAnyPossessedBot();

           break;


         case VK_UP:

           g_pRaven->AddBots(1); break;

         case VK_DOWN:

           g_pRaven->RemoveBot(); break;
           

        }
      }

      break;


    case WM_LBUTTONDOWN:
    {
      g_pRaven->ClickLeftMouseButton(MAKEPOINTS(lParam));
    }
    
    break;

   case WM_RBUTTONDOWN:
    {
      g_pRaven->ClickRightMouseButton(MAKEPOINTS(lParam));
    }
    
    break;

    case WM_COMMAND:
    {

     switch(wParam)
      {
      

      case IDM_GAME_LOAD:
          
          FileOpenDlg(hwnd, szFileName, szTitleName, "Raven map file (*.map)", "map");

          debug_con << "Filename: " << szTitleName << "";

          if (strlen(szTitleName) > 0)
          {
            g_pRaven->LoadMap(szTitleName);
          }

          break;

      case IDM_GAME_ADDBOT:

          g_pRaven->AddBots(1);
          
          break;

      case IDM_GAME_REMOVEBOT:
          
          g_pRaven->RemoveBot();

          break;

      case IDM_GAME_PAUSE:
          
          g_pRaven->TogglePause();

          break;



      case IDM_NAVIGATION_SHOW_NAVGRAPH:

        UserOptions->m_bShowGraph = !UserOptions->m_bShowGraph;

        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SHOW_NAVGRAPH, UserOptions->m_bShowGraph);

        break;
        
      case IDM_NAVIGATION_SHOW_PATH:

        UserOptions->m_bShowPathOfSelectedBot = !UserOptions->m_bShowPathOfSelectedBot;

        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SHOW_PATH, UserOptions->m_bShowPathOfSelectedBot);

        break;

      case IDM_NAVIGATION_SHOW_INDICES:

        UserOptions->m_bShowNodeIndices = !UserOptions->m_bShowNodeIndices;

        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SHOW_INDICES, UserOptions->m_bShowNodeIndices);

        break;

      case IDM_NAVIGATION_SMOOTH_PATHS_QUICK:

        UserOptions->m_bSmoothPathsQuick = !UserOptions->m_bSmoothPathsQuick;
        UserOptions->m_bSmoothPathsPrecise = false;
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SMOOTH_PATHS_PRECISE, UserOptions->m_bSmoothPathsPrecise);
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SMOOTH_PATHS_QUICK, UserOptions->m_bSmoothPathsQuick);

        break;

      case IDM_NAVIGATION_SMOOTH_PATHS_PRECISE:

        UserOptions->m_bSmoothPathsPrecise = !UserOptions->m_bSmoothPathsPrecise;
        UserOptions->m_bSmoothPathsQuick = false;
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SMOOTH_PATHS_QUICK, UserOptions->m_bSmoothPathsQuick);
        CheckMenuItemAppropriately(hwnd, IDM_NAVIGATION_SMOOTH_PATHS_PRECISE, UserOptions->m_bSmoothPathsPrecise);

        break;

      case IDM_BOTS_SHOW_IDS:

        UserOptions->m_bShowBotIDs = !UserOptions->m_bShowBotIDs;

        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_IDS, UserOptions->m_bShowBotIDs);

        break;

      case IDM_BOTS_SHOW_HEALTH:

        UserOptions->m_bShowBotHealth = !UserOptions->m_bShowBotHealth;
        
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_HEALTH, UserOptions->m_bShowBotHealth);

        break;

      case IDM_BOTS_SHOW_TARGET:

        UserOptions->m_bShowTargetOfSelectedBot = !UserOptions->m_bShowTargetOfSelectedBot;
        
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_TARGET, UserOptions->m_bShowTargetOfSelectedBot);

        break;

      case IDM_BOTS_SHOW_SENSED:

        UserOptions->m_bShowOpponentsSensedBySelectedBot = !UserOptions->m_bShowOpponentsSensedBySelectedBot;
        
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_SENSED, UserOptions->m_bShowOpponentsSensedBySelectedBot);

        break;


      case IDM_BOTS_SHOW_FOV:

        UserOptions->m_bOnlyShowBotsInTargetsFOV = !UserOptions->m_bOnlyShowBotsInTargetsFOV;
        
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_FOV, UserOptions->m_bOnlyShowBotsInTargetsFOV);

        break;

      case IDM_BOTS_SHOW_SCORES:

        UserOptions->m_bShowScore = !UserOptions->m_bShowScore;
        
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_SCORES, UserOptions->m_bShowScore);

        break;

      case IDM_BOTS_SHOW_GOAL_Q:

        UserOptions->m_bShowGoalsOfSelectedBot = !UserOptions->m_bShowGoalsOfSelectedBot;
        
        CheckMenuItemAppropriately(hwnd, IDM_BOTS_SHOW_GOAL_Q, UserOptions->m_bShowGoalsOfSelectedBot);

        break;

      }//end switch
    }

    
    case WM_PAINT:
      {
 		       
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);

        //fill our backbuffer with white
         BitBlt(hdcBackBuffer,
                0,
                0,
                cxClient,
                cyClient,
                NULL,
                NULL,
                NULL,
                WHITENESS);
          
         
         gdi->StartDrawing(hdcBackBuffer);

         g_pRaven->Render();

         gdi->StopDrawing(hdcBackBuffer);


         //now blit backbuffer to front
			   BitBlt(ps.hdc, 0, 0, cxClient, cyClient, hdcBackBuffer, 0, 0, SRCCOPY); 
          
         EndPaint (hwnd, &ps);

      }

      break;

    //has the user resized the client area?
		case WM_SIZE:
		  {
        //if so we need to update our variables so that any drawing
        //we do using cxClient and cyClient is scaled accordingly
			  cxClient = LOWORD(lParam);
			  cyClient = HIWORD(lParam);

        //now to resize the backbuffer accordingly. First select
        //the old bitmap back into the DC
			  SelectObject(hdcBackBuffer, hOldBitmap);

        //don't forget to do this or you will get resource leaks
        DeleteObject(hBitmap); 

			  //get the DC for the application
        HDC hdc = GetDC(hwnd);

			  //create another bitmap of the same size and mode
        //as the application
        hBitmap = CreateCompatibleBitmap(hdc,
											  cxClient,
											  cyClient);

			  ReleaseDC(hwnd, hdc);
			  
			  //select the new bitmap into the DC
        SelectObject(hdcBackBuffer, hBitmap);

      }

      break;
          
		 case WM_DESTROY:
			 {

         //clean up our backbuffer objects
         SelectObject(hdcBackBuffer, hOldBitmap);

         DeleteDC(hdcBackBuffer);
         DeleteObject(hBitmap); 
         

         // kill the application, this sends a WM_QUIT message  
				 PostQuitMessage (0);
			 }

       break;

     }//end switch

     //this is where all the messages not specifically handled by our 
		 //winproc are sent to be processed
		 return DefWindowProc (hwnd, msg, wParam, lParam);
}


//-------------------------------- WinMain -------------------------------
//
//	The entry point of the windows program
//------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     szCmdLine, 
                    int       iCmdShow)
{
  MSG msg;
  //handle to our window
	HWND						hWnd;

 //the window class structure
	WNDCLASSEX     winclass;

  // first fill in the window class stucture
	winclass.cbSize        = sizeof(WNDCLASSEX);
	winclass.style         = CS_HREDRAW | CS_VREDRAW;
  winclass.lpfnWndProc   = WindowProc;
  winclass.cbClsExtra    = 0;
  winclass.cbWndExtra    = 0;
  winclass.hInstance     = hInstance;
  winclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  winclass.hbrBackground = NULL;
  winclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  winclass.lpszClassName = g_szWindowClassName;
	winclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

  //register the window class
  if (!RegisterClassEx(&winclass))
  {
		MessageBox(NULL, "Registration Failed!", "Error", 0);

	  //exit the application
		return 0;
  }
		

  try
  {  		 
		 //create the window and assign its ID to hwnd    
     hWnd = CreateWindowEx (NULL,                 // extended style
                            g_szWindowClassName,  // window class name
                            g_szApplicationName,  // window caption
                            WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,  // window style
                            GetSystemMetrics(SM_CXSCREEN)/2 - WindowWidth/2,
                            GetSystemMetrics(SM_CYSCREEN)/2 - WindowHeight/2,                    
                            WindowWidth,     // initial x size
                            WindowHeight,    // initial y size
                            NULL,                 // parent window handle
                            NULL,                 // window menu handle
                            hInstance,            // program instance handle
                            NULL);                // creation parameters

     //make sure the window creation has gone OK
     if(!hWnd)
     {
       MessageBox(NULL, "CreateWindowEx Failed!", "Error!", 0);
     }

     
    //make the window visible
    ShowWindow (hWnd, iCmdShow);
    UpdateWindow (hWnd);
   
    //create a timer
    PrecisionTimer timer(FrameRate);

    //start the timer
    timer.Start();

    //enter the message loop
    bool bDone = false;

    while(!bDone)
    {
      while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) 
      {
        if( msg.message == WM_QUIT ) 
        {
          // Stop loop if it's a quit message
	        bDone = true;
        } 

        else 
        {
          TranslateMessage( &msg );
          DispatchMessage( &msg );
        }
      }

      if (timer.ReadyForNextFrame() && msg.message != WM_QUIT)
      {
        g_pRaven->Update();
        
        //render 
        RedrawWindow(hWnd);
      }

      //give the OS a little time
      Sleep(2);
     					
    }//end while

  }//end try block

  catch (const std::runtime_error& err)
  {
    ErrorBox(std::string(err.what()));
    //tidy up
    delete g_pRaven;
    UnregisterClass( g_szWindowClassName, winclass.hInstance );
    return 0;
  }
  
 //tidy up
 UnregisterClass( g_szWindowClassName, winclass.hInstance );
 delete g_pRaven;
 return msg.wParam;
}


