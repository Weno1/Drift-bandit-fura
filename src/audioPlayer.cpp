#include "audioPlayer.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"

AudioPlayer::AudioPlayer()
{
    _data = new uint8_t[BUFFER_SIZE];
}

bool AudioPlayer::isPlaying() const
{
    return _isPlaying;
}

void AudioPlayer::play()
{

}

void AudioPlayer::iqrHandler()
{

}

AudioPlayer::~AudioPlayer()
{
    delete[] _data;
}