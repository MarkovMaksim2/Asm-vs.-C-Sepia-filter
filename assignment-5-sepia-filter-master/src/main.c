#include "../include/bmp_handle.h"
#include "../include/filters.h"
#include <stdio.h>
#include <time.h>

/* Calculating int value by string function.
 * ARGUMENTS:
 *   - number of arguments:
 *       int argc;
 *   - arguments array:
 *       char **array
 * RETURNS:
 *   (int) program code.
 */
int main( int argc, char** argv ) {
    FILE* in, *out;
    struct image img, img1;
    enum read_status rst;
    enum write_status wst;
    clock_t exec_start_c, exec_start_asm, exec_end_c, exec_end_asm;

    if (argc != 4) {
        fprintf(stderr, "There must be 3 arguments, you have %d arguments\n", argc - 1);
        return 0;
    }

    /* reading data from file */
    if ((in = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", argv[1]);
        return 0;
    }

    rst = from_bmp(in, &img);
    fclose(in);

    print_read_status(rst);
    if (rst != READ_OK) {
        return 0;
    }

    img1 = copy(&img);


    /* Rotating image */

    exec_start_c = clock();
    sepia(&img);
    exec_end_c = clock();

    exec_start_asm = clock();
    sepia_asm(&img1);
    exec_end_asm = clock();


    /* Writing data in file */
    if ((out = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", argv[2]);
        destructor(&img);
        return 0;
    }

    wst = to_bmp(out, &img);
    fclose(out);

    print_write_status(wst);
    destructor(&img);

    if ((out = fopen(argv[3], "wb")) == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", argv[3]);
        destructor(&img1);
        return 0;
    }

    wst = to_bmp(out, &img1);
    fclose(out);

    print_write_status(wst);
    destructor(&img1);

    fprintf(stdout, "Sepia filter algorithm time on C: %f s\n", (double)(exec_end_c - exec_start_c) / CLOCKS_PER_SEC);
    fprintf(stdout, "Sepia filter algorithm time on asm: %f s\n", (double)(exec_end_asm - exec_start_asm) / CLOCKS_PER_SEC);

    return 0;
} /* end of 'main' function */
