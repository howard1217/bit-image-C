/*
 * PROJ1-1: YOUR TASK B CODE HERE
 * 
 * Feel free to define additional helper functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include "sparsify.h"
#include "utils.h"

/* Returns a NULL-terminated list of Row structs, each containing a NULL-terminated list of Elem structs.
 * See sparsify.h for descriptions of the Row/Elem structs.
 * Each Elem corresponds to an entry in dense_matrix whose value is not 255 (white).
 * This function can return NULL if the dense_matrix is entirely white.
 */
Row *dense_to_sparse(unsigned char *dense_matrix, int width, int height) {
    /* YOUR CODE HERE */
    int index = 0;
    Row* root = NULL;
    Row* currRow = NULL;
    Elem* curr = NULL;
    int positionOnRow = 0;
    int rowCount = 0;
    while (rowCount * width + positionOnRow < width * height) {
        Elem* head = NULL;
        while (positionOnRow < width) {
            if (dense_matrix[rowCount * width + positionOnRow] != 255) {
                Elem* tempElem = malloc(sizeof(Elem));
		if (!tempElem) allocation_failed();
                tempElem->x = positionOnRow;
                tempElem->value = dense_matrix[rowCount * width + positionOnRow];
                tempElem->next = NULL;
                if (head == NULL) {
                    head = tempElem;
                    curr = tempElem;
                } else {
                    curr->next = tempElem;
                    curr = curr->next;
                }
            }
            positionOnRow++;
        }
        positionOnRow = 0;
        if (head != NULL) {
            Row* tempRow = malloc(sizeof(Row));
	    if (!tempRow) allocation_failed();
            tempRow->y = rowCount;
            tempRow->elems = head;
            tempRow->next = NULL;
            if (root == NULL) {
                root = tempRow;
                currRow = tempRow;
            } else {
                currRow->next = tempRow;
                currRow = tempRow;
            }
        }
        rowCount++;
    }
    return root;
}

/* Frees all memory associated with SPARSE. SPARSE may be NULL. */
void free_sparse(Row *sparse) {
    /* YOUR CODE HERE */
    if (sparse == NULL) {
	return;
    }
    Row* prevRow = sparse;
    Row* currRow = prevRow->next;
    while (prevRow != NULL) {
        Elem* prevElem = prevRow->elems;
        Elem* currElem;
        while (prevElem != NULL) {
	    currElem = prevElem->next;
	    free(prevElem);
	    prevElem = currElem;
        }
        free(prevRow);
        prevRow = currRow;
	if (prevRow != NULL) {
	    currRow = prevRow->next;
	}
    }
}

