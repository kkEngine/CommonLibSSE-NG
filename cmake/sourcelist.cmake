file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "include/*.h" "src/*.cpp")

source_group(
	TREE "${CMAKE_CURRENT_SOURCE_DIR}"
	FILES ${SOURCES}
)
