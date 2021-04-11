########################################
# NOM1 : TRAORE ZIE ABASSE             #
# NOM2 : KOFFI BROU DELPHIN            #
# CLASSE : MASTER 1 SIGL&MBDS - ESATIC #
# PROF : Dr DIABY MOUSTAPHA            #
########################################

#Authentification connexion
Login: abasse
Password: abasse2021


#compilation de tous les fichiers ".c"
gcc *.c -o -lmysqlclient program

#compilation final
./program

#o compilation
clang -Wall -Wextra -std=c99 *.c -o -lmysqlclient program

##############################################################

#envoi de projet sur github

1- git init 

2- git add .

3- git commit -m "Un message"

4- git remote add origin le-lien-de-votre-repository

5- git remote -v (pour verifier la connexion)

6- git push origin master

##############################################################