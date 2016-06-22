#include "StPicoArrays.h"

//              ARRAY NAMES
//============================================================================================
const char* StPicoArrays::picoArrayNames [__NALLPICOARRAYS__] = {"Event","Tracks","EmcTrigger","MtdTrigger",
								 "BTOWHit","BTofHit","MtdHit",
								 "EmcPidTraits","BTofPidTraits","MtdPidTraits"};

//              ARRAY TYPES
//============================================================================================
const char* StPicoArrays::picoArrayTypes [__NALLPICOARRAYS__] = {"StPicoEvent","StPicoTrack","StPicoEmcTrigger","StPicoMtdTrigger",
								 "StPicoBTOWHit","StPicoBTofHit","StPicoMtdHit",
								 "StPicoEmcPidTraits","StPicoBTofPidTraits","StPicoMtdPidTraits"};

//              ARRAY SIZES
//============================================================================================
// These are intial sizes. Automatically resized if too small.
// Choosing too large initial values gives a performance penalty when reading
// only selected picoDst branches
int StPicoArrays::picoArraySizes [__NALLPICOARRAYS__    ] = {1,1000,100,100,
							     100,100,100,
							     100,100,100};

//              ARRAY COUNTERS
//============================================================================================
int   StPicoArrays::picoArrayCounters [__NALLPICOARRAYS__ ] = {0,0,0,0,
							       0,0,0,
							       0,0,0};
StPicoArrays::StPicoArrays()
{}
