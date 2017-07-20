# Text based game principles

A game is stored in a directory : 
`mygame/`.

For each scene in the game, we create a file :
`mygame/scene01.sc`

For the game data, we use the file :
`mygame/config.tg`

Finally, save files will be in `mygame/saves/`.

## Scene architecture

A scene is a set of events with multiple choices available to the player to advance the story.

Example of scene file `start.sc`:

    [General]
    title=start
    author=
    id=001

    [Content]
    Hello  {{player_name}}! now, it is time to begin. Wake up, hero! But you sick now brah, hf
    
    [Actions]
    set IS_HEALTHY 0
    additem gold 10

    [Dependencies]
    beginning.sc # this is the next scene

    [Choices]
    Hello hello.sc
    Run run.sc

    # This is a comment in any file of the game
    
    # Exemples de syntaxe :
    # file = scene1.sc
    # [Dependencies]
    # scene2.sc
    #
    # scene2.sc will be loaded with scene1.sc
    # choices will be combined
    #
    # In dependencies and choices :
    # if BOOLEAN: scene3.sc
    # if BOOLEAN: "Choice" scene3.sc
    # have <item_name>: scene4.sc
    # is <state_name>: scene5.sc
    # if in the bool table BOOLEAN is TRUE, add choice or load scene
    
    [Style]
    background_image=bg
    text_color=red
    text_style=bold
    
    [Resources]
    bg=background_1920_1080.jpg
    
### General
Contains the scene metadata. (title, name, author, ..., date). Most of these won't appear in the game, but are useful to track scenes data.

### Content
Here goes the text of the scene. You can use `{{attribute}}` to get a value, if it means something to the program.

Example :

    Infile : Hello {{player_name}} ! What is a {{player_race_name}} like you doing here ?
    Result : Hello Albert ! What is a birdpeople like you doing here ?

### Dependencies
Scene dependencies are other scenes : they are loaded in the current scene, usually under conditions. Their choices are added to the current scene's.
A scene can't be a dependency of itself.

### Choices
Choices are offered to the player to continue the story. The syntax is `<choice> <scene.sc>`. You shouldn't have too many choices available. 
If there are no choices in your scenes, just write the filename of the next scene (choice will then be 'Next').

### Actions
This category contains the actions enacted on the game state when the scene unravel :
- `set <boolean> <value>` : sets the game value <boolean> to value <value> (0 or 1)
- 

### Requirements
In the two categories previously mentioned, you can add conditional statements to withhold certain choices or dependencies.

Other categories are WIP.

## Game data
In the file `mygame/config.tg` are stored all the booleans that can serve for conditions.
(WIP, maybe we can store some more things inside it). Anyway, it contains the consts of the game.
    
    [General]
    title=The darkest dungeon
    author=Escalife
    date=12.03.2017
    version=0.1
    first=start.sc
    
    [Scenes]
    newgame:start.sc
    
    [Values]
    # PLAYER VALUES
    IS_HEALTHY 1
    IS_LIVING 1
    IS_ROOTED
    
    [Items] # or maybe in its own file ?
    gold=Gold
    broken_sword=Broken sword
    small_iron_key=Small Iron Key

If the const has no value, then it is loaded as 0 by the game.

## Save files
A save file will contain information pertaining to the player (state, stats, inventory) and a set of the game values
as it was when saving the game.

