# MonsterSimulator

Write a program that simulates the fight between two monsters. For this two monsters are to be created with the help of object-oriented programming.  

Create a class that represents a monster. This monster must have at least the following attributes: 
* Health Points (HP)
* Attack Damage (AD)
* Defense Points (DP)
* Speed (S)
* Race

Possible races are orc, troll and goblin. All monsters have a method to attack, which should be called Attack. 

At the beginning the program shall ask for an input to determine which two monsters shall fight against each other. 

This is realized by integer values (1 = Orc, 2 = Troll, 3 = Goblin) followed by 4 float values to determine the above mentioned attributes, which the user can enter himself. 

The order HP - AD - DP - S has to be followed. The program must not allow a fight between monsters of the same race.

Afterwards the program calculates who wins the fight. The formula for this is: Damage = Attack Damage - Defense Points. If the damage is negative, it will be set to 0. The damage is subtracted from the life points of the respective monster. If the monster still has life points left after an attack, it will now perform an attack. This is repeated until a monster dies.

The complete attack mechanics is realized by the attack method. The monster with the higher speed value performs the first attack. After a monster is defeated, the program displays who won and how many rounds the fight lasted. Each attack counts as a round.

Before you start, create a schedule in the form of a table with 3 columns. On this table write down the milestones of your planned implementation in the first column. In the second column, write down how long you think it will take you to complete each milestone. As you work, measure your time. When the milestone is completed, write in the third column how long it actually took you.

# Requirement

You need [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/)

## Visual Studio 2022

Start by opening [MonsterSimulator](./MonsterSimulator.sln).

# Schedule

| Milestone | Planned time | Actual time |
| --- | --- | --- |
| Create class for monsters | 1h | 53min |
| Create a main controller | 5min | 5min |
| Create a view for the main menu | 30min | 22min |
| Create a view in order to create a monster | 1h | 3h03 |
| Create a view used to display the fight | 2h | 1h02 |
| Implement the actual fight with some animations | 4h | - |
| Display the result of the fight and return to menu | 30min | 23min |
| Make various improvements | 4h | - |
| Clean and comments all project | 2h | - |
| Implement Interactive Objects | 6h | 4h18 |

## Interactive objects

Some Interactive objects have function to set and get values used.

| Milestone | Done |
| --------- | ---- |
| Create the basic button | X |
| Implement a onKeyPressed on each interactive objects | X |
| Create the BasicField that take a custom condition and some events | X |
| Create different type of fields (int) | X |
| Create a selector like for the races | X |
| Create an image button (button with an image) | X |
| Add an option if you can increment int field with left/right arrow | X |
| Add a list of Interactive Objects in every view | X |
| Add IO in the constructor of each view | X |
| Trigger event on each IO only if they are selected | X |