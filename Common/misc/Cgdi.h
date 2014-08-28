#ifndef CGDI_H
#define CGDI_H
//------------------------------------------------------------------------
//
//  Name:   Cgdi.h
//
//  Desc:   A singleton class to help alleviate the tedium of using the
//          GDI. Call each method using the #define for gdi->
//          eg gdi->Line(10, 20, 300, 300)
//          You must always call gdi->StartDrawing() prior to any 
//          rendering, and isComplete any rendering with gdi->StopDrawing()
//
//  Author: Mat Buckland 2001 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <windows.h>
#include <string>
#include <vector>
#include <cassert>

#include "2D/Vector2D.h"


//------------------------------- define some colors
const int NumColors = 15;

const COLORREF colors[NumColors] =
{
  RGB(255,0,0),
  RGB(0,0,255),
  RGB(0,255,0),
  RGB(0,0,0),
  RGB(255,200,200),
  RGB(200,200,200),
  RGB(255,255,0),
  RGB(255,170,0),
  RGB(255,0,170),
  RGB(133,90,0),
  RGB(255,255,255),  
  RGB(0, 100, 0),        //dark green
  RGB(0, 255, 255),       //light blue
  RGB(200, 200, 200),     //light grey
  RGB(255, 230, 230)      //light pink
};


//make life easier on the fingers
#define gdi Cgdi::Instance()

class Cgdi
{
public:
  
  int NumPenColors()const{return NumColors;}

  //enumerate some colors
  enum
  {
    red,
    blue, 
    green,
    black,
    pink,
    grey,
    yellow,
    orange,
    purple,
    brown,   
    white,
    dark_green,
    light_blue,
    light_grey,
    light_pink,
    hollow
  };

  
  
private:

  HPEN m_OldPen;

  //all the pens
  HPEN   m_BlackPen;
  HPEN   m_WhitePen;
  HPEN   m_RedPen;
  HPEN   m_GreenPen;
  HPEN   m_BluePen;
  HPEN   m_GreyPen;
  HPEN   m_PinkPen;
  HPEN   m_OrangePen;
  HPEN   m_YellowPen;
  HPEN   m_PurplePen;
  HPEN   m_BrownPen;
  
  HPEN   m_DarkGreenPen;
  HPEN   m_LightBluePen;
  HPEN   m_LightGreyPen;
  HPEN   m_LightPinkPen;

  HPEN   m_ThickBlackPen;
  HPEN   m_ThickWhitePen;
  HPEN   m_ThickRedPen;
  HPEN   m_ThickGreenPen;
  HPEN   m_ThickBluePen;
  
  HBRUSH m_OldBrush;

  //all the brushes
  HBRUSH  m_RedBrush;
  HBRUSH  m_GreenBrush;
  HBRUSH  m_BlueBrush;
  HBRUSH  m_GreyBrush;
  HBRUSH  m_BrownBrush;
  HBRUSH  m_YellowBrush;
  HBRUSH  m_OrangeBrush;

  HBRUSH  m_LightBlueBrush;
  HBRUSH  m_DarkGreenBrush;

  HDC    m_hdc;

  //constructor is private
  Cgdi();

  //copy ctor and assignment should be private
  Cgdi(const Cgdi&);
  Cgdi& operator=(const Cgdi&);

public:

  ~Cgdi();
  
  static Cgdi* Instance();

  void BlackPen(){if(m_hdc){SelectObject(m_hdc, m_BlackPen);}}
  void WhitePen(){if(m_hdc){SelectObject(m_hdc, m_WhitePen);}}
  void RedPen()  {if(m_hdc){SelectObject(m_hdc, m_RedPen);}}
  void GreenPen(){if(m_hdc){SelectObject(m_hdc, m_GreenPen);}}
  void BluePen() {if(m_hdc){SelectObject(m_hdc, m_BluePen);}}
  void GreyPen() {if(m_hdc){SelectObject(m_hdc, m_GreyPen);}}
  void PinkPen() {if(m_hdc){SelectObject(m_hdc, m_PinkPen);}}
  void YellowPen() {if(m_hdc){SelectObject(m_hdc, m_YellowPen);}}
  void OrangePen() {if(m_hdc){SelectObject(m_hdc, m_OrangePen);}}
  void PurplePen() {if(m_hdc){SelectObject(m_hdc, m_PurplePen);}}
  void BrownPen() {if(m_hdc){SelectObject(m_hdc, m_BrownPen);}}
  
