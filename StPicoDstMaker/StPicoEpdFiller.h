#ifndef StPicoEpdFiller_h
#define StPicoEpdFiller_h

class StMuDst;
class StPicoDst;


/**
 * This class fills a TClonesArray of StPicoEpdHit objects that make up the BBC
 * detector.
 */
class StPicoEpdFiller
{
public:

  StPicoEpdFiller(StPicoDst& picoDst) : mPicoDst(picoDst) {}

  void fill(const StMuDst& muDst);

private:

  StPicoDst&  mPicoDst;

};

#endif

