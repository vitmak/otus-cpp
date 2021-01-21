#include "lib.h"
#include <gtest/gtest.h>

TEST(Version, ValidVersion) {
	ASSERT_GT(version(), 0);
}
