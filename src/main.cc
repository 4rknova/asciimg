#include <cstdio>
#include <nimg/pixmap.h>
#include <nimg/color.h>
#include <nimg/sample.h>
#include <nimg/luminance.h>
#include <nimg/img.h>
#include "argparse.h"

static const char ascii_glyphs[] = {
    ' ', '.', ',', ':', ';', 'i', 't', '%', 'X', '$', '@', '#'
};

int main (int argc, char ** argv)
{
    env_t environment;
    int err = setup(argc, argv, &environment);

    if (err) return err;

    nimg::Pixmap img;
    err = nimg::io::load::image(environment.filepath, img);
    
    if (err) return err;

    for (size_t y = 0; y < environment.height; ++y) {
        for (size_t x = 0; x < environment.width; ++x) {
            float u = x / (float)(environment.width)
                , v = y / (float)(environment.height);
            nimg::ColorRGBAf c = nimg::sample::bilinear(img, u, v);
            float res = nimg::eval::luminance(c);

            if (environment.invert) res = 1.0 - res;

            if (res < environment.threshold) res = 0.f;

            size_t l = sizeof(ascii_glyphs) - 1;

            const char *p = ascii_glyphs + int(l * res);
            printf("%c", *p);
        }
        printf("\n");
    }

    return 0;
}
