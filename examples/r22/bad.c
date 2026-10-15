/*
 * MISRA C:2012 Chapter 22 - Resources - BAD examples.
 */
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "misra_examples.h"

/* === Rule 22.1 === */
/* A file opened and never closed: the handle leaks on every call. */
static void r22_1(void)
{
    FILE *fp = fopen("log.txt", "w");
    if (fp != NULL)
    {
        (void)fputs("hello\n", fp);
    }
}

/* === Rule 22.2 === */
/* Freeing memory that malloc did not return, and freeing twice. */
static void r22_2(void)
{
    int32_t local = 0;
    int32_t *heap = malloc(sizeof(int32_t));
    free(&local);                   /* not from malloc */
    free(heap);
    free(heap);                     /* double free */
}

/* === Rule 22.3 === */
/* The same file open for reading and writing on two streams: the two
 * buffers see inconsistent contents. */
static void r22_3(void)
{
    FILE *in = fopen("data.txt", "r");
    FILE *out = fopen("data.txt", "w");
    if ((in != NULL) && (out != NULL))
    {
        (void)fputc('x', out);
        (void)fgetc(in);
    }
}

/* === Rule 22.4 === */
/* Writing to a stream opened read-only. */
static void r22_4(void)
{
    FILE *fp = fopen("config.txt", "r");
    if (fp != NULL)
    {
        (void)fputs("new setting\n", fp);
        (void)fclose(fp);
    }
}

/* === Rule 22.5 === */
/* Dereferencing a FILE pointer: a copy of a FILE object is not a working
 * stream, and its layout is private to the library. */
static void r22_5(FILE *fp)
{
    FILE copy = *fp;
    (void)copy;
}

/* === Rule 22.6 === */
/* Using a stream after it has been closed. */
static void r22_6(void)
{
    FILE *fp = fopen("log.txt", "w");
    if (fp != NULL)
    {
        (void)fclose(fp);
        (void)fputs("too late\n", fp);
    }
}

/* === Rule 22.7 === */
/* EOF compared with a value that was converted first: stored in a
 * char, byte 0xFF becomes indistinguishable from EOF (or EOF is never
 * seen if char is unsigned). */
static int32_t r22_7(FILE *fp)
{
    int32_t count = 0;
    char c = (char)fgetc(fp);
    while (c != EOF)
    {
        count++;
        c = (char)fgetc(fp);
    }
    return count;
}

/* === Rule 22.8 === */
/* errno not cleared before the call: a stale error from earlier code
 * looks like a failure of strtol. */
static long r22_8(const char *text)
{
    long value = strtol(text, NULL, 10);
    if (errno != 0)
    {
        value = 0;
    }
    return value;
}

/* === Rule 22.9 === */
/* errno never checked after strtol: overflow goes unnoticed. */
static long r22_9(const char *text)
{
    errno = 0;
    return strtol(text, NULL, 10);
}

/* === Rule 22.10 === */
/* errno tested after a function that is not documented to set it
 * (fopen is not in MISRA's list of errno-setting functions). */
static int32_t r22_10(void)
{
    int32_t failed = 0;
    FILE *fp;
    errno = 0;
    fp = fopen("data.txt", "r");
    if (errno != 0)
    {
        failed = 1;
    }
    if (fp != NULL)
    {
        (void)fclose(fp);
    }
    return failed;
}

void r22_bad(void)
{
    r22_1();
    r22_2();
    r22_3();
    r22_4();
    r22_5(stdin);
    r22_6();
    (void)r22_7(stdin);
    (void)r22_8("12");
    (void)r22_9("12");
    (void)r22_10();
}
