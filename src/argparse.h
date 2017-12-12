#ifndef ASCIIMG_ARGPARSE_H_INCLUDED
#define ASCIIMG_ARGPARSE_H_INCLUDED

#include <cstddef>

struct env_t
{
    size_t      width;
    size_t      height;
    float       threshold;
    bool        invert;
    const char *filepath;

    env_t();
};

int setup(int argc, char **argv, env_t *env);

#endif /* ASCIIMG_ARGPARSE_H_INCLUDED */
