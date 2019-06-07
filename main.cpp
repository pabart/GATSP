/*
    Universidad Autónoma de Aguascalientes
    Proyecto Final Metaheurísticas
    Integrantes:
        Pablo Arturo Alemán Silva
        Joaquín Fernández Alfaro
    Dr. en C. Luis Fernando Gutiérrez Marfileño
*/
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<math.h>
#include<vector>
#include<windows.h>

using namespace std;

struct nodo{
	int valores[131][27]={{0}};
	struct nodo* sig;
};

struct nodo2{
	int valores[50][27];
	struct nodo2* sig;
};

typedef nodo *nueva;
nueva primero=NULL;
nueva ultimo=NULL;
nueva aux;
nueva nuevo1=(nueva)malloc(sizeof(nodo));

typedef nodo2 *nueva2;
nueva2 primero2=NULL;
nueva2 ultimo2=NULL;
nueva2 aux2;

int  coord[131][2] = { {0,13},
                {0,26},
                {0,27},
                {0,39},
                {2,0},
                {5,13},
                {5,19},
                {5,25},
                {5,31},
                {5,37},
                {5,43},
                {5,8},
                {8,0},
                {9,10},
                {10,10},
                {11,10},
                {12,10},
                {12,5},
                {15,13},
                {15,19},
                {15,25},
                {15,31},
                {15,37},
                {15,43},
                {15,8},
                {18,11},
                {18,13},
                {18,15},
                {18,17},
                {18,19},
                {18,21},
                {18,23},
                {18,25},
                {18,27},
                {18,29},
                {18,31},
                {18,33},
                {18,35},
                {18,37},
                {18,39},
                {18,41},
                {18,42},
                {18,44},
                {18,45},
                {25,11},
                {25,15},
                {25,22},
                {25,23},
                {25,24},
                {25,26},
                {25,28},
                {25,29},
                {25,9},
                {28,16},
                {28,20},
                {28,30},
                {28,34},
                {28,40},
                {28,43},
                {28,47},
                {32,26},
                {32,31},
                {33,15},
                {33,26},
                {33,29},
                {33,31},
                {34,15},
                {34,26},
                {34,29},
                {34,31},
                {34,38},
                {34,41},
                {34,5},
                {35,17},
                {35,31},
                {38,16},
                {38,20},
                {38,30},
                {38,34},
                {40,22},
                {41,23},
                {41,32},
                {41,34},
                {41,35},
                {41,36},
                {48,22},
                {48,27},
                {48,6},
                {51,45},
                {51,47},
                {56,25},
                {57,12},
                {57,25},
                {57,44},
                {61,45},
                {61,47},
                {63,6},
                {64,22},
                {71,11},
                {71,13},
                {71,16},
                {71,45},
                {71,47},
                {74,12},
                {74,16},
                {74,20},
                {74,24},
                {74,29},
                {74,35},
                {74,39},
                {74,6},
                {77,21},
                {78,10},
                {78,32},
                {78,35},
                {78,39},
                {79,10},
                {79,33},
                {79,37},
                {80,10},
                {80,41},
                {80,5},
                {81,17},
                {84,20},
                {84,24},
                {84,29},
                {84,34},
                {84,38},
                {84,6},
                {107,27}};

void push(nodo *lista,nodo2 *lista2, bool f){
    //Nodo de la población inicial
    if(f){
        lista->sig=NULL;
        if(primero==NULL){
            primero=lista;
            ultimo=lista;
        }
        else{
            ultimo->sig=lista;
            ultimo=lista;
        }
    }
    //Nodo de los 50 mejores
    else{
        lista2->sig=NULL;
        if(primero2==NULL){
            primero2=lista2;
            ultimo2=lista2;
        }
        else{
            ultimo2->sig=lista2;
            ultimo2=lista2;
        }
    }

}

void mostrar(){
	nueva i=primero;
	while(i!=NULL){
        for(int j=0;j<131;j++){
            for(int k=0;k<27;k++){
                printf("%d ",i->valores[j][k]);
            }
            printf("\n");
        }
		i=i->sig;
		cout<<endl;
	}
}

//Imprime nodo2
void mostrar2(){
	nueva2 i=primero2;
	while(i!=NULL){
        for(int j=0;j<50;j++){
            for(int k=0;k<27;k++){
                printf("%d ",i->valores[j][k]);
            }
            printf("\n");
        }
		i=i->sig;
		cout<<endl;
	}
}

