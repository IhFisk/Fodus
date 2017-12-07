#include "personnage.h"

void perso_creerPerso(map m,perso *p,coord *c, int vie, int dmg,persoTab joueurs,int numperso)
{
	MLV_Image *pers = MLV_load_image("../textures/knight/knight_walkdown1.png");
  	p->pos.x = c->x;
  	p->pos.y = c->y;
  	p->vie = vie;
  	p->dmg = dmg;

  	joueurs[numperso] = *p;

	MLV_draw_image(pers,(p->pos.x)*40+5,(p->pos.y)*40-15);
  	m[p->pos.y][p->pos.x] = '3';

}


int perso_deplacer(map m, perso *p, int numJ, persoTab joueur, int direction, int pm)
{
	MLV_Image *pers = MLV_load_image("../textures/knight/knight_walkdown1.png");

  	m[p->pos.y][p->pos.x] = '0';
  	if(direction == 0 && m[p->pos.y][p->pos.x -1] == '0')//gauche
  	{
    	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m);
    	p->pos.x --;
    	pm --;
  	}

  	if(direction == 1 && m[p->pos.y][p->pos.x +1] == '0') //droite
  	{
    	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m);
    	p->pos.x ++;
    	pm --;
  	}

  	if(direction == 2 && m[p->pos.y - 1][p->pos.x] == '0') //haut
  	{
    	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m);
    	p->pos.y --;
    	pm --;
  	}

  	if(direction == 3 && m[p->pos.y + 1][p->pos.x] == '0') //bas
  	{
    	perso_nettoyer((p->pos.x)*40,(p->pos.y)*40,m);
    	p->pos.y ++;
    	pm --;
  	}

	MLV_draw_image(pers,(p->pos.x)*40+5,(p->pos.y)*40-15);
  	m[p->pos.y][p->pos.x] = '3';
  	joueur[numJ].pos.x = p->pos.x;
  	joueur[numJ].pos.y = p->pos.y;

  	MLV_actualise_window();
  	return pm;
}

void perso_attaque(map m,perso *p1,persoTab joueurs,int x,int y,int nbJoueurs)
{
  int i;
  // animation d'attaque au coordonnées c a ajouter
  for(i=1;i<=nbJoueurs;i++)
  if(x == joueurs[i].pos.x && y == joueurs[i].pos.y)
  {
    joueurs[i].vie -= p1->dmg;
    m[joueurs[i].pos.y][joueurs[i].pos.x] = '3';
  }

}

void perso_nettoyer(int x,int y,map m)
{
	MLV_Image *mur = MLV_load_image("../textures/case_mur.png");
	MLV_Image *sol = MLV_load_image("../textures/case_sol.png");
	MLV_draw_image(sol,x,y);
	if(m[y/40-1][(x/40)] == '1')
		MLV_draw_image(mur,x,y-40);
	else
		MLV_draw_image(sol,x,y-40);
	MLV_actualise_window();
}

void perso_nettoyerAttaque(map m,int x,int y,persoTab joueurs,int nbJ)
{
  	int i,j;
  	for(i=0;i<17;i++)
  	{
    	for(j=0;j<27;j++)
    	{
      		if(m[i][j]=='2')
      		{
        		m[i][j] = '0';
        		perso_nettoyer(j*40,i*40,m);
      		}
	      	if(m[i][j]=='4')
	      	{
	        	m[i][j] = '3';
	        	MLV_draw_filled_rectangle(j*40,i*40,40,40, MLV_COLOR_BLUE);
	      	}
    	}
  	}
  	m[y][x] = '3';
}

void perso_attaqueE(map m, int x, int y)
{
  	int i = 6,j;
  	for(j=0;j<=i;j++)
  	{
    	if(m[y-j][x+i-j] == '0')
    	{
      		m[y-j][x+i-j] = '2';
      		MLV_draw_filled_rectangle((x+i-j)*40,(y-j)*40,40,40,MLV_COLOR_GREEN);
    	}
    	if(m[y-j][x+i-j] == '3')
    	{
      		m[y-j][x+i-j] = '4';
      		MLV_draw_rectangle((x+i-j)*40,(y-j)*40,40,40,MLV_COLOR_GREEN);
    	}
    	if(m[y-j][x-i+j] == '0')
    	{
      		m[y-j][x-i+j] = '2';
      		MLV_draw_filled_rectangle((x-i+j)*40,(y-j)*40,40,40,MLV_COLOR_GREEN);
    	}
    	if(m[y-j][x-i+j] == '3')
    	{
      		m[y-j][x-i+j] = '4';
      		MLV_draw_rectangle((x-i+j)*40,(y-j)*40,40,40,MLV_COLOR_GREEN);
    	}

    	if(m[y+j][x+i-j] == '0')
    	{
      		m[y+j][x+i-j] = '2';
      		MLV_draw_filled_rectangle((x+i-j)*40,(y+j)*40,40,40,MLV_COLOR_GREEN);
    	}

    	if(m[y+j][x+i-j] == '3')
    	{
      		m[y+j][x+i-j] = '4';
      		MLV_draw_rectangle((x+i-j)*40,(y+j)*40,40,40,MLV_COLOR_GREEN);
    	}

    	if(m[y+j][x-i+j] == '0')
    	{
      		m[y+j][x-i+j] = '2';
      		MLV_draw_filled_rectangle((x-i+j)*40,(y+j)*40,40,40,MLV_COLOR_GREEN);
    	}

		if(m[y+j][x-i+j] == '3')
    	{
      		m[y+j][x-i+j] = '4';
      		MLV_draw_rectangle((x-i+j)*40,(y+j)*40,40,40,MLV_COLOR_GREEN);
    	}
  	}
}

void perso_attaqueA(map m, int x, int y)
{
  	int i;
  	i = 1;
  	while(i <= 3 && m[y][x+i] != '1')
  	{
    	if(m[y][x+i] == '0')
    	{
      		m[y][x+i] = '2';
      		MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
    	}
    if(m[y][x+i] == '3')
    {
      MLV_draw_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
      m[y][x+i] = '4';
    }
    i++;
  }
  i = 1;
  while( i <= 3 && m[y+i][x] != '1')
  {
    if(m[y+i][x] == '0')
    {
      m[y+i][x] ='2';
      MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
    }
    if(m[y+i][x] == '3')
    {
      MLV_draw_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
      m[y+i][x] = '4';
    }
    i++;
  }
  i = -1;
  while(i >= -3 && m[y][x+i] != '1')
  {
    if(m[y][x+i] == '0')
    {
      m[y][x+i] = '2';
      MLV_draw_filled_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
    }
    if(m[y][x+i] == '3')
    {
      MLV_draw_rectangle((x+i)*40,y*40,40,40,MLV_rgba(0,255,0,100));
      m[y][x+i] = '4';
    }
    i--;
  }
  i = -1;
  while(i >= -3 && m[y+i][x] != '1')
  {
    if(m[y+i][x] == '0')
    {
      m[y+i][x] = '2';
      MLV_draw_filled_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
    }
    if(m[y+i][x] == '3')
    {
      MLV_draw_rectangle(x*40,(y+i)*40,40,40,MLV_rgba(0,255,0,100));
      m[y+i][x] = '4';
    }
    i--;
  }
}
