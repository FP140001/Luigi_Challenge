//**************************
//Tutoriel SDL 2.0
//
// AUTEUR : Florian PASCAL
//          IUT GEII BRIVE
//**************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "IUTSDL.h"
#include <SDL2/SDL_mixer.h> // pour la musique


// -----------------------------------------------------
// Constantes
// -----------------------------------------------------
// Nom du jeu
#define TITRE "Luigi Challenge GEII"

// Dimensions de la grille
#define NBL 20          // Nombre de lignes
#define NBC 35          // Nombre de colonnes

// Dimensions des cases : correspond au images bitmap
#define CASE_W 34       // Largeur
#define CASE_H 34       // Hauteur

// Dimensions de l'écran
#define SCREEN_W NBC*CASE_W
#define SCREEN_H NBL*CASE_H

// Types de mouvements Mario. Indices des sprites correspondants dans le tableau des textures.
#define MOVE_LEFT    0
#define MOVE_RIGHT   1
#define MOVE_UP      2
#define MOVE_DOWN    3

// Position à atteindre pour fin du jeu : en haut à droite
#define XFIN    NBC-1
#define YFIN    0



// -----------------------------------------------------
// Globales
int compteur,mnt,pRecup,vie,action=0;
Mix_Music *music = NULL;
Mix_Chunk *bruit = NULL;



// -----------------------------------------------------
// Pour affichage (traitement timer)
char gTitle[100] = "";              // Titre a afficher sur la fenetre

// Bitmaps pour l'affichage
SDL_Texture *pTexturedollar ;
SDL_Texture *pTexturedollar2 ;
SDL_Texture *pTexturedollar3 ;
SDL_Texture *pTexturedollar4 ;
SDL_Texture *pTexturedollar5 ;
SDL_Texture *pTexturedollar6 ;
SDL_Texture *pTexturedollar7 ;
SDL_Texture *pTexturedollar8 ;
SDL_Texture *pTexturedollar9 ;
SDL_Texture *pTexturedollar10 ;
SDL_Texture *pTexturedollar11 ;
SDL_Texture *pTexturedollar12 ;
SDL_Texture *pTexturedollar13 ;
SDL_Texture *pTexturedollar14 ;
SDL_Texture *pTexturedollar15 ;
SDL_Texture *pTexturedollar16 ;
SDL_Texture *pTextureFond ;
SDL_Texture *pTextureMur ;
SDL_Texture *pTextureMario[4] ;     // Sprites Mario pour chaque direction de deplacement
SDL_Texture *pTexturedrapeau ;
SDL_Texture *pTexturebombe ;
SDL_Texture *pTextureGagne ;
SDL_Texture *pTexturePerdu ;
SDL_Texture *pTextureFond2 ;
SDL_Texture *pTextureFond3 ;
SDL_Texture *pTextureFond4 ;
SDL_Texture *pTextureFond5 ;
SDL_Texture *pTextureCle1 ;
SDL_Texture *pTextureCle2 ;
SDL_Texture *pTextureCle3 ;
SDL_Texture *pTextureCle4 ;
SDL_Texture *pTexturecactus ;
SDL_Texture *pTextureAcceuil ;
SDL_Texture *pTextureLave ;
SDL_Texture *pTextureBois ;
SDL_Texture *pTextureMur2 ;
SDL_Texture *pTextureMur3 ;
SDL_Texture *pTextureMur4 ;
SDL_Texture *pTextureMur5 ;

// Coordonnées écran de chacune des cases pour l'affichage du fond et des sprites
SDL_Rect rectGrille[NBC][NBL] ;
char fond_jeu[NBC][NBL];
void musique(int i);
void bruitage (int i);

