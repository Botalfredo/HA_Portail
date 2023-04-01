# Projet portail

Les documents contenus dans ce git permette de connecter un ESP a un serveur MQTT distant il servira d'exemple pour des trames subscibes et publis . Le projet permet de piloter un portail à distance via l'interface electronique suivante.
![Schematic_Home assistant mqtt relay_2023-04-01](https://user-images.githubusercontent.com/68150357/229284383-ee89f37b-43ed-45c6-8685-3892d9c4fec8.png)

Le code communique sur le sujet /portail avec 4 messages.

- 0 : message d'état permanant, commande renvoyée après une action
- 1 : message pour une ouverture pieton
- 2 : message grande ouverture
- 3 : message fermeture

#define à modifer en entete du fichier .ino pour adapter
-SSID
-PASSWORD
-IP du broker MQTT
-ID connction MQTT
-Password connectiion MQTT
-Topic de communication

