#include "songs.h"

Song MakeSong(Name n, Duration d)
{
    Song s;
    s.name = n;
    s.duration = d;
    return s;   // return by value!
}

void BuildSong(Song *s, Name n, Duration d)
{
    s->name = n;
    s->duration = d;
}

void SetName(Song *s, Name n)
{
    s->name = n;
}

void SetDuration(Song *s, Duration d)
{
    s->duration = d;
}

int IsDuration(int n)
{
    return 1 <= n && n <= SHRT_MAX;
}
