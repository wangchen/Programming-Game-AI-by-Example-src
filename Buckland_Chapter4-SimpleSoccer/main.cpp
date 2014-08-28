#pragma warning (disable:4786)
#include <windows.h>
#include <time.h>

#include "constants.h"
#include "misc/utils.h"
#include "Time/PrecisionTimer.h"
#include "SoccerPitch.h"
#include "misc/Cgdi.h"
#include "ParamLoader.h"
#include "Resource.h"
#include "misc/WindowUtils.h"
#include "debug/DebugConsole.h"


//--------------------------------- Globals ------------------------------
//
//------------------------------------------------------------------------

char* g_szApplicationName = "Simple Soccer";
char*	g_szWindowClassName = "MyWindowClass";

SoccerPitch* g_SoccerPitch;

//create a timer
PrecisionTimer timer(Prm.FrameRate);


//used when a user clicks on a menu item to ensure the option is 'checked'
//correctly
void CheckAllMenuItemsAppropriately(HWND hwnd)
{
   CheckMenuItemAppropriately(hwnd, IDM_SHOW_REGIONS, Prm.bRegions);
   CheckMenuItemAppropriately(hwnd, IDM_SHOW_STATES, Prm.bStates);
   CheckMenuItemAppropriately(hwnd, IDM_SHOW_IDS, Prm.bIDs);
   CheckMenuItemAppropriately(hwnd, IDM_AIDS_SUPPORTSPOTS, Prm.bSupportSpots);
   CheckMenuItemAppropriately(hwnd, ID_AIDS_SHOWTARGETS, Prm.bViewTargets);
   CheckMenuItemAppropriately(hwnd, IDM_AIDS_HIGHLITE, Prm.bHighlightIfThreatened);
}


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
         
         g_SoccerPitch = new SoccerPitch(cxClient, cyClient); 
         
         CheckAllMenuItemsAppropriately(hwnd);

      }

      break;

    case WM_COMMAND:
      {
        switch(wParam)
        {
          case ID_AIDS_NOAIDS:

            Prm.bStates        = 0;
            Prm.bRegions       = 0;
            Prm.bIDs           = 0;
            Prm.bSupportSpots  = 0;
            Prm.bViewTargets   = 0;

            CheckAllMenuItemsAppropriately(hwnd);

            break;
            
          case IDM_SHOW_REGIONS:

            Prm.bRegions = !Prm.bRegions;

            CheckAllMenuItemsAppropriately(hwnd);

            break;

          case IDM_SHOW_STATES:

            Prm.bStates = !Prm.bStates;

            CheckAllMenuItemsAppropriately(hwnd);

            break;

          case IDM_SHOW_IDS:

            Prm.bIDs = !Prm.bIDs;

            CheckAllMenuItemsAppropriately(hwnd);

            break;


          case IDM_AIDS_SUPPORTSPOTS:

            Prm.bSupportSpots = !Prm.bSupportSpots;

            CheckAllMenuItemsAppropriately(hwnd);

             break;

           case ID_AIDS_SHOWTARGETS:

            Prm.bViewTargets = !Prm.bViewTargets;

            CheckAllMenuItemsAppropriately(hwnd);

             break;
              
           case IDM_AIDS_HIGHLITE:

            Prm.bHighlightIfThreatened = !Prm.bHighlightIfThreatened; 

            CheckAllMenuItemsAppropriately(hwnd);

            break;
            
        }//end switch
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

          case 'R':
            {
               delete g_SoccerPitch;
           
               g_SoccerPitch = new SoccerPitch(cxClient, cyClient);
            }

            break;

          case 'P':
            {
              g_SoccerPitch->TogglePause();
            }

            break;

        }//end switch
        
      }//end WM_KEYUP

      break;

    
    case WM_PAINT:
      {
 		       
         PAINTSTRUCT ps;
          
         BeginPaint (hwnd, &ps);
         
         gdi->StartDrawing(hdcBackBuffer);
         
         g_SoccerPitch->Render();

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

  //handle to our window
  HWND						hWnd;
    
  //our window class structure
  WNDCLASSEX     winclass;
		 
  // first fill in the window class stucture
  winclass.cbSize        = sizeof(WNDCLASSEX);
  winclass.style         = CS_HREDRAW | CS_VREDRAW;
  winclass.lpfnWndProc   = WindowProc;
  winclass.cbClsExtra    = 0;
  winclass.cbWndExtra    = 0;
  winclass.hInstance     = hInstance;
  winclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  winclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
  winclass.hbrBackground = NULL;
  winclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
  winclass.lpszClassName = g_szWindowClassName;
  winclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));

  //register the window class
  if (!RegisterClassEx(&winclass))
  {
    MessageBox(NULL, "Registration Failed!", "Error", 0);

    //exit the application
    return 0;
  }

  //create the window and assign its ID to hwnd    
  hWnd = CreateWindowEx (NULL,                 // extended style
                         g_szWindowClassName,  // window class name
                         g_szApplicationName,  // window caption
                         WS_OVERLAPPED | WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
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
  
  //start the timer
  timer.Start();

  MSG msg;

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
      //update game states
      g_SoccerPitch->Update(); 
      
      //render 
      RedrawWindow(hWnd, true);

      Sleep(2);
    }
   					
  }//end while

  delete g_SoccerPitch;

  UnregisterClass( g_szWindowClassName, winclass.hInstance );

  return msg.wParam;
}


