#! C:\perl\bin\perl

##################################################
# Fullmoon - FileArchiveCreater
# Copyright (c) 2010-2012,2015 Queue Sakura-Shiki
# Released under the MIT license

use strict;
use Time::HiRes;

my $archiveName = "./archive.dat";

my @dir_list = @ARGV;
my @file_list;
my %file_hash;
my %file_size_by_hash;

sub readFiles {
	my $dirName = $_[0];
	opendir DH, $dirName or (print STDERR "ERR01 - Directory Not Found. -> "+$dirName) and die;
	foreach ( readdir DH ) {
		next if /^\.{1,2}$/;
		my $filePath = $dirName."/".$_;
		if ( -f $filePath ) {
			my $hash = 0;
			my $shiftCount = 0;
			for ( my $i = 0; $i < length($filePath); $i++) {
				my $c = substr($filePath, $i, 1);
				$hash = $hash ^ ((0xFF&(ord($c)*$i))<<$shiftCount*8);
				$shiftCount++;
				if ( $shiftCount == 4 ) { $shiftCount=0; }
			}
			if(defined $file_hash{$hash}) {
				print STDERR "ERR02 - File name hash is duplicated. Change file name -> "+$filePath;
				exit;
			} else {
				$file_hash{$hash} = $filePath;
			}
			$file_size_by_hash{$hash} = -s $filePath;
		} else {
			readDirectories($filePath);
		}
	}
}

sub readDirectories {
	readFiles($_[0]);
}

foreach ( @dir_list ) {
	readDirectories($_);
}
open DAT, ">".$archiveName;
binmode DAT;
my $beginByte = int(keys %file_hash)*3*4 + 1*4;
my $biFileCount = pack "I", int(keys %file_hash);
print DAT $biFileCount;
foreach( sort keys %file_hash ) {
	my $biData = pack "I I I", $_,$beginByte, $file_size_by_hash{$_};
	print DAT $biData;
	$beginByte += $file_size_by_hash{$_};
}

foreach ( sort keys %file_hash ) {
	open INFILE, "<".$file_hash{$_} or die;
	binmode INFILE;
	my $buf;
	read(INFILE, $buf, (-s $file_hash{$_}));
	print DAT $buf;

}
my $lastByte = tell DAT;
close DAT;
