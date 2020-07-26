# Include paths.
include_directories(
	../include
)

# Test sources.
set (GTEST_SOURCES
	isometry_TEST.cc
	vector3_TEST.cc
	matrix3_TEST.cc
	old_general_TEST.cc
)

cppcourse_build_tests(${GTEST_SOURCES})
