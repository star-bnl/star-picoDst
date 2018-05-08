cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(star-picoDst)

# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# By default build shared libraries but allow the user to change if desired
OPTION(BUILD_SHARED_LIBS "Global flag to cause add_library to create shared libraries if on" ON)

# This project depends on ROOT
find_package(ROOT)

if( ${ROOT_CXX_FLAGS} MATCHES "-m32" )
	message(STATUS "Found -m32 option in $ROOT_CXX_FLAGS (root-config). Will add it to $CMAKE_CXX_FLAGS")
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS FALSE)
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" )
endif()

find_package(STAR)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-D__ROOT__)


include_directories(
	${ROOT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${STAR_INCLUDE_DIRS}
)


root_generate_dictionary(
	StPicoDstMaker_dict
	StPicoDstMaker/StPicoDstMaker.h
)

add_library(
	StPicoDstMaker
	StPicoDstMaker/StPicoDstMaker.cxx
	StPicoDstMaker/StPicoBbcFiller.cxx
	StPicoDstMaker/StPicoEpdFiller.cxx
	StPicoDstMaker/StPicoFmsFiller.cxx
	StPicoDstMaker_dict.cxx
)

root_generate_dictionary(
	StPicoEvent_dict
	StPicoEvent/StPicoBTowHit.h
	StPicoEvent/StPicoBTofHit.h
	StPicoEvent/StPicoBTofPidTraits.h
	StPicoEvent/StPicoBEmcPidTraits.h
	StPicoEvent/StPicoEmcTrigger.h
	StPicoEvent/StPicoEvent.h
	StPicoEvent/StPicoFmsHit.h
	StPicoEvent/StPicoMtdHit.h
	StPicoEvent/StPicoMtdPidTraits.h
	StPicoEvent/StPicoMtdTrigger.h
	StPicoEvent/StPicoBbcTile.h
	StPicoEvent/StPicoEpdTile.h
	StPicoEvent/StPicoTrack.h
)

add_library(
	StPicoEvent
	StPicoEvent/StPicoArrays.cxx
	StPicoEvent/StPicoDst.cxx
	StPicoEvent/StPicoBTowHit.cxx
	StPicoEvent/StPicoBTofHit.cxx
	StPicoEvent/StPicoBTofPidTraits.cxx
	StPicoEvent/StPicoBEmcPidTraits.cxx
	StPicoEvent/StPicoCommon.cxx
	StPicoEvent/StPicoEmcTrigger.cxx
	StPicoEvent/StPicoEvent.cxx
	StPicoEvent/StPicoFmsHit.cxx
	StPicoEvent/StPicoMtdHit.cxx
	StPicoEvent/StPicoMtdPidTraits.cxx
	StPicoEvent/StPicoMtdTrigger.cxx
	StPicoEvent/StPicoBbcTile.cxx
	StPicoEvent/StPicoEpdTile.cxx
	StPicoEvent/StPicoTrack.cxx
	StPicoEvent_dict.cxx
)


install(TARGETS StPicoDstMaker StPicoEvent
	LIBRARY DESTINATION "${STAR_ADDITIONAL_INSTALL_PREFIX}/lib" OPTIONAL
	ARCHIVE DESTINATION "${STAR_ADDITIONAL_INSTALL_PREFIX}/lib" OPTIONAL)
