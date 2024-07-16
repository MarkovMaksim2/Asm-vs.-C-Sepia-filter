#include "../include/image.h"
#include <stdlib.h>

/* Image structure initialization function.
 * ARGUMENTS:
 *   - image width:
 *       const uint64_t width;
 *   - image height:
 *       const uint64_t height;
 * RETURNS:
 *   (struct image) initializated image with allocted memory for pixels.
 */
struct image init(const uint64_t width, const uint64_t height) {
    return (struct image)
    {
        width,
        height,
        (struct pixel*)malloc(sizeof(struct pixel) * width * height)
    };    
} /* end of 'init' function */

/* Image copy function.
 * ARGUMENTS:
 *   - pointer to image to copy:
 *       struct image const *img;
 * RETURNS:
 *   (struct image) image copy.
 */
struct image copy(struct image const *img) {
    size_t i;
    struct image cp = init(img->width, img->height); /* allocating memory for copy */

    if (!cp.data) {
        cp.width = cp.height = 0;
        return cp;
    }

    /* Copying pixels data */
    for (i = 0; i < cp.width * cp.height; i++) {
        cp.data[i] = img->data[i];
    }

    return cp;
} /* end of 'copy' function */

/* Image destructor function(free memory).
 * ARGUMENTS:
 *   - image to copy:
 *       struct image *img;
 * RETURNS: None.
 */
void destructor( struct image *img ) {
    if (img->data) {
        free(img->data);
        img->data = NULL;
    }
} /* end of 'destructor' function */
