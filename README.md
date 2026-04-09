*This project has been created as part of the 42 curriculum by betferna*

# get_next_line - @42

## Description
get_next_line is a function that reads a file line using a file descriptor. Each invocation of the function reads the next line from the file, allowing you to process the entire file content one line at a time.

## Prototype
char *get_next_line(int fd);
---

## Instructions
To use the function in your code, simply include its header:
`#include "get_next_line.h"`

### Compilation
The project must be compiled using `cc` with the flags `-Wall -Wextra -Werror` and -D BUFFER_SIZE=n to set up the buffer size. 

| Rule | Description |
| :--- | :--- |
| `make` | Compiles the mandatory part and creates `get_next-line.a`. |
| `make clean` | Removes all object files (`.o`). |
| `make fclean` | Removes object files. |
| `make re` | Performs a full recompilation (`fclean` + `all`). |

---
### Technical Considerations
* **Memory Management:** All heap-allocated memory is properly freed to ensure no leaks.
* **The Norm:** All code complies with the 42 School coding standard.

## Resources 
* **[Deepwiki / get_next_line reading utility](https://deepwiki.com/tdanielsousa/42School/4.2.1-get_next_line:-file-reading-utility)** .

* **[Man7 / read() man](https://www.man7.org/linux/man-pages/man2/read.2.html)** .
