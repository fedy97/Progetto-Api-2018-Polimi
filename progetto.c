#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

typedef struct el
{
	char charletto[256];
	struct el *R;
	struct el *L;
} elemlistabidir;

typedef struct el2
{
	struct el2 *R;
	int statosucc;
	bool isfinal;
	char scritto,direzione;
} cellatransizioni;

typedef struct
{
	cellatransizioni *cella[75];
} arraycelle;

typedef struct
{
	int statosucc, statoatt;
	char scritto,direzione;
	unsigned int profondo;
	int poscar;
	bool isfinal;
	elemlistabidir *tbidirstack;
} nodo;
bool sfora=false;
nodo queue[300];
int front=0;
int rear=0;
elemlistabidir* copialista(elemlistabidir *testacorrente)
	{
		elemlistabidir *start2=NULL, *previous=NULL, *cursore;
		cursore=testacorrente;
		int spostamento=0;
		while(cursore->R!=NULL) //torna indietro
		{
			cursore=cursore->R;
			spostamento++;
		}
		while(cursore!=NULL)
		{
			elemlistabidir* temp = malloc(sizeof(elemlistabidir));
			temp->R=NULL;
			temp->L=NULL;
			strcpy(temp->charletto, cursore->charletto);
			if(start2==NULL)
			{
				start2=temp;
				previous=temp;
			}
			else
			{
				previous->L=temp;
				temp->R=previous;
				previous=temp;
			}
			cursore=cursore->L;
		}
		//start2 deve ora puntare con la testina nel posto giusto dioppo
		for (int i=0; i<spostamento; i++)
		{
			start2=start2->L;
		}
		return start2;
	}

void push(bool final, int valuestatosucc, char valuescritto, int statoattt, char valuedirezione, elemlistabidir* testapushata, unsigned int prof, int poscarr)
{

    queue[rear].statosucc= valuestatosucc;
    queue[rear].scritto = valuescritto;
    queue[rear].statoatt = statoattt;
    queue[rear].isfinal = final;
    queue[rear].direzione = valuedirezione;
    queue[rear].tbidirstack = testapushata;
    queue[rear].poscar = poscarr;
    queue[rear].profondo = prof;
    rear++;
    if (rear==300)
  	{
  		rear=0;
  		sfora=true;
  	}
    return;


}

nodo pop()
{

    nodo n1;
    n1.statosucc = queue[front].statosucc;
    n1.scritto = queue[front].scritto;
    n1.statoatt = queue[front].statoatt;
    n1.direzione = queue[front].direzione;
    n1.poscar = queue[front].poscar;
    n1.isfinal = queue[front].isfinal;
    n1.tbidirstack = queue[front].tbidirstack;
    n1.profondo = queue[front].profondo;
    front++;
 	if (front==300)
 	{
 		front=0;
 	}
    return n1;

}


void freestack()
{
	if (front!=rear && front<rear)
	{
		for (int i=front;i<rear;i++)
		{
            elemlistabidir *elim;
            elemlistabidir *appoggio;
            elim=queue[i].tbidirstack;
            while (elim->L!=NULL)
            {
                elim=elim->L;
            }
            while (elim!=NULL)
            {
                appoggio=elim->R;
                free(elim);
                elim=appoggio;
            }
		}
	}
	else if (front!=rear && front>rear)
	{
		for (int i=front;i<300;i++)
		{
            elemlistabidir *elim;
            elemlistabidir *appoggio;
            elim=queue[i].tbidirstack;
            while (elim->L!=NULL)
            {
                elim=elim->L;
            }
            while (elim!=NULL)
            {
                appoggio=elim->R;
                free(elim);
                elim=appoggio;
            }
		}
	}
	front=0;
	rear=0;
	return;
}

