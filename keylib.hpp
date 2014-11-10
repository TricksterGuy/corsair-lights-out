#ifndef KEYLIB_HPP
#define KEYLIB_HPP

#include <string>

// Key representation
// Keys have a name, an x and y coordinate measured in roughly in 16th inches.
// Most keys are 3/4" apart.
class Key
{
    public:
        Key(const std::string& key_name, int real_x, int real_y, bool is_on_k70 = true);
        std::string name;
        int x, y;
        bool on_k70;
};

#define ON_COLOR 0xFF0000
#define OFF_COLOR 0x000000

class Keyboard
{
    public:
        ~Keyboard();
        static Keyboard& Instance()
        {
            static Keyboard instance;
            return instance;
        }
        /// Starts a batch of commands to send to the device.
        void StartBatch();
        /// Ends a batch.
        void EndBatch(bool flush = true);
        /// Flushes the stream so commands are sent to the device.
        void Flush();
        /// Turns the specified key led to color passed in.
        void KeyOn(const std::string& key_name, unsigned int color = ON_COLOR);
        /// Turns the specified key led off.
        void KeyOff(const std::string& key_name);
        /// Turns on entire keyboard to color.
        void AllOn(unsigned int color = ON_COLOR);
        /// Turns entire keyboard off.
        void AllOff();
    private:
        Keyboard();
        Keyboard(const Keyboard&);
        void operator=(const Keyboard&);
        bool batching;
        FILE* output;
};

// Gets key from specified location in keyboard grid
// Only K70 is supported at this time.
const Key& get_key(int x, int y, int keyboard);
extern Key NullKey;
extern Key positions[];

#endif
