#ifndef StPicoCut_h
#define StPicoCut_h

#include "TObject.h"

class StMuEvent;
class StMuTrack;
class StPicoTrack;

class StPicoCut : public TObject {
 public:
  StPicoCut();
  ~StPicoCut();

  bool passEvent( StMuEvent * );
  bool passTrack( StMuTrack * );
  ClassDef(StPicoCut,1)
};

#endif
