/*BY FILIPE MATUSALEM, SEP 2016     filipematus@gmail.com version1.1 MAR 2017*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



int main(int argc, char *argv[])
{
FILE *procar,*outcar;
int i,j,k,l,nbands,nkpts,nelect,nions,band;
char str[150],ch;

 if( argc < 2 ){
printf("\n\n");
printf("EEEEEEE   RRRRRRRR   RRRRRRRR   OOOOOOO   RRRRRRRR\n");
printf("EE        RR    RR   RR    RR   OO   OO   RR    RR\n");
printf("EE        RR    RR   RR    RR   OO   OO   RR    RR\n");
printf("EEEE      RRRRRRRR   RRRRRRRR   OO   OO   RRRRRRRR\n");
printf("EE        RRRR       RRRR       OO   OO   RRRR\n");
printf("EE        RR  RR     RR  RR     OO   OO   RR  RR\n");
printf("EEEEEEE   RR    RR   RR    RR   OOOOOOO   RR    RR\n\n");

printf("Enter the number of the band to analize as argument for the program!\n\n");
exit(0);}


band=atoi(argv[1]);


outcar = fopen("OUTCAR","r"); /* Arquivo ASCII, para leitura */
if(!outcar)
{
printf( "Error opening OUTCAR file\n");
exit(0);
}

procar = fopen("PROCAR","r"); /* Arquivo ASCII, para leitura */
if(!procar)
{
printf( "Error opening PROCAR file\n");
exit(0);
}


do
fscanf(outcar,"%s",str);                                      /*posiciona o ponteiro após a palavra NKPTS*/
while(strcmp(str,"NKPTS")!=0);
fscanf(outcar,"%s",str);        /*pula o =*/
fscanf(outcar,"%d",&nkpts);      /*lê o numero de kpts*/

do
fscanf(outcar,"%s",str);                                      /*posiciona o ponteiro após a palavra NKPTS*/
while(strcmp(str,"NBANDS=")!=0);
fscanf(outcar,"%d",&nbands);      /*lê o numero de bandas*/

do
fscanf(outcar,"%s",str);                                      /*posiciona o ponteiro após a palavra NKPTS*/
while(strcmp(str,"NIONS")!=0);
fscanf(outcar,"%s",str);        /*pula o =*/
fscanf(outcar,"%d",&nions);      /*lê o numero de kpts*/

do
fscanf(outcar,"%s",str);                                      /*posiciona o ponteiro após a palavra NKPTS*/
while(strcmp(str,"type")!=0);
fscanf(outcar,"%s",str);        /*pula o =*/


int types[10],ntypes;
i=0;
do{
fscanf(outcar,"%d",&types[i]); 
ch = getc(outcar);i++;}              
while(ch!='\n');
ntypes=i;


char str1[ntypes][10];   /*armazena ntypes palavras com 10 caracteres cada*/
rewind(outcar);

for(i=0;i<ntypes;i++){
	do
	fscanf(outcar,"%s",str);                                      /*posiciona o ponteiro após a palavra NKPTS*/
	while(strcmp(str,"POTCAR:")!=0);

	fscanf(outcar,"%s",str); fscanf(outcar,"%s",str1[i]); }

float mtx[nions][11],a,occup;

a=occup=0;
for(i=0;i<nions;i++){for(j=0;j<11;j++)mtx[i][j]=0;}



for(k=0;k<nkpts;k++){



do
{
do
fscanf(procar,"%s",str);                                      /*posiciona o ponteiro após a palavra band*/
while(strcmp(str,"band")!=0);
fscanf(procar,"%d",&i);
}
while(i!=band);



do
fscanf(procar,"%s",str);                                      /*posiciona o ponteiro após a palavra occ.*/
while(strcmp(str,"occ.")!=0);
fscanf(procar,"%f",&a); occup=occup+a;


for(i=0;i<3;i++){
do
ch = getc(procar);              /*pula 3 linhas*/
while(ch!='\n');}

 

for(i=0;i<nions;i++){mtx[i][10]==0;
	for(j=0;j<10;j++){fscanf(procar,"%f",&a);mtx[i][j]=mtx[i][j]+a;}
	do
	ch = getc(procar);              /*pula 1 linha*/
	while(ch!='\n');
}

}

for(i=0;i<nions;i++){for(j=1;j<10;j++)mtx[i][10]=mtx[i][10]+mtx[i][j];} //sum the contributions of each atom





printf("\n");
float total;
total=0;

printf("------------------------------------------------------------------------\n\n");
printf("SUM OF ABSOLUTE CONTRIBUTIONS OF EACH ORBITAL FOR BAND %d\n\n",band);
printf("atom    s      py     pz     px     dxy    dyz    dz2    dxz    dx2    tot\n");

for(i=0;i<nions;i++){printf("  %d  ",i+1);
	for(j=1;j<11;j++)printf("%6.3f ",mtx[i][j]); printf("\n"); total=total+mtx[i][10]; }


printf("\n");

float s[ntypes],p[ntypes],d[ntypes];

for(i=0;i<ntypes;i++)s[i]=p[i]=d[i]=0;
k=0;

printf("NORMALIZED CONTRIBUTION OF EACH TYPE\n\n");

for(l=0;l<ntypes;l++){
		k=k+types[l]; 
		for(i=k-types[l];i<k;i++){
			s[l]=s[l]+mtx[i][1];
			for(j=2;j<5;j++)p[l]=p[l]+mtx[i][j];
			for(j=5;j<10;j++)d[l]=d[l]+mtx[i][j];}

	printf("atom %2s -> s=%4.2f %%  p=%4.2f %%  d=%4.2f %%  \n\n",str1[l],100*s[l]/total,100*p[l]/total,100*d[l]/total);
}


printf("\n");
printf("AVERAGE OCCUPATION OF BAND %d is %f \n\n",band,occup/nkpts);

fclose(procar);
fclose(outcar);
}




