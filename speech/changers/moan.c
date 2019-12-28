#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "doom/m_random.c"

int clamp(int in) {
    if(in < 0) return 0;
    if(in > 255) return 255;
    return in;
}

#define FREQUENCY 11025
#define CHANNELS  1
#define CHUNKSIZE 4096
#define CHANNEL 1
#define LOOPS 0

void ensure(int ret) {
    if(-1 == ret) {
        exit(ret);
    }
}

Mix_Chunk *newChunk(int bufsize) {
    Mix_Chunk *ret;
    if(!(ret = (Mix_Chunk *)malloc(sizeof(Mix_Chunk)))) {
        fprintf(stderr,"problem allocating Mix_Chunk\n");
        return ret;
    }
    ret->allocated = 0;
    ret->volume = 128;
    ret->alen = bufsize;
    if(!(ret->abuf = (Uint8 *)malloc(bufsize))) {
        fprintf(stderr,"problem allocating abuf\n");
        return ret;
    }
    memset(ret->abuf, 0, ret->alen);
    return ret;
}
#define DEFAULT_PITCH 128
#define MIN(x,y) ((x) > (y) ? (y) : (x))

Mix_Chunk *abuse3(Mix_Chunk *osound, int pitch, unsigned char use_decimator) {
    Mix_Chunk *newchunk;
    int newsize;
    int i;
    newsize = (osound->alen)*((pitch+1)*100/DEFAULT_PITCH)/100; /* rounds up */
    newchunk = newChunk(newsize);
    printf("debug: inchunk size %d, pitch %d, outchunk size %d\n",
      osound->alen, pitch, newchunk->alen);

    if(newsize < osound->alen && use_decimator > 0) { /* decimator */
        unsigned int newi, oldi, count;
        unsigned long accumulator;
        printf("using decimator\n");

        for(i = oldi = count = accumulator = 0; i < osound->alen; ++i) {
            newi = (float)i / osound->alen * newsize;

            if(newi != oldi) {
                newchunk->abuf[oldi] = accumulator/count;
                accumulator = count = 0;
            }
            accumulator += osound->abuf[i];
            count++;
            oldi = newi;
        }
        newchunk->abuf[oldi] = accumulator/count;

    } else {
        /*
         * copy samples into smaller or larger dest buf
         */
        for(i = 0; i < newsize; ++i) {
            newchunk->abuf[i] = osound->abuf[osound->alen * i / newsize];
        }
    }

    return newchunk;
}

/* all possible pitches, see r.c */
#define NUM_PITCHES 32
Uint8 pitches[NUM_PITCHES] = {
    114, 130, 132, 139, 120, 128, 133, 135,
    123, 136, 116, 127, 115, 131, 134, 117,
    125, 143, 122, 126, 118, 119, 142, 138,
    121, 124, 113, 129, 144, 141, 140, 137
};



int main() {
    Mix_Chunk *osound, *sound;
    int channel, i;

    ensure(SDL_Init(SDL_INIT_AUDIO));

    ensure(Mix_OpenAudio( FREQUENCY, AUDIO_U8 /*MIX_DEFAULT_FORMAT*/, CHANNELS, CHUNKSIZE));

    printf("Mix_AllocateChannels: %d\n", Mix_AllocateChannels(1));
    printf("Mix_Volume: %d\n", Mix_Volume(-1, MIX_MAX_VOLUME));

    if(!(sound = Mix_LoadWAV("dspodth1.wav"))) {
        fprintf(stderr, "error in Mix_LoadWAV\n");
        exit(1);
    }
    printf("sound->alen=%d\n", sound->alen);
    printf("Mix_VolumeChunk: %d\n", Mix_VolumeChunk(sound, MIX_MAX_VOLUME));

    /* back up the original sound */
    osound = sound;

    for(i = 0; i < NUM_PITCHES; ++i) {
      sound = abuse3(osound, pitches[i], 0);
      ensure((channel = Mix_PlayChannel (-1, sound, LOOPS)));
      while(Mix_Playing(channel) != 0);
      sound = abuse3(osound, pitches[i], 1);
      ensure((channel = Mix_PlayChannel (-1, sound, LOOPS)));
      while(Mix_Playing(channel) != 0);
      //Mix_FreeChunk(sound); - may have to do this ourselves
    }

    Mix_FreeChunk(osound);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
