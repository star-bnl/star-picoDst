#include "StPicoDstMaker/StPicoArrays.h"

//              ARRAY NAMES
//============================================================================================
const char* StPicoArrays::picoArrayNames [__NALLPICOARRAYS__] = {"Event", "Track", "EmcTrigger", "MtdTrigger",
                                                                 "BTOWHit", "BTofHit", "MtdHit",
                                                                 "EmcPidTraits", "BTofPidTraits", "MtdPidTraits"
                                                                };

//              ARRAY TYPES
//============================================================================================
const char* StPicoArrays::picoArrayTypes [__NALLPICOARRAYS__] = {"StPicoEvent", "StPicoTrack", "StPicoEmcTrigger", "StPicoMtdTrigger",
                                                                 "StPicoBTowHit", "StPicoBTofHit", "StPicoMtdHit",
                                                                 "StPicoBEmcPidTraits", "StPicoBTofPidTraits", "StPicoMtdPidTraits"
                                                                };

//              ARRAY SIZES
//============================================================================================
// These are intial sizes. Automatically resized if too small.
// Choosing too large initial values gives a performance penalty when reading
// only selected picoDst branches
int StPicoArrays::picoArraySizes [__NALLPICOARRAYS__    ] = {1, 1000, 100, 100,
                                                             100, 100, 100,
                                                             100, 100, 100
                                                            };
StPicoArrays::StPicoArrays()
{}
