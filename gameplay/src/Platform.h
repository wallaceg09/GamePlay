/*
 * Platform.h
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

namespace gameplay
{

class Game;

/**
 * Defines a platform.
 */
class Platform
{
public:

    /**
     * Constructor.
     */
    static Platform* create(Game* game);

    /**
     * Begins processing the platform messages.
     *
     * This method handles all OS window messages and drives the game loop.
     * It normally does not return until the application is closed.
     */
    int enterMessagePump();

    /**
     * Gets the absolute platform time starting from when the message pump was started.
     */
    static long getAbsoluteTime();

    /**
     * Sets the absolute platform time since the start of the message pump.
     *
     * @param time The time to set (in milliseconds).
     */
    static void setAbsoluteTime(long time);

    /**
     * Gets whether vertical sync is enabled for the game display.
     * 
     * @return true if vsync is enabled; false if not.
     */
    static bool isVsync();

    /**
     * Sets whether vertical sync is enable for the game display.
     *
     * @param enable true if vsync is enabled; false if not.
     */
    static void setVsync(bool enable);

    /**
     * Gets the orientation angle the device is currently in.
     * 
     * @return The orientation angle.
     */
    static int getOrientationAngle();

    /**
     * Indicates whether the platform supports an accelerometer.
     * 
     * @return true if the accelerometer is supported, false otherwise.
     */
    static bool isAccelerometerSupported();

    /**
     * Gets the platform accelerometer pitch and roll.
     * 
     * @param pitch The pitch.
     * @param roll The roll.
     */
    static void getAccelerometerPitchAndRoll(float* pitch, float* roll);

private:

    /**
     * Constructor.
     */
    Platform(Game* game);

    /**
     * Constructor.
     */
    Platform(const Platform& copy);

    /**
     * Destructor.
     */
    ~Platform();

    Game* _game;

};

}

#endif