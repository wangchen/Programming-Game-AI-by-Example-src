#include "Debug/DebugConsole.h"
#include <iterator>
#pragma warning (disable : 4786)

//initialize static variable
std::vector<std::string> DebugConsole::m_Buffer;
HWND                     DebugConsole::m_hwnd       = NULL;
bool                     DebugConsole::m_bFlushed   = true;
bool                     DebugConsole::m_bDestroyed = false;
bool                     DebugConsole::m_bActive   = true;
std::ofstream            DebugConsole::m_LogOut;
int                      DebugConsole::m_iPosLeft;
int                      DebugConsole::m_iPosTop;




//-----------------------------------InfoWinProc-----------------------------
//
//-----------------------------------------------------------------------
LRESULT CALLBACK DebugConsole::DebugWindowProc(HWND hwnd, 
						                             UINT msg, 
                                         WPARAM wparam, 
                                         LPARAM lparam)
{
	//these hold the dimensions of the client window area
	static int cxClient, cyClient;

  //font dimensions
  static int cxChar, cyChar, cxCaps, cyPage;

  int iVertPos;

  TEXTMETRIC  tm;
  SCROLLINFO  si;   
  
  //get the size of the client window
  RECT rect;
  GetClientRect(hwnd, &rect);
	cxClient = rect.right;
	cyClient = rect.bottom;

	switch(msg)
	{	
		case WM_CREATE: 
		{
      //get the font info
      HDC hdc = GetDC(hwnd);

      GetTextMetrics(hdc, &tm);
      cxChar = tm.tmAveCharWidth;
      cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
      cyChar = tm.tmHeight + tm.tmExternalLeading;
     
      // Set vertical scroll bar range and page size
      si.cbSize = sizeof (si) ;
      si.fMask  = SIF_RANGE | SIF_PAGE;
      si.nMin   = 0 ;
      si.nMax   = 10 ;
      si.nPage  = cyClient / cyChar;

      SetScrollInfo (hwnd, SB_VERT, &si, TRUE) ;

      ReleaseDC(hwnd, hdc);

		} 
			
		break;

    case WM_KEYUP:
      {
        switch(wparam)
        {
           case VK_ESCAPE:
            {             
              SendMessage(hwnd, WM_DESTROY, NULL, NULL);
            }
          
            break;
        }
      }

      break;

    
    case WM_VSCROLL:
       
      //Get all the vertical scroll bar information
      si.cbSize = sizeof (si);
      si.fMask  = SIF_ALL;
      GetScrollInfo (hwnd, SB_VERT, &si) ;

      // Save the position for comparison later on
      iVertPos = si.nPos ;

      switch (LOWORD (wparam))
      {
        case SB_TOP:
             si.nPos = si.nMin ;
             break ;
               
        case SB_BOTTOM:
             si.nPos = si.nMax ;
             break ;
               
        case SB_LINEUP:
             si.nPos -= 1 ;
             break ;
               
        case SB_LINEDOWN:
             si.nPos += 1 ;
             break ;
               
        case SB_PAGEUP:
             si.nPos -= si.nPage ;
             break ;

        case SB_PAGEDOWN:
             si.nPos += si.nPage ;
             break ;
               
        case SB_THUMBTRACK:
             si.nPos = si.nTrackPos ;
             break ;
               
        default:
             break ;         
      }
          
      //Set the position and then retrieve it.  Due to adjustments
      //by Windows it may not be the same as the value set.
      si.fMask = SIF_POS ;
      SetScrollInfo (hwnd, SB_VERT, &si, TRUE) ;
      GetScrollInfo (hwnd, SB_VERT, &si) ;

      // If the position has changed, scroll the window and update it
      if (si.nPos != iVertPos)
      {                    
         ScrollWindow (hwnd, 0, cyChar * (iVertPos - si.nPos), NULL, NULL) ;
         UpdateWindow (hwnd) ;
         DrawWindow();
      }
      
      break ;
          

    case UM_SETSCROLL:
    {
      //Get all the vertical scroll bar information
      si.cbSize = sizeof (si);
      si.fMask  = SIF_ALL;
      GetScrollInfo (hwnd, SB_VERT, &si);

      si.nMin = 0;
      si.nMax = m_Buffer.size();

      si.nPos += 1;

      si.fMask  = SIF_RANGE | SIF_POS;
      SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
                        
      ScrollWindow (hwnd, 0, cyChar * si.nPos, NULL, NULL);
      DrawWindow();     
    }  

    break;

		case WM_PAINT: 
		{
      PAINTSTRUCT ps;
      
		  BeginPaint(hwnd, &ps);

        SetBkMode(ps.hdc, TRANSPARENT);
        SetTextColor(ps.hdc, RGB(255,255,255));

        if (m_Buffer.size() > 1)
        {
     
          // Get vertical scroll bar position
          si.cbSize = sizeof (si) ;
          si.fMask  = SIF_POS ;
          GetScrollInfo (hwnd, SB_VERT, &si) ;
          iVertPos = si.nPos ;
     
          //number of lines we can fit on this page
          int PageSize = (int)(cyClient / cyChar) - 1;

          int StartIndex = 0;
      
          if (iVertPos > PageSize)
          {
            StartIndex = iVertPos - PageSize;
          }

          std::vector<std::string>::iterator beg = m_Buffer.begin() + StartIndex;
          std::vector<std::string>::iterator end = m_Buffer.begin() + StartIndex+PageSize+1;

          int line=0;

          for (beg; (beg !=end) && (beg != m_Buffer.end()); ++beg)
          {
            TextOut(ps.hdc, 0, cyChar*line++, (*beg).c_str(), (*beg).size()); 
          }
        }
    
			EndPaint(hwnd, &ps);
		} 
			
		break;

    case WM_SIZE:
      {
      }
      break;

		case WM_DESTROY: 
		{
      m_bDestroyed = true;  

			DestroyWindow(m_hwnd);
 		} 
			
		break;

		default:break;

	}//end switch

	// default msg handler 
	if (!m_bDestroyed)
  {
    return DefWindowProc(hwnd, msg, wparam, lparam);
  }
  else
  {
    return NULL;
  }

}


