#ifndef _SCROLLBASE_H_
#define _SCROLLBASE_H_


#include "orx/orx.h"

#ifdef __SCROLL_DEBUG__
  #include <typeinfo>
#endif // __SCROLL_DEBUG__

#include "ScrollObject.h"


//! Template helpers
template<class T, class U>
inline static T ScrollCast(U _p)
{
#ifdef __SCROLL_DEBUG__
  T pDummy = orxNULL;

  // Valid?
  if(_p)
  {
    // Calls dynamic cast
    pDummy = dynamic_cast<T>(_p);

    // Checks
    orxASSERT(pDummy && "Impossible cast from %s to %s!", typeid(U).name(), typeid(T).name());
  }

  // Done!
  return pDummy;

#else // __SCROLL_DEBUG__

  // Done!
  return static_cast<T>(_p);

#endif // __SCROLL_DEBUG__
}

template<class Child, class Parent>
struct ScrollIsA
{
  struct stNo
  {
  };

  struct stYes
  {
    orxU32 u32Dummy;
  };

  static stNo   Convert(...);
  static stYes  Convert(const Parent &);
  enum {Value = (sizeof(Convert(*(Child *)0)) == sizeof(stYes))};
};

template <class T>
struct ScrollIsPolymorphic
{
  struct Dummy1 : public T
  {
                  Dummy1();
            char  au8Padding[256];
  };
  struct Dummy2 : public T
  {
                  Dummy2();
    virtual void  DummyVirt(void);
            char  au8Padding[256];
  };

  enum {Value = (sizeof(Dummy1) == sizeof(Dummy2))};
};


//! Object binder abstract class
class ScrollObjectBinderBase
{
  friend class ScrollBase;

protected:

  static        orxHASHTABLE *          GetTable();
  static        void                    DeleteTable();
  static        ScrollObjectBinderBase *GetBinder(const orxSTRING _zName, orxBOOL _bAllowDefault = orxTRUE);

                                        ScrollObjectBinderBase() {}
  virtual                              ~ScrollObjectBinderBase() {}


private:

  static        ScrollObjectBinderBase *GetDefaultBinder();

  virtual       ScrollObject *          CreateObject(const orxSTRING _zModelName, const orxSTRING _zInstanceName, ScrollObject::Flag _xFlags) = 0;
  virtual       ScrollObject *          CreateObject(orxOBJECT *_pstOrxObject, const orxSTRING _zInstanceName, ScrollObject::Flag _xFlags) = 0;
  virtual       void                    DeleteObject(class ScrollObject *_poObject) = 0;
  virtual       void                    DeleteObject(class ScrollObject *_poObject, const orxSTRING _zModelName) = 0;

  static  const orxU32                  su32TableSize;

//! Variables
private:

  static        orxHASHTABLE *          spstTable;
};


//! Object binder template class
template<class O>
class ScrollObjectBinder : public ScrollObjectBinderBase
{
  friend class ScrollBase;

public:

  static        ScrollObjectBinder<O> * GetInstance(orxS32 _s32SegmentSize = -1);
  static        void                    Register(const orxSTRING _zModelName, orxS32 _s32SegmentSize);


protected:

                                        ScrollObjectBinder(orxS32 _s32SegmentSize);
  virtual                              ~ScrollObjectBinder();

private:

                ScrollObject *          CreateObject(const orxSTRING _zModelName, const orxSTRING _zInstanceName, ScrollObject::Flag _xFlags);
                ScrollObject *          CreateObject(orxOBJECT *_pstOrxObject, const orxSTRING _zInstanceName, ScrollObject::Flag _xFlags);

                void                    DeleteObject(class ScrollObject *_poObject);
                void                    DeleteObject(class ScrollObject *_poObject, const orxSTRING _zModelName);

                O *                     GetNextObject(const O *_poObject = orxNULL) const;
                O *                     GetPreviousObject(const O *_poObject = orxNULL) const;


private:

                orxBANK *               mpstBank;
                ScrollObject *          mpoFirstObject;
                ScrollObject *          mpoLastObject;
  static        ScrollObjectBinder<O> * spoInstance;
};


