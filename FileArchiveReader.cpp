/*************************************************
 * Fullmoon - FileArchiveReader
 * Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
 * Released under the MIT license
 */

#include "FileArchiveReader.h"

UINT32 FileArchiveReader::archiveSize;
FileArchiveReader::Header Archiver::archiveHeaders[ARCHIVE_SIZE];

int FileArchiveReader::initialize( LPWSTR path ) {

	INT32 a;
	a = sizeof(archiveHeaders);
	if ( EnginConfig::useArchive() ) {
		FILE* fp = fopen(path,"rb");
		if ( !fp ) {
			return -1;
		} 
		INT32 datas[4];
		for ( int i=0 ; i<4 ; i++ ) {
			if( (datas[i] = fgetc(fp)) == EOF ) {
				return -1;
			}
		}
		archiveSize = (0xFF&datas[0])<<0 | (0xFF&datas[1])<<8 | (0xFF&datas[2])<<16 | (0xFF&datas[3])<<24;

		for ( int i=0 ; i<archiveSize ; i++ ) {
			for ( int j=0 ; j<4 ; j++ ) {
				if( (datas[j] = fgetc(fp)) == EOF ) {
					return -1;
				}
			}
			archiveHeaders[i].hash = (0xFF&datas[0])<<0 | (0xFF&datas[1])<<8 | (0xFF&datas[2])<<16 | (0xFF&datas[3])<<24;
			for ( int j=0 ; j<4 ; j++ ) {
				if( (datas[j] = fgetc(fp)) == EOF ) {
					return -1;
				}
			}
			archiveHeaders[i].beginPoint = (0xFF&datas[0])<<0 | (0xFF&datas[1])<<8 | (0xFF&datas[2])<<16 | (0xFF&datas[3])<<24;
			for ( int j=0 ; j<4 ; j++ ) {
				if( (datas[j] = fgetc(fp)) == EOF ) {
					return -1;
				}
			}
			archiveHeaders[i].size = (0xFF&datas[0])<<0 | (0xFF&datas[1])<<8 | (0xFF&datas[2])<<16 | (0xFF&datas[3])<<24;

		}
		fclose( fp );
	}
}

FileArchiveReader::Header* FileArchiveReader::getFile( LPWSTR filename ) {
	size_t size;
	char str[255];
	wcstombs_s(&size, str, 255, filename, _TRUNCATE);
	UINT32 hash = 0;
	INT32 shiftCount=0;
	for ( int i=0 ; i<size-1 ; i++ ) {
		hash ^= (0xFF&(str[i]*i))<<shiftCount*8;
		shiftCount++;
		if ( shiftCount==4 ) { shiftCount = 0; }
	}
	for ( int i=0 ; i<archiveSize ; i++ ) {
		if ( archiveHeaders[i].hash == hash ) {
			return &archiveHeaders[i];
		}
	}
	return NULL;
}


