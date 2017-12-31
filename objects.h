#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 400;

class Player{
  public:
         int x;
         int y;
         int lives;
         int speed;
         int boundx;
         int boundy;
         int score;
         int contadorBrinco;
         bool caer;
         ALLEGRO_BITMAP *image[4][3];
         int cont;
  
         Player(ALLEGRO_BITMAP *image01,ALLEGRO_BITMAP *image02,ALLEGRO_BITMAP *image03,
                ALLEGRO_BITMAP *image11,ALLEGRO_BITMAP *image12,ALLEGRO_BITMAP *image13,
                ALLEGRO_BITMAP *image21,ALLEGRO_BITMAP *image22,ALLEGRO_BITMAP *image23,
                ALLEGRO_BITMAP *image31,ALLEGRO_BITMAP *image32,ALLEGRO_BITMAP *image33);
         void dibujar_player(bool, bool, bool, bool);
         void mover_derecha();    
         void mover_izquierda();
         void mover_arriba(bool);
         //void mover_abajo();
};

Player::Player(ALLEGRO_BITMAP *image01,ALLEGRO_BITMAP *image02,ALLEGRO_BITMAP *image03,
               ALLEGRO_BITMAP *image11,ALLEGRO_BITMAP *image12,ALLEGRO_BITMAP *image13,
               ALLEGRO_BITMAP *image21,ALLEGRO_BITMAP *image22,ALLEGRO_BITMAP *image23,
               ALLEGRO_BITMAP *image31,ALLEGRO_BITMAP *image32,ALLEGRO_BITMAP *image33){
               
    x = 0;
    y = 300;
    lives = 3;
    speed = 10;
    boundx = 20;
    boundy = 20;
    score = 0; 
    contadorBrinco = 0;
    caer = true;       
    
    image[0][0]=image01;
    image[0][1]=image02;
    image[0][2]=image03;
    
    image[1][0]=image11;
    image[1][1]=image12;
    image[1][2]=image13;
    
    image[2][0]=image21;
    image[2][1]=image22;
    image[2][2]=image23;
    
    image[3][0]=image21;
    image[3][1]=image22;
    image[3][2]=image23;

    int cont = 0;     
}

void Player::dibujar_player(bool UP, bool DOWN, bool LEFT, bool RIGHT){
    
     if(UP || DOWN || RIGHT || LEFT){
           //El error está en que sólo se ejecuta cuando es cierto y adentro de esta condiciób está
           //lo que se tiene que hacer en caso de que no sea positivo
          if(UP){
               if(cont==1 || cont==3){
                    al_convert_mask_to_alpha(image[2][0], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[2][0], x , y, 0);
               }
               if(cont==0){
                            al_convert_mask_to_alpha(image[2][1], al_map_rgb(255,255,255));
                  al_draw_bitmap(image[2][1], x , y, 0);
               }
               if(cont==2){
                            al_convert_mask_to_alpha(image[2][2], al_map_rgb(255,255,255));
                  al_draw_bitmap(image[2][2], x , y, 0);
               }
               cont++;
               if(cont==4)
                    cont=0;
          }
          if(DOWN){
               if(cont==1 || cont==3){
                    al_convert_mask_to_alpha(image[3][0], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[3][0], x , y, 0);
               }
               if(cont==0){
                             al_convert_mask_to_alpha(image[3][1], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[3][1], x , y, 0);
               }
               if(cont==2){
                    al_convert_mask_to_alpha(image[3][2], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[3][2], x , y, 0);
               }
               cont++;
               if(cont==4)
                     cont=0;
          }
          if(LEFT){
                 if(cont==1 || cont==3){
                      al_convert_mask_to_alpha(image[0][0], al_map_rgb(255,255,255));
                      al_draw_bitmap(image[0][0], x , y, 0);
                }
                if(cont==0){
                     al_convert_mask_to_alpha(image[0][1], al_map_rgb(255,255,255));
                     al_draw_bitmap(image[0][1], x , y, 0);
                }
                if(cont==2){
                     al_convert_mask_to_alpha(image[0][2], al_map_rgb(255,255,255));
                     al_draw_bitmap(image[0][2], x , y, 0);
                }
                cont++;
                if(cont==4)
                     cont=0;
          }
          if(RIGHT){
               if(cont==1 || cont==3){
                    al_convert_mask_to_alpha(image[1][0], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[1][0], x , y, 0);
               }
               if(cont==0){
                    al_convert_mask_to_alpha(image[1][1], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[1][1], x , y, 0);
               }
               if(cont==2){
                    al_convert_mask_to_alpha(image[1][2], al_map_rgb(255,255,255));
                    al_draw_bitmap(image[1][2], x , y, 0);
               }
               cont++;
               if(cont==4)
                    cont=0;          
          } 
          
     }
     else
     {
         al_convert_mask_to_alpha(image[3][0], al_map_rgb(255,255,255));
         al_draw_bitmap(image[3][0], x , y, 0);    
     }
     
}

