# Archimedes' approximation of Pi - SFML test
Old code I wrote to test the SFML library for C++, uploaded here for archival purposes. Last modified October 12, 2022. This was not made with accuracy as a main objective, the focus was visualization. The code is pretty messy.
 
It asks you for a number. The left and right arrows decrease and increase it by 1, the up and down arrows multiply and divide it by 10. After pressing Enter it uses Archimedes' method of exhaustion to approximate pi. It starts with a 3-sided polygon (equilateral triangle) inside a circumscribed circle and keeps adding sides until it reaches the number you entered, showing the approximated pi value for each polygon and comparing it to the real value.

## Builds
**Windows:** Run the .exe from inside the `Windows/` folder, alongside the DLLs and the `fonts/` folder. SFML doesn't need to be installed.
**Linux (64-bit):** Go into the `Linux/` folder and run `run.sh`. Keep everything in there together. SFML doesn't need to be installed.

The `fonts/` folder needs to stay — the program loads a font from it at runtime.

## Other stuff
I also threw in two abandoned projects: an unfinished attempt at Conway's Game of Life (last edited December 17, 2022) and a Raycasting test (last edited October 13, 2022). Life got in the way and I never finished them, which I now regret.