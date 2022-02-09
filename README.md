# minishell
As beautiful as a shell


## Introduction 🤔

The objective of this project is to create a simple shell and learn a lot about processes and file descriptors

Minishell is 42's second largest project. It's a minimum viable version of a real shell. The main objective is to have a good understanding of creating and synchronizing processes using the C programming language.


## Installation & Usage ❕

1. Download/Clone this repo

        git clone https://github.com/kazuumaVII/cub_3d.git
2. `cd` into the root directory and run `make`

        cd cub_3d
        make

3. After building the source `./test` from the project root.


## Mandatory  🌐

key  | function |
---|------|
left/right arrow or `q`/`e`| turn				|
`w` `a` `s` `d` | move					|

you may edit all these settings:

resolution, ceiling and floor colors (range 0 - 255), walls and sprite textures, map. The map must be sorrounded by walls(1) and have the initial player position and direction (W- west, E- east, N-north, S-south)

```
R 1280 720

C 92, 148, 252
F 128, 208, 15

WE ./textures/walls/mario_1.XPM
EA ./textures/walls/mario_4.XPM
NO ./textures/walls/mario_2.XPM
SO ./textures/walls/mario_3.XPM
S ./textures/sprites/mario.XPM

11111111111111111111111
100S0010000100010000111
11000000000000000000111
10000000011111000000011
10020000000000000001111
10000010000000000111111
11102011000100000000011
10000011000100002000001
11000001000100000000111
11000020010110200011111
11011000001110002000111
11111111111111111111111
```

## Builtins implemented  🔨

command | description  |
---|------|
**echo** | echo the STRING(s) to standart output. **-n** flag: do not output the trailing newline |
**cd** | change the shell working directory	(with a relative or absolute path)|
**pwd** | print name of current/working directory	|
**export** | set export attribute for shell variables | 
**unset** | unset values of shell variables |
**env** | print the environment	| 
**exit** | cause the shell to exit with the exit status specified	| 


## Final grade : 100/115 ✅
Mandatory part : 100/100

Bonus : 0/15
