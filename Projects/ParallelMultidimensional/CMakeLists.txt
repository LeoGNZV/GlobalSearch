find_package(MPI REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/src/ 
		${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/sample_src/
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/evolvent/include
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/evolvent/src
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/extended/include
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/extended/src
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/include
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/output_system/include
		${MPI_CXX_INCLUDE_PATH})

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/sample_src/Hill/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/sample_src/Shekel/*.cpp
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/sample_src/Grishagin/*.cpp
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/sample_src/GKLS/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/src/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/src/*.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../GCGen/src/*.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/evolvent/include/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/evolvent/src/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/extended/include/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/extended/src/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/include/Common.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/output_system/include/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../Globalizer/globalizer/output_system/src/*.cpp
			"*.cpp"
			"*.h*")

add_executable(ParallelMultidimensional ${SRC_FILES})

target_link_libraries(ParallelMultidimensional MPI::MPI_CXX)