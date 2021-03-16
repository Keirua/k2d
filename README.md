# K2D, « something that looks like a 2D game engine »

I've just dug out my very first large open source project, a 2D game engine. It was published around 2004 I think, and I'm quite proud of what young me built. I've cleaned up the code a bit, removed the non-portable elements. It does not compile yet. I remember putting everything I knew about video games and C++. This is not a large project for me now that I'm working professionnally in this field, but

It comes with an empty project that you can just copy and start to use in order to build a game, and with a sample game that you can both play and use to learn the framework. There was no documentation, only a short "have fun and here my email in case of bugs" during the only release it had !

Here is the feature list:

 - Texture management
 - Sprites
 - Animations
 - Bitmap fonts
 - Debug console (with functions with parameters)
 - box/box and sphere/sphere collision detection
 - Fade-in
 - Highscore management
 - Particle system. You have to code the effects, but the idea is there
 - Sound
 - Blending / color keying
 - …and much more !

It relied on 4 main libraries:

 - fmod (sound)
 - DevIL (image loading)
 - SDL (windowing)
 - Glfw (opengl)

It does not build yet, but I'm quite confident I can have it run somehow even though my C/C++ is quite rusty now (pun intended).

## French release message, at the time

K2D - Un truc qui ressemble a un moteur 2D (mais de très loin alors)

   Enfin arrive la version 1.0 du (ô combien attendu) moteur K2D.
Ne vous attendez pas a des miracles, Il est plus la pour simplifier les choses que pour 
tout faire pour vous...

   Bref, voila liste de tous les machins étranges qu' on peut
faire avec (connu en anglais sous le nom de feature list):
- Gestion des textures
- Sprites
- Animations
- Fonts (ou comment faire tenir en 4 lignes ce qui est censé tenir sur 1)
- Console pour les debuggage (supportant les fonctions a parametres)
- Collision box/box, sphere/sphere...
- Effets de fondu
- Gestion des highscores
- Particules (plus ou moins, il faut juste coder les effets voulus, 
mais l architecture est la)
- Son
- Blending / Color keying
- ... et pleins d autres trucs cachés

   Les librairies nécessaires pour cela sont:
Fmod : www.fmod.org/
DevIL: openil.sourceforge.net/
SDL  : www.libsdl.org/

Un projet vide est présent dans le dossier Empty_project, et une démo a été réalisée 
dans le dosser Bubble. L executable ainsi que les données se trouvent dans le dossier 
Bubble\Release. Les sources completes du programme, sous license GPL, se trouvent
dans le répertoire K2D (présent un peu partout, certes)
Les informations concernant la license GPL se trouvent dans le fichier gpl.txt
