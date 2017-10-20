#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

typedef struct
{
    int width;
}Brick;


#define SIZE 10
typedef struct node_s {
	int priority;
	void *data;

}node;

typedef struct
{
	node nodes[SIZE];
	int head, tail;
	//size_t numElements;
	//size_t elementsize;
}PriorityQueue;

void *enqueue(PriorityQueue *pq, int priorty, void *value)
{
	pq->tail = 0;
	pq->head = -1;

	if ((pq->tail + 1) % SIZE == pq->head)
	{
		//printf("queue overflow");
		

	}
	pq->tail = pq->tail + 1 % SIZE;
	pq->nodes[pq->tail].data = value; //this
	pq->nodes[pq->tail].priority = priorty;
}

int *dequeue(PriorityQueue *pq)
{
	void *value = NULL;
	node temp;

	int i;
	if (pq->head == pq->tail)
	{
		//printf("priority underflow");
	}
		int max_priority = pq->head;
		for (i = pq->head; i != pq->tail; i += (i + 1 % SIZE))
		{
			if (pq->nodes[max_priority].priority < pq->nodes[i].priority)
			{
				max_priority = i;
				value = pq->nodes[i].data;
			}

		}
			for (i = max_priority; i != pq->tail; i += (i + 1 % SIZE))
			{
				temp = pq->nodes[i];
				pq->nodes[i] = pq->nodes[i + 1 % SIZE];
				pq->nodes[i + 1 % SIZE] = temp;
			}
		pq->tail = (pq->tail - 1) % SIZE;
		//pq->head = (pq->head + 1) % SIZE;


	}



void draw_stack(Sprite *brick,Vector2D start,Brick *bricklist,unsigned int count)
{
    unsigned int i,j;
    int brickheight = 32;
    int brickwidth = 32;
    Vector2D drawPosition;
    if (!brick)return;
    if (!bricklist)return;
    for (i = 0; i < count; i++)
    {
        //vertical draw
        drawPosition.x = start.x - ((bricklist[i].width * brickwidth)/2);
        drawPosition.y = start.y - ((i + 1) * brickheight);
        for (j = 0;j < bricklist[i].width;j++)
        {
            //horizontal draw
            drawPosition.x += brickwidth;
            gf2d_sprite_draw(
                brick,
                drawPosition,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                0);
        }
    }
}


int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
	int i;
    const Uint8 * keys;
    Sprite *sprite,*brick;
	PriorityQueue *queue;

	
    static Brick bricklist[] = 
    {
        {2},  
        {7},  
        {1},  
        {5},  
        {14},  
        {9},  
        {13},  
        {24},  
        {16},  
        {22}
    };
    

    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {0,0,255,200};
   


    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(17);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
	//for (i = 0; i < SIZE; i++)
	//{
	//	enqueue(&queue, &bricklist[i], bricklist->width);
	//}
	//for (i = 0; i < SIZE; i++)
	//{
	//	dequeue(&queue);
	//}
	for (i = 0; i < SIZE; i++)
	{
		enqueue(&queue, &bricklist[i], bricklist->width);
	}
	
	dequeue(&queue);
	
    
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    brick = gf2d_sprite_load_all("images/brick.png",32,32,16);
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    /*main game loop*/


    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
            
            draw_stack(brick,vector2d(600,700),bricklist,10);
            
            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
