*This project has been created as part
of the 42 curriculum by erocha--*

# Pipex

![Norm_pass](https://img.shields.io/badge/Norm-Passed-green)
![Score](https://img.shields.io/badge/Score-In_Progress-green)
![Language](https://img.shields.io/badge/Language-C-blue)

### *Description*

<img src="https://flagcdn.com/16x12/gb.png" alt="GB Flag">

The Pipex project aims to deepen the understanding of UNIX mechanisms by reproducing the behavior of shell pipes in C. It involves handling file descriptors, redirection, and executing multiple commands through child processes.

<img src="https://flagcdn.com/16x12/fr.png" alt="FR Flag">

Le projet Pipex vise à approfondir la compréhension des mécanismes UNIX en reproduisant le comportement des pipes du shell en C. Il s'agit de manipuler les descripteurs de fichiers, les redirections et d'exécuter plusieurs commandes via des processus fils.

### *Instructions*

<img src="https://flagcdn.com/16x12/gb.png" alt="GB Flag">

The mandatory part must be compiled with `make`. You can then run the executable with the following syntax:  
`./pipex file1 "cmd1" "cmd2" file2`  
This is equivalent to the shell command: `< file1 cmd1 | cmd2 > file2`.

<img src="https://flagcdn.com/16x12/fr.png" alt="FR Flag">

La partie obligatoire doit être compilée avec `make`. Vous pouvez ensuite lancer l'exécutable avec la syntaxe suivante :  
`./pipex file1 "cmd1" "cmd2" file2`  
Cela équivaut à la commande shell : `< file1 cmd1 | cmd2 > file2`.

### *Resources*

<img src="https://flagcdn.com/16x12/gb.png" alt="GB Flag">

I used Google Gemini AI to understand the concepts of `fork()`, `execve()`, and how `pipe()` synchronizes communication between processes.

<img src="https://flagcdn.com/16x12/fr.png" alt="FR Flag">

J'ai utilisé l'IA de Google Gemini pour comprendre les concepts de `fork()`, `execve()`, et comment `pipe()` synchronise la communication entre les processus.