//! Code
ScrollObject::ScrollObject() : mpstObject(orxNULL), mzName(orxNULL), mzModelName(orxNULL), mxFlags(FlagNone)
{
  // Clears nodes
  orxMemory_Zero(&mstNode, sizeof(orxLINKLIST_NODE));
  orxMemory_Zero(&mstChronoNode, sizeof(orxLINKLIST_NODE));
}

ScrollObject::~ScrollObject()
{
}


void ScrollObject::Enable(orxBOOL _bEnable, orxBOOL _bRecursive)
{
  // Updates its status
  orxObject_Enable(mpstObject, _bEnable);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Updates its status
      orxObject_Enable(pstChild, _bEnable);
    }
  }
}

orxVECTOR &ScrollObject::GetPosition(orxVECTOR &_rvPosition, orxBOOL _bWorld) const
{
  // Local?
  if(_bWorld == orxFALSE)
  {
    // Updates result
    orxObject_GetPosition(mpstObject, &_rvPosition);
  }
  else
  {
    // Updates result
    orxObject_GetWorldPosition(mpstObject, &_rvPosition);
  }

  // Done!
  return _rvPosition;
}

void ScrollObject::SetPosition(const orxVECTOR &_rvPosition, orxBOOL _bWorld)
{
  // Local?
  if(_bWorld == orxFALSE)
  {
    // Updates its position
    orxObject_SetPosition(mpstObject, &_rvPosition);
  }
  else
  {
    // Updates its position
    orxObject_SetWorldPosition(mpstObject, &_rvPosition);
  }
}

orxVECTOR &ScrollObject::GetScale(orxVECTOR &_rvScale, orxBOOL _bWorld) const
{
  // Local?
  if(_bWorld == orxFALSE)
  {
    // Updates result
    orxObject_GetScale(mpstObject, &_rvScale);
  }
  else
  {
    // Updates result
    orxObject_GetWorldScale(mpstObject, &_rvScale);
  }

  // Done!
  return _rvScale;
}

void ScrollObject::SetScale(const orxVECTOR &_rvScale, orxBOOL _bWorld)
{
  // Local?
  if(_bWorld == orxFALSE)
  {
    // Updates its scale
    orxObject_SetScale(mpstObject, &_rvScale);
  }
  else
  {
    // Updates its scale
    orxObject_SetWorldScale(mpstObject, &_rvScale);
  }
}

orxFLOAT ScrollObject::GetRotation(orxBOOL _bWorld) const
{
  orxFLOAT fResult;

  // Local?
  if(_bWorld == orxFALSE)
  {
    // Updates result
    fResult = orxObject_GetRotation(mpstObject);
  }
  else
  {
    // Updates result
    fResult = orxObject_GetWorldRotation(mpstObject);
  }

  // Done!
  return fResult;
}

void ScrollObject::SetRotation(orxFLOAT _fRotation, orxBOOL _bWorld)
{
  // Local?
  if(_bWorld == orxFALSE)
  {
    // Updates its rotation
    orxObject_SetRotation(mpstObject, _fRotation);
  }
  else
  {
    // Updates its rotation
    orxObject_SetWorldRotation(mpstObject, _fRotation);
  }
}

orxVECTOR &ScrollObject::GetSpeed(orxVECTOR &_rvSpeed, orxBOOL _bRelative) const
{
  // Relative?
  if(_bRelative != orxFALSE)
  {
    // Updates result
    orxObject_GetRelativeSpeed(mpstObject, &_rvSpeed);
  }
  else
  {
    // Updates result
    orxObject_GetSpeed(mpstObject, &_rvSpeed);
  }

  // Done!
  return _rvSpeed;
}

void ScrollObject::SetSpeed(const orxVECTOR &_rvSpeed, orxBOOL _bRelative)
{
  // Relative?
  if(_bRelative != orxFALSE)
  {
    // Updates its speed
    orxObject_SetRelativeSpeed(mpstObject, &_rvSpeed);
  }
  else
  {
    // Updates its speed
    orxObject_SetSpeed(mpstObject, &_rvSpeed);
  }
}

