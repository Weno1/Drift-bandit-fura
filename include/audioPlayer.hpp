#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"

#define BUFFER_SIZE     1024

class AudioPlayer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    bool isPlaying() const;

    void play();
    void stop();

private:
    bool _isPlaying = false;

    volatile uint32_t _posPointer = 0;
    uint8_t* _data = nullptr;

    static AudioPlayer* _instance;

    void getAudioFile();

    void iqrHandler();
};