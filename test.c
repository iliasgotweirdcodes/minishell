# include <unistd.h>

#include <unistd.h>
#include <stdio.h>

// int main() {
//     char cwd[256];
//     if (getcwd(cwd, sizeof(cwd)) != NULL) {
//         printf("Current dir: %s\n", cwd);
//     } else {
//         perror("getcwd() error");
//     }
//     return 0;
// }


void printer(char *str)
{
    int i = 0;
    int j = 0;
    int len = 0;
    while (str[j] && (str[j] == ' ' || str[j] == '\t'))
        j++;
    while (str[j])
    {
        j++;
        len++;
    }
    //j--;
    while (str[j] && (str[j] == ' ' || str[j] == '\t'))
    {
        j--;
        len--;
    }
    printf("%d \n", len);
    //j++;
    while (i < len)
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        while  (str[i] && str[i] != ' ' && str[i] != '\t')
        {
            write (1, &str[i], 1);
            i++;
        }
        if (str[i] == '\0')
            break ;
        if (str[i + 1] && (str[i] == ' ' || str[i] == '\t'))
        {
            write (1, "   ", 3);
        }
        i++;
    }
}

int main(int ac, char **av)
{
    if (ac == 2)
        printer(av[1]);
    else
        write(1, "\n", 1);
}