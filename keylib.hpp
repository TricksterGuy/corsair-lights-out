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

// Gets key from specified location in keyboard grid
// Only K70 is supported at this time.
const Key& get_key(int x, int y, int keyboard);

extern Key NullKey;

#endif
