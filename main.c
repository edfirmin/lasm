#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "libasm.h"

static int g_fail = 0;

#define CHECK(cond, msg) do { \
    if (cond) printf("  OK   %s\n", msg); \
    else { printf("  KO   %s\n", msg); g_fail++; } \
} while (0)

static int sign(long n) { return (n > 0) - (n < 0); }

static void test_strlen(void)
{
    const char *tests[] = {"", "a", "hello world", "42", "line\nbreak\ttab", NULL};
    printf("== ft_strlen ==\n");
    for (int i = 0; tests[i]; i++)
        CHECK(ft_strlen(tests[i]) == strlen(tests[i]), tests[i][0] ? tests[i] : "(empty)");
    char *big = malloc(100001);
    memset(big, 'x', 100000); big[100000] = 0;
    CHECK(ft_strlen(big) == 100000, "100k string");
    free(big);
}

static void test_strcpy(void)
{
    char b1[64], b2[64];
    const char *tests[] = {"", "a", "hello world", "with\ttabs\nand nl", NULL};
    printf("== ft_strcpy ==\n");
    for (int i = 0; tests[i]; i++) {
        memset(b1, 'X', 64); memset(b2, 'X', 64);
        char *r1 = ft_strcpy(b1, tests[i]);
        char *r2 = strcpy(b2, tests[i]);
        CHECK(r1 == b1 && (r2 == b2) && memcmp(b1, b2, strlen(tests[i]) + 1) == 0,
            tests[i][0] ? tests[i] : "(empty)");
    }
}

static void test_strcmp(void)
{
    struct { const char *a, *b; } t[] = {
        {"", ""}, {"a", ""}, {"", "a"}, {"abc", "abc"}, {"abc", "abd"},
        {"abd", "abc"}, {"abc", "abcd"}, {"abcd", "abc"},
        {"\x80", "a"}, {"a", "\x80"}, {"\xff", "\x01"}, {"test\x7f", "test\x80"},
    };
    printf("== ft_strcmp ==\n");
    for (unsigned i = 0; i < sizeof(t)/sizeof(*t); i++) {
        char msg[64];
        snprintf(msg, 64, "cmp(\"%s\",\"%s\") ft=%d libc=%d",
            t[i].a, t[i].b, ft_strcmp(t[i].a, t[i].b), strcmp(t[i].a, t[i].b));
        CHECK(sign(ft_strcmp(t[i].a, t[i].b)) == sign(strcmp(t[i].a, t[i].b)), msg);
    }
}

static void test_write(void)
{
    printf("== ft_write ==\n");
    int fd = open("/tmp/ft_w", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    ssize_t r = ft_write(fd, "hello", 5);
    CHECK(r == 5, "write 5 bytes returns 5");
    close(fd);
    char buf[8] = {0};
    fd = open("/tmp/ft_w", O_RDONLY);
    read(fd, buf, 8); close(fd);
    CHECK(memcmp(buf, "hello", 5) == 0, "content actually written");

    errno = 0;
    r = ft_write(-1, "x", 1);
    int e1 = errno;
    errno = 0;
    ssize_t r2 = write(-1, "x", 1);
    int e2 = errno;
    char msg[64];
    snprintf(msg, 64, "bad fd: ret %zd/%zd errno %d/%d (EBADF=%d)", r, r2, e1, e2, EBADF);
    CHECK(r == r2 && e1 == e2 && e1 == EBADF, msg);

    /* Note macOS: Le buffer NULL cause un Segfault dans la libc/Kernel. 
       On teste simplement si la taille 0 fonctionne correctement. */
    CHECK(ft_write(1, "", 0) == 0, "count 0 returns 0");
}

static void test_read(void)
{
    printf("== ft_read ==\n");
    int fd = open("/tmp/ft_w", O_RDONLY);
    char buf[8] = {0};
    ssize_t r = ft_read(fd, buf, 5);
    CHECK(r == 5 && memcmp(buf, "hello", 5) == 0, "read 5 bytes");
    r = ft_read(fd, buf, 5);
    CHECK(r == 0, "EOF returns 0");
    close(fd);

    errno = 0;
    r = ft_read(-1, buf, 5);
    int e1 = errno;
    errno = 0;
    ssize_t r2 = read(-1, buf, 5);
    int e2 = errno;
    char msg[64];
    snprintf(msg, 64, "bad fd: ret %zd/%zd errno %d/%d (EBADF=%d)", r, r2, e1, e2, EBADF);
    CHECK(r == r2 && e1 == e2 && e1 == EBADF, msg);
}

static void test_strdup(void)
{
    printf("== ft_strdup ==\n");
    const char *tests[] = {"", "a", "hello world", NULL};
    for (int i = 0; tests[i]; i++) {
        char *d = ft_strdup(tests[i]);
        CHECK(d && d != tests[i] && strcmp(d, tests[i]) == 0,
            tests[i][0] ? tests[i] : "(empty)");
        free(d);
    }
    char *big = malloc(65537);
    memset(big, 'y', 65536); big[65536] = 0;
    char *d = ft_strdup(big);
    CHECK(d && strcmp(d, big) == 0, "64k string dup + free");
    free(d); free(big);
}

int main(void)
{
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    printf("\n%s (%d fail)\n", g_fail ? "SOME TESTS FAILED" : "ALL TESTS PASSED", g_fail);
    return g_fail != 0;
}