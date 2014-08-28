#ifndef FRAMECOUNTER_H
#define FRAMECOUNTER_H


#define TickCounter FrameCounter::Instance()

class FrameCounter
{
private:

  long m_lCount;

  int  m_iFramesElapsed;

  FrameCounter():m_lCount(0), m_iFramesElapsed(0){}

  //copy ctor and assignment should be private
  FrameCounter(const FrameCounter&);
  FrameCounter& operator=(const FrameCounter&);

public:

  static FrameCounter* Instance();

  void Update(){++m_lCount; ++m_iFramesElapsed;}

  long GetCurrentFrame(){return m_lCount;}

  void Reset(){m_lCount = 0;}

  void Start(){m_iFramesElapsed = 0;}
  int  FramesElapsedSinceStartCalled()const{return m_iFramesElapsed;}

};

#endif