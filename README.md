# yet-another-board-game
## An ENGG1340/COMP2113 Project by: 
#### Jiang Zhejun 3035855868 @Sk3W3d
#### Fan Zheyu 3035845203 @LordUky

## Features to be implemented: 
 1. Choose the number of players and select the character (satisfying code requirement 3: dynamic memmory management. Each player will be created as a new instance of character object, which then satisfies code requirement 2)
 2. Randomly roll the dice to obtain Points of Energy (POE) for futher gameplay (satisfying code requirement 1)
 3. The gamemap and its background methods will be stored in a cpp file. (code requirement 2). There will be random elements generated in the game map. (code requirement 1)
 4. Game characters along with their status, abilities will be created as objects and stored in a cpp file. (code requirement 2)
 5. Gameplay logics will be stored in a cpp file. (code requirement 5 achieved through feature 3, 4, and 5)
 6. Temparary game status can be saved in an txt file and the players can resume the game. (code requirement 4)

## Game Development plan: 
 1. gamemap.cpp will be firstly developed. This cpp will generate the gamemap, and will contain the methods including gamemap output, random element generation, character position output, detect if the character is out of map. 
 2. gameplay.cpp will be then developed. This cpp will execute all gameplay logics, including creating a new game, choosing player number, playing the game, and storing and reading game status. 
 3. character.cpp will be developed lastly. This cpp will record all properties and abilities of all characters. 

## --- The following is the game detail. ---
#### The game details may change during the development process. 
## 0. Symbols in the Board Game (not finalized yet, may still change after testing)
|                     |     Symbol    |     Unicode                         |     Meaning                               |   |
|---------------------|---------------|-------------------------------------|-------------------------------------------|---|
|     walls           |     █         |     U+2588                          |     (single cell of walls)                |   |
|     Items           |     ▧         |     U+25A7                          |     mirror                                |   |
|                     |     ꁵ        |     U+A075                          |     Electric pole                         |   |
|     buffs           |     +         |     U+002B                          |     Health recovery buff                  |   |
|                     |     ▿         |     U+25BF                          |     Shield buff                           |   |
|     (Jedi) Roles    |     ꆜ        |     U+A19C                          |     Luke Skywalker                        |   |
|                     |     ꅧ        |     U+A167                          |     Han Solo                              |   |
|                     |     ꀐ        |     U+A010                          |     Obi-wan Kenobi                        |   |
|                     |     ꉩ        |     U+A269                          |     R2D2                                  |   |
|                     |     ꄬ        |     U+A12C                          |     Chewbacca                             |   |
|     (Sith) Roles    |     ꄑ        |     U+A111                          |     Darth Vader                           |   |
|                     |     ꀇ        |     U+A007                          |     Jango Fett                            |   |
|                     |     ꈳ        |     U+A233                          |     Tusken Raider                         |   |
|                     |     ꎉ, ◘     |     U+A389     U+25D8               |     Darth Maul     Darth Maul in walls    |   |
|                     |     ꐡ        |     U+A421                          |     Darth Sidious                         |   |
|     others          |     *         |     U+002A                          |     Cursor when showing dot               |   |

## 1. Introduction of the Game
### The game is a turn-based competitive game, and for the characteristic design, we had the movie Star Wars as reference. It is a simplified version of another dramatically more complicated board game called “Jedi feast”, which was designed by us in our middle schools.

## 2. Abstract
### This game is an interesting text-based multi-player turn-based competitive game, and the number of players is not limited (more than 1, of course). All the elements (map, roles, buffs, etc.) are text-basely demonstrated. During the game, the players fight individually, and their goal is to eliminate (kill) all the other players and be the final survivor. There are various of unique roles in the game, each of which has distinct names, features and abilities. Each player chose one role at the beginning of the game, and the chosen role is controlled and stands for the player during the whole game. The basic operations of the roles are move and attack, which all consume a certain amount of energy (energy is get randomly at the beginning of each round). 