void Player::mover_izquierda(){
    x -= speed;
    if( x < boundx)
        x = 0;    
}

void Player::mover_derecha(){
    x += speed;
    if( x >= WIDTH - boundy )
        x = WIDTH - boundy;    
}

void Player::mover_arriba(bool UP){
     if(caer){
          y +=speed;
     }
     else if(!caer && UP){
          y -= speed;
          contadorBrinco++;  
     }
     
     if(contadorBrinco >= 10  || contadorBrinco <= 10 && !UP)
     {
          contadorBrinco  = 0;
          caer = true;
     }
}

class Piso{
     public:
            int x1,x2;
            int y1,y2;
            int boundx;
            int boundy;
            
            Piso(int, int, int, int);
            void dibujar_piso();
            void colision_piso(Player &player);
};

Piso::Piso(int px1, int py1, int px2, int py2){
     x1 = px1;
     y1 = py1;
     x2 = px2;
     y2 = py2;    
     cout<<x1<<"  "<<y1<<"  "<<x2<<"  "<<y2<<endl;        
}

void Piso::dibujar_piso(){
     al_draw_filled_rectangle(x1,y1,x2,y2,al_map_rgb(255,00,00)); 
}

void Piso::colision_piso(Player &player){
     cout<<"Vairble caer    "<<player.caer<<"  Vairble &playerx "<<player.x<<"  Vairble &playery "<<player.y<<"  contador"<<player.contadorBrinco<<endl;
     //x1 = 0 , x2 = 700, y1 = 370,  y2 = 390
     if(player.x + player.boundx >= x1 && player.x + player.boundx <= x2
        && player.y + player.boundy == y1){
          player.caer = false;
          cout<<"Vairble caer    "<<player.caer<<"  Vairble &playerx "<<player.x<<"  Vairble &playery "<<player.y<<endl;
     }
     
}

class Enemigo{
     public:
            int x;
            int y;
            int tipo;//1 izquierda a derecha, 2 subir y bajar
            int boundx;
            int boundy;
            int estado;
            int contd;
            int conti;
            int sped;
            ALLEGRO_BITMAP *image[2];
            
            Enemigo(int,int, int,ALLEGRO_BITMAP *malo1,ALLEGRO_BITMAP *malo2);
            void dibujar_enemigo();
            void actualizar_enemigo();
            void colision_enemigo(Player $player);              
};

Enemigo::Enemigo(int a, int b, int t, ALLEGRO_BITMAP *malo1,ALLEGRO_BITMAP *malo2){
     x = a; y = b; tipo = t; estado = 0; cont = 0; sped = 10
     image[0] = malo1; image [2]= malo2;
}

void Enemigo::dibujar_enemigo(){
     if(estado ==0)
     {
          al_draw_bitmap(image[0],x,y,0);
     }
     if(estado = 1)
     {
          al_draw_bitmap(image[1],x,y,0);
     }
}

void Enemigo::actualizar_enemigo(){
     if(tipo == 1)
     {
         if(contd<=10)
         {
              x += sped;
              cont++;     
         }
         else if(conti >10)
         {
              
         }
     }
}

