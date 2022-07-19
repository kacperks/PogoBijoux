#include <AL/al.h>

extern "C"
{
    #include "Sound.h"
};

class SoundHandler
{
    public:
        bool playMusic(const char filename[], bool loop)
        {
            music = loadSound(filename);
            playSound(0, loop, music);
        }

        bool playSoundEffect(const char filename[], bool loop)
        {
            music = loadSound(filename);
            playSound(1, loop, music);
        }

    private:
        ALuint music;
        ALuint soundEffect;
};
