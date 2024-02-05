/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exceve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rfinneru <rfinneru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/05 11:59:00 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/02/05 13:43:29 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

int main() {
    // Specify the path to your program executable
    char *programPath = "builtins/echo";

    // Arguments for the new program (first argument is usually the program name)
    char *args[] = {programPath, "echo", "test", NULL};

    // Environment variables (you can pass the current environment or customize it)
    char *env[] = {NULL};


    printf("%s, %s, %s\n", programPath, args[1], args[2]);        
    // Execute the new program
    execve(programPath, args, NULL);

    // If execve() fails, it will return only if there is an error
    perror("execve");
    return 1;
}
