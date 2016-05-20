#
# Example cmake command with parameters:
#
# cmake -D STAR_BASE_DIR=~/star-repos/star-base \
#       -D STAR_STEVENT_DIR=~/star-repos/star-stevent \
#       -D STAR_MUDST_DIR=~/star-repos/star-muDst \
#       -D STAR_TABLES_DIR=~/star-repos/star-tables \
#       -D STAR_EMC_DIR=~/star-repos/star-emc \
#       -D STAR_TRIGGER_DIR=~/star-repos/star-trigger \
#       -D STAR_PAMS_DIR=~/star-repos/star-pams \
#       -D STAR_DAQ_DIR=~/star-repos/star-daq \
#       -D CMAKE_INSTALL_PREFIX=./ ../
#

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(star-picoDst)

# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/star-cmake")

# This project depends on ROOT
find_package(ROOT)

if(NOT ROOT_FOUND)
	message(FATAL_ERROR "FATAL: ROOT package not found")
endif()

# Perform some setup standard to STAR experiment environment
include(StarCommon)

add_definitions(-D__ROOT__)


include_directories(
	${ROOT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${STAR_BASE_DIR}
	${STAR_STEVENT_DIR}
	${STAR_MUDST_DIR}
	${STAR_TABLES_DIR}
	${STAR_EMC_DIR}
	${STAR_TRIGGER_DIR}
	${STAR_PAMS_DIR}/global/inc
	${STAR_DAQ_DIR}
)


root_generate_linkdef_and_dictionary(StPicoDstMaker HEADERS "StPicoDstMaker/*.h")

add_library (
	StPicoDstMaker
	SHARED
	StPicoDstMaker/StPicoArrays.cxx
	StPicoDstMaker/StPicoBTOWHit.cxx
	StPicoDstMaker/StPicoBTofHit.cxx
	StPicoDstMaker/StPicoBTofPidTraits.cxx
	StPicoDstMaker/StPicoConstants.cxx
	StPicoDstMaker/StPicoCut.cxx
	StPicoDstMaker/StPicoDst.cxx
	StPicoDstMaker/StPicoDstMaker.cxx
	StPicoDstMaker/StPicoEmcPidTraits.cxx
	StPicoDstMaker/StPicoEmcTrigger.cxx
	StPicoDstMaker/StPicoEvent.cxx
	StPicoDstMaker/StPicoMtdHit.cxx
	StPicoDstMaker/StPicoMtdPidTraits.cxx
	StPicoDstMaker/StPicoMtdTrigger.cxx
	StPicoDstMaker/StPicoTrack.cxx
	StPicoDstMaker/StPicoV0.cxx
	StPicoDstMaker_dict.cxx
)


install(TARGETS StPicoDstMaker DESTINATION "${STAR_ADDITIONAL_INSTALL_PREFIX}/lib")