int main()
{

	elemlistabidir *nuovoelemlista;
	unsigned int maxpassi;
	char carrun;
	elemlistabidir *testaelemlista, *elemcursore;
	char lol[30]="";
	int statosucccor,statocorrente;
	int numconv=5;
	int accletto;
	char lettocor,scrittocor,direzionecor;
	arraycelle *vett;
	cellatransizioni *cursore, *nuovatr, *cursore2;
	testaelemlista=NULL;

	int capacity=1;
	int used=0;
	vett=malloc(sizeof(arraycelle)*capacity);
	for (int i=0;i<75;i++) vett[0].cella[i]=NULL;
	scanf("%s\n", lol); //legge tr
	while (numconv==5)
	{
		numconv=scanf("%d %c %c %c %d\r\n", &statocorrente, &lettocor, &scrittocor, &direzionecor, &statosucccor);
		if (numconv==5)
		{
			if (statocorrente>used || statosucccor>used) //se si passa ad un nuovo stato, creazione nuovo slot
			{
				if (statocorrente>statosucccor) capacity=statocorrente+1;
				else capacity=statosucccor+1;
				vett=realloc(vett, sizeof(arraycelle)*capacity);
				while (used+1<capacity)
				{
					for (int i=0; i<75; i++)
					{
						vett[used+1].cella[i]=NULL;
					}
					used++;
				}
			}
			if (vett[statocorrente].cella[lettocor-48]==NULL) //se non e' ancora inizializzato
			{
				vett[statocorrente].cella[lettocor-48]=malloc(sizeof(cellatransizioni));
				vett[statocorrente].cella[lettocor-48]->statosucc=statosucccor;
				vett[statocorrente].cella[lettocor-48]->isfinal=false;
				vett[statocorrente].cella[lettocor-48]->scritto=scrittocor;
				vett[statocorrente].cella[lettocor-48]->direzione=direzionecor;
				vett[statocorrente].cella[lettocor-48]->R=NULL;
			}
			else if (vett[statocorrente].cella[lettocor-48]!=NULL) //se e' gia presente lo stato concateno la nuova tr
			{
				nuovatr=malloc(sizeof(cellatransizioni));
				nuovatr->statosucc=statosucccor;
				nuovatr->scritto=scrittocor;
				nuovatr->isfinal=false;
				nuovatr->direzione=direzionecor;
				nuovatr->R=vett[statocorrente].cella[lettocor-48];
				vett[statocorrente].cella[lettocor-48]=nuovatr;
			}
		}

	}
	int j=0;
	numconv=1;
	scanf("%s", lol); //legge acc
	while (numconv==1)
	{
		numconv=scanf("%d", &accletto);
		if (numconv==1)
		{
			int k=0;
			while (k<capacity) //setta gli stati finali
			{
				for (int i=0; i<75; i++)
				{
					cursore=vett[k].cella[i];
					while (cursore!=NULL)
					{
						if (cursore->statosucc==accletto) cursore->isfinal=true;
						cursore=cursore->R;
					}
				}
				k++;
			}
		}
	}
 	/*j=0;
	while (j<capacity) //stampa transizioni
	{
		int i=0;
		while (i<75)
		{
			cursore=vett[j].cella[i];
			while (cursore!=NULL)
			{
				printf("%d %c %c %d --> ", j, cursore->scritto, cursore->direzione, cursore->statosucc);
				cursore=cursore->R;
			}
			i++;
		}
		printf("\n");
		j++;
	}*/
	int ris;
	scanf("%s\n", lol); //legge max

	scanf("%u\n", &maxpassi);
	//printf("%d\n", maxpassi);
	scanf("%s\n", lol); //legge run
	ris=scanf("%c", &carrun);
	//putchar(carrun);
	while(ris!=EOF) //scorre tutte le stringhe in input
	{
		testaelemlista=NULL;

		int p=0;
		while (carrun!='\n' && ris!=EOF) //mette in lista bidir i caratteri
		{
			if (testaelemlista==NULL)
			{
				testaelemlista = malloc(sizeof(elemlistabidir));
				testaelemlista->charletto[0]=carrun;
				testaelemlista->charletto[255]='\0';
				testaelemlista->L=NULL;
				testaelemlista->R=NULL;
				elemcursore=testaelemlista;
			}
			else if (carrun=='\r')
			{

			}
			else if (p<=254)
			{
				elemcursore->charletto[p]=carrun;
			}
			else
			{
				p=0;
				nuovoelemlista = malloc(sizeof(elemlistabidir));
				nuovoelemlista->charletto[0]=carrun;
				nuovoelemlista->charletto[255]='\0';
				nuovoelemlista->L=elemcursore;
				nuovoelemlista->R=NULL;
				elemcursore->R=nuovoelemlista;
				elemcursore=nuovoelemlista;
			}
			ris=scanf("%c", &carrun);
			//putchar(carrun);
			p++;
		}

		while (p<=254)
		{
			elemcursore->charletto[p]='*';
			p++;
		}
		elemcursore->charletto[255]='\0';
		//DFS
		cursore2=vett[0].cella[(testaelemlista->charletto[0])-48];


		while (cursore2!=NULL)
		{
			push(cursore2->isfinal, cursore2->statosucc, cursore2->scritto, 0, cursore2->direzione, copialista(testaelemlista),1,0);
			cursore2=cursore2->R;
		}
		if (rear==0)
		{
			printf("0\n");
			goto fine;
		}
	    nodo trpoppata;
		unsigned int maxprof=0;
		while(rear!=front)
		{
            trpoppata = pop();
            int el=0;
            if ((trpoppata.tbidirstack)->charletto[trpoppata.poscar]==trpoppata.scritto && trpoppata.statoatt==trpoppata.statosucc && trpoppata.direzione=='S')
            {
                maxprof=maxpassi;
                goto qui;
            }
            if (trpoppata.statosucc==trpoppata.statoatt && (trpoppata.tbidirstack)->charletto[trpoppata.poscar]=='_' && trpoppata.scritto=='_' && ((trpoppata.direzione=='R' && trpoppata.tbidirstack->charletto[trpoppata.poscar+1]=='*') || (trpoppata.direzione=='L' && trpoppata.tbidirstack->charletto[trpoppata.poscar-1]=='*')))
            {
                maxprof=maxpassi;
                goto qui;
            }

            //printf("%c %c %d \t", trpoppata.scritto, trpoppata.direzione, trpoppata.statosucc);
            if (maxprof<trpoppata.profondo)
            {
                maxprof=trpoppata.profondo;
            }
            (trpoppata.tbidirstack)->charletto[trpoppata.poscar]=trpoppata.scritto; //sostituisci carattere
            if ((trpoppata.poscar)!=254 && trpoppata.direzione=='R')
            {
                trpoppata.poscar=(trpoppata.poscar)+1;
                if ((trpoppata.tbidirstack)->charletto[trpoppata.poscar]=='*')
                {
                    (trpoppata.tbidirstack)->charletto[trpoppata.poscar]='_';
                }
            }
            else if ((trpoppata.poscar)!=0 && trpoppata.direzione=='L')
            {
                trpoppata.poscar=(trpoppata.poscar)-1;
                if ((trpoppata.tbidirstack)->charletto[trpoppata.poscar]=='*')
                {
                    (trpoppata.tbidirstack)->charletto[trpoppata.poscar]='_';
                }
            }
            else if (trpoppata.direzione=='R' && (trpoppata.poscar)==254 && (trpoppata.tbidirstack)->R==NULL)
            {
                nuovoelemlista = malloc(sizeof(elemlistabidir));
                nuovoelemlista->charletto[0]='_';
                int p=1;
                while (p<=254)
                {
                    nuovoelemlista->charletto[p]='*';
                    p++;
                }
                nuovoelemlista->charletto[255]='\0';
                nuovoelemlista->L=(trpoppata.tbidirstack);
                nuovoelemlista->R=NULL;
                trpoppata.poscar=0;
                (trpoppata.tbidirstack)->R=nuovoelemlista;
                (trpoppata.tbidirstack)=nuovoelemlista;
            }
            else if (trpoppata.direzione=='L' && (trpoppata.poscar)==0 && (trpoppata.tbidirstack)->L==NULL)
            {

                nuovoelemlista = malloc(sizeof(elemlistabidir));
                nuovoelemlista->charletto[254]='_';
                nuovoelemlista->charletto[255]='\0';
                int p=253;
                while (p>=0)
                {
                    nuovoelemlista->charletto[p]='*';
                    p--;
                }

                nuovoelemlista->R=(trpoppata.tbidirstack);
                nuovoelemlista->L=NULL;
                trpoppata.poscar=254;
                (trpoppata.tbidirstack)->L=nuovoelemlista;
                (trpoppata.tbidirstack)=nuovoelemlista;
            }
            else if (trpoppata.direzione=='L' && (trpoppata.poscar)==0 && (trpoppata.tbidirstack)->L!=NULL)
            {
                (trpoppata.tbidirstack)=(trpoppata.tbidirstack)->L;
                trpoppata.poscar=254;
            }
            else if (trpoppata.direzione=='R' && (trpoppata.poscar)==254 && (trpoppata.tbidirstack)->R!=NULL)
            {
                (trpoppata.tbidirstack)=(trpoppata.tbidirstack)->R;
                trpoppata.poscar=0;
            }
            //stampalista(trpoppata.tbidirstack);

            cursore=vett[trpoppata.statosucc].cella[((trpoppata.tbidirstack)->charletto[trpoppata.poscar])-48];

            int visit=1;
            if (trpoppata.profondo<maxpassi)
            {
                while (cursore!=NULL)
                {
                    if (visit==1)
                    {
                        push(cursore->isfinal, cursore->statosucc, cursore->scritto, trpoppata.statosucc, cursore->direzione, trpoppata.tbidirstack, (trpoppata.profondo)+1, trpoppata.poscar);
                        visit=2;
                        el=1;
                    }
                    else
                    {
                        push(cursore->isfinal, cursore->statosucc, cursore->scritto, trpoppata.statosucc, cursore->direzione, copialista(trpoppata.tbidirstack), (trpoppata.profondo)+1, trpoppata.poscar);
                        el=1;
                    }
                    cursore=cursore->R;
                }
            }
            qui: if (el==0)
            {
                elemlistabidir *elim;
                elemlistabidir *appoggio;
                elim=trpoppata.tbidirstack;
                while (elim->L!=NULL)
                {
                    elim=elim->L;
                }
                while (elim!=NULL)
                {
                    appoggio=elim->R;
                    free(elim);
                    elim=appoggio;
                }
            }
            if (trpoppata.isfinal==true)
            {
                printf("1\n");
                break;
            }
            if (maxprof==maxpassi && front==rear)
            {
                printf("U\n");
                break;
            }
            if (front==rear && maxprof<maxpassi)
            {
                printf("0\n");
                break;
            }

		}

		fine: freestack();

		elemcursore=testaelemlista;
		while (elemcursore->L!=NULL) //mi sposto tutto a sx
		{
			elemcursore=elemcursore->L;
		}
		while (elemcursore!=NULL) //elimina lista
		{
			nuovoelemlista=elemcursore->R;
			free(elemcursore);
			elemcursore=nuovoelemlista;
		}

		ris=scanf("%c", &carrun);
		//putchar(carrun);
	}

	j=0;
	while (j<capacity) //libera lista tr
		{
			for (int k=0; k<75; k++)
			{
				if (vett[j].cella[k]!=NULL)
				{
					cursore=vett[j].cella[k]->R;
					free(vett[j].cella[k]);
					while (cursore!=NULL)
					{
						nuovatr=cursore->R;
						free(cursore);
						cursore=nuovatr;
					}
				}
			}
			j++;
		}
	free(vett);
	return 0;
}
