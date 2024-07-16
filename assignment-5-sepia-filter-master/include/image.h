#ifndef IMAGE_H
#define IMAGE_H

#include <inttypes.h>

/* Pixel represention structure */
#pragma pack(push, 1)
struct pixel { uint8_t b, g, r; };
#pragma pack(pop)

/* Image represention structure */
struct image {
  uint64_t width, height;
  struct pixel* data;
};

/* Image structure initialization function.
 * ARGUMENTS:
 *   - image width:
 *       const uint64_t width;
 *   - image height:
 *       const uint64_t height;
 * RETURNS:
 *   (struct image) initializated image with allocted memory for pixels.
 */
struct image init(const uint64_t width, const uint64_t height);

/* Image copy function.
 * ARGUMENTS:
 *   - pointer to image to copy:
 *       struct image const *img;
 * RETURNS:
 *   (struct image) image copy.
 */
struct image copy(struct image const *img);

/* Image destructor function(free memory).
 * ARGUMENTS:
 *   - image to copy:
 *       struct image *img;
 * RETURNS: None.
 */
void destructor( struct image *img );


#endif /* IMAGE_H */
