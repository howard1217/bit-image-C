/*
 * PROJ1-1: YOUR TASK A CODE HERE
 *
 * You MUST implement the calc_min_dist() function in this file.
 *
 * You do not need to implement/use the swap(), flip_horizontal(), transpose(), or rotate_ccw_90()
 * functions, but you may find them useful. Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "digit_rec.h"
#include "utils.h"
#include "limits.h"

/* Calculate the length of an array. */
int length(unsigned char *arr) {
    int counter = 0;
    while (arr[counter] != '\0') {
        counter += 1;
    }
    return counter;
}

/* Swaps the values pointed to by the pointers X and Y. */
void swap(unsigned char *x, unsigned char *y) {
    /* Optional function */
    unsigned char temp = *x;
    *x = *y;
    *y = temp;
}

/* Flips the elements of a square array ARR across the y-axis. */
void flip_horizontal(unsigned char *arr, int width) {
    /* Optional function */
    int i = 0;
    while (arr[i] != '\0') {
                int j = 0;
                for (; j < width / 2; j++) {
                swap(&arr[i + j], &arr[i + (width - 1 - j)]);
                }
                i += width;
    }
}

/* Transposes the square array ARR. */
void transpose(unsigned char *arr, int width) {
    /* Optional function */
    int i = 0;
    for (; i < width; i++) {
        int j = i;
        for(; j < width; j++) {
            swap(&arr[i * width + j], &arr[i + j * width]);
        }
    }
}

/* Rotates the square array ARR by 90 degrees counterclockwise. */
void rotate_ccw_90(unsigned char *arr, int width) {
    /* Optional function */
    flip_horizontal(arr, width);
    transpose(arr, width);
}

/* Returns the squared Euclidean distance between TEMPLATE and IMAGE. The size of IMAGE
 * is I_WIDTH * I_HEIGHT, while TEMPLATE is square with side length T_WIDTH. The template
 * image should be flipped, rotated, and translated across IMAGE.
 */
unsigned int calc_min_dist(unsigned char *image, int i_width, int i_height, 
        unsigned char *template, int t_width) {
    unsigned int min_dist = UINT_MAX;
    /* YOUR CODE HERE */
    int tempSum = 0;
    int dx = i_width - t_width + 1;
    int dy = i_height - t_width + 1;
    int x = 0; //counter for translation in x direction.
    int y = 0; //counter for translation in y direction.
    int i = 0; //counter for adding in x direction.
    int j = 0; //counter for adding in y direction.
    int r = 0; //counter for rotation.
    int f = 0; //counter for flipping.
    for (; f < 2; f++) {
        for (; r < 4; r++) {
            for (; x < dx; x++) {
                for (; y < dy; y++) {
                    for (; j < t_width; j++) {
                        for (; i < t_width; i++) {
                            int delta = labs(template[i + (j * t_width)] - image[(i + x) + (j + y) * i_width]);
                            tempSum += delta * delta;
                        }
			i = 0;
                    }
                    if (tempSum < min_dist) {
                        min_dist = tempSum;
			if (min_dist == 0) return 0;
                    }
                    j = 0;
                    tempSum = 0;
                }
                y = 0;
            }
            x = 0;
            rotate_ccw_90(template, t_width);
        }
        r = 0;
        transpose(template, t_width);
    }   
    return min_dist;
}   
