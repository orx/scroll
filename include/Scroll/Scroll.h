#ifndef _SCROLL_H_
#define _SCROLL_H_


//! Defines
#if defined(__orxDEBUG__) && !defined(__orxANDROID__) && !defined(__orxANDROID_NATIVE__)

  #define __SCROLL_DEBUG__

#endif // __orxDEBUG__ && !__orxANDROID__ && !__orxANDROID_NATIVE__


//! Includes
#include "ScrollBase.h"

#ifndef __NO_SCROLLED__
  #include "ScrollEd.h"
#endif // __NO_SCROLLED__


//! Scroll template class
template<class G>
class Scroll : public ScrollBase
{
public:

  static        G &             GetInstance();
                void            Execute(int argc, char **argv);
#ifdef __orxMSVC__
                void            Execute();
#endif // __orxMSVC__

                ScrollObject *  CreateObject(const orxSTRING _zModelName);
          template<class O> O * CreateObject(const orxSTRING _zModelName)   {return ScrollCast<O *>(CreateObject(_zModelName));}
                void            DeleteObject(ScrollObject *_poObject);

                orxSTATUS       SetMapName(const orxSTRING _zMapName);
          const orxSTRING       GetMapName() const;
          const orxSTRING       GetMapShortName() const;
                orxSTATUS       LoadMap();


protected:

                                Scroll<G>()                                 {}
  virtual                      ~Scroll<G>()                                 {}


private:

  virtual       orxSTATUS       Init()                                      {return orxSTATUS_FAILURE;}
  virtual       orxSTATUS       Run()                                       {return orxSTATUS_FAILURE;}
  virtual       void            Exit()                                      {}
  virtual       void            Update(const orxCLOCK_INFO &_rstInfo)       {}
  virtual       void            CameraUpdate(const orxCLOCK_INFO &_rstInfo) {}
  virtual       orxBOOL         MapSaveFilter(const orxSTRING _zSectionName,
                                              const orxSTRING _zKeyName,
                                              const orxSTRING _zFileName,
                                              orxBOOL _bUseEncryption)      {return orxFALSE;}
  virtual       void            BindObjects()                               {}

  virtual       void            OnObjectCreate(ScrollObject *_poObject)     {}
  virtual       void            OnObjectDelete(ScrollObject *_poObject)     {}
  virtual       void            OnMapLoad()                                 {}
  virtual       void            OnMapSave(orxBOOL _bEncrypt)                {}
  virtual       void            OnStartGame()                               {}
  virtual       void            OnStopGame()                                {}
  virtual       void            OnPauseGame(orxBOOL _bPause)                {}

  virtual const orxSTRING       GetEncryptionKey() const;


//! Variables
};


#ifdef __SCROLL_IMPL__

//! Inline include
#include "Scroll.inl"

#endif // __SCROLL_IMPL__

#endif // _SCROLL_H_
