# Minesweeper-Assembly
A minesweeper game written in 16-bit assembly. Compiled with NASM. Runs on DOS.

The project is abandoned. I've released the source in the hopes that it will help others how to make a game in assembly.

![Screenshot1](https://github.com/accidentalrebel/minesweeper-assembly/blob/master/images/screenshot1.png)

![Screenshot2](https://github.com/accidentalrebel/minesweeper-assembly/blob/master/images/screenshot2.png)

## Implemented features
+ Debug functions - Contains simple but handy functions for debbuging. Can log single characters and can do assertions.
+ Random number generation - Uses Xorshift algorithm. Can generate a random number from 0 to 65534. Also has helper functions to generate a value from within a range or a random percentage.
+ Cursor functions - Contains helper functions to place and move the text cursor on the screen.
+ Board setup - The game sets up the board by drawing it and adding bombs randomly on it.

## How to Run
The shell script `build_and_run.sh' does the building and running using [DOS-Box](https://www.dosbox.com/). You may be able to run the game using other emulators but I haven't tested them yet.

## Testing
I've implemented unit tests on most of the code. Test functions have names with a "test" prefix. Call these to see if your changes broke anything.

## Answers to questions you may have

### Why assembly?
I started this project because I missed coding in Assembly. I really like how there's little to no abstraction when coding in Assembly unlike with higher level languages. The programmer is in complete control and I like it very much.

### Then why abandon the project?
There came a point when things became tedious. I know how to implement what I had in mind but thinking about the hoops I'd have to do to do to get it done made me realize the hard truth as to why people don't make games in Assembly anymore. The more you want to add, the more unwieldy the codebase becomes.

### Why 16-bit?
I wanted a challenge so I restricted myself to having less registers. I've also read that older DOS games were made in 16-bit assembly.

### Why DOS?
I have a good amount of experience with DOS interrupts thanks to my previous Assembly game, [SudokuBoy](https://github.com/accidentalrebel/SudokuBoy). It has a limited API but you can already do a lot with it.

### Why NASM?
It is the most widely used assembler I've seen lately. One big reason I chose this is because there's a [nasm-mode](https://github.com/skeeto/nasm-mode) Emacs package that handles syntax-highlighting and automatic indentation. With this I didn't need to install a different editor for writing assembly.

### Powerkit?
My plan was to build the game engine along with the game so I could use it again in future assembly projects. Powerkit is the name I give to all my internal game engines.

### How does the random generation work?
The random number generator requires a seed. For this project I made use of the system time for the first seed. I then use the output of the first seed as the input for the next number generation, and then that for the next, and so on.

### Why Xorshift algorithm for random generation?
Xorshift is the easiest to implement especially because I've restricted myself to using 16-bit registers. Read more about it here: https://en.wikipedia.org/wiki/Xorshift

### Why text-mode? Why not VGA?
Because I like how text-mode graphics look and because it's easier to implement than VGA.

## References
+ [INT 21h Reference](spike.scu.edu.au/~barry/interrupts.html) - MS DOS API
+ [INT 10h Reference](http://stanislavs.org/helppc/int_10.html) - Video BIOS Services
+ [The Zen of Assembly](http://www.jagregory.com/abrash-zen-of-asm/#introduction-pushing-the-envelope) - The book that reignited my interest with Assembly. Targeted for advanced users.
+ [ASM tutorial](https://github.com/0xAX/asm) - A good introductory tutorial to assembly
+ [SokobanDOS](https://github.com/adamsmasher/sokobanDOS/tree/master/lesson1) - Another good tutorial. Gave me the idea to target 16-bit DOS specifically.