void pop(bool f){
    //Nodo de la población inicial
    if(f){
       aux = primero;
        if(aux -> sig == NULL){
            primero = NULL;
            ultimo = NULL;
            free(aux);
        }
        else{
            primero = aux -> sig;
            free(aux);
        }
    }

    //Nodo de los 50 mejores
    else{
        aux2 = primero2;
        if(aux2 -> sig == NULL){
            primero2 = NULL;
            ultimo2 = NULL;
            free(aux2);
        }
        else{
            primero2 = aux2->sig;
            free(aux2);
        }
    }

}

void mejores(){
    nueva2 nuevo = (nueva2)malloc(sizeof(nodo2));
    nueva k = primero;
    for(int i=0;i<50;i++){
        for(int j=0;j<27;j++){
            nuevo->valores[i][j] = k->valores[i][j];
        }
    }
    push(k,nuevo,0);
}

//Segunda etapa
void cruce(){
    nueva nuevo100=(nueva)malloc(sizeof(nodo));
    nueva2 k=primero2;
    for (int i = 0; i < 131; ++i){
        for(int l=0;l<27;l++){
            nuevo100->valores[i][l]=0;
        }
    }
    int con=0;
    int piv;
    int q;
    int a=1;
    for(int i=0;i<131;i++){
        for(int j=1;j<5;j++){
            if(j==1){
                a=i+1;
            }
            bool existe = false;
            nuevo100->valores[con][0] = 1;
            nuevo100->valores[con][131] = 1;
            nuevo100->valores[con][1] = k->valores[i][1];
            nuevo100->valores[con][130] = k->valores[i][24];
            piv = k->valores[a][1];
            while(!existe){
                q = 1;
                while(k->valores[i][q] != piv && q!=26){
                    q++;
                }
                piv = k->valores[a][q];
                existe = std::find(std::begin(nuevo100->valores[con]),std::end(nuevo100->valores[con]), piv) != std::end(nuevo100->valores[con]);
                nuevo100->valores[con][q] = k->valores[i][q];
            }

            existe = false;
            //Mete los valores terminando el ciclo
            for(int l=1;l<131;l++){
                if(nuevo100->valores[con][l]==0 && !(std::find(std::begin(nuevo100->valores[con]),std::end(nuevo100->valores[con]), k->valores[a][l]) != std::end(nuevo100->valores[con]))){
                    nuevo100->valores[con][l] = k->valores[a][l];
                }

            }

            for(int l=1;l<132;l++){
                if(nuevo100->valores[con][l]==0){
                    for(int m=2;m<132;m++){
                        if(!(std::find(std::begin(nuevo100->valores[con]),std::end(nuevo100->valores[con]), m) != std::end(nuevo100->valores[con]))){
                            nuevo100->valores[con][l] = m;
                            m = 26;
                        }

                    }
                }
            }
            con++;
            a++;
        }
    }
    push(nuevo100,k,1);
}


//Tercera etapa
void mutacion(){
    nueva j = primero;
    int aux;
    for(int i=0;i<131;i++){
        aux = j->valores[i][3];
        j->valores[i][3] = j->valores[i][22];
        j->valores[i][22] = aux;
    }
}

void burbuja(int v[131][27], int n){
    int tem;
    for(int i=0;i<n-1;i++){
        for(int j=i+1; j<n;j++){
            if(v[i][132]>v[j][132]){
                for(int k=0;k<27;k++){
                    tem=v[i][k];
                    v[i][k]=v[j][k];
                    v[j][k]=tem;
                }
            }
        }
    }
}


void distancia(){
    nueva j=primero;
    int suma=0;

    for(int i=0;i<131;i++){
        suma=0;
        for(int k=0;k<25;k++){
            suma += (sqrt(pow((coord[j->valores[i][k]-1][0] - coord[j->valores[i][k+1]-1][0]),2)) + (pow((coord[j->valores[i][k]-1][1] - coord[j->valores[i][k+1]-1][1]),2)));
        }
        j->valores[i][132] = suma;
    }
}

int myrandom (int i) { return std::rand()%i;}

