#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <time.h>
#include "fonction.h"

//declaration des variables
static char host[255] = "localhost";
static char user[255] = "root";
static char pass[255] = "";
static char dbname[255] = "Parking"; 

static unsigned int port = 3306;

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char requetes[333];

//connexion a la base de donnée

void connexion_bd(void){
    conn = mysql_init(NULL);
    
    if (! (mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
    {
        fprintf(stderr, "\n Error: %s [%d]\n", mysql_error(conn), mysql_errno(conn));
        exit(1);
    }else{
        printf("Connexion ok !!! \n\n");
    }
}


//authentification du user

int connexion_user(){

    char logins[50];
    char password[50];
    int reponse;

    printf("##> Entrer les identifiants : \n");
    printf("# Login #> ");
    scanf("%s", logins);

    printf("# Password #> ");
    scanf("%s", password);
    printf("\n");

    sprintf(requetes,"select count(*) from admin_user where login='%s' and pass_word='%s';",logins,password);
    
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        reponse = atoi(mysql_fetch_row(res)[0]);
    }

    if (reponse != 0){
        printf("Accès autorisée !!! \n\n");
        return 1;
    }else{
        printf("Accès refusée !!! \n\n");
        return 0;
    }
}

//deconnexion de l'utilisateur
int deconnexion(){
    return 0;
}

//creation de place dans le parking
void creer_place(){

    char nom_place[50];
    int type;

    printf("##> Entrer les identifiants : \n");
    printf("# Nom id place (Ex: A1,B1,C1,...) #> ");
    scanf("%s", nom_place);

    printf("# Type vehicule (1- voiture classique| 2- camion| 3-engins deux roues) #> ");
    scanf("%i", &type);
    printf("\n");

    sprintf(requetes,"insert into Place values(NULL,'%s','%i','%i');",nom_place,0,type);

    if (!(mysql_query(conn, requetes)))
    {
        printf("Création réussi !!! \n\n");
    }else{
        printf("Création échoué !!! \n\n");
    }
}

// nombre de place du parking
int nombre_place(){
    sprintf(requetes,"select count(*) as nb_place from Place where 1;");
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        return atoi(mysql_fetch_row(res)[0]);
    }
    
}

// nombre de place disponible
int nombre_place_dispo(){
    sprintf(requetes,"select count(*) as nb_place from Place where statut=0;");
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        return atoi(mysql_fetch_row(res)[0]);
    }
    
}

// nombre de place occupée
int nombre_place_occup(){
    sprintf(requetes,"select count(*) as nb_place from Place where statut=1;");
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        return atoi(mysql_fetch_row(res)[0]);
    }
    
}

//afficher des places du parking
void consulter_place(){
    int i=1;
    sprintf(requetes,"SELECT * FROM Place");
    if(!(mysql_query(conn, requetes)))
    {
        printf("OK \n");
        printf("#************* liste des places du parking *************# \n");
    }else{
        printf("\n################# AUCUN ENREGISTREMENT ##################\n");
        printf("#****************  liste des places    *****************# \n\n");
    }
    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("    %d - Place : %s ", i,row[1]);
        if(atoi(row[2]) == 0){
            printf("- Libre ");
        }else{
            printf("- Occupée ");
        }

        if(atoi(row[3]) == 1){
            printf("- Voiture classique \n");
        }else if(atoi(row[3]) == 2){
            printf("- Camion \n");
        }else{
            printf("- Deux roues \n");
        }

        i = i + 1;
    }
    printf("\n");
    printf("<-> Nb place : %d - %d Libre - %d Occupée \n",nombre_place(),nombre_place_dispo(),nombre_place_occup());
    printf("#****************  liste des places    *****************# \n\n");
}

//enregistrement de new client
void Ajouter_client(){
    char num_matricule[50];
    char num_phone[50];
    int statut;

    printf("##> Entrer les identifiants : \n");
    printf("# Numero matricule #> ");
    scanf("%s", num_matricule);

    printf("# Numero téléphone #> ");
    scanf("%s", num_phone);
    printf("\n");

    printf("# Type vehicule #> ");
    scanf("%i", &statut);
    printf("\n");

    sprintf(requetes,"insert into Client values(NULL,'%s','%s','%d');",num_matricule,num_phone,statut);

    if (!(mysql_query(conn, requetes)))
    {
        printf("Création réussi !!! \n");
    }else{
        printf("Création échoué !!! \n");
    }
}

