#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;

struct AudioData
{
	Uint8 *idx;
	Uint32 len;
};

void callbackfun(void *data, Uint8 *buffer, int buffer_len)
{
AudioData *audio = (AudioData*)data;

if( audio->len == 0)
{
	return;
}

Uint32 length = (Uint32)buffer_len;
length = (length > audio->len ? audio->len : length);

SDL_memcpy(buffer, audio->idx, length);

audio->idx += length;
audio->len -= length;


}

int main()
{

SDL_Init(SDL_INIT_EVERYTHING);

SDL_AudioSpec aud_wav_spec;

Uint8 *wav_start;
Uint32 wav_len;



if(SDL_LoadWAV("sample_30_sec.wav", &aud_wav_spec, &wav_start, &wav_len) == NULL)
{
	cout << "error 1" << endl;
	return 1;
}
else
{
cout << "file loaded" << endl;
}

AudioData audio;
audio.idx = wav_start;
audio.len = wav_len;


cout << "calling callback function" << endl;

aud_wav_spec.callback = callbackfun;
aud_wav_spec.userdata = &audio;

SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL,0, &aud_wav_spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
if(device == 0)
{
	cout << "error 2" << endl;
	return 1;
}
else
{
cout << "opening audio was success" << endl;
}

SDL_PauseAudioDevice(device,0);
cout << ":::playing audio:::" << endl;

while(audio.len > 0)
{
	SDL_Delay(100);
	//cout << "Looping \n";
}



SDL_CloseAudioDevice(device);
cout << "closing the audio device" << endl;
SDL_FreeWAV(wav_start);
cout << "free wav" << endl;
SDL_Quit();



return 0;
}
