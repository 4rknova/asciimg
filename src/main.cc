#include <cstdio>
#include <nimg/pixmap.h>
#include <nimg/color.h>
#include <nimg/sample.h>
#include <nimg/luminance.h>
#include <nimg/img.h>

static const char ascii_glyphs[] = {
    ' ', '.', ',', ':', ';', 'i', 't', '%', 'X', '$', '@', '#'
};

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

            size_t l = sizeof(ascii_glyphs);

            const char *p = ascii_glyphs + int(l * res);
            printf("%c", *p);
        }
        printf("\n");
    }

    return 0;
}