  void DarkGreenPen() {if(m_hdc){SelectObject(m_hdc, m_DarkGreenPen);}}
  void LightBluePen() {if(m_hdc){SelectObject(m_hdc, m_LightBluePen);}}
  void LightGreyPen() {if(m_hdc){SelectObject(m_hdc, m_LightGreyPen);}}
  void LightPinkPen() {if(m_hdc){SelectObject(m_hdc, m_LightPinkPen);}}

  void ThickBlackPen(){if(m_hdc){SelectObject(m_hdc, m_ThickBlackPen);}}
  void ThickWhitePen(){if(m_hdc){SelectObject(m_hdc, m_ThickWhitePen);}}
  void ThickRedPen()  {if(m_hdc){SelectObject(m_hdc, m_ThickRedPen);}}
  void ThickGreenPen(){if(m_hdc){SelectObject(m_hdc, m_ThickGreenPen);}}
  void ThickBluePen() {if(m_hdc){SelectObject(m_hdc, m_ThickBluePen);}}

  void BlackBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(BLACK_BRUSH));}
  void WhiteBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(WHITE_BRUSH));} 
  void HollowBrush(){if(m_hdc)SelectObject(m_hdc, GetStockObject(HOLLOW_BRUSH));}
  void GreenBrush(){if(m_hdc)SelectObject(m_hdc, m_GreenBrush);}
  void RedBrush()  {if(m_hdc)SelectObject(m_hdc, m_RedBrush);}
  void BlueBrush()  {if(m_hdc)SelectObject(m_hdc, m_BlueBrush);}
  void GreyBrush()  {if(m_hdc)SelectObject(m_hdc, m_GreyBrush);}
  void BrownBrush() {if(m_hdc)SelectObject(m_hdc, m_BrownBrush);}
  void YellowBrush() {if(m_hdc)SelectObject(m_hdc, m_YellowBrush);}
  void LightBlueBrush() {if(m_hdc)SelectObject(m_hdc, m_LightBlueBrush);}
  void DarkGreenBrush() {if(m_hdc)SelectObject(m_hdc, m_DarkGreenBrush);}
  void OrangeBrush() {if(m_hdc)SelectObject(m_hdc, m_OrangeBrush);}



  //ALWAYS call this before drawing
  void StartDrawing(HDC hdc)
  {
    assert(m_hdc == NULL);
    
    m_hdc = hdc;

    //get the current pen
    m_OldPen = (HPEN)SelectObject(hdc, m_BlackPen);
    //select it back in
    SelectObject(hdc, m_OldPen);

    m_OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    SelectObject(hdc, m_OldBrush);
  }

  
  
  //ALWAYS call this after drawing
  void StopDrawing(HDC hdc)
  {
    assert(hdc != NULL);
    
    SelectObject(hdc, m_OldPen);
    SelectObject(hdc, m_OldBrush);

    m_hdc = NULL;
 
  }


  //---------------------------Text

  void TextAtPos(int x, int y, const std::string &s)
  {
    TextOut(m_hdc, x, y, s.c_str(), s.size());
  }

  void TextAtPos(double x, double y, const std::string &s)
  {
    TextOut(m_hdc, (int)x, (int)y, s.c_str(), s.size());
  }

  void TextAtPos(Vector2D pos, const std::string &s)
  {
    TextOut(m_hdc, (int)pos.x, (int)pos.y, s.c_str(), s.size());
  }

  void TransparentText(){SetBkMode(m_hdc, TRANSPARENT);}

  void OpaqueText(){SetBkMode(m_hdc, OPAQUE);}

  void TextColor(int color){assert(color < NumColors); SetTextColor(m_hdc, colors[color]);}
  void TextColor(int r, int g, int b){SetTextColor(m_hdc, RGB(r,g,b));}


  //----------------------------pixels
  void DrawDot(Vector2D pos, COLORREF color)
  {
    SetPixel(m_hdc, (int)pos.x, (int)pos.y, color);
  }

  void DrawDot(int x, int y, COLORREF color)
  {
    SetPixel(m_hdc, x, y, color);
  }
  
  //-------------------------Line Drawing

  void Line(Vector2D from, Vector2D to)
  {
    MoveToEx(m_hdc, (int)from.x, (int)from.y, NULL);
    LineTo(m_hdc, (int)to.x, (int)to.y);
  }

  void Line(int a, int b, int x, int y)
  {
    MoveToEx(m_hdc, a, b, NULL);
    LineTo(m_hdc, x, y);
  }

  void Line(double a, double b, double x, double y)
  {
    MoveToEx(m_hdc, (int)a, (int)b, NULL);
    LineTo(m_hdc, (int)x, (int)y);
  }



  void PolyLine(const std::vector<Vector2D>& points)
  {
    //make sure we have at least 2 points
    if (points.size() < 2) return;

    MoveToEx(m_hdc, (int)points[0].x, (int)points[0].y, NULL);

    for (unsigned int p=1; p<points.size(); ++p)
    {
      LineTo(m_hdc, (int)points[p].x, (int)points[p].y);
    }
  }

  void LineWithArrow(Vector2D from, Vector2D to, double size)
  {
    Vector2D norm = Vec2DNormalize(to-from);

    //calculate where the arrow is attached
    Vector2D CrossingPoint = to - (norm * size);
    
    //calculate the two extra points required to make the arrowhead
    Vector2D ArrowPoint1 = CrossingPoint + (norm.Perp() * 0.4f * size); 
    Vector2D ArrowPoint2 = CrossingPoint - (norm.Perp() * 0.4f * size); 

    //draw the line
    MoveToEx(m_hdc, (int)from.x, (int)from.y, NULL);
    LineTo(m_hdc, (int)CrossingPoint.x, (int)CrossingPoint.y);

    //draw the arrowhead (filled with the currently selected brush)
    POINT p[3];
    
    p[0] = VectorToPOINT(ArrowPoint1);
    p[1] = VectorToPOINT(ArrowPoint2);
    p[2] = VectorToPOINT(to);                  
                       
    SetPolyFillMode(m_hdc, WINDING);
    Polygon(m_hdc, p, 3);

  }

  void Cross(Vector2D pos, int diameter)
  {
    Line((int)pos.x-diameter, (int)pos.y-diameter, (int)pos.x+diameter, (int)pos.y+diameter);
    Line((int)pos.x-diameter,(int)pos.y+diameter, (int)pos.x+diameter, (int)pos.y-diameter);
  }


  //---------------------Geometry drawing methods

  void Rect(int left, int top, int right, int bot)
  {
    Rectangle(m_hdc, left, top, right, bot);
  }

  void Rect(double left, double top, double right, double bot)
  {
    Rectangle(m_hdc, (int)left, (int)top, (int)right, (int)bot);
  }



  void ClosedShape(const std::vector<Vector2D> &points)
  {
    MoveToEx(m_hdc, (int)points[0].x, (int)points[0].y, NULL);
    
    for (unsigned int p=1; p<points.size(); ++p)
    {
      LineTo(m_hdc, (int)points[p].x, (int)points[p].y);
    }

    LineTo(m_hdc, (int)points[0].x, (int)points[0].y);
  }


  void Circle(Vector2D pos, double radius)
  {
    Ellipse(m_hdc,
           (int)(pos.x-radius),
           (int)(pos.y-radius),
           (int)(pos.x+radius+1),
           (int)(pos.y+radius+1));
  }

  void Circle(double x, double y, double radius)
  {
    Ellipse(m_hdc,
           (int)(x-radius),
           (int)(y-radius),
           (int)(x+radius+1),
           (int)(y+radius+1));
  }

  void Circle(int x, int y, double radius)
  {
    Ellipse(m_hdc,
           (int)(x-radius),
           (int)(y-radius),
           (int)(x+radius+1),
           (int)(y+radius+1));
  }


  void SetPenColor(int color)
  {
    assert (color < NumColors);
    
   switch (color)
   {
    case black:BlackPen(); return;

    case white:WhitePen(); return;
    case red: RedPen(); return;
    case green: GreenPen(); return;
    case blue: BluePen(); return;
    case pink: PinkPen(); return;
    case grey: GreyPen(); return;
    case yellow: YellowPen(); return;
    case orange: OrangePen(); return;
    case purple: PurplePen(); return;
    case brown: BrownPen(); return;
    case light_blue: LightBluePen(); return;
    case light_grey: LightGreyPen(); return;
    case light_pink: LightPinkPen(); return;
    }//end switch
  }
};

#endif