// nombre de place du parking
int nombre_client(){
    sprintf(requetes,"select count(*) as nb_place from Client where 1;");
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        return atoi(mysql_fetch_row(res)[0]);
    }
    
}

//liste des clients reussi
void consulter_client(){
    int i=1;
    sprintf(requetes,"SELECT * FROM Client");
    if(!(mysql_query(conn, requetes)))
    {
        printf("#*************** liste des clients reussi **************# \n");
    }else{
        printf("\n################# AUCUN ENREGISTREMENT ##################\n");
        printf("#************* fin de la liste des clients *************# \n\n");
    }

    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("%d - Matricule : %s - Tel : %s ", i,row[1],row[2]);
        
        if(atoi(row[4]) == 1){
            printf("- Voiture classique ");
        }else if(atoi(row[4]) == 2){
            printf("- Camion ");
        }else{
            printf("- Engin deux roues ");
        }

        if(atoi(row[3]) == 1){
            printf("- Reservé \n");
        }else{
            printf("- Pas reservé \n");
        }

        i = i + 1;
    }
    printf("\n");
    printf("<-> Nb client : %d \n",nombre_client());
    printf("#************* fin de la liste des clients *************# \n\n");
}

//supprimer un client
void supprimer_client(){

    char num_matricule[50];

    printf("# Numero matricule #> ");
    scanf("%s", num_matricule);

    sprintf(requetes,"delete from Client where num_matricule='%s';",num_matricule);

    if (!(mysql_query(conn, requetes)))
    {
        printf("Suppression réussi !!! \n");
    }else{
        printf("Suppression échoué !!! \n");
    }
}

// nombre de reservation de place du parking
int nombre_reservation(){
    sprintf(requetes,"select count(*) as nb_place from Reservation where 1;");
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        return atoi(mysql_fetch_row(res)[0]);
    }
    
}

//liste des reservations
void consulter_reserve(){
    int i=1;
    sprintf(requetes,"SELECT * FROM Reservation");

    int day, mois, an;
    time_t now;
        
    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    //printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *localtemp = localtime(&now);    
    day = localtemp->tm_mday;          
    mois = localtemp->tm_mon + 1;     
    an = localtemp->tm_year + 1900;  

    // Afficher la date courante
    printf("La date d\'entrée : %d-%02d-%02d\n", an, mois, day);

    if(!(mysql_query(conn, requetes)))
    {
        printf("#******************************* liste des reservations clients *******************************# \n");
    }else{
        printf("\n#################################### AUCUN ENREGISTREMENT ######################################\n");
        printf("#************************** fin de la liste des reservations clients **************************# \n\n");
    }

    res = mysql_store_result(conn);

    while (row = mysql_fetch_row(res))
    {
        printf("    %d - Entrée : %s - Tarif : %d FCFA ", i,row[1],atoi(row[5]));
        if(atoi(row[6]) == 1){
            printf("- Voiture classique ");
        }else if(atoi(row[6]) == 2){
            printf("- Camion ");
        }else{
            printf("- Deux roues ");
        }
                //selection le id d'une place disponible
            sprintf(requetes, "select num_matricule from Client where id ='%i';", atoi(row[2]));
            if(!(mysql_query(conn, requetes))){
                res = mysql_store_result(conn);
                printf("- %s \n",mysql_fetch_row(res)[0]);
            }

        i = i + 1;
    }
    printf("\n");
    printf("<-> Nb reservation : %d \n",nombre_reservation());
    printf("#************************** fin de la liste des reservations clients **************************# \n\n");
}

