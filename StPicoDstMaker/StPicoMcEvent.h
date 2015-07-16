#ifndef StPicoMcEvent_hh
#define StPicoMcEvent_hh

#include "TObject.h"
#include "StThreeVectorF.hh"

class StMcEvent;
class StPicoMcEvent : public TObject {

 public:
  StPicoMcEvent();
  ~StPicoMcEvent(){ ; };
  StPicoMcEvent( StMcEvent const* mcEvent);
  StThreeVectorF const& pVertex();
 private:
  StThreeVectorF mVertex;


  ClassDef(StPicoMcEvent,1)
};
inline StThreeVectorF const& StPicoMcEvent::pVertex(){ return mVertex; };

#endif
