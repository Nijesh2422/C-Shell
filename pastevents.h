#ifndef __PASTEVENTS_H
#define __PASTEVENTS_H

void pasteventsadd(FILE *FilePointer, const char *PATHOFFILE, char *input);
void pastevents(FILE *FilePointer);
void pasteventspurge(FILE *FilePointer, const char *PATHOFFILE);
void Pastevents(FILE *FilePointer, const char *PATHOFFILE, char **Command);
void Pasteventsexecute(char *INPUT, const char *HomeDirectory, char *PrevDirectory, FILE *FilePointer, char *input, const char *PATHOFFILE, char **ARGV);

#endif