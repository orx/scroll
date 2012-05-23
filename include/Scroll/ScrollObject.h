#ifndef _ScrollObject_H_
#define _ScrollObject_H_


//! ScrollObject class
class ScrollObject
{
  friend class ScrollBase;
  friend class ScrollEd;
  template <class O> friend class ScrollObjectBinder;

public:

  enum Flag
  {
    FlagNone      = 0x00000000,

    FlagSave      = 0x00000001,
    FlagSmoothed  = 0x00000002,
    FlagTiled     = 0x00000004,
    FlagRunTime   = 0x00000008,

    MaskAll       = 0xFFFFFFFF
  };


                void                    SetFlags(Flag _xAddFlags, Flag _xRemoveFlags = FlagNone)  {mxFlags = (Flag)(mxFlags & ~_xRemoveFlags); mxFlags = (Flag)(mxFlags | _xAddFlags);}
                void                    SwapFlags(Flag _xSwapFlags)                               {mxFlags = (Flag)(mxFlags ^ _xSwapFlags);}
                orxBOOL                 TestFlags(Flag _xTestFlags) const                         {return (mxFlags & _xTestFlags) ? orxTRUE : orxFALSE;}
                orxBOOL                 TestAllFlags(Flag _xTestFlags) const                      {return ((mxFlags & _xTestFlags) == _xTestFlags) ? orxTRUE : orxFALSE;}
                Flag                    GetFlags(Flag _xMask = MaskAll) const                     {return (Flag)(mxFlags & _xMask);}
                orxOBJECT *             GetOrxObject() const                                      {return mpstObject;}
                const orxSTRING         GetName() const                                           {return mzName;}
                const orxSTRING         GetModelName() const                                      {return mzModelName;}
                orxU64                  GetGUID() const                                           {return orxSTRUCTURE(mpstObject)->u64GUID;}

                void                    Enable(orxBOOL _bEnable, orxBOOL _bRecursive = orxTRUE);

                orxVECTOR &             GetPosition(orxVECTOR &_rvPosition, orxBOOL _bWorld = orxFALSE) const;
                void                    SetPosition(const orxVECTOR &_rvPosition, orxBOOL _bWorld = orxFALSE);

                orxVECTOR &             GetScale(orxVECTOR &_rvScale, orxBOOL _bWorld = orxFALSE) const;
                void                    SetScale(const orxVECTOR &_rvScale, orxBOOL _bWorld = orxFALSE);

                orxFLOAT                GetRotation(orxBOOL _bWorld = orxFALSE) const;
                void                    SetRotation(orxFLOAT _fRotation, orxBOOL _bWorld = orxFALSE);

                orxVECTOR &             GetSpeed(orxVECTOR &_rvSpeed, orxBOOL _bRelative = orxFALSE) const;
                void                    SetSpeed(const orxVECTOR &_rvSpeed, orxBOOL _bRelative = orxFALSE);

                orxCOLOR &              GetColor(orxCOLOR &_rstColor) const;
                void                    SetColor(const orxCOLOR &_rstColor, orxBOOL _bRecursive = orxTRUE);

                void                    GetFlip(orxBOOL &_rbFlipX, orxBOOL &_rbFlipY) const;
                void                    SetFlip(orxBOOL _bFlipX, orxBOOL _bFlipY, orxBOOL _bRecursive = orxTRUE);

                void                    AddFX(const orxSTRING _zFXName, orxBOOL _bRecursive = orxTRUE);
                void                    AddFX(const orxSTRING _zFXName, orxFLOAT _fDelay, orxBOOL _bRecursive = orxTRUE);
                void                    RemoveFX(const orxSTRING _zFXName, orxBOOL _bRecursive = orxTRUE);

                void                    AddShader(const orxSTRING _zShaderName, orxBOOL _bRecursive = orxTRUE);
                void                    RemoveShader(const orxSTRING _zShaderName, orxBOOL _bRecursive = orxTRUE);

                void                    AddSound(const orxSTRING _zSoundName);
                void                    RemoveSound(const orxSTRING _zSoundName);

                orxFLOAT                GetLifeTime() const; 
                void                    SetLifeTime(orxFLOAT _fLifeTime);

                void                    PushConfigSection(orxBOOL _bPushInstanceSection = orxFALSE) const;
                void                    PopConfigSection() const;

protected:

                                        ScrollObject();
                virtual                ~ScrollObject();


private:

  virtual       void                    OnCreate();
  virtual       void                    OnDelete();
  virtual       void                    Update(const orxCLOCK_INFO &_rstInfo);
  virtual       void                    OnStartGame();
  virtual       void                    OnStopGame();
  virtual       void                    OnPauseGame(orxBOOL _bPause);

  virtual       orxBOOL                 OnRender();

  virtual       orxBOOL                 OnCollide(ScrollObject *_poCollider, const orxSTRING _zPartName, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal);
  virtual       orxBOOL                 OnSeparate(ScrollObject *_poCollider);

  virtual       void                    OnNewAnim(const orxSTRING _zOldAnim, const orxSTRING _zNewAnim, orxBOOL _bCut);
  virtual       void                    OnAnimEvent(const orxSTRING _zAnim, const orxSTRING _zEvent, orxFLOAT _fTime, orxFLOAT _fValue);

                void                    SetDifferentialMode(orxBOOL _bDifferential = orxTRUE);

                void                    SetOrxObject(orxOBJECT *_pstObject);


//! Variables
private:

                orxOBJECT *             mpstObject;
                const orxSTRING         mzName;
                const orxSTRING         mzModelName;
                Flag                    mxFlags;
                orxLINKLIST_NODE        mstNode;
                orxLINKLIST_NODE        mstChronoNode;
};


//! Operators
inline ScrollObject::Flag operator|(ScrollObject::Flag _x1, ScrollObject::Flag _x2)
{
  return ScrollObject::Flag(int(_x1) | int(_x2));
}
inline ScrollObject::Flag & operator|=(ScrollObject::Flag &_x1, ScrollObject::Flag _x2)
{
  _x1 = _x1 | _x2;
  return _x1;
}

inline ScrollObject::Flag operator&(ScrollObject::Flag _x1, ScrollObject::Flag _x2)
{
  return ScrollObject::Flag(int(_x1) & int(_x2));
}
inline ScrollObject::Flag & operator&=(ScrollObject::Flag &_x1, ScrollObject::Flag _x2)
{
  _x1 = _x1 & _x2;
  return _x1;
}

inline ScrollObject::Flag operator^(ScrollObject::Flag _x1, ScrollObject::Flag _x2)
{
  return ScrollObject::Flag(int(_x1) ^ int(_x2));
}
inline ScrollObject::Flag & operator^=(ScrollObject::Flag &_x1, ScrollObject::Flag _x2)
{
  _x1 = _x1 ^ _x2;
  return _x1;
}

inline ScrollObject::Flag operator~(ScrollObject::Flag _x1)
{
  return ScrollObject::Flag(~int(_x1));
}


#ifdef __SCROLL_IMPL__

//! Inline include
#include "ScrollObject.inl"

#endif // __SCROLL_IMPL__

#endif // _ScrollObject_H_