//! Scroll object bind helper
template<class O>
inline static void ScrollBindObject(const orxSTRING _zName, orxS32 _s32SegmentSize = 128)
{
#ifdef __SCROLL_DEBUG__
  if(!ScrollIsA<O, ScrollObject>::Value)
  {
    orxLOG("[ERROR] Binding object <%s>: class %s has to derive from class ScrollObject!", _zName, typeid(O).name());
  }
#endif // __SCROLL_DEBUG__

  // Instances corresponding binder
  ScrollObjectBinder<O>::Register(_zName, _s32SegmentSize);
}


//! ScrollBase abstract class
class ScrollBase
{
  friend class ScrollEd;
  template <class O> friend class ScrollObjectBinder;

public:

  static        ScrollBase &    GetInstance();
                void            Execute(int argc, char **argv);

                orxSTATUS       StartGame();
                orxSTATUS       StopGame();
                orxBOOL         IsGameRunning() const;
                orxSTATUS       PauseGame(orxBOOL _bPause);
                orxBOOL         IsGamePaused() const;

                orxVIEWPORT *   GetMainViewport() const;
                orxCAMERA *     GetMainCamera() const;
                ScrollObject *  GetObject(orxU64 _u64GUID) const;
          template<class O> O * GetObject(orxU64 _u64GUID) const;
                ScrollObject *  GetNextObject(const ScrollObject *_poObject = orxNULL, orxBOOL _bChronological = orxFALSE) const;
          template<class O> O * GetNextObject(const O *_poObject = orxNULL) const;
                ScrollObject *  GetPreviousObject(const ScrollObject *_poObject = orxNULL, orxBOOL _bChronological = orxFALSE) const;
          template<class O> O * GetPreviousObject(const O *_poObject = orxNULL) const;


protected:

                                ScrollBase();
  virtual                      ~ScrollBase();

                orxSTATUS       SetMapName(const orxSTRING _zMapName);
          const orxSTRING       GetMapName() const;
          const orxSTRING       GetMapShortName() const;
                orxSTATUS       LoadMap();
                orxSTATUS       SaveMap(orxBOOL _bEncrypt = orxFALSE, const orxCONFIG_SAVE_FUNCTION _pfnMapSaveFilter = orxNULL);
                orxSTATUS       ResetMap();
                ScrollObject *  CreateObject(const orxSTRING _zModelName, ScrollObject::Flag _xFlags = ScrollObject::FlagNone, const orxSTRING _zInstanceName = orxNULL);
                ScrollObject *  CreateObject(orxOBJECT *_pstOrxObject, ScrollObject::Flag _xFlags = ScrollObject::FlagNone, const orxSTRING _zInstanceName = orxNULL);
                void            DeleteObject(ScrollObject *_poObject);

                ScrollObject *  PickObject(const orxVECTOR &_rvPosition) const;
                ScrollObject *  PickObject(const orxOBOX &_rstBox) const;

                orxCOLOR *      GetObjectConfigColor(const ScrollObject *_poObject, orxCOLOR &_rstColor);
                orxSTATUS       SetObjectConfigColor(ScrollObject *_poObject, const orxCOLOR &_rstColor);

                void            SetLayerNumber(orxU32 _u32LayerNumber);
                orxU32          GetLayerNumber() const;

                orxU32          GetLayer(const orxVECTOR &_rvPosition) const;
                orxFLOAT        GetLayerDepth(orxU32 _u32Layer = 0) const;

                void            SetEditorMode(orxBOOL _bEnable = orxTRUE);
                orxBOOL         IsEditorMode() const;

                void            SetDifferentialMode(orxBOOL _bEnable = orxTRUE);
                orxBOOL         IsDifferentialMode() const;

  static  const orxSTRING       szConfigClockFrequency;

  static  const orxSTRING       szInputSetGame;
  static  const orxSTRING       szConfigSectionMap;
  static  const orxSTRING       szConfigMainViewport;
  static  const orxSTRING       szConfigCameraPosition;
  static  const orxSTRING       szConfigCameraZoom;
  static  const orxSTRING       szConfigDifferential;
  static  const orxSTRING       szConfigLayerNumber;
  static  const orxSTRING       szConfigNoSave;
  static  const orxSTRING       szConfigScrollObjectNumber;
  static  const orxSTRING       szConfigScrollObjectPrefix;
  static  const orxSTRING       szConfigScrollObjectFormat;
  static  const orxSTRING       szConfigScrollObjectRuntimeFormat;
  static  const orxSTRING       szConfigScrollObjectName;
  static  const orxSTRING       szConfigScrollObjectPosition;
  static  const orxSTRING       szConfigScrollObjectRotation;
  static  const orxSTRING       szConfigScrollObjectScale;
  static  const orxSTRING       szConfigScrollObjectColor;
  static  const orxSTRING       szConfigScrollObjectAlpha;
  static  const orxSTRING       szConfigScrollObjectSmoothing;
  static  const orxSTRING       szConfigScrollObjectTiling;


private:

