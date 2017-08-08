# Simple Text Game Engine

## Introduction

This project aims to design an develop a simple text game engine.

From my understanding, a text-based game is essentially composed of 'scenes', which contains the text that will appear on screen.
If the game is static (little to no interaction needed from the player, or in this case spectator), the game engine need only display text, and have the current scene followed by the next scene when the player wants to move on. However, if the game is dynamic, as in a RPG setting, you need more than just text.
For every scene, you want to know what is happening, and how to have the scene
impacts the player. In turn, the player is given choice as to what happen next,
which points to the corresponding scene.

---

## The structure of a scene

### Content

This is text. That's it. Unleash your creativity !

![text image](../text.png)

No, really, there's more to it.

For now, encoding isn't the matter, but it will become primordial depending of the language you want to write your textgame in.
You can use Markdown syntax to style your content (this is also how this document is written, by the way). 
You can look it up or go on [Wikipedia](https://en.wikipedia.org/Markdown).
This markdown will then be translated in HTML, so you can try and add html tags for additional effects, if you feel like it. (No guaranty it will work as intended, though ...)

As you will see in the next chapters, specific characters are used by the game engine to allow certain features. If you try to use them in your scene in an unintended purpose (e.g. using $ to figure money), the game may not act accordingly, and it might break the content of the scene.

#### Including scenes into other scenes

When you write a scene, you may want to reuse the text of other scenes to describe the same thing happening, or in a ever slightly different way (see [Randomly generated content](#randomcontent)). It would then be a good idea to be able to include other scenes into your scene. If this is done, the content of the included scene will be inserted in the content of the current scene, and its actions will be processed. The choices available to the player however will not include the choices of the included scene, only those of the current main scene.
So think carefully how and why you want to include a scene, as it will not give the player additional choices. This may be subject to change in the future, but for now is isn't supported. See [Choices](#choices) for more details.

For now, a possible syntax to include scenes could be :

    Including scenes : "walking aloof", "running for you life", "eating beef"
    Main scene content:
    
    Today is a great day. However, ...
      $1 // include "walking aloof" scene here
    Suddenly, the sky lit up. Thunder roared, putting you in shambles.
      $2 // include "running for your life" scene here
    You enter what seems to be a butchery warehouse. You find yourself hungry.
      $3 // include "eating beef" scene here
    Happy ending !

Ideally, it doesn't automatically creates a new paragraph for each inclusion.

#### Variables

As aforementioned, you can use variables in your content. Either you want to display the player name (in a dialog for example), or it is some other info related to the game that you can't include raw into the scene.

Syntax is still up for debate :
* `{{player_name}}`
* `$player_name`

Another idea could be to allow you to declare scene variables, whose scope would then encompass the scene and its included scenes (not its children) but it is not a feature for now. Wondering how useful that could be ...

#### Conditional content

WIP

#### Randomly generated content

WIP

#### 'Throw a dice'/'Toss a coin' content

WIP

### Actions

When a scene happens, you may want to alter the player data; either adding items to the player inventory,
changing a stat, and so on. This is where you do it.

### Choices

The choices the player can make at the end of the scene. By default, one choice is available : 
Next. To set it, you need only tell the game engine what is the next scene.

### Actions and choices requirements

### Additional resources

Images, sounds

We should be able to choose whether all ressources of all scenes are loaded (could be unwise)
or maybe just load the scene ressources and all its childs', and so on. Or just load and use right when needed.

### Additional info

* Position and layout of the text
* Position and layout of the images
* Animations ?

## Player Data

Inventory and bool values

## Game files

### Configuration files

Defining variables, items, player data, booleans

#### Main game configuration file

#### Setting data values

#### Creating items

#### Declaring global variables

### Scene files

### Saved progress files

## Game engine

### Qt and QML

### Applications

This is a pet project, but you can use it if you feel like it.
