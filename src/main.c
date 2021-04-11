#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <time.h>
#include "fonction.h"

//declaration des variables

int main(){
    //le choix d'operation a effectuer
    int choix;
    int connexion;

    connexion_bd();
    printf("############################################################# \n");
    printf("#********* ********* ********* ********* ********* *********# \n");
    printf("#******** Bienvenue dans notre Parking informatique ********# \n");
    printf("#********* ********* ********* ********* ********* *********# \n");
    printf("############################################################# \n");
    printf("\n\n");

    //phase d'authentification
    do
    {
        printf("#-----------------------------------------------------------# \n");
        printf("#******** Phase d\'authentification pour la gestion  ********# \n");
        printf("#-----------------------------------------------------------# \n");

        /* code */
        connexion = 0;
        connexion = connexion_user();
        //"abasse","abasse2021"

        if(connexion == 1){
            system("clear");

            do{
                /* code */
                printf("############################################################# \n");
                printf("#******** Bienvenue dans notre parking informatique ********# \n");
                printf("############################################################# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 1 ENREGISTRER UN NOUVEAU CLIENT        *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 2 AFFICHER LES CLIENTS                 *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 3 AFFICHER LES PLACES DISPONIBLES      *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 4 FAIRE UNE RESERVATION DE PLACE       *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 5 AFFICHER LES RESERVATIONS DE PLACE   *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 6 ANNULER UNE RESERVATION DE PLACE     *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 7 SUPPRIMER UN CLIENT                  *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 8 AJOUTER UNE NOUVELLE PLACE           *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 9 SE DECOONECTER                       *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 10 NETTOYER LE TERMINAL                *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("# ********* 0 EXIT                                 *********# \n");
                printf("#-----------------------------------------------------------# \n");
                printf("#******** Bienvenue dans notre parking informatique ********# \n");
                printf("############################################################# \n");
    
                printf("CHOISISSEZ : ");
                scanf("%i", &choix);
                printf("\n");
        
                switch (choix){
                    case 1:
                        printf("Enregistrement d\'un nouveau client : \n");
                        connexion_bd();
                        Ajouter_client();
                        //"SF2567CI","0123456789"
                        break;

                    case 2:
                        printf("Liste des clients du parking : \n");
                        connexion_bd();
                        consulter_client();
                        break;

                    case 3:
                        printf("Liste des places du parking : \n");
                        connexion_bd();
                        consulter_place();
                        break;

                    case 4:
                        printf("Reservation de place : \n");
                        connexion_bd();
                        reserver_place();
                        break;

                    case 5:
                        printf("Liste des reservations de place : \n");
                        connexion_bd();
                        consulter_reserve();
                        break;

                    case 6:
                        printf("Annulation de reservation : \n");
                        connexion_bd();
                        supprimer_reservation();
                        break;

                    case 7:
                        printf("Suppression d\'un client : \n");
                        connexion_bd();
                        supprimer_client();
                        break;
        
                    case 8:
                        printf("Création d\'une nouvelle place de stationnement : \n");
                        connexion_bd();
                        creer_place();
                        break;

                    case 9:
                        connexion = deconnexion();
                        break;

                    case 10:
                        system("clear");
                        break;
            
                    case 0:
                        printf("Aurevoir et très bientôt !!! \n");
                        exit(EXIT_SUCCESS);
                        break;

                    default:
                        system("cls");
                        printf("ERREUR OUPSSS !!! VEUILLEZ SAISIR A NOUVEAU UN CHIFFRE DE 0 À 10 : \n");
                        break;
                    }

                }while (choix != 0 && connexion == 1);

                connexion == 10;

        }

    }while (connexion == 0);
    getchar();

    printf("################################################################ \n");
    printf("#********* ********* *********    ********* ********* *********# \n");
    printf("#******** Aurevoir, parking informatque vous remercie *********# \n");
    printf("#********* ********* *********    ********* ********* *********# \n");
    printf("################################################################ \n");

    return 0;
}