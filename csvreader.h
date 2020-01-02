/**
 *  @file csvreader.h
 *  @version 0.1.0-dev0
 *  @date Wed Jan  1 21:33:23 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef _CSVREADER_H_
#define _CSVREADER_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "csvreader"

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