  virtual       orxSTATUS       Init() = 0;
  virtual       orxSTATUS       Run() = 0;
  virtual       void            Exit() = 0;
  virtual       void            Update(const orxCLOCK_INFO &_rstInfo) = 0;
  virtual       void            CameraUpdate(const orxCLOCK_INFO &_rstInfo) = 0;
  virtual       void            BindObjects() = 0;
  virtual       orxBOOL         MapSaveFilter(const orxSTRING _zSectionName, const orxSTRING _zKeyName, const orxSTRING _zFileName, orxBOOL _bUseEncryption) = 0;

  virtual       void            OnObjectCreate(ScrollObject *_poObject) = 0;
  virtual       void            OnObjectDelete(ScrollObject *_poObject) = 0;
  virtual       void            OnMapLoad() = 0;
  virtual       void            OnMapSave(orxBOOL _bEncrypt) = 0;
  virtual       void            OnStartGame() = 0;
  virtual       void            OnStopGame() = 0;
  virtual       void            OnPauseGame(orxBOOL _bPause) = 0;

  virtual const orxSTRING       GetEncryptionKey() const = 0;


                orxSTATUS       BaseInit();
                orxSTATUS       BaseRun();
                void            BaseExit();
                void            BaseUpdate(const orxCLOCK_INFO &_rstInfo);
                void            BaseCameraUpdate(const orxCLOCK_INFO &_rstInfo);
                orxBOOL         BaseMapSaveFilter(const orxSTRING _zSectionName, const orxSTRING _zKeyName, const orxSTRING _zFileName, orxBOOL _bUseEncryption);
                orxSTRING       GetNewObjectName(orxCHAR _zName[32], orxBOOL bRunTime = orxFALSE);

                orxSTATUS       AddObject(ScrollObject *_poObject);
                orxSTATUS       RemoveObject(ScrollObject *_poObject);

  static  void                  DeleteInstance();

  static  orxSTATUS orxFASTCALL StaticInit();
  static  orxSTATUS orxFASTCALL StaticRun();
  static  void      orxFASTCALL StaticExit();
  static  void      orxFASTCALL StaticUpdate(const orxCLOCK_INFO *_pstInfo, void *_pstContext);
  static  void      orxFASTCALL StaticCameraUpdate(const orxCLOCK_INFO *_pstInfo, void *_pstContext);
  static  orxBOOL   orxFASTCALL StaticMapSaveFilter(const orxSTRING _zSectionName, const orxSTRING _zKeyName, const orxSTRING _zFileName, orxBOOL _bUseEncryption);
  static  orxSTATUS orxFASTCALL StaticEventHandler(const orxEVENT *_pstEvent);


//! Variables
protected:

  static        ScrollBase *    spoInstance;

private:

                orxLINKLIST     mstObjectList;
                orxLINKLIST     mstObjectChronoList;
                orxSTRING       mzMapName;
                orxBOOL         mbEditorMode;
                orxBOOL         mbDifferentialMode;
                orxBOOL         mbObjectListLocked;
                orxBOOL         mbIsRunning;
                orxBOOL         mbIsPaused;
                const orxSTRING mzCurrentObject;
                orxVIEWPORT *   mpstMainViewport;
                orxCAMERA *     mpstMainCamera;
                orxS32          ms32NextObjectID;
                orxS32          ms32RuntimeObjectID;
                orxU32          mu32LayerNumber;
                orxCONFIG_SAVE_FUNCTION mpfnCustomMapSaveFilter;
};


#ifdef __SCROLL_IMPL__

//! Inline include
#include "ScrollBase.inl"

#endif // __SCROLL_IMPL__

#endif // _SCROLLBASE_H_
