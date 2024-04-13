**newbie.c - A Simple Custom Shell Implementation**

**Purpose**

This project implements a basic command-line shell for educational purposes. It demonstrates core concepts in C programming, including:

* **Standard input/output handling** 
* **Dynamic memory allocation** (malloc, realloc)
* **String manipulation**
* **Process creation and management** (fork, execvp, wait) 

**Features**

* **Customizable Prompt:** Displays the username as part of the shell prompt.
* **Command Execution:** Executes system commands entered by the user.
* **Graceful Exit:** Handles 'quit' and 'exit' commands to terminate the shell.

**How to Use**

1. **Compile the code:**
   ```bash
   gcc newbie.c -o newbie 
   ```
2. **Run the executable:**
   ```bash
   ./newbie 
   ```

**Example Interaction**

```
newbie@linuxuser >$ ls -a
.    ..   newbie  newbie.c  README.md
newbie@linuxuser >$ date
Sun Apr 14 09:56:10 IST 2024
newbie@linuxuser >$ exit
Thank You for Using newbie shell
```

**Understanding the Code**

* **Header Files:** Includes necessary standard libraries.
* **Global Variables:** Defines variables storing input state and username.
* **`readinput()` function:** 
   * Reads user input character by character until a space or newline is encountered.
   * Dynamically allocates memory for the input string.
* **`runcommand()` function:**
   * Creates a child process using `fork()`.
   * Executes the specified command using `execvp()`.
   * Waits for child process termination using `wait()`.
* **`main()` function:**
    * Retrieves the username from the `USER` environment variable.
    * Implements the main shell loop:
        * Displays the prompt.
        * Reads command input using `readinput()`.
        * Parses input into commands and arguments.
        * Executes commands (or handles 'quit' / 'exit').

**Notes**

* This is a simplified shell implementation and lacks features like command history, I/O redirection, and advanced argument parsing.
* Consider exploring these enhancements for additional learning.
