/**
 * @author Lennart Niecksch (lniecksch@uos.de)
 * @brief  generating rectangles within a range and sorting them by area.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <errno.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 	800
#define WINDOW_HEIGHT 	600


void draw_rectangle(const struct SDL_Rect *rectangle, SDL_Renderer *renderer)
{
	/* Set render color to green */
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, rectangle);
}

int compare_by_width(const void * rect_first, const void * rect_sec)
{
	return (*((struct SDL_Rect* const *)rect_first))->w - (*((struct SDL_Rect* const *)rect_sec))->w;
}


struct SDL_Rect* generate_rectangle(int max_range, int min_range)
{
	int 				width;				/* Width of a new triangle 		*/
	int 				height;				/* Height of a new triangle 	*/
	struct SDL_Rect* 	rectangle;			/* A pointer to a new triangle  */
	int 				offset;				/* The vertical offset 			*/
	static int 			vert_pos = 0;		/* STATIC! vertical position	*/

	/*
	 * Generate random width and height in the given range.
	 *
	 * We represent the set [a, b] with a set [0, a - b] and add an offset
	 * (the lower bound a) to guarantee it is in [a, b].
	 * We also take an subset of [0, RAND_MAX] with length a - b
	 * to ensure we get an uniform distribution.
	 */
	do
	{
		height = rand();
	}
	while (height >= (RAND_MAX - RAND_MAX % (max_range - min_range + 1)));
	height =  height % (max_range - min_range + 1) + min_range;

	do
	{
		width = rand();
	}
	while (width >= (RAND_MAX - RAND_MAX % (max_range - min_range + 1)));
	width = width % (max_range - min_range + 1) + min_range;

	/* Create a new rectangle */
	rectangle = malloc(sizeof(struct SDL_Rect));

	if (NULL == rectangle) {
		printf("Unable to allocate memory for new rectangle\n");
		return NULL;
	}

	/* Save width and height */
	rectangle->h = height;
	rectangle->w = width;

	/* Center the rectangle around the middle of the screen */
	offset 		 = rectangle->w / 2;
	rectangle->x = WINDOW_WIDTH / 2 - offset;
	rectangle->y = vert_pos;

	/*
	 * Increase verticel position by height of the rectangle
	 * and add a small offset to separate them
	 */
	vert_pos = vert_pos + height + 5;

	return rectangle;
}

void clean_up(struct SDL_Rect** rectangles, int size, SDL_Window *window, SDL_Renderer *renderer) {

	int i;

	/* Destroy renderer */
	if(NULL != renderer)
	{
		SDL_DestroyRenderer(renderer);
	}

	/* Destroy window */
	if(NULL != window)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();

	for (i = 0; i < size; i++)
	{
		if(NULL != rectangles[i])
		{
			free(rectangles[i]);
		}
	}

	if(NULL != rectangles)
	{
		free(rectangles);
	}
}


int main(int argc, char **argv)
{
    int 	i;
    int 	num;
    long 	tmp;
    char 	*aux;
    int 	max_range;
    int 	min_range;
    int 	area;
    int 	vertPos;

    /* Pointer to SDL stuff */
    SDL_Window*			window;
    SDL_Renderer* 		renderer;
    struct SDL_Rect** 	rectangles;

    /* Init pointers */
    window 		= 0;
    renderer 	= 0;
    rectangles 	= 0;

    if (argc != 4)
    {
        printf("Please specify the correct number of arguments!\n"
               "usage: rectangles <num rectangles> <max width> <max height>\n");
        return -1;
    }

    tmp = strtol(argv[1], &aux, 10);

    if ( tmp > INT_MAX || *aux != '\0'|| tmp < 1 )
    {
        printf("Please enter a number >= 1 for the number of rectangles to generate\n");
        return -1;
    }
    else
    {
        num = (int) tmp;
    }

    tmp = strtol(argv[2], &aux, 10);

    if ( tmp > INT_MAX || *aux != '\0' || tmp < 1 )
    {
        printf("Please enter a valid positive integer value for the minimum width and height of the rectangles\n");
        return -1;
    }
    else
    {
        min_range = (int) tmp;
    }

    tmp = strtol(argv[3], &aux, 10);

    if ( tmp > INT_MAX || *aux != '\0' || tmp < 1 || tmp < min_range )
    {
        printf("Please enter a valid positive integer value for the maximum width and height of the rectangles"
               " which is greater or equal to the minimum size\n");
        return -1;
    } else
    {
        max_range = (int) tmp;
    }

    rectangles = malloc(sizeof(struct SDL_Rect*) * num);

    if (NULL == rectangles)
    {
        printf("Unable to allocate memory for rectangles\n");
        clean_up(rectangles, 0, NULL, NULL);
        return -1;
    }

    srand(time(NULL));


    /* Fill the array with randomly generated rectangles */
    for (i = 0; i < num; i++) {
        if(NULL == (rectangles[i] = generate_rectangle(max_range, min_range)))
        {
            printf("Error generating rectangle\n");
            clean_up(rectangles, i - 1, NULL, NULL);
            return -1;
        }
    }

    printf("Unsorted array:\n");
    for (i = 0; i < num; i++)
    {
        area = rectangles[i]->h * rectangles[i]->w;
        printf("%d: height: %d width: %d area: %d\n", i, rectangles[i]->h, rectangles[i]->w, area);
    }

    /* sort the array */
    qsort(rectangles, (size_t) num, sizeof(struct SDL_Rect*), &compare_by_width);


    printf("\nSorted array: \n");
    for(i = 0; i < num; i++)
    {
        area = rectangles[i]->h * rectangles[i]->w;
        printf("%d: height: %d width: %d area: %d\n", i, rectangles[i]->h, rectangles[i]->w, area);
    }

    if((SDL_Init(SDL_INIT_VIDEO)) != 0)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        clean_up(rectangles, num, NULL, NULL);
        return -1;
    }

    window = SDL_CreateWindow("Sorted by width", 0, 0, 800, 600, SDL_WINDOW_SHOWN);

    if(NULL == window)
    {
       fprintf(stderr, "%s\n", SDL_GetError());
       clean_up(rectangles, num, NULL, NULL);
       return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(NULL == renderer)
    {
       fprintf(stderr, "%s\n", SDL_GetError());
       clean_up(rectangles, num, window, NULL);
       return -1;
    }

    vertPos = 0;
    for(i = 0; i < num; i++)
    {
    	/* draw_rectangle(rectangles[i], renderer); */
    	/*
    	 * Increase verticel position by height of the rectangle
    	 * and add a small offset to separate them
    	 */
    	rectangles[i]->y = vertPos;
    	vertPos = vertPos + rectangles[i]->h + 5;
    	draw_rectangle(rectangles[i], renderer);
    }

    /* Present the result */
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);

    clean_up(rectangles, num, window, renderer);

    return 0;
}

