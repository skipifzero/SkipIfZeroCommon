#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

#include <SDL.h> // SDL_GetBasePath();

#include "sfz/util/IO.hpp"

using std::string;

const string& basePath()
{
	static const string path{SDL_GetBasePath()}; // Leaks by design. :P
	return path;
}

const string& stupidFileName()
{
	static const string stupid{"jfioaejfaiojefaiojfeaojf.fajefaoejfa"};
	return stupid;
}

TEST_CASE("createFile() & fileExists() & deleteFile()", "[sfz::IO]")
{
	const string filePath = basePath() + stupidFileName();
	const char* fpath = filePath.c_str();

	bool resExists1 = sfz::fileExists(fpath);
	if (resExists1) {
		bool del = sfz::deleteFile(fpath);
		REQUIRE(del);
		resExists1 = sfz::fileExists(fpath);
	}
	REQUIRE(!resExists1);

	bool resCreate = sfz::createFile(fpath);
	REQUIRE(resCreate);

	bool resExists2 = sfz::fileExists(fpath);
	REQUIRE(resExists2);

	bool resDelete = sfz::deleteFile(fpath);
	REQUIRE(resDelete);

	bool resExists3 = sfz::fileExists(fpath);
	REQUIRE(!resExists3);
}

TEST_CASE("createDirectory() & directoryExists() & deleteDirectory()", "[sfz::IO]")
{
	const string dirPath = basePath() + stupidFileName();
	const char* dpath = dirPath.c_str();

	bool resExists1 = sfz::directoryExists(dpath);
	if (resExists1) {
		bool del = sfz::deleteDirectory(dpath);
		REQUIRE(del);
		resExists1 = sfz::directoryExists(dpath);
	}
	REQUIRE(!resExists1);

	bool resCreate = sfz::createDirectory(dpath);
	REQUIRE(resCreate);

	bool resExists2 = sfz::directoryExists(dpath);
	REQUIRE(resExists2);

	bool resDelete = sfz::deleteDirectory(dpath);
	REQUIRE(resDelete);

	bool resExists3 = sfz::directoryExists(dpath);
	REQUIRE(!resExists3);
}