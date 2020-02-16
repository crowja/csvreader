/**
 *  @file csvreader.h
 *  @version 0.2.0-dev0
 *  @date Sun Feb 16, 2020 04:31:33 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef CSVREADER_H
#define CSVREADER_H

struct csvreader;

/**
 *  @brief Create and return a new csvreader object.
 *  @details FIXME longer description here ...
 */
struct csvreader *csvreader_new(char *fname);

/**
 *  @brief Clean up and free a csvreader structure.
 *  @details FIXME longer description here ...
 */
void        csvreader_free(struct csvreader **pp);

/**
 *  @brief Initialize a csvreader object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a csvreader object
 *  @param x FIXME
 */
int         csvreader_init(struct csvreader *p, void *x);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */
const char *csvreader_version(void);

int         csvreader_next(struct csvreader *p, unsigned *n, char ***cpp);

#endif
