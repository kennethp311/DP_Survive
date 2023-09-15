# Dynamic Programming Survival Game

<ins>**Project Goal:**</ins> Give a dynamic programming algorithm with a runtime of _O_(_n_<sup>2</sup>) that outputs a boolean that reports whether it is possible for the player to reach the bottom right tile without running out of HP. <br />

 ---


<ins>**Input Format:**</ins> A text file named _blank_.txt will be parsed as the second argument to your program. <br />
**(1)** First line will contain 2 integers _n_, _H_.                                     <br />
**(2)** The next _n_<sup>2</sup> - 1 lines will contain 4 integers _x_, _y_, _t_, _v_.               <br />
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

 ---

<ins>**Test a Single File:** </ins>                     <br />
**Step 1)** make _DP_Survive_                           <br />
**Step 2)** ./_DP_Survive_ _blank_.txt                  <br />

<ins>**Test Multiple Files within a Folder:** </ins>    <br />
**Step 1)** make _DP_Survive_                           <br />
**Step 2)** ./_DP_Survive_ _blank_.txt                  <br />

<ins>**Generate a Folder of Random Test Files:** </ins> <br />
**Step 1)** make _Test_File_Generator_                  <br />
**Step 2)** ./_DP_Survive_ _blank_.txt                  <br />

 ---

<ins>**How I Solved This Problem:** </ins>   <br />
I solved this problem using a dynamic programing technique called _tabulation_. By creating a _n_ by _n_ table, I can store the greatest possible HP you can have when landing on a specific tile. First we define the base cases ie the first row and column of the grid, by comparing the health behind it and the health after landing, storing the option with the maximum HP within our table. Next we fill in the table iteratively (starting from the base cases and ending to (_n_ - 1 , _n_ - 1)), by comparing the options that are to the left or above the current tile position, storing the option that has the maximum HP withen our table. Finally, we can check the health value that was stored in the our table at the last (_n_ - 1 , _n_ - 1) position. Returning 1 if our HP _H_ is greater than or equal to 0, otherwise returning 0. Therefore, I would essentially check every possible path such that it results with the greatest HP. 

The complicated aspect of this project, results from having a protection/multiplier tile. Due to rule that the player can decide when to use a protection/multiplier tile, it increases the number of possibilities a player can play the game. For example, a player can use a protection token to avoid damage, but they could've saved it later on when the future damage tile's value were much higher. In order to check every possiblities, I have created separate Tables each for storing the maximum health when saving a Protection/Multiplier Token or both Tokens. Hence suppose table _P_ holds the maximum health at tile (_i_ , _j_) while saving the Protection Token, while our main table _T_ holds the maximum health at tile (_i_ , _j_) while using the Protection Token (assuming we land on a damage tile). Therefore, we can compare these tables values and store the greatest health within the main table _T_. 
