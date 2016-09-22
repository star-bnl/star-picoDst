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
            if (track->flag() < 0 || fabs(track->momentum().mag()) < 1.e-10
                || track->dca().mag() > 3 || fabs(track->momentum().pseudoRapidity()) > 1) continue;

            double const eta = track->momentum().pseudoRapidity() ;
            std::string chargeName = track->charge() > 0 ? "Pos" : "Neg";
            std::string tpcHalfName = eta > 0 ? "West" : "East";

            double const beta = track->btofPidTraits().beta();
            double const mass2 = beta <= 1.e-5 ? -999. : track->momentum().mag2() * (std::pow(1./beta, 2) - 1);

            if(track->nHitsFit(kTpcId) >= 10)
            {
              custom_refMult["refMultHalf"+chargeName+tpcHalfName] += 1;
              if(fabs(eta) > 0.5) custom_refMult["refMult2"+chargeName+tpcHalfName] += 1;
              if(track->nSigmaProton() < -3. && mass2 < 0.4) custom_refMult["refMult3"+chargeName+tpcHalfName] += 1;
            }

            if(track->nHitsFit(kTpcId) >= 15)
            {
              if((mass2 <= -990. && fabs(track->nSigmaKaon()) > 3) ||
                 (mass2 >  -990. && (mass2 > 0.6 || mass2 < 0.1))) custom_refMult["refMult4"+chargeName+tpcHalfName] += 1;
            }
        }
        return custom_refMult;
    }
}
#endif
