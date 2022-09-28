/* 
 * WU'S LINE ALGORITHM
 * Simple implementation of Wu's Line Algorithm
 * with help from Wikipedia and Geeks4Geeks
 * NHC - 2021 
 */

#include <SDL2/SDL.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>

SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

void 
swap(int* a, int* b) { 
	int temp = *a;
	*a = *b;
	*b = temp;
}

//integer part of x
int 
ipart(float x) { 
	return floor(x);
}
int
_round(float x) { 
	return ipart(x+0.5);
}
//fractional part of x
float 
fpart(float x) { 
	return x - floor(x);
} 
float
rfpart(float x) { 
	return 1 - fpart(x);
} 

//plot the line with coord values x,y; and brightness value c (where  0 <= c <= 1)
void 
plot_point(int x, int y, float brightness) { 
	int c = 255*brightness;
	SDL_SetRenderDrawColor(renderer, c, c, c, 255);
	SDL_RenderDrawPoint(renderer, x, y);
}
void
plot_line(int x0, int y0, int x1, int y1) { 
	int steep = abs(y1-y0) > abs(x1-x0);

	if (steep) { 
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if (x0 > x1) { 
		swap(&x0, &x1);
		swap(&y0, &y1);
	}

	float dx = x1-x0;
	float dy = y1-y0;
	float gradient = dy/dx;
	if (dx == 0.0)
		gradient = 1;

	int xpxl1 = x0;
	int xpxl2 = x1;
	float intersectY = y0;

	if (steep) { 
		int x;
		for (x = xpxl1; x<=xpxl2; x++) { 
			plot_point(ipart(intersectY), x, rfpart(intersectY));
			plot_point(ipart(intersectY)-1, x, fpart(intersectY));
			intersectY += gradient;
		}
	}
	else { 
		int x;
		for (x=xpxl1; x<=xpxl2; x++) { 
			plot_point(x, ipart(intersectY), rfpart(intersectY));
			plot_point(x, ipart(intersectY)-1, fpart(intersectY));
			intersectY += gradient;
		}
	}
}

int
main(int argc, char* args[]) { 
	SDL_Event event;
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) { 
		window = SDL_CreateWindow("Wuline algorithm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if(window != 0) { 
			renderer = SDL_CreateRenderer(window, -1, 0);
		}
	}
	else
		return 1;

	while (1) { 
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)  
			break;
		
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		plot_line(80, 200, 550, 150);
		plot_line(560, 280, 90, 330); 
		
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}
