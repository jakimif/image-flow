#include "argumentParser.h"

#include <gtest/gtest.h>

TEST(ArgumentParser, RegisterFlag) {
	ArgumentParser argParser;

	EXPECT_FALSE(argParser.isFlagRegistered("rename"));
	argParser.registerFlag("rename");
	EXPECT_TRUE(argParser.isFlagRegistered("rename"));
}

TEST(ArgumentParser, RegisterFlagWithWhiteSpace) {
	ArgumentParser argParser;

	argParser.registerFlag("any flag");
	EXPECT_FALSE(argParser.isFlagRegistered("any flag"));
}