#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libasm.h"

#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"

void test_strlen(void) {
    printf("=== TEST FT_STRLEN ===\n");
    const char *tests[] = {"Hello World!", "", "42", "Un texte un peu plus long...", NULL};
    for (int i = 0; tests[i]; i++) {
        size_t sys = strlen(tests[i]);
        size_t my  = ft_strlen(tests[i]);
        printf("Str: \"%s\"\n -> Standard: %zu | Libasm: %zu [%s]\n", 
               tests[i], sys, my, (sys == my) ? GREEN "OK" RESET : RED "FAIL" RESET);
    }
    printf("\n");
}

void test_strcpy(void) {
    printf("=== TEST FT_STRCPY ===\n");
    char src[] = "Hello 42!";
    char dst_sys[50];
    char dst_my[50];

    strcpy(dst_sys, src);
    ft_strcpy(dst_my, src);
    printf("Resultat: \"%s\" [%s]\n\n", 
           dst_my, (strcmp(dst_sys, dst_my) == 0) ? GREEN "OK" RESET : RED "FAIL" RESET);
}

void test_strcmp(void) {
    printf("=== TEST FT_STRCMP ===\n");
    char *s1[] = {"Hello", "Hello", "Bonjour", "", "ABC", NULL};
    char *s2[] = {"Hello", "World", "Bon",     "", "ABD", NULL};

    for (int i = 0; s1[i]; i++) {
        int sys = strcmp(s1[i], s2[i]);
        int my  = ft_strcmp(s1[i], s2[i]);
        // Compare le signe des valeurs de retour (strcmp peut renvoyer n'importe quelle diff)
        int ok = (sys == my) || (sys < 0 && my < 0) || (sys > 0 && my > 0);
        printf("s1: \"%s\" | s2: \"%s\"\n -> Standard: %d | Libasm: %d [%s]\n",
               s1[i], s2[i], sys, my, ok ? GREEN "OK" RESET : RED "FAIL" RESET);
    }
    printf("\n");
}

void test_write(void) {
    printf("=== TEST FT_WRITE ===\n");
    
    // 1. Test ecriture valide
    printf("Standard : ");
    fflush(stdout);
    ssize_t sys = write(1, "Test 123\n", 9);
    printf("Libasm   : ");
    fflush(stdout);
    ssize_t my  = ft_write(1, "Test 123\n", 9);
    printf(" -> Return sys: %zd | my: %zd [%s]\n", sys, my, (sys == my) ? GREEN "OK" RESET : RED "FAIL" RESET);

    // 2. Test erreur FD invalide
    errno = 0;
    sys = write(-1, "test", 4);
    int sys_err = errno;

    errno = 0;
    my = ft_write(-1, "test", 4);
    int my_err = errno;

    printf("FD Invalide (-1):\n -> Return sys: %zd (errno %d: %s)\n -> Return my : %zd (errno %d: %s) [%s]\n\n",
           sys, sys_err, strerror(sys_err), my, my_err, strerror(my_err),
           (sys == my && sys_err == my_err) ? GREEN "OK" RESET : RED "FAIL" RESET);
}

void test_read(void) {
    printf("=== TEST FT_READ ===\n");
    char buf1[100] = {0};
    char buf2[100] = {0};

    // 1. Lecture depuis /dev/urandom ou fichier temporaire
    int fd = open("/etc/issue", O_RDONLY);
    if (fd > 0) {
        ssize_t sys = read(fd, buf1, 20);
        close(fd);

        fd = open("/etc/issue", O_RDONLY);
        ssize_t my = ft_read(fd, buf2, 20);
        close(fd);

        printf("Lecture fichier:\n -> Sys: %zd octets (\"%.10s...\")\n -> My : %zd octets (\"%.10s...\") [%s]\n",
               sys, buf1, my, buf2, (sys == my && memcmp(buf1, buf2, sys) == 0) ? GREEN "OK" RESET : RED "FAIL" RESET);
    }

    // 2. Test Erreur (FD invalide)
    errno = 0;
    ssize_t sys_err_ret = read(-1, buf1, 10);
    int sys_err = errno;

    errno = 0;
    ssize_t my_err_ret = ft_read(-1, buf2, 10);
    int my_err = errno;

    printf("FD Invalide (-1):\n -> Return sys: %zd (errno %d)\n -> Return my : %zd (errno %d) [%s]\n\n",
           sys_err_ret, sys_err, my_err_ret, my_err,
           (sys_err_ret == my_err_ret && sys_err == my_err) ? GREEN "OK" RESET : RED "FAIL" RESET);
}

void test_strdup(void) {
    printf("=== TEST FT_STRDUP ===\n");
    const char *str = "Tester strdup en assembly!";

    char *sys = strdup(str);
    char *my  = ft_strdup(str);

    printf("Original : \"%s\"\n", str);
    printf("Standard : \"%s\"\n", sys);
    printf("Libasm   : \"%s\" [%s]\n\n", my, (strcmp(sys, my) == 0) ? GREEN "OK" RESET : RED "FAIL" RESET);

    free(sys);
    free(my);
}

int main(void) {
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    return 0;
}