//----------------------------- Create -----------------------------------
//
//------------------------------------------------------------------------
bool DebugConsole::Create()
{
  m_hwnd       = NULL;
  m_iPosLeft   = 0;
  m_iPosTop    = 0;
  m_bFlushed   = true;

  //open log file
  m_LogOut.open("DebugLog.txt");

  
  WNDCLASSEX wDebugConsole = {sizeof(WNDCLASSEX), 
                       CS_HREDRAW | CS_VREDRAW,
                       DebugWindowProc,
                       0,
                       0, 
                       GetModuleHandle(NULL),
						           NULL,
						           NULL,
						           (HBRUSH)(GetStockObject(GRAY_BRUSH)),
						           NULL,
						           "Debug",
						           NULL }; 


  //register the window class
  if (!RegisterClassEx(&wDebugConsole))
  {
    MessageBox(NULL, "Registration of Debug Console Failed!", "Error", 0);

    //exit the application
    return false;
  }
	

  //get the size of the client window
 // RECT rectActive;
 // GetClientRect(GetActiveWindow(), &rectActive);

	// Create the info window
  m_hwnd = CreateWindow("Debug",
                            "Debug Console", 
									          WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU| WS_VSCROLL | WS_THICKFRAME,
                            0,
									          0,
                            DEBUG_WINDOW_WIDTH,
									          DEBUG_WINDOW_HEIGHT,
									          NULL,
									          NULL,
									          wDebugConsole.hInstance,
									          NULL );

    //make sure the window creation has gone OK
  if(!m_hwnd)
  {
    MessageBox(m_hwnd, "CreateWindowEx Failed!", "Error!", 0);

    return false;
  }
	
	// Show the window
	UpdateWindow(m_hwnd);

  return true;

}

//---------------------------- Instance ---------------------------------------
//  
//  Retrieve a pointer to an instance of this class
//-----------------------------------------------------------------------------
DebugConsole* DebugConsole::Instance()
{
   static DebugConsole instance;     
   static bool created = false;
   if ( !created)
   {Create();created = true;}
   
   return &instance;
}

//--------------------------- WriteAndResetBuffer -----------------------------
//-----------------------------------------------------------------------------
void DebugConsole::WriteAndResetBuffer()
{
 
  m_iPosLeft   = 0;
  m_iPosTop    = 0;
  m_bFlushed   = true;
      
  //write out the contents of the buffer to a file
  std::vector<std::string>::iterator it = m_Buffer.begin();

  for (it; it != m_Buffer.end(); ++it)
  {
    m_LogOut << *it << std::endl;
  }

  m_Buffer.clear();

  SendMessage(m_hwnd, UM_SETSCROLL, NULL, NULL);
}