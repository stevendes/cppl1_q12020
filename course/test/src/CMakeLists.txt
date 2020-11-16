# Include paths.
include_directories(
	../include
)

# Test sources.
set (GTEST_SOURCES
	isometry_TEST.cpp
	vector3_TEST.cpp
	matrix3_TEST.cpp
)

cppcourse_build_tests(${GTEST_SOURCES})
