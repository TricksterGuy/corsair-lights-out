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
        void StartBatch();
        void EndBatch(bool flush = true);
        void Flush();
        void KeyOn(const std::string& key_name, unsigned int color = ON_COLOR);
        void KeyOff(const std::string& key_name);
        void AllOn(unsigned int color = ON_COLOR);
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
