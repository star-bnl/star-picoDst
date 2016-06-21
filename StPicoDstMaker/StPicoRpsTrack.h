#ifndef __StPicoRpsTrack_hh__
#define __StPicoRpsTrack_hh__

#include "TObject.h"
#include "TVector3.h"
#include "TRef.h"
#include <vector>

using namespace std;

class StMuRpsTrackPoint;
class StMuRpsTrack;

class StPicoRpsTrack : public TObject {
public:
	enum StPicoRpsTrackType { rpsLocal, rpsGlobal, rpsUndefined };
    enum StPicoRpsAngles { rpsAngleThetaX, rpsAngleThetaY, rpsAngleTheta, mNumberOfAngleTypes };
    enum {mNumberOfStationsInBranch = 2};

protected:
    TRef mTrackPoints[mNumberOfStationsInBranch];   // reference to track points (local tracks)
    TVector3 mP;								    // three-vector with reconstructed track momentum
    Int_t          mBranch;                         // detectors branch, EU=0, ED=1, WU=2, WD=3 
    StPicoRpsTrackType mType;                         // type of the track
    
public:
    StPicoRpsTrack();
    StPicoRpsTrack(const StPicoRpsTrack&);
    ~StPicoRpsTrack();

    StPicoRpsTrack& operator=(const StPicoRpsTrack&);

    const StPicoRpsTrackPoint* trackPoint(unsigned int)const ;
    TVector3 pVec() const;
    int branch() const;
    StPicoRpsTrackType type() const;
    unsigned int planesUsed() const;
    
    double theta(unsigned int = rpsAngleTheta) const;
    double thetaRp(unsigned int = rpsAngleTheta) const;
    double phi() const;
    double phiRp() const;
    double t(double) const;
    double xi(double) const;
    double p() const;
    double pt() const;
    double eta() const;
    double time() const;

    void setTrackPoint( StPicoRpsTrackPoint*, unsigned int);
    void setP(const TVector3&);
    void setBranch(int);
    void setType(StPicoRpsTrackType type);
    
    ClassDef(StPicoRpsTrack, 1)
};

inline const StPicoRpsTrackPoint* StPicoRpsTrack::trackPoint(unsigned int station) const {
    return station < mNumberOfStationsInBranch ? static_cast<const StPicoRpsTrackPoint*>(mTrackPoints[station].GetObject()) : nullptr;
}
inline TVector3 StPicoRpsTrack::pVec() const { return mP; }
inline int StPicoRpsTrack::branch() const { return mBranch; }
inline StPicoRpsTrack::StPicoRpsTrackType StPicoRpsTrack::type() const { return mType; }
inline double StPicoRpsTrack::phi() const { return mP.Phi(); }
inline double StPicoRpsTrack::t(double beamMomentum) const {
  return -2*beamMomentum*beamMomentum*(1-xi(beamMomentum))*(1-cos(theta(rpsAngleTheta)));
}
inline double StPicoRpsTrack::xi(double beamMomentum) const {
    return (beamMomentum - mP.Mag())/beamMomentum;
}
inline double StPicoRpsTrack::p() const { return mP.Mag(); }
inline double StPicoRpsTrack::pt() const { return mP.Perp(); }
inline double StPicoRpsTrack::eta() const { return mP.PseudoRapidity(); }

inline void StPicoRpsTrack::setTrackPoint(StPicoRpsTrackPoint* trackPoint, unsigned int station) {
    if (station<mNumberOfStationsInBranch)
        mTrackPoints[station] = trackPoint;
}
inline void StPicoRpsTrack::setP(const TVector3& P) { mP = P; }
inline void StPicoRpsTrack::setBranch(int branch) { mBranch = branch; }
inline void StPicoRpsTrack::setType(StPicoRpsTrackType type) { mType = type; }

#endif
