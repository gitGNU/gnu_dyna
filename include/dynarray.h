/**
 * @file
 * @author Luiji Maryo <luiji@users.sourceforge.net>
 * @version 0.0.0b
 *
 * @section LICENSE
 *
 * Copyright (c) 2010-2011 Entertaining Software, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * Macros to create and manipulate dynamically resizing arrays. It includes
 * functions to add, insert, and remove elements from the array and has
 * functions for properly maintaining lists of pointers (i.e. deallocating the
 * pointers when they are removed from the array).
 */

#ifndef DYNARRAY_H
#define DYNARRAY_H

/** Major version. */
#define DYNA_VERSION_MAJOR 0
/** Minor version. */
#define DYNA_VERSION_MINOR 0
/** Build/release version. */
#define DYNA_VERSION_BUILD 0
/** Release status ([a]lpha, [b]eta, [p]roduction). */
#define DYNA_VERSION_STATUS 'b'
/** Combined version of the previous into a string. */
#define DYNA_VERSION "0.0.0b"

/** Copyright string. */
#define DYNA_COPYRIGHT "Copyright (C) 2010-2011 Entertaining Software, Inc."

/**
 * Allocate a chunk of memory.
 *
 * Define DYNA_MALLOC before including dynarray.h in order to use an allocation
 * function other then C's standard malloc(). If DYNA_MALLOC is not declared,
 * malloc.h will be automatically included.
 *
 * @param SIZE  the size of the memory chunk to allocate
 */
#ifndef DYNA_MALLOC
# include <malloc.h>
# define DYNA_MALLOC(SIZE) malloc (SIZE);
#endif

/**
 * Allocate or resize a chunk of memory.
 *
 * Define DYNA_REALLOC before including dynarray.h in order to use an allocation
 * function other then C's standard realloc(). If DYNA_REALLOC is not declared,
 * malloc.h will be automatically included.
 *
 * @param POINTER  the pointer to the memory to resize
 * @param SIZE     the new size for the memory chunk
 */
#ifndef DYNA_REALLOC
# include <malloc.h>
# define DYNA_REALLOC(POINTER, SIZE) realloc (POINTER, SIZE);
#endif

/**
 * Deallocate a chunk of memory.
 *
 * Define DYNA_FREE before including dynarray.h in order to use an deallocation
 * function other then C's standard free(). If DYNA_FREE is not declared,
 * malloc.h will be automatically included.
 *
 * @param POINTER  the pointer to the memory to deallocate
 */
#ifndef DYNA_FREE
# include <malloc.h>
# define DYNA_FREE(POINTER) free (POINTER);
#endif

/**
 * Declare a new array that accepts elements of the specified type. Afterwards
 * you must call DYNA_INIT to initialize the array.
 *
 * @param TYPE  the type that the array will hold
 * @param NAME  the name for the array
 */
#define DYNA_DECLARE(TYPE, NAME) \
	struct \
	{ \
	  size_t block_size; \
	  int count; \
	  TYPE *array; \
	} *NAME;

/**
 * Same as DYNA_DECLARE but with the variables declared with the static
 * keyword.
 */
#define DYNA_DECLARE_STATIC(TYPE, NAME) \
	static struct \
	{ \
	  size_t block_size; \
	  int count; \
	  TYPE *array; \
	} *NAME;

/**
 * Initialize a DynArray.
 *
 * @b WARNING: Do @b NOT pass different values to DYNA_DECLARE or
 * DYNA_DECLARE_STATIC and the corrosponding DYNA_INIT calls. It may result in
 * seroius errors that may not be caught at compile-time.
 *
 * @param TYPE   the same type that you passed to DYNA_DECLARE or
 *               DYNA_DECLARE_STATIC
 * @param ARRAY  the array to initialize
 */
#define DYNA_INIT(TYPE, ARRAY) \
	{ \
	  struct \
	  { \
	    size_t block_size; \
	    int count; \
	    void *array; \
	  } voidarray; \
	  ARRAY = DYNA_MALLOC (sizeof (voidarray)); \
	  ARRAY->block_size = sizeof (TYPE); \
	  ARRAY->count = 0; \
	  ARRAY->array = DYNA_MALLOC (ARRAY->block_size); \
	}

/**
 * Uninitialize the specified array.
 *
 * @b WARNING: If this is an array of pointers, you should use call
 * DYNA_DELETE_ALL first to unallocate all of the memory chunks pointed to by
 * the array.
 */