//reservation de place
void reserver_place(){
    int somme;
    int day, mois, an;
    int h, min, s;

    //variable d'entrees
    char num_matricule[50];
    int id_client;
    int id_place;
    int nb_heure;
    int type;

    printf("##> Entrer les identifiants : \n");
    printf("# Numero matricule voiture #> ");
    scanf("%s", num_matricule);
    
    //selection le id du client en question
    sprintf(requetes, "select * from Client where num_matricule='%s';", num_matricule);

    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        //printf("OK 1\n");
        while (row = mysql_fetch_row(res)){
            id_client = atoi(row[0]);
            type = atoi(row[4]);
            //printf("OK 2\n");
        }
    }else{
        printf("client introuvable \n");
        exit(EXIT_SUCCESS);
    }
        
    //selection le id d'une place disponible
    sprintf(requetes, "select id from Place where type ='%i' limit 0,1;", type);
    if(!(mysql_query(conn, requetes))){
        res = mysql_store_result(conn);
        id_place = atoi(mysql_fetch_row(res)[0]);
    }else{
        printf("Aucune place disponible \n");
        exit(EXIT_SUCCESS);
    }

    printf("# Nombre heure stationnement #> ");
    scanf("%i", &nb_heure);

    printf("\n");

    time_t now;
        
    // Renvoie l'heure actuelle
    time(&now);
    // Convertir au format heure locale
    // le format 2021-04-09
    struct tm *localtemp = localtime(&now);    
    day = localtemp->tm_mday;          
    mois = localtemp->tm_mon + 1;     
    an = localtemp->tm_year + 1900;
    h = localtemp->tm_hour;        
    min = localtemp->tm_min;       
    s = localtemp->tm_sec;

    if(type == 1){ //voiture classique
        if(nb_heure < 24){
            somme = 500*nb_heure;
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }else if (nb_heure > 24)
        {
            somme = 20000 + 500*(nb_heure - 24);
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }else
        {
            somme = 20000;
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }
        
    }else if(type == 2){ //camion
        if(nb_heure < 24){
            somme = 700*nb_heure;
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }else if (nb_heure > 24)
        {
            somme = 30000 + 700*(nb_heure - 24);
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }else
        {
            somme = 30000;
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }
        
    }else{// engins à deux roues
        if(nb_heure < 24){
            somme = 300*nb_heure;
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }else if (nb_heure > 24)
        {
            somme = 10000 + 300*(nb_heure - 24);
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }

            }else{
                printf("Création échoué !!! \n");
            }
        }else
        {
            somme = 10000;
            sprintf(requetes,"insert into Reservation values(NULL,'%d-%02d-%02d %02d:%02d:%02d','%d','%d','%d','%d','%d');",an,mois,day,h,min,s,id_client,id_place,nb_heure,somme,type);
            if (!(mysql_query(conn, requetes))){
                printf("Création réussi !!! \n");

                //mise a jour de la table Client
                sprintf(requetes,"update Client set statut=1 where id='%d';",id_client);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec client !!! \n");
                }

                //mise a jour de la table Place
                sprintf(requetes,"update Place set statut=1 where id='%d';",id_place);
                if (!(mysql_query(conn, requetes))){
                    printf(" Ok !!! \n");
                }else{
                    printf("Echec place !!! \n");
                }
                
            }else{
                printf("Création échoué !!! \n");
            }
        }
        
    }
}

//suppression de reservation
void supprimer_reservation(){

    int id;
    int id_client;
    int id_place;
    id_client = 0;
    id_place = 0;

    printf("# Numero id #> ");
    scanf("%i", &id);

    sprintf(requetes,"select * from Reservation where id='%d';",id);
    if (!(mysql_query(conn, requetes)))
    {
        res = mysql_store_result(conn);

        while (row = mysql_fetch_row(res))
        {
            id_client = atoi(row[2]);
            id_place = atoi(row[3]);
        }
    
        if(id_client != 0 && id_place != 0){
            //mise a jour de la table Client
            sprintf(requetes,"update Client set statut=0 where id='%d';",id_client);
            if (!(mysql_query(conn, requetes))){
                printf(" Ok !!! \n");
            }else{
                printf("Echec client !!! \n");
            }

            //mise a jour de la table Place
            sprintf(requetes,"update Place set statut=0 where id='%d';",id_place);
            if (!(mysql_query(conn, requetes))){
                printf(" Ok !!! \n");
            }else{
                printf("Echec place !!! \n");
            }
        }

    }else{
        printf("Suppression échoué !!! \n");
    }
    
    sprintf(requetes,"delete from Reservation where id='%d';",id);
    if (!(mysql_query(conn, requetes)))
    {
        printf("Suppression réussi !!! \n");
    }else{
        printf("Suppression échoué !!! \n");
    }
}