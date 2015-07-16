#include "StPicoMcEvent.h"

#include "StMcEvent.hh"
#include "StMcVertex.hh"
StPicoMcEvent::StPicoMcEvent() : 
  mVertex()
{
  ;
}
StPicoMcEvent::StPicoMcEvent(StMcEvent const* mcEvent) : 
  mVertex(mcEvent->primaryVertex()->position())
{
  ;
}
