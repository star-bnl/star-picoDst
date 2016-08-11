#ifndef StPicoArrays_h
#define StPicoArrays_h

enum picoDstTypes {picoEvent=0, picoTrack, picoEmcTrigger, picoMtdTrigger,
		   picoBTOWHit, picoBTofHit, picoMtdHit,
		   picoEmcPidTraits, picoBTofPidTraits, picoMtdPidTraits};
enum NPICOARRAYS { __NALLPICOARRAYS__ = 10 };

class StPicoArrays {
  public:
  StPicoArrays();
///< names of the TBranches in the TTree/File
  static const char*   picoArrayNames[__NALLPICOARRAYS__];

///< names of the classes, the TClonesArrays are arrays of this type
  static const char*   picoArrayTypes[__NALLPICOARRAYS__    ];

///< maximum sizes of the TClonesArrays
  static int           picoArraySizes[__NALLPICOARRAYS__    ];

///< number of entries in current event, currently not used
  static int           picoArrayCounters[__NALLPICOARRAYS__    ];
};

#endif