orxCOLOR &ScrollObject::GetColor(orxCOLOR &_rstColor) const
{
  // Updates result
  orxObject_GetColor(mpstObject, &_rstColor);

  // Done!
  return _rstColor;
}

void ScrollObject::SetColor(const orxCOLOR &_rstColor, orxBOOL _bRecursive)
{
  // Updates object's color
  orxObject_SetColor(mpstObject, &_rstColor);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Updates its color
      orxObject_SetColor(pstChild, &_rstColor);
    }
  }
}

void ScrollObject::GetFlip(orxBOOL &_rbFlipX, orxBOOL &_rbFlipY) const
{
  // Updates result
  orxObject_GetFlip(mpstObject, &_rbFlipX, &_rbFlipY);
}

void ScrollObject::SetFlip(orxBOOL _bFlipX, orxBOOL _bFlipY, orxBOOL _bRecursive)
{
  // Updates its flip
  orxObject_SetFlip(mpstObject, _bFlipX, _bFlipY);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Updates its flip
      orxObject_SetFlip(pstChild, _bFlipX, _bFlipY);
    }
  }
}

void ScrollObject::AddFX(const orxSTRING _zFXName, orxBOOL _bRecursive)
{
  // Adds FX to object
  orxObject_AddFX(mpstObject, _zFXName);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Adds FX to it
      orxObject_AddFX(pstChild, _zFXName);
    }
  }
}

void ScrollObject::AddFX(const orxSTRING _zFXName, orxFLOAT _fDelay, orxBOOL _bRecursive)
{
  // Adds FX to object
  orxObject_AddDelayedFX(mpstObject, _zFXName, _fDelay);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Adds FX to it
      orxObject_AddDelayedFX(pstChild, _zFXName, _fDelay);
    }
  }
}

void ScrollObject::RemoveFX(const orxSTRING _zFXName, orxBOOL _bRecursive)
{
  // Removes FX from object
  orxObject_RemoveFX(mpstObject, _zFXName);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Removes FX from it
      orxObject_RemoveFX(pstChild, _zFXName);
    }
  }
}

void ScrollObject::AddShader(const orxSTRING _zShaderName, orxBOOL _bRecursive)
{
  // Adds shader to object
  orxObject_AddShader(mpstObject, _zShaderName);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Adds shader to it
      orxObject_AddShader(pstChild, _zShaderName);
    }
  }
}

void ScrollObject::RemoveShader(const orxSTRING _zShaderName, orxBOOL _bRecursive)
{
  // Removes shader from object
  orxObject_RemoveShader(mpstObject, _zShaderName);

  // Recursive?
  if(_bRecursive != orxFALSE)
  {
    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Removes shader from it
      orxObject_RemoveShader(pstChild, _zShaderName);
    }
  }
}

void ScrollObject::AddSound(const orxSTRING _zSoundName)
{
  // Adds sound to object
  orxObject_AddSound(mpstObject, _zSoundName);
}

void ScrollObject::RemoveSound(const orxSTRING _zSoundName)
{
  // Removes sound from object
  orxObject_RemoveSound(mpstObject, _zSoundName);
}

orxFLOAT ScrollObject::GetLifeTime() const
{
  orxFLOAT fResult;

  // Updates result
  fResult = orxObject_GetLifeTime(mpstObject);

  // Done!
  return fResult;
}

void ScrollObject::SetLifeTime(orxFLOAT _fLifeTime)
{
  // Updates its lifetime
  orxObject_SetLifeTime(mpstObject, _fLifeTime);
}

void ScrollObject::PushConfigSection(orxBOOL _bPushInstanceSection) const
{
  // Pushes its model section
  orxConfig_PushSection(_bPushInstanceSection ? mzName : mzModelName);
}

void ScrollObject::PopConfigSection() const
{
  // Pops config section
  orxConfig_PopSection();
}

