#ifndef StPicoBbcFiller_h
#define StPicoBbcFiller_h

class StMuDst;
class StPicoDst;


/**
 * This class fills a TClonesArray of StPicoBbcHit objects that make up the BBC
 * detector
 */
class StPicoBbcFiller
{
public:

  StPicoBbcFiller(StPicoDst& picoDst) : mPicoDst(picoDst) {}

  void fill(const StMuDst& muDst);

private:

  StPicoDst&  mPicoDst;

};

#endif

