#ifndef __StPicoRpsTrackPoint_hh__
#define __StPicoRpsTrackPoint_hh__

#include "TObject.h"
#include "TVector3.h"

// #include "StEvent/StMuRpsTrackPoint.h"

class StMuRpsTrackPoint;

class StPicoRpsTrackPoint : public TObject {

public:
    enum StPicoRpsTrackPointQuality {rpsNormal, rpsGolden, rpsNotSet};
    enum {mNumberOfPmtsInRp = 2, mNumberOfPlanesInRp = 4};
protected:

	// position (x, y, z)
	TVector3	mPosition;
	// 	RP# (e.g. E1U=0)
	Int_t		mRpId;
	// IDs of clusters in RpsCollection
	Int_t 		mClusterId[mNumberOfPlanesInRp];
	// Track Point Quality
    StPicoRpsTrackPointQuality mQuality;
    // time
    double mTime[mNumberOfPmtsInRp];

public:
	StPicoRpsTrackPoint();
    StPicoRpsTrackPoint(const StPicoRpsTrackPoint&);
	~StPicoRpsTrackPoint();

    StPicoRpsTrackPoint& operator=(const StPicoRpsTrackPoint&);

	TVector3 positionVec() const;
    Int_t rpId() const;
    Int_t clusterId(unsigned int planeId ) const;
    double time(unsigned int) const;
    StPicoRpsTrackPointQuality quality() const;
    
    double x() const;
    double y() const;
    double z() const;
    
    void setPosition(const TVector3&);
    void setRpId(Int_t);
    void setClusterId(Int_t, unsigned int);
    void setQuality(StPicoRpsTrackPointQuality quality);
    unsigned int planesUsed() const;

    void setTime(double, unsigned int);


private:

	ClassDef(StPicoRpsTrackPoint,1)
};

inline TVector3 StPicoRpsTrackPoint::positionVec() const { return mPosition; }
inline Int_t StPicoRpsTrackPoint::rpId() const { return mRpId; }
inline Int_t StPicoRpsTrackPoint::clusterId(unsigned int planeId ) const {
    return planeId<mNumberOfPlanesInRp ? mClusterId[planeId] : -1;
}
inline StPicoRpsTrackPoint::StPicoRpsTrackPointQuality StPicoRpsTrackPoint::quality() const { return mQuality; }
inline double StPicoRpsTrackPoint::x() const { return mPosition.x(); }
inline double StPicoRpsTrackPoint::y() const { return mPosition.y(); }
inline double StPicoRpsTrackPoint::z() const { return mPosition.z(); }

inline void StPicoRpsTrackPoint::setPosition(const TVector3& position){
    mPosition = position;
}
inline void StPicoRpsTrackPoint::setRpId(Int_t rpId) { mRpId = rpId; }
inline void StPicoRpsTrackPoint::setClusterId(int clusterId, unsigned int planeId) {
    if( planeId<mNumberOfPlanesInRp )
        mClusterId[planeId] = clusterId;
}
inline void StPicoRpsTrackPoint::setQuality(StPicoRpsTrackPointQuality quality ) {
    mQuality = quality;
}
inline double StPicoRpsTrackPoint::time(unsigned int pmtId) const {
    return pmtId<mNumberOfPmtsInRp ? mTime[pmtId] : -1;
}
inline void StPicoRpsTrackPoint::setTime(double timeVal, unsigned int pmtId){
    if( pmtId<mNumberOfPmtsInRp ) mTime[pmtId] = timeVal;
}



#endif
