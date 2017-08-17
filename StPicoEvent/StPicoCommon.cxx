#include "StPicoEvent/StPicoCommon.h"
#include "St_base/StMessMgr.h"

#ifdef StarLocal_StMessMgr_h

std::ostream& LOG_INFO = std::cout;
std::ostream& LOG_WARN = std::cout;
std::ostream& LOG_ERROR = std::cerr;
std::ostream& LOG_FATAL = std::cerr;
std::ostream& LOG_DEBUG = std::cout;

std::ostream& endm(std::ostream& os) { return std::endl(os); }

#endif


namespace StarPicoDst
{

std::set<DetectorSide> detectorSides{ DetectorSide::East, DetectorSide::West};

}
