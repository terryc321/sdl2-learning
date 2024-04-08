

#include <stdlib.h>
#include <stdbool.h> 

#include<unistd.h>
// unistd sleep 

#include <libguile.h>

#include <SDL.h>
#include <SDL_image.h>

/* first pass - ignore all error handling */

/* silly definition */

/* prototypes compensate for C language */
static SCM sdl_init();
static SCM my_hostname (void);
static SCM sdl_quit();

/* external procedure in hello.scm scheme file which we will call from c during event loop */
/* allow us to redefine procedures and values on the fly */
static SCM scheme_func_event_loop_server_poll ;
static SCM scheme_func_get_title ; // window title
static SCM scheme_func_run;


/* globals */
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* lettuce_sur;
SDL_Texture* lettuce_tex;


static SCM sdl_destroy_lettuce_tex()
{
  SDL_DestroyTexture(lettuce_tex);
  return SCM_UNDEFINED;
}

static SCM sdl_destroy_renderer()
{
  SDL_DestroyRenderer(renderer);
  return SCM_UNDEFINED;
}


static SCM sdl_destroy_window()
{
  SDL_DestroyWindow(window);  
  return SCM_UNDEFINED;
}



static SCM sdl_event_loop()
{
  Uint32 count = 0;
  while (true) {
    count ++;
    SDL_Event ev;
    if (SDL_PollEvent(&ev)) {  // poll until all events are handled!
      // decide what to do with this event.
      if (ev.type == SDL_QUIT) {
	return SCM_UNDEFINED;
	break;
      }
    }
    
    /*
    if (SDL_WaitEvent(&e)) {
      if (e.type == SDL_QUIT) {
	break;
      }
    }
    */
    //sleep(1);

    // poll server for any new scheme code
    scm_call_0(scheme_func_event_loop_server_poll);

    // call scheme code for the title of window
    // absolutely solved dynamic problem -- need to lookup procedure before we call it so
    // we can always be guaranteed to get latest and greatest
    // look up latest version of get-title - see if redefining it gives a new version ??
    scheme_func_get_title = scm_variable_ref(scm_c_lookup("get-title"));    
    SCM s_title = scm_call_0(scheme_func_get_title);
    char *c_title = scm_to_locale_string(s_title);
    printf("[%u] current window title = %s\n" , count, c_title);
    SDL_SetWindowTitle(window, c_title);

    
    // display lettuce
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, lettuce_tex, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
  
  return SCM_UNDEFINED;
}


static SCM sdl_make_lettuce_texture()
{
    lettuce_tex = SDL_CreateTextureFromSurface(renderer, lettuce_sur);
    /* if (lettuce_tex == NULL) { */
    /*     std::cout << "Error creating texture"; */
    /*     return 6; */
    /* } */    
    SDL_FreeSurface(lettuce_sur);
    return SCM_UNDEFINED;        
}

static SCM sdl_make_lettuce_surface()
{
  lettuce_sur = IMG_Load("lettuce.png");
  /* if (lettuce_sur == NULL) { */
  /*   std::cout << "Error loading image: " << IMG_GetError(); */
  /*   return 5; */
  /* } */
  return SCM_UNDEFINED;    
}

static SCM sdl_make_renderer()
{
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  /* if (renderer == NULL) { */
  /*   std::cout << "Error renderer creation"; */
  /*   return 4; */
  /* } */
  return SCM_UNDEFINED;    
}

static SCM sdl_make_window()
{
 window = SDL_CreateWindow("First program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    /*  if (window == NULL) { */
    /*     std::cout << "Error window creation"; */
    /*     return 3; */
    /* } */
  return SCM_UNDEFINED;
}


static SCM sdl_image_init()
{
  int res = IMG_Init(IMG_INIT_PNG);
  return scm_from_int(res);
}
static SCM sdl_image_quit()
{
  IMG_Quit();
  return SCM_UNDEFINED;
}

/* static is only c routines used in this file only */
static SCM my_hostname (void)
{
  char *s = getenv ("HOSTNAME");
  if (s == NULL)
    return SCM_BOOL_F;
  else
    return scm_from_locale_string (s);
}

static SCM sdl_init()
{
  int res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  return scm_from_int(res);
}

static SCM sdl_quit()
{
  SDL_Quit();
  return SCM_UNDEFINED;
}



static void
inner_main (void *data, int argc, char **argv)
{
  /* can we put these in a module using c */
  scm_c_define_gsubr ("my-hostname", 0, 0, 0, my_hostname);
  scm_c_define_gsubr ("sdl-init", 0, 0, 0, sdl_init);
  scm_c_define_gsubr ("sdl-quit", 0, 0, 0, sdl_quit);  
  scm_c_define_gsubr ("sdl-image-init", 0, 0, 0, sdl_image_init);
  scm_c_define_gsubr ("sdl-image-quit", 0, 0, 0, sdl_image_quit);  
  scm_c_define_gsubr ("sdl-make-window", 0, 0, 0, sdl_make_window);  
  scm_c_define_gsubr ("sdl-make-renderer", 0, 0, 0, sdl_make_renderer);  
  scm_c_define_gsubr ("sdl-make-lettuce-surface", 0, 0, 0, sdl_make_lettuce_surface);  
  scm_c_define_gsubr ("sdl-make-lettuce-texture", 0, 0, 0, sdl_make_lettuce_texture);  

  scm_c_define_gsubr ("sdl-event-loop", 0, 0, 0, sdl_event_loop);  

  scm_c_define_gsubr ("sdl-destroy-lettuce-tex", 0, 0, 0, sdl_destroy_lettuce_tex);  
  scm_c_define_gsubr ("sdl-destroy-renderer", 0, 0, 0, sdl_destroy_renderer);
  scm_c_define_gsubr ("sdl-destroy-window", 0, 0, 0, sdl_destroy_window);  

  // read hello.scm
  scm_c_primitive_load("hello.scm");

  // event-loop-server-poll defined in hello.scm
  scheme_func_event_loop_server_poll = scm_variable_ref(scm_c_lookup("event-loop-server-poll"));
  scheme_func_get_title = scm_variable_ref(scm_c_lookup("get-title"));
  scheme_func_run = scm_variable_ref(scm_c_lookup("run"));

  //scm_call_0(scheme_func_run);
  // lastly start the repl
  scm_shell (argc, argv);
  
}



// embed guile interpreter
// https://www.gnu.org/software/guile/manual/html_node/Linking-Guile-into-Programs.html    
int main(int argc,char **argv){
  // hopefully switching from boot_guile
  //scm_init_guile();
  
  //inner_main();
  scm_boot_guile (argc, argv, inner_main, 0);
  return 0; /* never reached */
}


