/*
 * MISRA C:2012 Chapter 22 - Resources - GOOD examples.
 *
 * These examples necessarily use <stdio.h> and <stdlib.h>, which Rules
 * 21.3 and 21.6 forbid. A project that uses them needs a documented
 * deviation from those rules; Chapter 22 then governs HOW they are used.
 */
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "misra_examples.h"

/* === Rule 22.1 === */
/* Every resource obtained is released on every path. */
static bool r22_1(void)
{
    bool ok = false;
    FILE *fp = tmpfile();
    if (fp != NULL)
    {
        ok = (fputs("hello\n", fp) >= 0);
        if (fclose(fp) != 0)
        {
            ok = false;
        }
    }
    return ok;
}

/* === Rule 22.2 === */
/* Free only what malloc returned, exactly once, then forget the pointer. */
static void r22_2(void)
{
    int32_t *heap = malloc(sizeof(int32_t));
    if (heap != NULL)
    {
        *heap = 1;
        free(heap);
        heap = NULL;
    }
}

/* === Rule 22.3 === */
/* One stream, opened for update ("w+"), for both reading and writing. */
static int32_t r22_3(void)
{
    int32_t ch = EOF;
    FILE *fp = tmpfile();           /* tmpfile opens in "wb+" mode */
    if (fp != NULL)
    {
        (void)fputc('x', fp);
        rewind(fp);
        ch = fgetc(fp);
        (void)fclose(fp);
    }
    return ch;
}

/* === Rule 22.4 === */
/* Open with a mode that matches what you do with the stream. */
static bool r22_4(void)
{
    bool ok = false;
    FILE *fp = tmpfile();           /* opened for writing */
    if (fp != NULL)
    {
        ok = (fputs("new setting\n", fp) >= 0);
        (void)fclose(fp);
    }
    return ok;
}

/* === Rule 22.5 === */
/* A FILE pointer is only ever passed to library functions. */
static bool r22_5(FILE *fp)
{
    return ferror(fp) == 0;
}

/* === Rule 22.6 === */
/* After fclose, set the pointer to NULL so it cannot be reused. */
static void r22_6(void)
{
    FILE *fp = tmpfile();
    if (fp != NULL)
    {
        (void)fputs("in time\n", fp);
        (void)fclose(fp);
        fp = NULL;
    }
}

/* === Rule 22.7 === */
/* Keep the result of fgetc in an int and compare it with EOF directly. */
static int32_t r22_7(FILE *fp)
{
    int32_t count = 0;
    int ch = fgetc(fp);
    while (ch != EOF)
    {
        count++;
        ch = fgetc(fp);
    }
    return count;
}

/* === Rule 22.8 === */
/* === Rule 22.9 === */
/* Clear errno immediately before the call, test it immediately after. */
static bool r22_8_9(const char *text, long *out)
{
    bool ok;
    errno = 0;
    *out = strtol(text, NULL, 10);
    ok = (errno == 0);
    return ok;
}

/* === Rule 22.10 === */
/* errno is tested only after functions documented to set it (strtol,
 * strtoul, ftell, fgetpos, fsetpos, ...). fopen reports failure through
 * its return value, so test that instead. */
static bool r22_10(void)
{
    bool opened = false;
    FILE *fp = tmpfile();
    if (fp != NULL)
    {
        opened = true;
        (void)fclose(fp);
    }
    return opened;
}

void r22_good(void)
{
    long value = 0;
    FILE *fp = tmpfile();
    (void)r22_1();
    r22_2();
    (void)r22_3();
    (void)r22_4();
    r22_6();
    if (fp != NULL)
    {
        (void)r22_5(fp);
        (void)r22_7(fp);
        (void)fclose(fp);
    }
    (void)r22_8_9("12", &value);
    (void)r22_10();
}
