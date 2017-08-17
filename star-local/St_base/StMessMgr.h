#ifndef StarLocal_StMessMgr_h
#define StarLocal_StMessMgr_h

#include <iostream>

extern std::ostream& LOG_INFO;
extern std::ostream& LOG_WARN;
extern std::ostream& LOG_ERROR;
extern std::ostream& LOG_FATAL;
extern std::ostream& LOG_DEBUG;

std::ostream& endm(std::ostream& os);

#endif
