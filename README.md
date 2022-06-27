# Sfml_Game
Část hry naprogramované v sfml, základní funkce: pohyb, kolize a střelba
Mapa je upravitelná pomocí dvojrozměrného pole. Ta je předána metodě třídy Game a zde je předána třídě TileMap která jednotlivé bloky převede do jedné "textury"
a pak pomocí kolize čtyřúhelník a kruh zjistí nejbližší bod mezi kruhem a čtyřúhelníkem.

vzhled hry a způsob zakomponování kolizí je inspirován od https://youtu.be/D2a5fHX-Qrs
vše je to převedeno do sfml a je zde použit můj vlastní způsob zjištění nejbližších objektů od hráče(kruhu)
