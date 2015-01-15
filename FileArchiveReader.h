/*************************************************
 * Fullmoon - FileArchiveReader
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */

#include <Windows.h>

#define ARCHIVE_SIZE 1000

class FileArchiveReader
{
public:
	static struct Header {
		UINT32 hash;
		UINT32 beginPoint;
		UINT32 size;
	};
	static UINT32 archiveSize;
	static Header archiveHeaders[ARCHIVE_SIZE];
	static void initialize( LPWSTR path );
	static Header* getFile( LPWSTR filename );
private:
	FileArchiveReader(void) {};
	~FileArchiveReader(void) {};
};