Uint32 callback( Uint32 interval, void* param )
{
    compteur+=interval;
    if((compteur==60000)||(mnt>0))
    {
        if(compteur==60000)
        {
            compteur=0;
            mnt+=1;
        }
        sprintf(gTitle,"Luigi Challenge | Temps de jeu : %d m %d s | Nombre de pieces recuperes : %d (bonus x2) | Vie utilisees : %d/10", mnt, compteur/1000, pRecup, vie);
    }
    else
    {
        sprintf(gTitle,"Luigi Challenge | Temps de jeu : %d s | Nombre de pieces recuperes : %d (bonus x2) | Vie utilisees : %d/10", compteur/1000, pRecup, vie);
    }
    return interval;
}
// -----------------------------------------------------
// Initialisations jeu
// -----------------------------------------------------
// Chargement des bitmaps pour affichage
void initTextures(SDL_Renderer *sdlRenderer)
{
    pTexturedollar=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar2=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar3=IUTSDL_LoadTexture(sdlRenderer,"images/dollar2.bmp",0xFF,0xFF,0xFF);
    pTexturedollar4=IUTSDL_LoadTexture(sdlRenderer,"images/dollar2.bmp",0xFF,0xFF,0xFF);
    pTexturedollar5=IUTSDL_LoadTexture(sdlRenderer,"images/dollar2.bmp",0xFF,0xFF,0xFF);
    pTexturedollar6=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar7=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar8=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar9=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar10=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar11=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar12=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTexturedollar13=IUTSDL_LoadTexture(sdlRenderer,"images/dollar.bmp",0xFF,0xFF,0xFF);
    pTextureFond=IUTSDL_LoadTexture(sdlRenderer, "images/fond.bmp" ,0xFF,0xFF,0xFF);
    pTextureFond2=IUTSDL_LoadTexture(sdlRenderer, "images/fond_2.bmp" ,0xFF,0xFF,0xFF);
    pTextureFond3=IUTSDL_LoadTexture(sdlRenderer, "images/fond3.bmp" ,0xFF,0xFF,0xFF);
    pTextureFond4=IUTSDL_LoadTexture(sdlRenderer, "images/fond4.bmp" ,0xFF,0xFF,0xFF);
    pTextureFond5=IUTSDL_LoadTexture(sdlRenderer, "images/fond5.bmp" ,0xFF,0xFF,0xFF);
    pTextureMur=IUTSDL_LoadTexture(sdlRenderer, "images/mur.bmp" ,0xFF,0xFF,0xFF);
    pTextureMur2=IUTSDL_LoadTexture(sdlRenderer, "images/mur.bmp" ,0xFF,0xFF,0xFF);
    pTextureMur3=IUTSDL_LoadTexture(sdlRenderer, "images/mur.bmp" ,0xFF,0xFF,0xFF);
    pTextureMur4=IUTSDL_LoadTexture(sdlRenderer, "images/mur.bmp" ,0xFF,0xFF,0xFF);
    pTextureMur5=IUTSDL_LoadTexture(sdlRenderer, "images/mur.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_LEFT]=IUTSDL_LoadTexture(sdlRenderer, "images/Mario-gauche.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_RIGHT]=IUTSDL_LoadTexture(sdlRenderer, "images/Mario-droite.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_UP]=IUTSDL_LoadTexture(sdlRenderer, "images/Mario-haut.bmp" ,0xFF,0xFF,0xFF);
    pTextureMario[MOVE_DOWN]=IUTSDL_LoadTexture(sdlRenderer, "images/Mario-bas.bmp" ,0xFF,0xFF,0xFF);
    pTexturedrapeau=IUTSDL_LoadTexture(sdlRenderer,"images/drapeau.bmp",0xFF,0xFF,0xFF);
    pTexturebombe=IUTSDL_LoadTexture(sdlRenderer,"images/bombe.bmp",0xFF,0xFF,0xFF);
    pTextureGagne=IUTSDL_LoadTexture(sdlRenderer,"images/gagne.bmp",0xFF,0xFF,0xFF);
    pTexturePerdu=IUTSDL_LoadTexture(sdlRenderer,"images/perdu.bmp",0xFF,0xFF,0xFF);
    pTextureCle1=IUTSDL_LoadTexture(sdlRenderer,"images/cle_1.bmp",0xFF,0xFF,0xFF);
    pTextureCle2=IUTSDL_LoadTexture(sdlRenderer,"images/cle_1.bmp",0xFF,0xFF,0xFF);
    pTextureCle3=IUTSDL_LoadTexture(sdlRenderer,"images/cle_1.bmp",0xFF,0xFF,0xFF);
    pTextureCle4=IUTSDL_LoadTexture(sdlRenderer,"images/cle_1.bmp",0xFF,0xFF,0xFF);
    pTexturecactus=IUTSDL_LoadTexture(sdlRenderer,"images/cactus.bmp",0xFF,0xFF,0xFF);
    pTextureAcceuil=IUTSDL_LoadTexture(sdlRenderer,"images/accueil.bmp",0xFF,0xFF,0xFF);
    pTextureLave=IUTSDL_LoadTexture(sdlRenderer, "images/lave.bmp" ,0xFF,0xFF,0xFF);
    pTextureBois=IUTSDL_LoadTexture(sdlRenderer, "images/bois.bmp" ,0xFF,0xFF,0xFF);
}

// Initialisation coordonnées des cases de la grille
void initRectGrille()
{
    for (int i=0 ; i<NBC ; i++ )
    {
        for (int j=0 ; j<NBL ; j++)
        {
            rectGrille[i][j].x = i * CASE_W ;
            rectGrille[i][j].y = j * CASE_H ;
            rectGrille[i][j].w = CASE_W ;
            rectGrille[i][j].h = CASE_H ;
        }
    }
}

// Affichage contenu fixe de la grille : fond et murs
void affichageFond(SDL_Renderer *sdlRenderer)
{
    // Affichage du fond sur toute la grille
    for (int i=0 ; i<NBC ; i++ )
    {
        for (int j=0 ; j<NBL ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond, NULL, &rect);
            fond_jeu[i][j]='f';
        }
    }

    for (int i=14 ; i<29 ; i++ )
    {
        for (int j=0 ; j<7 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond2, NULL, &rect);
            fond_jeu[i][j]='ff';
        }
    }

    for (int i=0 ; i<13 ; i++ )
    {
        for (int j=8 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond3, NULL, &rect);
            fond_jeu[i][j]='fff';
        }
    }

    for (int i=21 ; i<29 ; i++ )
    {
        for (int j=7 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond4, NULL, &rect);
            fond_jeu[i][j]='ffff';
        }
    }

    for (int i=30 ; i<35 ; i++ )
    {
        for (int j=0 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureFond5, NULL, &rect);
            fond_jeu[i][j]='fffff';
        }
    }

    //Affichage Clé
    for (int i=1 ; i<2 ; i++ )
    {
        for (int j=17 ; j<18 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureCle1, NULL, &rect);
            fond_jeu[i][j]='z';
        }
    }

    for (int i=24 ; i<25 ; i++ )
    {
        for (int j=3 ; j<4 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureCle2, NULL, &rect);
            fond_jeu[i][j]='a';
        }
    }

    for (int i=28 ; i<29 ; i++ )
    {
        for (int j=18; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureCle3, NULL, &rect);
            fond_jeu[i][j]='e';
        }
    }

    for (int i=12 ; i<13; i++ )
    {
        for (int j=0; j<1 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureCle4, NULL, &rect);
            fond_jeu[i][j]='x';
        }
    }


    //Emplacement des bombes
    for (int i=18 ; i<19 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }

    for (int i=16 ; i<17 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }

    for (int i=1 ; i<2 ; i++ )
    {
        for (int j=0 ; j<1 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=16 ; i<17 ; i++ )
    {
        for (int j=5 ; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=28 ; i<29 ; i++ )
    {
        for (int j=3 ; j<4 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=18 ; i<19 ; i++ )
    {
        for (int j=6 ; j<7 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=23 ; i<24 ; i++ )
    {
        for (int j=1 ; j<2 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=24 ; i<25 ; i++ )
    {
        for (int j=4 ; j<5 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=22 ; i<23 ; i++ )
    {
        for (int j=5 ; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=26 ; i<27 ; i++ )
    {
        for (int j=9 ; j<10 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=28 ; i<29 ; i++ )
    {
        for (int j=13 ; j<14 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=22 ; i<23 ; i++ )
    {
        for (int j=18 ; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=25; i<26 ; i++ )
    {
        for (int j=8 ; j<9 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=27 ; i<28 ; i++ )
    {
        for (int j=19 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=21 ; i<22 ; i++ )
    {
        for (int j=8 ; j<9 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=25 ; i<26 ; i++ )
    {
        for (int j=14 ; j<15 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=31 ; i<32 ; i++ )
    {
        for (int j=5 ; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=33 ; i<34 ; i++ )
    {
        for (int j=15 ; j<16 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=32 ; i<33 ; i++ )
    {
        for (int j=18 ; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=30 ; i<31 ; i++ )
    {
        for (int j=5 ; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=33 ; i<34 ; i++ )
    {
        for (int j=8 ; j<9; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=0 ; i<1 ; i++ )
    {
        for (int j=2 ; j<3 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }
    for (int i=6 ; i<7; i++ )
    {
        for (int j=2 ; j<3 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturebombe, NULL, &rect);
            fond_jeu[i][j]='b';
        }
    }


    //Emplacement des pièces
    for (int i=2 ; i<3 ; i++ )
    {
        for (int j=2 ; j<3 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar3, NULL, &rect);
            fond_jeu[i][j]='g';
        }
    }
    for (int i=26 ; i<27 ; i++ )
    {
        for (int j=2 ; j<3 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar4, NULL, &rect);
            fond_jeu[i][j]='2';
        }
    }
    for (int i=25 ; i<26; i++ )
    {
        for (int j=11; j<12 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar5, NULL, &rect);
            fond_jeu[i][j]='i';
        }
    }

    for (int i=15 ; i<16; i++ )
    {
        for (int j=5; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar, NULL, &rect);
            fond_jeu[i][j]='p';
        }
    }
    for (int i=17 ; i<18 ; i++ )
    {
        for (int j=15; j<16 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar2, NULL, &rect);
            fond_jeu[i][j]='q';
        }
    }
    for (int i=33 ; i<34 ; i++ )
    {
        for (int j=12; j<13 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar6, NULL, &rect);
            fond_jeu[i][j]='r';
        }
    }
    for (int i=23 ; i<24 ; i++ )
    {
        for (int j=12; j<13 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar7, NULL, &rect);
            fond_jeu[i][j]='s';
        }
    }
    for (int i=27 ; i<28 ; i++ )
    {
        for (int j=18; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar8, NULL, &rect);
            fond_jeu[i][j]='t';
        }
    }
    for (int i=25 ; i<26 ; i++ )
    {
        for (int j=9; j<10 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar9, NULL, &rect);
            fond_jeu[i][j]='h';
        }
    }
    for (int i=15 ; i<16 ; i++ )
    {
        for (int j=1; j<2 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar10, NULL, &rect);
            fond_jeu[i][j]='y';
        }
    }
    for (int i=28 ; i<29; i++ )
    {
        for (int j=0; j<1 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar11, NULL, &rect);
            fond_jeu[i][j]='k';
        }
    }

    for (int i=32 ; i<33 ; i++ )
    {
        for (int j=0; j<1 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedollar13, NULL, &rect);
            fond_jeu[i][j]='n';
        }
    }


    //Drapeau placer en [0;34]
    for(int i=NBC-1; i<NBC ; i++ )
    {
        for (int j=0 ; j<1 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturedrapeau, NULL, &rect); //affiche le drpeau
            fond_jeu[i][j]='d';
        }
    }

    //Emplacement bois
    for (int i=14 ; i<20 ; i++ )
    {
        for (int j=8 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureLave, NULL, &rect);
            fond_jeu[i][j]='l';
        }
    }


    for(int i=14 ; i<19 ; i++ )
    {
        for (int j=18 ; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=15 ; i<19 ; i++ )
    {
        for (int j=16 ; j<17 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=18 ; i<19 ; i++ )
    {
        for (int j=17 ; j<18 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=14 ; i<15 ; i++ )
    {
        for (int j=18 ; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=15 ; i<16 ; i++ )
    {
        for (int j=13 ; j<16 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=16 ; i<20 ; i++ )
    {
        for (int j=13 ; j<14 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=19 ; i<20 ; i++ )
    {
        for (int j=11 ; j<13 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=14 ; i<19 ; i++ )
    {
        for (int j=11 ; j<12 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=14 ; i<19 ; i++ )
    {
        for (int j=11 ; j<12 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=14 ; i<15 ; i++ )
    {
        for (int j=9 ; j<11 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=14 ; i<18; i++ )
    {
        for (int j=9 ; j<10 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    for(int i=17 ; i<18; i++ )
    {
        for (int j=8 ; j<9 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureBois, NULL, &rect);
            fond_jeu[i][j]='w';
        }
    }

    //Murs placer
    for(int i=17 ; i<18 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur5, NULL, &rect);
            fond_jeu[i][j]='m5';
        }
    }
    for (int i=0 ; i<5 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

    for (int i=4 ; i<5 ; i++ )
    {
        for (int j=0 ; j<4 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

    for (int i=4 ; i<5 ; i++ )
    {
        for (int j=5 ; j<7 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

    for (int i=5 ; i<10 ; i++ )
    {
        for (int j=5 ; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

    for (int i=9 ; i<10 ; i++ )
    {
        for (int j=2 ; j<6 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

        //MUR CENTRAL
    for (int i=13 ; i<14 ; i++ )
    {
        for (int j=0 ; j<17 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }
    for (int i=13 ; i<14 ; i++ )
    {
        for (int j=17 ; j<18 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur3, NULL, &rect);
            fond_jeu[i][j]='m3';
        }
    }
    /*for (int i=13 ; i<14 ; i++ )
    {
        for (int j=18 ; j<20 ; j++)
        {
            SDLi4pj97_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }*/
    for (int i=9 ; i<16 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

    for (int i=19 ; i<22 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }
    for (int i=22 ; i<23 ; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur4, NULL, &rect);
            fond_jeu[i][j]='m4';
        }
    }
    for (int i=23; i<29; i++ )
    {
        for (int j=7 ; j<8 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

    for (int i=20 ; i<21 ; i++ )
    {
        for (int j=7 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }

        //Mur droite entier
    for (int i=29 ; i<30; i++ )
    {
        for (int j=0 ; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur, NULL, &rect);
            fond_jeu[i][j]='m';
        }
    }
    for (int i=29 ; i<30; i++ )
    {
        for (int j=19 ; j<20 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTextureMur2, NULL, &rect);
            fond_jeu[i][j]='m2';
        }
    }


    //Emplacement Cactus
    for (int i=1 ; i<2 ; i++ )
    {
        for (int j=12 ; j<13 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=5 ; i<6 ; i++ )
    {
        for (int j=10; j<11 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=11; i<12 ; i++ )
    {
        for (int j=18; j<19 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=8; i<9 ; i++ )
    {
        for (int j=10; j<11 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=6; i<7; i++ )
    {
        for (int j=15; j<16 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=6; i<7; i++ )
    {
        for (int j=15; j<16 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=8; i<9; i++ )
    {
        for (int j=17; j<18 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=8; i<9; i++ )
    {
        for (int j=17; j<18 ; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=10; i<11; i++ )
    {
        for (int j=14; j<15; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=1; i<2; i++ )
    {
        for (int j=18; j<19; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=1; i<2; i++ )
    {
        for (int j=16; j<17; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=2; i<3; i++ )
    {
        for (int j=8; j<9; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }
    for (int i=9; i<10; i++ )
    {
        for (int j=8; j<9; j++)
        {
            SDL_Rect rect = rectGrille[i][j] ;      // Rect associ& à la case
            SDL_RenderCopy(sdlRenderer, pTexturecactus, NULL, &rect);
            fond_jeu[i][j]='c';
        }
    }


}

// Affichage Mario
void affichageMario(SDL_Renderer *sdlRenderer, int x, int y, int sens)
{
    SDL_Rect rectMario ;
    rectMario.x = x*CASE_W ;
    rectMario.y = y*CASE_H ;
    rectMario.w = CASE_W ;
    rectMario.h = CASE_H ;
    SDL_RenderCopy(sdlRenderer, pTextureMario[sens], NULL, &rectMario);
}

// Fonction d'initialisation du jeu
void init(SDL_Renderer *sdlRenderer)
{
    // Init random
    srand(time(NULL));

    // Textures pour afficher éléments du jeu
    initTextures(sdlRenderer) ;

    // Grille pour affichage décors. Attention Table colonne/ligne pour respecter le sens x=colonne et y=ligne
    initRectGrille() ;

    // Affichage de la grille et des murs
    affichageFond(sdlRenderer) ;

    // Mise à jour de l'affichage
    IUTSDL_RefreshScreen(sdlRenderer);
}

void Gagne(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectG;
    rectG.x = 0*CASE_W;
    rectG.y = 0*CASE_H;
    rectG.w = 35*CASE_W;
    rectG.h = 25*CASE_H;
    SDL_RenderCopy(sdlRenderer, pTextureGagne, NULL, &rectG);
    IUTSDL_RefreshScreen(sdlRenderer);
    SDL_Delay(5000);
}

void Perdu(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectP;
    rectP.x = 0*CASE_W;
    rectP.y = 0*CASE_H;
    rectP.w = 35*CASE_W;
    rectP.h = 25*CASE_H;
    SDL_RenderCopy(sdlRenderer, pTexturePerdu, NULL, &rectP);
    IUTSDL_RefreshScreen(sdlRenderer);
    SDL_Delay(7500);
}
void debut(SDL_Renderer *sdlRenderer)
{
    SDL_Rect rectD;
    rectD.x = 0*CASE_W;
    rectD.y = 0*CASE_H;
    rectD.w = 35*CASE_W;
    rectD.h = 20*CASE_H;
    SDL_RenderCopy(sdlRenderer, pTextureAcceuil, NULL, &rectD);
    IUTSDL_RefreshScreen(sdlRenderer);
    SDL_Delay(10000);
    init(sdlRenderer);
    affichageFond(sdlRenderer) ;
    IUTSDL_RefreshScreen(sdlRenderer);
    mnt = 0 ;
    compteur = 0 ;
}
void musique (int i)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if(i==1)
    {
        music = Mix_LoadMUS("m_b/luigi.mp3");
        Mix_PlayMusic(music, -1);
    }
    if(i==3)
    {
        music = Mix_LoadMUS("m_b/ga.mp3"); //perdu
        Mix_PlayMusic(music, -1);
    }
    if(i==4)
    {
        music = Mix_LoadMUS("m_b/w.mp3"); //gagner
        Mix_PlayMusic(music, -1);
    }
}

void bruitage (int i)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if(i==9)
    {
        bruit = Mix_LoadWAV("m_b/piece.wav");
        Mix_PlayChannel(-1, bruit, 0);
    }
    if(i==8)
    {
        bruit = Mix_LoadWAV("m_b/cactus.wav");
        Mix_PlayChannel(-1, bruit, 0);
    }
    if(i==10)
    {
        bruit = Mix_LoadWAV("m_b/lave.wav");
        Mix_PlayChannel(-1, bruit, 0);
    }
    if(i==11)
    {
        bruit = Mix_LoadWAV("m_b/porte.wav");
        Mix_PlayChannel(-1, bruit, 0);
    }

}
// -----------------------------------------------------
// Fonction main
// -----------------------------------------------------
int main( int argc, char* args[] )
{
    SDL_Window   *pScreen=NULL;         // Fenetre
    SDL_Renderer *sdlRenderer=NULL;     // Declaration du Buffer Video

    // Nouvelles positions pour calcul
    int x, y ;
    int sens ;

    // Position Mario
    int xMario, yMario ;        // Position de Mario
    // Direction Mario
    int dirMario ;

    // Rappel : la console reste utilisable
    printf("\nVous pouvez faire des traces par printf sur la fenetre console pour debugger ... \n") ;
    printf("Le point de depart va s'afficher.\nUtiliser les fleches pour deplacer Mario\nFermer la fenetre pour terminer\n") ;
    SDL_Delay(2000) ;
    //
    // Initialisations graphique SDL
    // LAISSER TEL QUEL ! OK Sir Halluin
    //
    // Initialisation utilisation de la SDL
    if( IUTSDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) != NO_ERROR )
    {
        printf("Erreur IUTSDL\n") ;
        exit(1) ;
    }
    // Création de la fenêtre
    pScreen = IUTSDL_CreateWindow(TITRE, SCREEN_W, SCREEN_H);
    if (pScreen == NULL)
    {
        printf("Erreur IUTSDL\n") ;
        exit(1) ;
    }

    // Icône
    IUTSDL_SetWindowIcon (pScreen, ".\\images/Mario-icone-64.bmp");

    // Début affichege
    //sdlRenderer = SDL_CreateRenderer(pScreen, -1, 0 /*SDL_RENDERER_ACCELERATED*/);      // Association du Buffer Video à la Fenetre
    sdlRenderer = SDL_CreateRenderer(pScreen, -1, SDL_RENDERER_SOFTWARE);      // Association du Buffer Video à la Fenetre

    IUTSDL_ClearScreen(sdlRenderer);

    // Fin d'initialisation graphique SDL


    // Timer
    // Création d'un timer pour affichage du titre. La fonction callback sera appellée périodiquement toutes les 100ms
    SDL_TimerID timerID = SDL_AddTimer(100, callback, NULL );


    // Jeu
    // Initialisations
    init(sdlRenderer) ;
    debut(sdlRenderer);
    //musique(1);


    // Positionner Mario pour les test : au milieu
    xMario = 0 ;
    yMario = 0 ;
    dirMario = MOVE_DOWN ;

    // Jeu
    int sortie = 0 ;
    while(!sortie)
    {
        // Affichage titre de fenetre
        SDL_SetWindowTitle(pScreen, gTitle);

        // Attendre un poil
        SDL_Delay(50) ;

        // Recup des evenements externe (clavier, souris)
        SDL_Event( event );
        while( SDL_PollEvent( &event ) != 0 )
        {
            sens = -1 ;
            switch ( event.type)
            {
                case SDL_QUIT :
                    // Sortie
                    SDL_SetWindowTitle(pScreen, "       Merci d'avoir jouer, a bientot  !!!        ") ;
                    sortie = 1 ;
                    break;

                case SDL_KEYDOWN :
                    switch( event.key.keysym.sym )
                    {
                        case SDLK_LEFT:
                            sens = MOVE_LEFT ;
                            break;
                        case SDLK_RIGHT:
                            sens = MOVE_RIGHT ;
                            break;
                        case SDLK_UP:
                            sens = MOVE_UP ;
                            break;
                        case SDLK_DOWN:
                            sens = MOVE_DOWN ;
                            break;
                        case 27: //touche Echap
                            sortie = 1;
                            break;
                    }
            }

            // Traitement des evenements du type fleche
            if ((sens == MOVE_UP)&&(fond_jeu[xMario][yMario-1]!='m'))
            {
                dirMario=sens ;
                if (y>0)
                {
                    x=xMario ;
                    y=yMario-1 ;
                }

            }
            else if ((sens == MOVE_DOWN)&&(fond_jeu[xMario][yMario+1]!='m'))
            {
                dirMario=sens ;
                if (y<19)
                {
                    x=xMario ;
                    y=yMario+1 ;
                }


            }
            else if ((sens == MOVE_LEFT)&&(fond_jeu[xMario-1][yMario]!='m'))
            {
                dirMario=sens ;
                if (x>0)
                {
                    x=xMario-1 ;
                    y=yMario ;
                }

            }
            else if ((sens == MOVE_RIGHT)&&(fond_jeu[xMario+1][yMario]!='m'))
            {
                dirMario=sens ;
                if (x<34)
                {
                    x=xMario+1 ;
                    y=yMario ;
                }
            }
            else
            {
                x=xMario ;
                y=yMario ;
            }

            if(fond_jeu[xMario][yMario]=='d') //fin drapeau
            {
                musique(4);
                Gagne(sdlRenderer);
                sortie=1;
                break;
            }
            if((fond_jeu[xMario][yMario]=='b')||((vie==10))||((mnt==40))) //bombe
            {
                musique(3);
                Perdu(sdlRenderer);
                sortie=1;
                break;
            }

            //Pièce
            if(fond_jeu[xMario][yMario]=='p') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }
            if(fond_jeu[xMario][yMario]=='q') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar2); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }
            if(fond_jeu[xMario][yMario]=='g') //pièce
            {
                bruitage(9);
                pRecup = pRecup + 5;
                SDL_DestroyTexture(pTexturedollar3); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }
            if(fond_jeu[xMario][yMario]=='2') //pièce
            {
                bruitage(9);
                pRecup = pRecup + 5;
                SDL_DestroyTexture(pTexturedollar4); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }

            if(fond_jeu[xMario][yMario]=='i') //pièce
            {
                bruitage(9);
                pRecup = pRecup + 5;
                SDL_DestroyTexture(pTexturedollar5); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }

            if(fond_jeu[xMario][yMario]=='r') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar6); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }

            if(fond_jeu[xMario][yMario]=='s') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar7); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }

            if(fond_jeu[xMario][yMario]=='t') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar8); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }

            if(fond_jeu[xMario][yMario]=='h') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar9); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }
            if(fond_jeu[xMario][yMario]=='y') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar10); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }
            if(fond_jeu[xMario][yMario]=='k') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar11); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }
            if(fond_jeu[xMario][yMario]=='n') //pièce
            {
                bruitage(9);
                pRecup++;
                SDL_DestroyTexture(pTexturedollar13); //Efface TOUTE les pièces dès qu'on passe sur 1 pièce !
            }


            // Clé
            if(fond_jeu[xMario][yMario]=='z') //clé 1
            {
                SDL_DestroyTexture(pTextureCle1);
                SDL_DestroyTexture(pTextureMur3);
                bruitage(11);
            }

            if(fond_jeu[xMario][yMario]=='a') //clé 2
            {
                SDL_DestroyTexture(pTextureCle2);
                SDL_DestroyTexture(pTextureMur4);
                bruitage(11);
            }

            if(fond_jeu[xMario][yMario]=='e') //clé 3
            {
                SDL_DestroyTexture(pTextureCle3);
                SDL_DestroyTexture(pTextureMur2);
                bruitage(11);
            }

            if(fond_jeu[xMario][yMario]=='x') //clé 4
            {
                SDL_DestroyTexture(pTextureCle4);
                SDL_DestroyTexture(pTextureMur5);
                bruitage(11);

            }

            if(fond_jeu[xMario][yMario]=='l') //lave
            {
                bruitage(10);
                vie++;
            }
            if(fond_jeu[xMario][yMario]=='c') //lave
            {
                bruitage(10);
                vie++;
            }
            // Déplacement
            xMario=x ;
            yMario=y ;
            affichageFond(sdlRenderer); // efface les Marios
            affichageMario(sdlRenderer, xMario, yMario, dirMario) ;
        }

        // Mise à jour de l'affichage
        IUTSDL_RefreshScreen(sdlRenderer);
    }

    SDL_Delay(1000);

    // Ménage
    SDL_RemoveTimer( timerID );
    Mix_FreeMusic(music); //Libération de la musique
    Mix_CloseAudio();


    // Affichage score final
    printf("\n Aurevoir !!\n") ;

    return 0 ;
}
