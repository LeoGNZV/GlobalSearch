include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/src/ 
		${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/sample_src/)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/sample_src/Hill/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/sample_src/Shekel/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/src/*.cpp
                    ${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/src/*.h
                    ${CMAKE_CURRENT_SOURCE_DIR}/../GCGen/src/*.hpp
			"*.cpp"
			"*.h*")

add_executable(MainProj ${SRC_FILES})