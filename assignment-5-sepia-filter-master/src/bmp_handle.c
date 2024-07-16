#include "../include/bmp_handle.h"
#include <stdio.h>

#define BMP_SIGNATURE 0x4d42

/* BMP image header representation structure */
#pragma pack(push, 1)
struct /* __attribute__((packed)) */ bmp_header{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

/* Calculate image padding bytes for bmp file function.
 * ARGUMENTS:
 *   - image width:
 *       uint64_t width;
 * RETURNS:
 *   (uint8_t) number of padding bytes.
 */
uint8_t get_padding(const uint64_t width) {
    return (4 - (width * sizeof(struct pixel)) % 4) % 4;
} /* end of 'get_padding' function */

/* Reading image data from bmp file function.
 * ARGUMENTS:
 *   - file pointer:
 *       FILE* in;
 *   - image to copy data from file:
 *       struct image* img;
 * RETURNS:
 *   (read_status) status of reading data from bmp file.
 */
enum read_status from_bmp( FILE* in, struct image* img ) {
    struct bmp_header header;
    size_t i;

    /* Reading file header */
    if (!fread(&header, sizeof(struct bmp_header), 1, in)) {
        return READ_INVALID_HEADER;
    }

    if (header.bfType != BMP_SIGNATURE) {
        return READ_INVALID_SIGNATURE;
    }

    /* Creating new image */
    *img = init(header.biWidth, header.biHeight > 0 ? header.biHeight : -1 * header.biHeight);

    /* calculating file padding */
    uint8_t row_padding = get_padding(img->width);

    if (!img->data) {
        return READ_INVALID_MEMORY_ALLOCATION;
    }

    /* Reading pixels data */
    if (header.biHeight > 0) {
        for (i = 0; i < img->height; i++) {
            if (!fread(img->data + (img->height - i - 1) * img->width, sizeof(struct pixel), img->width, in)) {
                destructor(img);
                return READ_INVALID_BITS;
            }
            fseek(in, row_padding, SEEK_CUR);
        }
    }
    else {
        for (i = 0; i < img->height; i++) {
            if (!fread(img->data + i * img->width, sizeof(struct pixel), img->width, in)) {
                destructor(img);
                return READ_INVALID_BITS;
            }
            fseek(in, row_padding, SEEK_CUR);
        }
    }

    return READ_OK;
} /* end of 'from_bmp' function */

/* Writing image data to bmp file function.
 * ARGUMENTS:
 *   - file to write in pointer:
 *       FILE* in;
 *   - image to write data to file:
 *       struct image* img;
 * RETURNS:
 *   (write_status) status of writing data to bmp file.
 */
enum write_status to_bmp(FILE* out, struct image const* img) {
    size_t i, j;

    /* calculating padding */
    uint8_t row_padding = get_padding(img->width);

    /* Setting bmp header */
    struct bmp_header header;
    header.bfType = BMP_SIGNATURE;
    header.biSizeImage = (uint32_t)(img->height * (img->width * sizeof(struct pixel) + row_padding));
    header.bfileSize = (uint32_t)(sizeof(struct bmp_header) + header.biSizeImage);
    header.bfReserved = 0;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = sizeof(struct bmp_header) - 14;
    header.biWidth = (uint32_t)img->width;
    header.biHeight = (uint32_t)img->height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biXPelsPerMeter = 2835;
    header.biYPelsPerMeter = 2835;
    header.biClrUsed = 0;
    header.biClrImportant = 0;

    if (!fwrite(&header, sizeof(struct bmp_header), 1, out)) {
        return WRITE_ERROR_HEADER;
    }

    /* writing pixels */
    for (i = img->height; i > 0; i--) {
        if (!fwrite(&img->data[(i - 1) * img->width], sizeof(struct pixel), img->width, out)) {
            return WRITE_ERROR_BITS;
        }

        for (j = 0; j < row_padding; j++) {
            fputc(0, out);
        }
    }

    return WRITE_OK;
} /* end of 'to_bmp' function */

/* Printing read status to stdin/stderr function.
 * ARGUMENTS:
 *   - read status:
 *       const enum read_status st;
 * RETURNS: None.
 */
void print_read_status(const enum read_status st) {
    switch (st) {
    case READ_INVALID_SIGNATURE:
        fprintf(stderr, "BMP file invalid signature\n");
        break;
    case READ_INVALID_HEADER:
        fprintf(stderr, "Cannot BMP file header\n");
        break;
    case READ_INVALID_MEMORY_ALLOCATION:
        fprintf(stderr, "Unable to allocate memory\n");
        break;
    case READ_INVALID_BITS:
        fprintf(stderr, "Unable to read BMP pixels data\n");
        break;
    case READ_OK:
        printf("Reading data was ok\n");
        break;
    default:
        break;
    }
} /* end of 'print_read_status' function */

/* Printing write status to stdin/stderr function.
 * ARGUMENTS:
 *   - read status:
 *       const enum write_status st;
 * RETURNS: None.
 */
void print_write_status(const enum write_status st) {
    switch (st) {
    case WRITE_ERROR_HEADER:
        fprintf(stderr, "Unable to write header\n");
        break;
    case WRITE_ERROR_BITS:
        fprintf(stderr, "Unable to write pixel bit\n");
        break;
    case WRITE_OK:
        printf("Writing data was ok\n");
        break;
    default:
        break;
    }
} /* end of 'print_write_status' function */
