# Village_Prophecy
Game in C++ using the SFML framework.

#Game Tutorial

##Game Controls:

To close the game at ANY point press ESC.

###Normal Game Mode Controls:

Movement: 'W', 'A', 'S' and 'D' keys.

Interact with a Game Object: 'R'

###Combat Controls:

Change option: 

'W' for up.

'A' for left.

'S' for down.

'D' for right.

Confirm the current combat choice by pressing Enter.

Go back to the choice menu at anytime during your turn by pressing space.

##Game Info

###Concept
The Idea is that the player will have to survive aswell as increase the strenght of his character at the same time and become strong enough to beat the game end boss before the limited amount of in-game days run out. There are 4 kinds of diffrent areas at the writing of this tutorial, these 4 areas are called Base, Survival, Hostile and Final. 

In the Base area you as the player is (mostly) safe from harm, this is where you rest the area works as a base area for you as the player.

In the Survival area the player can gather resources used to restore health or construct a fire place used to warm the player at night.

In the Hostile area the player can grow in strenght by defeating mindless skeletons. Beware though because the closer you get to the deadline of the in-game days the stronge these skeletons becomes.

In the Final area resides the final boss of the game which the player needs to defeat to win the game. Unlike the skeletons these won't grow in strenght the further you get into the game, but they are really dangerous from start.

###Player Stats
The following image shows the players stats.

<img src="http://i.imgur.com/UtwKOEo.png"></img>

If HP reaches 0 you lose the game. 

Hunger and Mood is not implemented at the writing of this tutorial.

Stamina is used up by skills and is restored whenever the player goes to sleep. Some enemies can drain the player stamina with special attacks.

###Action Points
The following image shows the player Action Points.

<img src="http://i.imgur.com/y6mzraI.png"></img>

These carry a veary important game element, see these at the remainder of the current game day. Doing diffrent things and interacting with certain game objects will consume your AP. 

Example is that if you construct a game object using materials, for each item you add to the construction of that game object you lose 1 Action Point. Gathering a game object also consumes 1 Action Point.

When you win a battle you also lose 1 Action Point.

*IMPORTANT:* If your Action Points reaches 0 and you enter combat you will suffer from a fatigue and only do 20% of your max damage.

###Player Inventory
The following displays the players inventory. Any collected game items will be displayed in this inventory.

<img src="http://i.imgur.com/woDCU73.png"></img>

At the moment of the writing of this tutorial there is only 1 game object the player can collect and put in his inventory. That object is a log and is harvested from trees. The image also shows one of these trees.
