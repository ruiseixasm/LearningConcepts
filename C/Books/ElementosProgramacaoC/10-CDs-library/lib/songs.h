#ifndef LIB_SONGS
#define LIB_SONGS

#include <limits.h>

typedef char *Name;
typedef short Duration;

typedef struct {
    Name name;
    Duration duration;
} Song;

Song MakeSong(Name n, Duration d);
void BuildSong(Song *s, Name n, Duration d);
void SetName(Song *s, Name n);
void SetDuration(Song *s, Duration d);
int IsDuration(int n);

#endif /* LIB_SONGS */
