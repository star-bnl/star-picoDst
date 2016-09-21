#ifndef StPicoUtilities_h
#define StPicoUtilities_h
#include <unordered_map>
#include <string>
#include <cmath>
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"

namespace StPicoUtilities
{
    std::unordered_map<std::string, unsigned int> calculateRefMult(const StMuDst& muDst)
    {
        // in your function define a map of all the refMults you want
        std::unordered_map<std::string, unsigned int> custom_refMult = 
        {
            {"refMult2NegEast", 0},
            {"refMult2NegWest", 0},
            {"refMult2PosEast", 0},
            {"refMult2PosWest", 0},
            {"refMult3NegEast", 0},
            {"refMult3NegWest", 0},
            {"refMult3PosEast", 0},
            {"refMult3PosWest", 0},
            {"refMult4NegEast", 0},
            {"refMult4NegWest", 0},
            {"refMult4PosEast", 0},
            {"refMult4PosWest", 0},
            {"refMultHalfNegEast", 0},
            {"refMultHalfNegWest", 0},
            {"refMultHalfPosEast", 0},
            {"refMultHalfPosWest", 0}
        };

        for (Int_t itrk = 0; itrk < muDst.primaryTracks()->GetEntries(); ++itrk)
        {
            StMuTrack* track = muDst.primaryTracks(itrk) ;
            if (!track) continue;

            // these first 3 checks are suitable for all refMult
            if (track->flag() < 0 || fabs(track->momentum().mag()) < 1.e-10 || track->dca().mag() > 3) continue;

            // calculation for mass square
            const Double_t eta = track->momentum().pseudoRapidity() ;
            const Double_t charge = track->charge();
            const Double_t nsigmaproton= track->nSigmaProton();
            const Double_t nsigmakaon= track->nSigmaKaon();

            double const beta = track->btofPidTraits().beta();
            double const mass2 = beta <= 1.e-5 ? -999. : track->momentum().mag2() * (std::pow(1./beta, 2) - 1);

            // finally, check nHitsfit, charge, eta, pid, if a track satisfies gets inside the if, count it.
            if(track->nHitsFit(kTpcId) >= 10)
            {
                if (charge < 0 && eta > -1.0 && eta < -0.5) ++custom_refMult["refMult2NegEast"];
                if (charge > 0 && eta > -1.0 && eta < -0.5) ++custom_refMult["refMult2PosEast"];
                if (charge < 0 && eta > 0.5 && eta < 1.0) ++custom_refMult["refMult2NegWest"];
                if (charge > 0 && eta > 0.5 && eta < 1.0) ++custom_refMult["refMult2PosWest"] ;
                if (charge < 0 && eta > -1.0 && eta < 0 && nsigmaproton < (-3.0) && mass2 < 0.4) ++custom_refMult["refMult3NegEast"];
                if (charge > 0 && eta > -1.0 && eta < 0 && nsigmaproton < (-3.0) && mass2 < 0.4) ++custom_refMult["refMult3PosEast"];
                if (charge < 0 && eta > 0 && eta < 1.0 && nsigmaproton < (-3.0) && mass2 < 0.4) ++custom_refMult["refMult3NegWest"]; 
                if (charge > 0 && eta > 0 && eta < 1.0 && nsigmaproton < (-3.0) && mass2 < 0.4) ++custom_refMult["refMult3PosWest"];
                if (charge < 0 && eta < 0 && eta > -1.0) ++custom_refMult["refMultHalfNegEast"];
                if (charge > 0 && eta < 0 && eta > -1.0) ++custom_refMult["refMultHalfPosEast"];
                if (charge < 0 && eta > 0 && eta < 1.0) ++custom_refMult["refMultHalfNegWest"];
                if (charge > 0 && eta > 0 && eta < 1.0) ++custom_refMult["refMultHalfPosWest"];
            }

            if(track->nHitsFit(kTpcId) >= 15)
            {
                if (mass2 <= -990)
                {
                    if (charge < 0 && eta > -1.0 && eta < 0 && (nsigmakaon > 3 || nsigmakaon < -3)) ++custom_refMult["refMult4NegEast"];
                    if (charge > 0 && eta > -1.0 && eta < 0 && (nsigmakaon > 3 || nsigmakaon < -3)) ++custom_refMult["refMult4PosEast"];
                    if (charge < 0 && eta > 0 && eta < 1.0 && (nsigmakaon > 3 || nsigmakaon < -3)) ++custom_refMult["refMult4NegWest"];
                    if (charge > 0 && eta > 0 && eta < 1.0 && (nsigmakaon > 3 || nsigmakaon < -3)) ++custom_refMult["refMult4PosWest"];
                }
                else
                {
                    if ( charge < 0 && eta > -1.0 && eta < 0 && (mass2 > 0.6 || mass2 < 0.1)) ++custom_refMult["refMult4NegEast"];
                    if ( charge > 0 && eta > -1.0 && eta < 0 && (mass2 > 0.6 || mass2 < 0.1)) ++custom_refMult["refMult4PosEast"];
                    if ( charge < 0 && eta > 0 && eta < 1.0 && (mass2 > 0.6 || mass2 < 0.1)) ++custom_refMult["refMult4NegWest"];
                    if ( charge > 0 && eta > 0 && eta < 1.0 && (mass2 > 0.6 || mass2 < 0.1)) ++custom_refMult["refMult4PosWest"];
                }
            }
        }
        return custom_refMult;
    }
}
#endif
