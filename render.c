#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <SDL.h>

#include "render.h"

/* Initialize all rendering, and open the window. */
SDL_Surface *render_init (void) {

  if (SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL init failed.\n");
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

  if (!screen) {
    fprintf(stderr, "Failed to set video mode.\n");
    SDL_Quit();
    return NULL;
  }

  SDL_WM_SetCaption("Hyperbolic Walkabout", "Hyper3");

  if (GLEW_OK != glewInit()) {
    fprintf(stderr, "GLEW init failed.\n");
    SDL_Quit();
    return NULL;
  }

  return screen;

}

/* Render the scene.  This function has no side-effects other than drawing to
   the screen. */
void render (void) {

    /* Clear screen */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Render all objects here */
    /* XXX TODO */

    /* Flip up new screen */
    SDL_GL_SwapBuffers();

}

/* All logic happens here.  When this returns, you exit. */
void renderloop (SDL_Surface *screen) {

  int prevTime = SDL_GetTicks();
  int currTime;
  int done = 0;
  SDL_Event event;

  while (!done) {

    /* Wait until IDLE_MSECS milliseconds pass */
    currTime = SDL_GetTicks();
    int difference = currTime - prevTime;
    if (difference <= IDLE_MSECS) {
      SDL_Delay(IDLE_MSECS - difference);
      currTime = SDL_GetTicks();
      difference = currTime - prevTime;
    }
    prevTime = currTime;

    /* Do actual changes, such as movement, here */
    /* XXX TODO */

    /* Update screen, based on global variables */
    render(screen);

    /* Check for events */
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_q) {
          done = 1;
        }
        break;
      case SDL_VIDEORESIZE:
        screen = SDL_SetVideoMode(event.resize.w, 
                                  event.resize.h, 0,
                                  SDL_OPENGL | SDL_RESIZABLE);
        reshape(L, screen->w, screen->h);
        break;
      case SDL_QUIT:
        done = 1;
        break;
      }
    }
    Uint8 *keys = SDL_GetKeyState(NULL);
    if (keys[SDLK_ESCAPE]) {
      done = 1;
    }

  }
}
