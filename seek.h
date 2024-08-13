#ifndef __SEEK_H
#define __SEEK_H

void seek(char **ARGV, const char *HomeDirectory,char* PrevDirectory);
void RealSeek(char *PathtotheDirectory, int eflag, int fflag, int dflag, const char *Target, const char *DupeHome, char *PETH);

#endif