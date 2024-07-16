#include "filters.h"

#include <stddef.h>

extern void pixel_filter_asm(struct pixel* p);

uint8_t clamp(uint16_t value) {
    return value > 255 ? 255 : value;
}

void sepia( struct image *img ) {
    size_t i;
    uint8_t r, g, b;

    if (img == NULL) return;

    for (i = 0; i < img->width * img->height; i++) {
        r = clamp((uint16_t)(0.393 * img->data[i].r + 0.769 * img->data[i].g + 0.189 * img->data[i].b));
        g = clamp((uint16_t)(0.349 * img->data[i].r + 0.686 * img->data[i].g + 0.168 * img->data[i].b));
        b = clamp((uint16_t)(0.272 * img->data[i].r + 0.534 * img->data[i].g + 0.131 * img->data[i].b));

        img->data[i].r = r;
        img->data[i].g = g;
        img->data[i].b = b;
    }
}

void sepia_asm( struct image *img ) {
    size_t i;

    if (img == NULL) return;

    for (i = 0; i < img->width * img->height; i++) {
        pixel_filter_asm(img->data + i);
    }
}