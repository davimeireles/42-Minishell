#!/bin/bash

# Nome do arquivo com os comandos
test_file="test_commands.txt"

# Executa cada comando no arquivo
while IFS= read -r command; do
    echo "Executing command: $command"
    echo "$command" | valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline_leaks ./minishell
done < "$test_file"
