#include <limits>
#include "TMath.h"
#include "St_base/StMessMgr.h"

#include "StPicoEvent/StPicoBEmcPidTraits.h"


//----------------------------------------------------------------------------------
StPicoBEmcPidTraits::StPicoBEmcPidTraits() :
  mTrackIndex(-1),
  mBEMCId(-9999), mBTOWADC0(-9999), mBTOWE0(-9999), mBTOWE(-9999),
  mBEMCDistZ(-9999), mBEMCDistPhi(-9999),
  mBSMDNEta(std::numeric_limits<unsigned char>::max()), mBSMDNPhi(std::numeric_limits<unsigned char>::max()),
  mBTOWId(-9999), mBTOWId23(std::numeric_limits<unsigned char>::max()),
  mBTOWE1(-9999), mBTOWE2(-9999), mBTOWE3(-9999),
  mBTOWDistEta(-9999), mBTOWDistPhi(-9999)
{
  // constructor
}

//----------------------------------------------------------------------------------
StPicoBEmcPidTraits::StPicoBEmcPidTraits(Int_t index, Int_t id, Int_t adc0, Float_t const* e, Float_t const* dist, Int_t const* nhit, Int_t const* ntow): StPicoBEmcPidTraits()
{
  mTrackIndex = (index > std::numeric_limits<short>::max()) ? -1 : (Short_t)index;

  auto getConstrainedShort = [](float x) { return fabs(x) >= std::numeric_limits<short>::max() ? std::numeric_limits<short>::max() : (short)(TMath::Nint(x));};

  mBEMCId       = (id > std::numeric_limits<short>::max()) ? -1 : (Short_t)id;
  mBTOWADC0     = (adc0 > std::numeric_limits<unsigned short>::max()) ? std::numeric_limits<unsigned short>::max() : (UShort_t)adc0;
  mBTOWE0       = getConstrainedShort(e[0] * 1000.);
  mBTOWE        = getConstrainedShort(e[1] * 1000.);
  mBEMCDistZ    = getConstrainedShort(dist[0] * 100.);
  mBEMCDistPhi  = getConstrainedShort(dist[1] * 10000.);
  mBSMDNEta     = (nhit[0] > std::numeric_limits<unsigned char>::max()) ? std::numeric_limits<unsigned char>::max() : (UChar_t)(nhit[0]);
  mBSMDNPhi     = (nhit[1] > std::numeric_limits<unsigned char>::max()) ? std::numeric_limits<unsigned char>::max() : (UChar_t)(nhit[1]);

  mBTOWId       = (ntow[0] <= 0 || ntow[0] > 4800) ? -1 : (Short_t)ntow[0];
  mBTOWId23     = (ntow[1] < 0 || ntow[1] >= 9 || ntow[2] < 0 || ntow[2] >= 9) ? -1 : (Char_t)(ntow[1] * 10 + ntow[2]);
  mBTOWE1       = getConstrainedShort(e[2] * 1000.);
  mBTOWE2       = getConstrainedShort(e[3] * 1000.);
  mBTOWE3       = getConstrainedShort(e[4] * 1000.);
  mBTOWDistEta  = getConstrainedShort(dist[2] * 10000.);
  mBTOWDistPhi  = getConstrainedShort(dist[3] * 10000.);
}

//----------------------------------------------------------------------------------
StPicoBEmcPidTraits::~StPicoBEmcPidTraits()
{
  // destructor
}

//----------------------------------------------------------------------------------
void StPicoBEmcPidTraits::Print(const Char_t* option) const
{
  LOG_INFO << "Matched track index = " << mTrackIndex << endm;
  LOG_INFO << " BEMC Id = " << bemcId() << " BTOW ADC0 = " << adc0() << " energy0 = " << e0() << " e = " << e() << endm;
  LOG_INFO << " BEMC distz = " << zDist() << " distphi = " << phiDist() << endm;
  LOG_INFO << " BSMD nEta/nPhi = " << nEta() << "/" << nPhi() << endm;
  LOG_INFO << " BTOW Id = " << btowId() << " tower Id 2/3 = " << btowId2() << " " << btowId3() << endm;
  LOG_INFO << " BTOW energy = " << e1() << " " << e2() << " " << e3() << endm;
  LOG_INFO << " BTOW position to center = " << etaTowDist() << " " << phiTowDist() << endm;
}
