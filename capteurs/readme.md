#Helpy - le détecteur de sourire
Ce projet a été réalisé dans le cadre du Hackathon organisé par le 8 fablab de Crest (26), le Do it weekend.
##Principe

##Détails techniques
Le dossier openFrameworks contient toute la bibliothèque openFrameworks ET l'add-on ofxFaceTracker. L'exemple "example-expressions" a été modifié par rapport à celui trouvable sur le dépôt officiel : il envoie les expressions reconnues sur la boucle locale (localhost, port 8338) à travers le protocole OSC (UDP).
Il est déjà compilé pour Linux-64 bits, maiq il est nécessaire de refaire tourner project generator (programme de openFrameworks) pour regénérer un Makefile.
Le dossier simple_OSC_python contient en particulier exemple-receive.py qui est utilié pour récupérer les expressions reconnues et passer les pins 5 et 6 du Raspberry à l'état HAUT, en fonction de l'expression reconnue. Le fichier exmple-send.py n'est pas utilisé.
##Membres
Les participants du projet sont : François Bouis, Thomas Dehaeze, Juliette Koch, Olivier Neyret et Florian Pignard