#define DYNA_UNINIT(ARRAY) \
	{ \
	  DYNA_FREE (ARRAY->array); \
	  DYNA_FREE (ARRAY); \
	}

/**
 * Get a value from a dynamic array.
 *
 * @param ARRAY  the name of the array that has the value you want
 * @param INDEX  the index of the value you want
 *
 * @returns the value you requested
 */
#define DYNA_GET(ARRAY, INDEX) ARRAY->array[INDEX]

/**
 * Set a value in a dynamic array.
 *
 * @param ARRAY  the name of the array to manipulate
 * @param INDEX  the index in the array to manipulate
 * @param VALUE  the new value for the specified index in the array
 */
#define DYNA_SET(ARRAY, INDEX) \
	{ \
	  ARRAY->array[INDEX] = VALUE; \
	}

/**
 * Add the specified element to the array. Note: If you are passing a pointer,
 * the array will contain a pointer to the same block of memory. This means that
 * deallocating the memory that you pass to DYNA_ADD will also effect the array
 * that you added the element to.
 *
 * @param ARRAY  the name of the array to manipulate
 * @param VALUE  the value to add to the array
 */
#define DYNA_ADD(ARRAY, VALUE) \
	{ \
	  ARRAY->count++; \
	  ARRAY = DYNA_REALLOC (ARRAY, ARRAY->block_size * ARRAY->count); \
	  ARRAY->array[ARRAY->count - 1] = VALUE; \
	}

/**
 * Insert the specified element into the array. Note: If you are passing a
 * pointer, the array will contain a pointer to the same block of memory. This
 * means that deallocating the memory that you pass to DYNA_INSERT will also
 * effect the array that you inserted the element into.
 *
 * @param ARRAY  the name of the array to manipulate
 * @param INDEX  the index to insert the element at
 * @param VALUE  the value to insert into the array
 */
#define DYNA_INSERT(ARRAY, INDEX, VALUE) \
	{ \
	  ARRAY->count++; \
	  ARRAY = DYNA_REALLOC (ARRAY, ARRAY->block_size * ARRAY->count); \
	  int i; \
	  for (i = ARRAY->count - 1; i > VALUE; i--) \
	    ARRAY[i] = ARRAY[i - 1]; \
	  ARRAY->array[INDEX] = VALUE; \
	}

/**
 * Remove the specified element from the array. Note: If it is a pointer array,
 * the memory that is pointed to will @b NOT be deallocated. If it is a pointer
 * that you want to remove and you want to free the memory pointed to, use
 * DYNA_DELETE instead.
 *
 * @param ARRAY  the name of the array to manipulate
 * @param INDEX  the index of the value to remove from the array
 */
#define DYNA_REMOVE(ARRAY, INDEX) \
	{ \
	  ARRAY->count--; \
	  int i; \
	  for (i = INDEX; i < ARRAY->count; i++) \
	    ARRAY[i] = ARRAY[i + 1]; \
	  ARRAY = DYNA_REALLOC (ARRAY, ARRAY->block_size * ARRAY->count); \
	}

/**
 * Free the block of memory pointed to by the specified element in the array
 * then remove the pointer from the array (<b>for use in pointer arrays
 * only</b>).
 *
 * @param ARRAY  the name of the array to manipulate
 * @param INDEX  the index of the pointer in question
 */
#define DYNA_DELETE(ARRAY, INDEX) \
	{ \
	  DYNA_FREE (ARRAY[i]); \
	  DYNA_REMOVE (ARRAY, INDEX) \
	}

/**
 * Call DYNA_REMOVE on all of the elements of the array.
 *
 * @param ARRAY  the name of the array to manipulate
 */
#define DYNA_REMOVE_ALL(ARRAY) \
	{ \
	  DYNA_FREE (ARRAY); \
	}

/**
 * Call DYNA_DELETE on all of the elements of the array (<b>for use in pointer
 * arrays only</b>).
 *
 * @param ARRAY  the name of the array to manipulate
 */
#define DYNA_DELETE_ALL(ARRAY) \
	{ \
	  int i; \
	  for (i = 0; i < ARRAY->count; i++) \
	    DYNA_FREE (ARRAY->array[i]); \
	  ARRAY->count = 0; \
	  DYNA_UNINIT (ARRAY); \
	}

/* vim: ts=8 sts=2 sw=2 noet: */
#endif /* !DYNARRAY_H */
