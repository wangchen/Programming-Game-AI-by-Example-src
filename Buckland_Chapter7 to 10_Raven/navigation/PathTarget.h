#ifndef PATH_TARGET_H
#define PATH_TARGET_H


class PathTarget
{
public:
  
  enum target_type {item, position, invalid};
  
private:

  int         m_iTargetItemType;

  Vector2D    m_vTargetPosition;

  target_type m_Type;

public:

  PathTarget():m_iTargetItemType(-1), m_Type(invalid){}
  
  void SetTargetAsItem(int ItemType);
  void SetTargetAsPosition(Vector2D TargetPosition);

  bool isTargetAnItem()const{return m_Type == item;}
  bool isTargetAPosition()const{return m_Type == position;}
  bool isTargetValid()const{return !(m_Type == invalid);}

  Vector2D GetTargetPosition()const;
  int      GetTargetType()const;

};

#endif