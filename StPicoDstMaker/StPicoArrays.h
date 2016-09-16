#ifndef StPicoArrays_h
#define StPicoArrays_h

enum class StPicoArrayType : unsigned int {Event=0, Track, EmcTrigger, MtdTrigger,
                                            BTOWHit, BTofHit, MtdHit,
		                                        EmcPidTraits, BTofPidTraits, MtdPidTraits};
enum NPICOARRAYS { __NALLPICOARRAYS__ = 10 };

class StPicoArrays {
  public:
  StPicoArrays();
/// names of the TBranches in the TTree/File
  static const char*   picoArrayNames[__NALLPICOARRAYS__];

/// names of the classes, the TClonesArrays are arrays of this type
  static const char*   picoArrayTypes[__NALLPICOARRAYS__    ];

/// maximum sizes of the TClonesArrays
  static int           picoArraySizes[__NALLPICOARRAYS__    ];
};

#endif
