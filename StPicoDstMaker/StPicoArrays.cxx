#include "StPicoDstMaker/StPicoArrays.h"

//              ARRAY NAMES
//============================================================================================
const char* StPicoArrays::picoArrayNames [NAllPicoArrays] = {"Event", "Track", "EmcTrigger", "MtdTrigger",
                                                             "BTOWHit", "BTofHit", "MtdHit",
                                                             "BbcTile", "EpdTile", "FmsHit",
                                                             "EmcPidTraits", "BTofPidTraits", "MtdPidTraits"
                                                            };

//              ARRAY TYPES
//============================================================================================
const char* StPicoArrays::picoArrayTypes [NAllPicoArrays] = {"StPicoEvent", "StPicoTrack", "StPicoEmcTrigger", "StPicoMtdTrigger",
                                                             "StPicoBTowHit", "StPicoBTofHit", "StPicoMtdHit",
                                                             "StPicoBbcTile", "StPicoEpdTile", "StPicoFmsHit",
                                                             "StPicoBEmcPidTraits", "StPicoBTofPidTraits", "StPicoMtdPidTraits"
                                                            };

//              ARRAY SIZES
//============================================================================================
// These are intial sizes. Automatically resized if too small.
// Choosing too large initial values gives a performance penalty when reading
// only selected picoDst branches
int StPicoArrays::picoArraySizes [NAllPicoArrays] = {1, 1000, 100, 100,
                                                     100, 100, 100,
                                                     100, 100, 1300,
                                                     100, 100, 100
                                                    };
StPicoArrays::StPicoArrays()
{}