int main(){
    printf("\t\t     Universidad Aut%cnoma de Aguascalientes\n\n",162);
    printf("\t\t`hdh/.:::::::.    -:::::::.sddmmmmmddhy+:\n");
    printf("\t\t`dmmm.::::::::`  -:::::::.+hhhhhhddddmmmmds:      \n");
    printf("\t\t`dmmm.::::::::.  ````````  `.--------:+ydmmmy-    \n");
    printf("\t\t`dmmm.::::::::.              `.::::::::--odmmd+   \n");
    printf("\t\t`dmmm.::::::::.         -.      .::::::::-:hmmd+  \n");
    printf("\t\t`dmmm.::::::::.        -//-.      `::::::::--dmmd \n");
    printf("\t\t`dmmm.::::::::.      `:///:`+-    .::::::::`ommm+ \n");
    printf("\t\t`dmmm.::::::::.     `:///:./ss+`  `::::::::.+mmmo \n");
    printf("\t\t`dmmm.::::::::.    .:///:./ssss:   ::::::::.+mmmo \n");
    printf("\t\t`dmmm.::::::::.   `:///:./sssss.   ::::::::.+mmmo \n");
    printf("\t\t`dmmm.::::::::.   -///-.+sssss:    ::::::::.+mmmo \n");
    printf("\t\t`dmmm.::::::::.   -//-.osssso-     ::::::::.+mmmo \n");
    printf("\t\t`hmmm--:::::::-    .:`+sssso.      ::::::::.+mmmo \n");
    printf("\t\t smmm+.::::::::.    ` +sss+`       ::::::::.+mmmo \n");
    printf("\t\t -dmmd:-::::::::.     `:o+`        ::::::::.+mmmo \n");
    printf("\t\t  /dmmd+--:::::::-`     ``         ::::::::.+mmmo \n");
    printf("\t\t   -ymmmho:--::::::-.`             ::::::::.+mmmo \n");
    printf("\t\t    `/ydmmdhyoooooooo++..-------.  ::::::::.+mmmo \n");
    printf("\t\t      `-oyddmmmmmmmmmmy.:::::::-`  `:::::::--dmmo \n");
    printf("\t\t         `.:/+ooooooo/.-:::::-.     `.-:::::--/o:\n");

    printf("\n\t\t\tProyecto Final Metaheur%csticas I",161);
    printf("\n\t\t\t\t   Presentan:\n\t\t\t   Pablo Arturo Alem%cn Silva\n\t\t\tJoaqu%cn Ulises Fern%cndez Alfaro",160,161,160);
    printf("\n\t\t\t\t   Profesor:\n\t\t   Dr. en C. Luis Fernando Guti%crrez Marfile%co",130,164);
    printf("\n");
    system("pause");

    system("cls");
    printf("\t /os/`                                      `+o+.  :os+.                                       /oo- \n");
    printf("\t-hhhh- :yyy/                          :oo/  +hhho  yhhh+ -syy+`                         .oo+` -hhhy \n");
    printf("\t :hh/  yhhhy `-:.                     yhhy`  ohs`  .yho  +hhhh. .:-                     +hhh-  /hy. \n");
    printf("\t  yy   `shy`.yhhhs              :yyo` `yh.   -h:    +h-   +hh- shhhy`             .sys.  sh:   `ho  \n");
    printf("\t  os    :h/ .yhhho `.           -yho`  os    `h.    :h`   `ho  ohhhs``.`          .shy.  :h`    s/  \n");
    printf("\t  /+    .h.  `sh+-yhhy/    `/+/  /y`   /+     y`    -y     y/   +hs.shhho     :+/` -h-   -y     o:  \n");
    printf("\t  :/     h`   :h`+hhhhs    .yhy` -s    :/     y     .s     o:   .h:-hhhhy.    shy-  y`   .s     +-  \n");
    printf("\t  :/     y    .s  :yh+/syyo..y`  .o    :/     s     `o     +-    y` -sho:oyyo-`s:   s    `o     +.  \n");
    printf("\t  :/     s    `o   :+`hhhhho`y   .o    :/     s     `o     +.    s   `s shhhhy o.   s    `o     +.  \n");
    printf("\t  :/     s    `o   /o :shyo:oho` -s    :/     s     `o     +.    s   .y`-syys:+hs-  y`   `s     +-  \n");
    printf("\t  :/     y    .s  :hho    .hhhhy./y    /+     y     .s     +-    y` .yhs`   `yhhhh:.h-   .s     o-  \n");
    printf("\t  /+     h`   :h` .+o:    `shhhs.yh/   +o     h`    .s     o:   .h: `+o/     ohhhy.oho   :y     o:  \n");
    printf("\t  +o    .h-  .yho`          ..`.yhhh+  sy    .h-    :y     y/  `shy.          `..`ohhhs` +h-    y/  \n");
    printf("\t  sy    /h+  :yhs`             -yhhho :hh/   :h/    /h.   -hs  .yhy-             `yhhhy``yho   `ho  \n");
    printf("\t .hh-  :hhh/   `                `::- -hhhh: `shs`  `yh+  .yhho   `                `-:-``yhhho  +hh. \n");
    printf("\t`yhhh. .oso.                         .shhs. ohhhs  shhh:  +ss:                          +yhy: /hhhy`\n");
    printf("\t /oo/                                       -oso-  -os+`                                      `+ss/ \n");
    printf("\n\nEl siguiente programa resuelve el problema del TSP aplicando la t%ccnica de optimizaci%cn conocida como Algoritmo \nGen%ctico, la instancia espec%cfica que se resuelve tiene 25 ciudades, y cada ciudad tiene como coordenadas un par \nordenado de valores, siendo (x,y) sus coordenadas en el plano xy.",130,162,130,161);
    printf("\nSe obtienen 131 poblaciones iniciales de manera aleatoria a partir de las cuales se obtiene las distancia de total \nde cada una, despu%cs de esto se obtienen las 50 mejores y se pasan a una lista auxiliar, con la cual se aplicar%c \nla t%cnica de cruce, mutaci%cn y selecci%cn, para despu%cs de esto repetir dicho proceso 131 veces.",130,160,130,162,162,130);
    printf("\nUna vez acabado el procedimiento, se muestra el vector final con la distancia mas pequeña de la %cltima generaci%cn.\n\n",163,162);
    system("pause");
    srand(time(NULL));
    int uno25[131]={1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,11 ,12 ,13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,21 ,22 ,23 ,24 ,25 ,26 ,27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 ,36 ,37 ,38 ,39 ,40 ,41 ,42 ,43 ,44 ,45 ,46 ,47 ,48 ,49 ,50 ,51 ,52 ,53 ,54 ,55 ,56 ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 ,66 ,67 ,68 ,69 ,70 ,71 ,72 ,73 ,74 ,75 ,76 ,77 ,78 ,79 ,80 ,81 ,82 ,83 ,84 ,85 ,86 ,87 ,88 ,89 ,90 ,91 ,92 ,93 ,94 ,95 ,96 ,97 ,98 ,99 ,100 ,101 ,102 ,103 ,104 ,105 ,106 ,107 ,108 ,109 ,110 ,111 ,112 ,113 ,114 ,115 ,116 ,117 ,118 ,119 ,120 ,121 ,122 ,123 ,124 ,125 ,126 ,127 ,128 ,129 ,130 ,131};
    int matAux[131][27]={{0}};
    nueva2 nuevoX=(nueva2)malloc(sizeof(nodo2));
    //nueva nuevo1=(nueva)malloc(sizeof(nodo));
    //for para el vector de la posicion j, osease el j-esimo vector
    for(int j=0;j<131;j++){
        nuevo1->valores[j][0]=1;
        nuevo1->valores[j][25]=1;
        random_shuffle(&uno25[0], &uno25[131]);
        for(int i=1;i<25;i++){
            nuevo1->valores[j][i]=uno25[i-1];
        }
    }
    push(nuevo1,nuevoX,1);
    printf("Generaci%cn 1\n",162);
    distancia();
    burbuja(nuevo1->valores,131);
    mostrar();
    for(int i=0;i<99;i++){
        mejores();
        cruce();
        pop(1);
        mutacion();
        distancia();
        burbuja(primero->valores,131);
        printf("Generaci%cn %d\n",162,i+2);
        mostrar();
        pop(0);
    }
    printf("\nEl mejor recorrido es de la generacion 131 es:\n");
    for (int i = 0; i < 132; ++i){
        printf("%d ", primero->valores[0][i]);
    }
    printf("\nCon una distancia total de: %d\n\n",primero->valores[0][26]);

    return 0;
}
