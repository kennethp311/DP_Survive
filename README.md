# Dynamic Programming Survival Game

<ins>**Project Goal:**</ins> Give a dynamic programming algorithm with a runtime of _O_(n<sup>2</sup>) that outputs a boolean that reports whether it is possible for the player to reach the bottom right tile without running out of HP. <br />

 ---


<ins>**Input Format:**</ins> A text file named _blank_.txt will be parsed as the second argument to your program. <br />
**(1)** First line will contain 2 integers _n_, _H_.                                     <br />
**(2)** The next n<sup>2</sup> - 1 lines will contain 4 integers _x_, _y_, _t_, _v_.               <br />
**(3)** (_x_ , _y_) = tile location, _t_ = tile type, _v_ = value of tile otherwise 0.   <br /> 

<ins>**Output Format:**</ins> A text file named _blank_out_.txt, which will contain a single integer; 1 if its possible to survive/win the game and 0 otherwise.        <br />

 ---


<ins>**Game Description:** </ins> <br />
You are playing a 2D dungeon crawler game called "_DP Survive_". The game is played on an _n_ by _n_ grid, where you start on the top left tile (0,0). Your goal is to reach the bottom right tile (_n_ - 1 , _n_ - 1) without dying. <br />

<ins>**Game Rules:** </ins> <br />
**(1)** The game is over if the player's health _H_ goes below 0 after moving to a tile. <br />
**(2)** Player is only able to move down and right. <br />
**(3)** The player can only hold a single protection and multipler token. <br />
**(4)** The player can hold both tokens and choose when to use them. <br />

<ins>**Types of Tiles:** </ins>  <br />
**Damage Tile** (_t_ = 0): Lose _d_ health.  <br />
**Healing Tile** (_t_ = 1): Gain _h_ health. <br />
**Protection Tile** (_t_ = 2): Receive a Protection Token, which can be used to avoid damage when landing on a Damage Tile.        <br />
**Multiplier Tile** (_t_ = 3): Receive a Multiplier Token, which can be used to gain double health when landing on a Health Tile.  <br />

