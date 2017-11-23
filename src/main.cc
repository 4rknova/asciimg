#include <cstdio>
#include <nimg/pixmap.h>
#include <nimg/color.h>
#include <nimg/sample.h>
#include <nimg/luminance.h>
#include <nimg/img.h>

//#define PALETTE " .,;+ltgti!lI?/\\|)(1}{][rcvzjftJUOQocxfXhqwWB8&%$#@"
#define PALETTE " .,~^/\\:!c|(<VXL8*#&"

// Colors
// ref: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main (int argc, char ** argv)
{
    if (argc != 3) {
        printf("usage: %s path_to_image_file widthxheight\n", argv[0]);
        return 1;
    }

    nimg::Pixmap img;
    nimg::io::load::image(argv[1], img);

    int w, h;
    sscanf(argv[2], "%dx%d", &w, &h);

    for (size_t y = 0; y < h; ++y) {
        for (size_t x = 0; x < w; ++x) {
            float u = x / (float)w
                , v = y / (float)h;
            nimg::ColorRGBAf c = nimg::sample::bilinear(img, u, v);
            float res = nimg::eval::luminance(c);

            size_t l = strlen(PALETTE);

            const char *p = PALETTE + int(l * res);
            printf("%c", *p);
        }
        printf("\n");
    }

    return 0;
}
