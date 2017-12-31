#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "objects.h"

enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};

int main(void){
    //Variables primitivas
    bool done = false;
    const int FPS = 60;
    bool redraw = true;
    bool isGameOver = false;
    //Variables de objetos
    
    ALLEGRO_BITMAP *image[4][3];
    
    //Variables de Allegro
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_FONT *font18 = NULL;
    ALLEGRO_BITMAP *fondo = NULL;
    
    //inicialización de funciones
    if(!al_init())
         return -1;
         
    display = al_create_display(WIDTH,HEIGHT);
    
    if(!display)
         return -1;
         
    //instalo dispositivos de entrada
    al_install_keyboard();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    
    //inicializo variables de allegro
    image[0][0] = al_load_bitmap("img//left1.bmp");
	image[0][1] = al_load_bitmap("img//left2.bmp");
	image[0][2] = al_load_bitmap("img//left3.bmp");
	
	image[1][0] = al_load_bitmap("img//right1.bmp");
	image[1][1] = al_load_bitmap("img//right2.bmp");
	image[1][2] = al_load_bitmap("img//right3.bmp");
	
	image[2][0] = al_load_bitmap("img//up1.bmp");
	image[2][1] = al_load_bitmap("img//up2.bmp");
	image[2][2] = al_load_bitmap("img//up3.bmp");
	
	image[3][0] = al_load_bitmap("img//down1.bmp");
	image[3][1] = al_load_bitmap("img//down2.bmp");
	image[3][2] = al_load_bitmap("img//down3.bmp"); 
	
	//LLamo a mis clases
	Player player( image[0][0], image[0][1], image[0][2],
                   image[1][0], image[1][1], image[1][2],
                   image[2][0], image[2][1], image[2][2],
                   image[3][0], image[3][1], image[3][2]);
    Piso piso0(0,390,800,400);
    Piso piso1(50,330,600,350);
 
 //inicializo algunas variables
    
    fondo = al_load_bitmap("fondo.png");
    
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);
    
    font18 = al_load_font("arial.ttf",18,0);
    
    //crear registros de eventos
    al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	
    
    al_start_timer(timer);
    
    while(!done)
    {
         ALLEGRO_EVENT ev;   
         al_wait_for_event(event_queue,&ev);
         
         if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
              done=true;
         }  
         else if(ev.type == ALLEGRO_EVENT_TIMER)
         {
              redraw=true;         
              //if(keys[UP])
                   player.mover_arriba(keys[UP]);
              if(keys[LEFT])
                   player.mover_izquierda();
              if(keys[RIGHT])
                   player.mover_derecha();
              if(!isGameOver)
              { 
                   piso0.colision_piso(player);
                   piso1.colision_piso(player);  
                  al_draw_textf(font18, al_map_rgb(255, 255, 255), 5, 5, 0, "Vidas: %i Score: %i", player.lives, player.score);             
              }
              
         }
         else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
         {
              switch(ev.keyboard.keycode)
              { 
                   case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                   case ALLEGRO_KEY_UP:
					    keys[UP] = true;
					    break;
		           /*case ALLEGRO_KEY_DOWN:
				     	keys[DOWN] = true;
					    break;*/
			   	   case ALLEGRO_KEY_RIGHT:
					    keys[RIGHT] = true;
					    break;
				   case ALLEGRO_KEY_LEFT:
					    keys[LEFT] = true;
					    break;
                           
              }          
         }
         else if(ev.type == ALLEGRO_EVENT_KEY_UP)
         {
              switch(ev.keyboard.keycode)
              { 
				   case ALLEGRO_KEY_UP:
					    keys[UP] = false;
					    break;
				   case ALLEGRO_KEY_DOWN:
					    keys[DOWN] = false;
					    break;
				   case ALLEGRO_KEY_RIGHT:
					    keys[RIGHT] = false;
					    break;
				   case ALLEGRO_KEY_LEFT:
					    keys[LEFT] = false;
					    break;                           
              }
              
         }
         if(redraw && al_is_event_queue_empty(event_queue))
         {
              redraw = false;
              if(!isGameOver)
              {
                   //al_draw_bitmap(fondo,0,0,0);
                   player.dibujar_player(keys[UP],keys[DOWN],keys[LEFT],keys[RIGHT]);
                   piso0.dibujar_piso();
                   piso1.dibujar_piso();
                   
              }          
              else
              {
                  al_draw_text(font18,al_map_rgb(255,0,0),WIDTH/2,HEIGHT/2,
                  ALLEGRO_ALIGN_CENTRE,"GAME OVER");
              }
         }
         al_flip_display();
         al_clear_to_color(al_map_rgb(0,0,0));
    }
    
    
}
