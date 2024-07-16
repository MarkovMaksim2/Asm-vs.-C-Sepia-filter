#ifndef BMP_HANDLE_H
#define BMP_HANDLE_H

#include "image.h"
#include  <stdint.h>
#include <stdio.h>

/* Statuses of reading bmp file information */
enum read_status  {
  READ_OK = 0,                   /* if everything is ok */
  READ_INVALID_SIGNATURE,        /* if bmp signature is not 0x4d42 */
  READ_INVALID_BITS,             /* if unable to read pixel bits */
  READ_INVALID_HEADER,           /* if header is invalid */
  READ_INVALID_MEMORY_ALLOCATION /* if is not availiable to allocate memory for image */
};

/* Reading image data from bmp file function.
 * ARGUMENTS:
 *   - file to read from pointer:
 *       FILE* in;
 *   - image to read data from file:
 *       struct image* img;
 * RETURNS:
 *   (read_status) status of reading data from bmp file.
 */
enum read_status from_bmp( FILE* in, struct image* img );

/* Printing read status to stdin/stderr function.
 * ARGUMENTS:
 *   - read status:
 *       const enum read_status st;
 * RETURNS: None.
 */
void print_read_status(const enum read_status st);

/* Statuses of writing bmp file information */
enum write_status  {
  WRITE_OK = 0,       /* if everything ok */
  WRITE_ERROR_HEADER, /* if unable to write header */
  WRITE_ERROR_BITS    /* if unable to write pixel bits */
};

/* Writing image data to bmp file function.
 * ARGUMENTS:
 *   - file to write in pointer:
 *       FILE* in;
 *   - image to write data to file:
 *       struct image* img;
 * RETURNS:
 *   (write_status) status of writing data to bmp file.
 */
enum write_status to_bmp( FILE* out, struct image const* img );

/* Printing write status to stdin/stderr function.
 * ARGUMENTS:
 *   - read status:
 *       const enum write_status st;
 * RETURNS: None.
 */
void print_write_status(const enum write_status st);

#endif /* BMP_HANDLE_H */
