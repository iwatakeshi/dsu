Assemblipede Features
=======================

 * Create/Edit your own level file(s)  ✔ **(see lvl-mickey.txt)**
    * At least one -- put at least a little bit of creativity into it ✔

* Space bar pauses game… ✔
    * keep the game map visible -- this will help a lot when taking screenshots ✔
    * shows instructions (i.e. wasd controls) ✔
    * …and gives option: ✔
        * Q to quit or hit space again to continue 

* Assemblipede dies (game over) when ✔
    * the head attempts to move off the map ✔ 
    * the head hits it's own body ✔
    * the head hits a wall character:  '+' | '-' ✔

* Assemblipede grows by one body segment ✔
    * when it eats a food:  * (asterisk is food) ✔

* Show a "score" above or below game map ✔
    * score is the current length of the Assemblipede 

* Portal ✔
    * the portal is a pair of zeros ✔
        * each can be anywhere on the map ✔
        * only one portal (one pair of zeros) on a map ✔
    * If head goes into one portal, it pops out the other, and in the opposite direction! ✔

    * portals should not be erased if Assemblipede move through them. ✔ 
    * if Assemblipede is partway through the portal ✔
        * it may safely re-enter from a different direction ✔
        * it is possible for a long Assemblipede to go through the portals 4 different ways simultaneously ✔ **(tested two ways)**
            * portals in the level file: ✔
            * just put a pair of zeros in the level file ✔
            * modify the loadlevel section of the program to detect the zeroes and store the locations of the two portals ✔ **(see _loadLevelWrapup)**
            * if there is just one '0' or more than two '0's … ✔
                * exit with a message like "bad level file format -- should be exactly 2 portals or none at all" ✔ **(see _badFileFormat2)**