void ScrollObject::SetDifferentialMode(orxBOOL _bDifferential)
{
  // Uses differential scrolling?
  if(_bDifferential)
  {
    // Enforces object's differential flags
    orxStructure_SetFlags(orxOBJECT_GET_STRUCTURE(mpstObject, FRAME), orxFRAME_KU32_FLAG_DEPTH_SCALE|orxFRAME_KU32_FLAG_SCROLL_X|orxFRAME_KU32_FLAG_SCROLL_Y, orxFRAME_KU32_FLAG_NONE);

    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Enforces its differential flags
      orxStructure_SetFlags(orxOBJECT_GET_STRUCTURE(pstChild, FRAME), orxFRAME_KU32_FLAG_DEPTH_SCALE|orxFRAME_KU32_FLAG_SCROLL_X|orxFRAME_KU32_FLAG_SCROLL_Y, orxFRAME_KU32_FLAG_NONE);
    }
  }
  else
  {
    // Removes object's differential flags
    orxStructure_SetFlags(orxOBJECT_GET_STRUCTURE(mpstObject, FRAME), orxFRAME_KU32_FLAG_NONE, orxFRAME_KU32_FLAG_DEPTH_SCALE|orxFRAME_KU32_FLAG_SCROLL_X|orxFRAME_KU32_FLAG_SCROLL_Y);

    // For all children
    for(orxOBJECT *pstChild = orxObject_GetChild(mpstObject);
        pstChild != orxNULL;
        pstChild = orxObject_GetSibling(pstChild))
    {
      // Removes its differential flags
      orxStructure_SetFlags(orxOBJECT_GET_STRUCTURE(pstChild, FRAME), orxFRAME_KU32_FLAG_NONE, orxFRAME_KU32_FLAG_DEPTH_SCALE|orxFRAME_KU32_FLAG_SCROLL_X|orxFRAME_KU32_FLAG_SCROLL_Y);
    }
  }
}

void ScrollObject::SetOrxObject(orxOBJECT *_pstObject)
{
  // Stores it
  mpstObject = _pstObject;

  // Valid?
  if(_pstObject)
  {
    // Stores model name
    mzModelName = orxObject_GetName(_pstObject);
  }
  else
  {
    // Clears model name
    mzModelName = orxNULL;
  }
}

void ScrollObject::OnCreate()
{
#ifdef __SCROLL_DEBUG__
  // Is a derived class?
  if(typeid(ScrollObject) != typeid(*this))
  {
    // Has to override this method in the derived class!
    orxLOG("[ERROR] You need to override the ScrollObject::OnCreate() method for derived class %s!", typeid(*this).name());
    orxBREAK();
  }
#endif // __SCROLL_DEBUG__
}

void ScrollObject::OnDelete()
{
#ifdef __SCROLL_DEBUG__
  // Is a derived class?
  if(typeid(ScrollObject) != typeid(*this))
  {
    // Has to override this method in the derived class!
    orxLOG("[ERROR] You need to override the ScrollObject::OnDelete() method for derived class %s!", typeid(*this).name());
    orxBREAK();
  }
#endif // __SCROLL_DEBUG__
}

void ScrollObject::Update(const orxCLOCK_INFO &_rstInfo)
{
}

orxBOOL ScrollObject::OnCollide(ScrollObject *_poCollider, const orxSTRING _zPartName, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal)
{
  return orxTRUE;
}

orxBOOL ScrollObject::OnSeparate(ScrollObject *_poCollider)
{
  return orxTRUE;
}

void ScrollObject::OnNewAnim(const orxSTRING _zOldAnim, const orxSTRING _zNewAnim, orxBOOL _bCut)
{
}

void ScrollObject::OnAnimEvent(const orxSTRING _zAnim, const orxSTRING _zEvent, orxFLOAT _fTime, orxFLOAT _fValue)
{
}

void ScrollObject::OnStartGame()
{
}

void ScrollObject::OnStopGame()
{
}

void ScrollObject::OnPauseGame(orxBOOL _bPause)
{
}

orxBOOL ScrollObject::OnRender()
{
  return orxTRUE;
}
