#include "StPicoRpsTrackPoint.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrackPoint.h"

ClassImp(StPicoRpsTrackPoint)

StPicoRpsTrackPoint::StPicoRpsTrackPoint() {
    mRpId = -1;
    for (unsigned int i=0; i<StMuRpsTrackPoint::mNumberOfPlanesInRp; ++i) mClusterId[i] = -1;
    for (unsigned int i=0; i<StMuRpsTrackPoint::mNumberOfPmtsInRp; ++i) mTime[i] = -1;
    mQuality = StPicoRpsTrackPoint::StPicoRpsTrackPointQuality::rpsNotSet;
}

StPicoRpsTrackPoint::StPicoRpsTrackPoint(const StPicoRpsTrackPoint& trackPoint) {
    *this = trackPoint;
}

StPicoRpsTrackPoint::~StPicoRpsTrackPoint() { /* no op */ }

StPicoRpsTrackPoint& StPicoRpsTrackPoint::operator=(const StPicoRpsTrackPoint& trackPoint) {
    if (this != &trackPoint) {
        mPosition = trackPoint.positionVec();
        mRpId = trackPoint.rpId();
        for (unsigned int i=0; i<StMuRpsTrackPoint::mNumberOfPlanesInRp; ++i ) mClusterId[i] = trackPoint.clusterId(i);
        for (unsigned int i=0; i<StMuRpsTrackPoint::mNumberOfPmtsInRp; ++i ) mTime[i] = trackPoint.time(i);
        mQuality = (StPicoRpsTrackPoint::StPicoRpsTrackPointQuality)trackPoint.quality();
    }
    return *this;
}

unsigned int StPicoRpsTrackPoint::planesUsed() const {
    unsigned int nPlanesUsed = 0;
    for(unsigned int i=0; i<StMuRpsTrackPoint::mNumberOfPlanesInRp; ++i)
        if (mClusterId[i]>-1) ++nPlanesUsed;
    return nPlanesUsed;
}
