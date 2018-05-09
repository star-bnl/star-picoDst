# - Find star soft include directories and libraries
#
#  STAR_FOUND
#  STAR_INCLUDE_DIRS
#  STAR_LIBRARIES
#  STAR_LIBRARY_DIRS
#


set(STAR_ROOT "$ENV{STAR}" CACHE STRING "Path to directory with STAR soft installed")
set(STAR_SRC  "$ENV{STAR}" CACHE STRING "Path to directory with STAR soft source")

if( NOT STAR_ROOT )
	message(WARNING "STAR_ROOT must be set, i.e. \"cmake -D STAR_ROOT=<path to STAR dir>\" "
	                "Alternatively, one can specify environment variable \"STAR\"")
endif()

# Make use of the $STAR_HOST_SYS evironment variable. If it is set use it as the
# typical STAR installation prefix
set(STAR_ADDITIONAL_INSTALL_PREFIX ".")

if( DEFINED ENV{STAR_HOST_SYS} )
	set(STAR_ADDITIONAL_INSTALL_PREFIX ".$ENV{STAR_HOST_SYS}")
	set(STAR_ROOT "${STAR_ROOT}/${STAR_ADDITIONAL_INSTALL_PREFIX}")
endif()


set(STAR_INCLUDE_DIRS
	"${STAR_ROOT}/include"
	"${STAR_ROOT}/include/StRoot"
	"${STAR_ROOT}/include/StarVMC"
	"${STAR_ROOT}/include_all"
	# The following is just a workaround for the STAR code design
	# disrespecting the file hierarchy
	"${STAR_SRC}/StRoot"
	"${STAR_SRC}/StarVMC")

set(STAR_LIBRARY_DIRS
	"${CMAKE_CURRENT_BINARY_DIR}/${STAR_ADDITIONAL_INSTALL_PREFIX}/lib"
	"${STAR_ROOT}/lib")

set( star_core_libs
	StarClassLibrary
	StarMagField
	StarRoot
	StBichsel
	StBTofUtil
	StChain
	StDbBroker
	StDbLib
	StDetectorDbMaker
	StDbUtilities
	StTpcDb
	St_db_Maker
	StEEmcUtil
	StEmcUtil
	StFmsDbMaker
	StFmsUtil
	StEvent
	StEventMaker
	StEventUtilities
	StMcEvent
	StGenericVertexMaker
	Sti
	StiUtilities
	StIOMaker
	StMuDSTMaker
	StStrangeMuDstMaker
	StDb_Tables
	StTableUtilities
	StUtilities
	St_base
	StiIst
	StiTpc
	StiPxl
	StiSsd
	StiSvt
	StiMaker
	StSsdDbMaker
	StSsdUtil
	StSstUtil
	StIstDbMaker
	StarGeometry
	StarAgmlLib
	StarAgmlUtil
	StSvtClassLibrary
	StFtpcTrackMaker
	StFtpcClusterMaker
	St_ctf
	geometry_Tables
	ftpc_Tables
)

set( STAR_LIBRARIES )

foreach( star_component ${star_core_libs} ${STAR_FIND_COMPONENTS} )

	find_library( STAR_${star_component}_LIBRARY ${star_component}
	              PATHS ${STAR_LIBRARY_DIRS} )
	
	if( STAR_${star_component}_LIBRARY )
		mark_as_advanced( STAR_${star_component}_LIBRARY )
		list( APPEND STAR_LIBRARIES ${STAR_${star_component}_LIBRARY} )
		if( STAR_FIND_COMPONENTS )
			list( REMOVE_ITEM STAR_FIND_COMPONENTS ${star_component} )
		endif()
	else()
		message( WARNING "Cannot find STAR component: ${star_component}" )
	endif()

endforeach()

if( STAR_LIBRARIES )
	list( REMOVE_DUPLICATES STAR_LIBRARIES )
endif()


message( STATUS "Found STAR libraries:" )
foreach( star_lib ${STAR_LIBRARIES} )
	message(STATUS "  ${star_lib}")
endforeach()


mark_as_advanced(STAR_INCLUDE_DIRS STAR_LIBRARIES STAR_LIBRARY_DIRS)


# Set STAR_FOUND to TRUE if all listed variables are TRUE
include( FindPackageHandleStandardArgs )

find_package_handle_standard_args(STAR DEFAULT_MSG
	STAR_INCLUDE_DIRS STAR_LIBRARIES STAR_LIBRARY_DIRS)
