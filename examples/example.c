/*
 * Copyright (c) 2010 Entertaining Software, Inc.
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
 */

/* Prints "Uno! Due! Tre!" (Italian for "One! Two! Three!") to the terminal. */

#include <dynarray.h>

int
main (int argc, char **argv)
{
  DYNA_DECLARE (char *, my_string_array);
  DYNA_INIT (my_string_array, char *);

  DYNA_ADD (my_string_array, "Uno!");
  DYNA_ADD (my_string_array, "Due!");
  DYNA_ADD (my_string_array, "Tre!");

  printf ("%s %s %s\n", DYNA_GET (my_string_array, 0),
	  DYNA_GET (my_string_array, 1), DYNA_GET (my_string_array, 2));

  DYNA_REMOVE_ALL (my_string_array);

  return 0;
}

/* vim: ts=8 sts=2 sw=2 noet: */
