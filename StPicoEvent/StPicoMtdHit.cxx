#include <limits>

#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoMtdHit.h"


//----------------------------------------------------------------------------------
StPicoMtdHit::StPicoMtdHit(): mgChannel(-1), mTriggerFlag(0), mLeadingEdgeTime{ -999., -999.}, mTrailingEdgeTime{ -999., -999}
{
}


//----------------------------------------------------------------------------------
StPicoMtdHit::~StPicoMtdHit()
{
  // dummy destructor
}

//----------------------------------------------------------------------------------
void StPicoMtdHit::Print(const Char_t* option) const
{
  LOG_INFO << " Backleg = " << backleg()
           << " Module  = " << module()
           << " Cell    = " << cell()
           << endm;
}
