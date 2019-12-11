/**
 *  @file csvreader.h
 *  @version 0.0.2-dev0
 *  @date Fri Dec  6 22:26:40 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
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
