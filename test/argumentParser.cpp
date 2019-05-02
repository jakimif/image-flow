#include "argumentParser.h"

#include <array>
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

TEST(ArgumentParser, RegisterOption) {
	ArgumentParser argParser;

	argParser.registerOption("folder");

	EXPECT_TRUE(argParser.isOptionRegistered("folder"));
}

TEST(ArgumentParser, RegisterOptionWithWhiteSpace) {
	ArgumentParser argParser;

	argParser.registerOption("any option");
	EXPECT_FALSE(argParser.isOptionRegistered("any option"));
}

TEST(ArgumentParser, Parse) {
	ArgumentParser argParser;

	std::array<const char*, 5> args = {"TestArgumentParser", "--flag", "--string=aAbbCc", "--number=48",
	                                   "--float=3.8"};
	argParser.registerFlag("flag");
	argParser.registerOption("string");
	argParser.registerOption("number");
	argParser.registerOption("float");

	argParser.parse(args.size(), args.data());

	EXPECT_FALSE(argParser.getFlag("unregistered_flag"));
	EXPECT_TRUE(argParser.getFlag("flag"));

	EXPECT_EQ(argParser.getOptionAs<std::string>("string"), "aabbcc");
	EXPECT_EQ(argParser.getOptionAs<int>("number"), 48);
	EXPECT_EQ(argParser.getOptionAs<float>("float"), 3.8f);
}

TEST(ArgumentParser, ParseInvalidArgs) {
	ArgumentParser argParser;

	EXPECT_NO_THROW(argParser.parse(0, nullptr));
	EXPECT_NO_THROW(argParser.parse(5, nullptr));
}