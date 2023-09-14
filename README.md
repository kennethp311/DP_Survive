# Dynamic Programming Survival Game




<ins>**Game Description:** </ins> <br />
You are playing a 2D dungeon crawler game called "DP Survive". The game is played on an _n_ by _n_ grid, where you start on the top left tile. Your goal is to reach the bottom right tile without dying. 
<br />

<ins>**Game Rules:** </ins> <br />
(1) The game is over if the player's health _H_ goes below 0 after moving to a tile. <br />
(2) Player is only able to move down and right. <br />
(3) The player can only hold a single protection and multipler token. <br />
(4) The player can hold both tokens and choose when to use them. <br />

<ins>**Types of Tiles:** </ins>  <br />
Damage Tile: Lose _d_ health.  <br />
Healing Tile: Gain _h_ health. <br />
Protection Tile: Receive a Protection Token, which can be used to avoid damage when landing on a Damage Tile.        <br />
Multiplier Tile: Receive a Multiplier Token, which can be used to gain double health when landing on a Health Tile.  <br />