## 3. Energy System
### When player-n takes his turn, a random number of points of energy (POE) is acquired by him. The possible POE acquisitions is 1-6. Doing an attack or moving one step (horizontally or vertically) consumes a certain amount of energy. The max POE that can be stored by a role is limited, and acquisitions of POE when total POE is excessing the limitation will not be counted. The POE storage limitation (Max POE) of every role is shown in section 6.

## 4. Map and Pixels
### The scene of the game is map-based, and the map is pixel-based as this is a text-based game. Any object of this game (roles, items, buffs, single cell of walls, etc.) has to be placed on one certain pixel!

## 5. (Active) Operations and related concepts
Operations are POE-based. See in section 3

### 5.1.	Move and Mass

The Mass of each role shows the POE consumption of its moving by a distance of 1 (the distance of two pixels are given by the Pythagorean theorem, rounded to one decimal place). The moving path is constructed by a line segment, and the player enter the coordinate (△x,△y) to declare his destination (the original point of the inputted coordinates in this game are always the current point of the object, not somewhere fixed on the map! 
Normally, the movement cannot pass through or stop at pixels occupied by walls.

### 5.2.	Attack and Health Point (HP)
The attacking process is when the attacker role cause damage to the attacked role. Different roles have different attacking abilities, damages, POE consumptions, and overheat. Overheat means how many times a role can apply a certain ability within one turn. They are declared in section 6. Attacked role’s health point (HP) is deducted, and a role is eliminated (killed) if its HP is not more than 0.

## 6. Roles and related items (not yet finalized, may still change after testing. )
Roles are chosen by players at the beginning of a game in one-to-one correspondence., and is not changeable during the game.

### Luke Skywalker
    Related items: N/A
    Max POE: 40
    Mass: 0.8
    HP: 480
    Ability 1 (attack): lightsaber 
        POE consumption: 12.
        Overheat: 2.
        Deals 95 damage to all enemies within distance of 5. 
        Cannot penetrate walls.

### Han Solo
    Related items: Mirror
        When Han’s attack hits a mirror, it can be reflected to any direction.
        The direction is declared by another inputs of 2-D coordinates.
        The times one single attack can be reflected is not limited.
        At most 5 mirrors are allowed to exist in the map simultaneously.
        If excessive mirrors are placed, random ones will be removed.
    Max POE: 55
    Mass: 1.
    HP: 480.
    Ability 1 (attack):
        POE consumption: 15
        Overheat: 2
        Deals 90 damage to one enemy.
        Cannot penetrate walls.
    Ability 2 (special): mirror
        POE consumption: 15
        Overheat: 2
        Han places a mirror at his current pixel.

### Obi-wan Kenobi
    Related items: N/A.
    Max POE: 60.
    Mass: 1.2.
    HP: 580.
    Ability 1 (attack): the force
        POE consumption: 7
        Overheat: 1
        Deals 70 damage to every enemy within range of 7.
        Regardless of walls.
        Obi-wan recovers HP of 50*(n-1), where n is the number of target hit by him.
    Ability 2 (special): force control
        POE consumption: 30
        Obi-wan directly get the nearest buff existing on the map.

### R2D2
    Related items: N/A
    Max POE: 30
    Mass: 0.6
    HP: 300
    Ability 1 (attack): arson
        POE consumption: 18
        Overheat: 1
        Set all entire blocks whose nearest pixel is within distance of 2 on fire.
        Deals 120 damage to all enemies in distance of 6 (nearest pixel) with the block.
    Ability 2 (special): robotic construction
        POE consumption: 2
        Overheat: 3
        R2D2 constructs wall cells on 1 empty pixel within a distance of 5.
    Ability 3 (passive): self repair
        R2D2 automatically recovers 10 HP at the beginning of its every turn.
        However the total HP of R2D2 cannot be no more than 550.

### Chewbacca
    Related items: N/A
    Max POE: 100
    Mass: 2
    HP: 800
    Ability 1 (attack): fist of fury
        POE consumption: (-8)
        Overheat: 1
        Deals 125 damage to one enemy within distance of 3.
    Ability 2 (special): roar (available only when HP not less than 180)
        POE consumption: 40
        Overheat: 1
        Pull all enemies within distance of 8 by distance of 3 (towards Chewbacca)
        Reset the POE storage of the enemies pulled.
    Ability 3 (passive): savage
        Mass becomes 0.8 when HP less than 180.

### Darth Vader
    Related items: N/A
    Max POE: 50
    Mass: 1.1
    HP: 480
    Ability 1 (attack): dark force
        POE consumption: 25
        Overheat: 2
        Push all enemies within distance of 4 away from Vader by distance of 8.
        Deals 120 damage.	
    Ability 2 (special): dark force control
        POE consumption: 10
        Overheat: 1
        Pull all enemies within distance of 10 by distance of 5 (towards Vader).

### Jango Fett
    Related items: N/A
    Max POE: 35
    Mass: 0.9
    HP: 400
    Ability 1 (attack): missile
        POE consumption: 15
        Overheat: 1
        Missile path is a polyline not longer than 12 with not more than 2 breakpoints.
        Deals 95 damage to every enemy within range of 4 when missile explodes.
        Destroy all cells of walls within this range. 
    Ability 2 (passive): special arm
        When Jango receives damage : he applies 10% of it to every enemy within distance of 10 at end of turn, regardless of walls.
    Ability 3 (passive):
        When Jango dies:his arming explodes and deals 200 damage to every enemy within distance 4.
        
### Tusken Raider
    Related Items: N/A
    Max POE: 30
    Mass: 1.5
    HP: 300
    Ability 1 (attack): snipe
        POE consumption: 6
        Overheat: 3
        Deals 70 damage to any one enemy existing on the map.
        However there is a 50% chance of missing.
    Ability 2 (special): absorb
        Deals 70 damage to every enemy in distance of 5.
        Absorb the sum of the deduction of their HP.
    Ability 3 (passive): dodge
        have 10% chance to recover 50 HP at every end of his trun.

### Darth Maul
    Related items: N/A
    Max POE: 40
    Mass: 1
    HP: 340
    Ability 1 (attack): double bladed lightsaber
        POE consumption: 11
        Overheat: 1
        Deals 80 damage to all enemy within distance of 6.
        Cannot penetrate walls.
        After attack, acquire a chance to move by a distance not more than 5.
        The moving consumes no POE.
    Ability 2 (passive): The Phantom Menace
        When moving, Darth Maul can pass and atop at pixels of walls.
        However, if he is in wall both at the start and the end of his turn :
        He receives 30 damage at the end of that (his) turn.

### Darth Sidious
    Related items: electric pole
        Darth Sidious’s lightening can conduct among electric poles.
        The conduct distance of poles are 5.
        Through this process, Darth Sidious’ attack can reach very far enemies.
        At most 5 poles are allowed to exist on the map simultaneously.
        If excessive poles are placed, random poles will be removed.
    Max POE: 75
    Mass: 1.5
    HP: 520
    Ability 1 (attack): dark force lightening
        POE consumption: 15
        Overheat: 2
        Deals 105 damage to all reachable enemys.
    Ability 2 (special): chancellor power
        POE consumption: 12
        Overheat: +∞
        Place a electric pole at current pixel and recover HP by 50.
    Ability 3 (passive): come back to life
        When Darth Sidious is defeated, he has 25% chance to immediately come back to life with 100 HP and previous POE.

## 7. Buffs
Roles can get buffs when they pass or stop at their pixels.

Buffs are effective automatically, no extra operations are needed.

Buffs will be randomly generated for every 5 rounds.

### 7.1.	Health recovery buff
HP += 50 at the start of next 2 turns.
### 7.2.	Shield buff
Absorb the next damage.

## 8. That's all
That is all for the rule of the text-based《Yet another board game》. Thanks for finish reading it, and we wish you have fun!
