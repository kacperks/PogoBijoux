#include <AL/al.h>
void initAudioEngine();
int stopAudioEngine();
ALuint playSound(int sourceToUse, int loop, ALuint buffer);
ALuint loadSound(const char filename[]);
