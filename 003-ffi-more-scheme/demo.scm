
#|
how much can we do from guile scheme

|#

(use-modules (system foreign))
(use-modules (system foreign-library))

#|
(define-module (math bessel)
  #:use-module (system foreign)
  #:use-module (system foreign-library)
  #:export (j0))

(foreign-library-function "libm" "j0"
                          #:return-type double
                          #:arg-types (list double))


(define init (foreign-library-pointer "libm" "j0"))
|#

;; this is the shared library
;; /usr/local/lib/libSDL2.so

(define sdl-init(foreign-library-pointer "libSDL2" "SDL_Init"))
(define sdl-quit(foreign-library-pointer "libSDL2" "SDL_Init"))

(define sdl-create-texture-from-surface(foreign-library-pointer "libSDL2" "SDL_CreateTextureFromSurface"))
(define sdl-create-renderer(foreign-library-pointer "libSDL2" "SDL_CreateRenderer"))
(define sdl-create-window(foreign-library-pointer "libSDL2" "SDL_CreateWindow"))

(define sdl-destroy-texture (foreign-library-pointer "libSDL2" "SDL_DestroyTexture"))
(define sdl-destroy-renderer(foreign-library-pointer "libSDL2" "SDL_DestroyRenderer"))
(define sdl-destroy-window (foreign-library-pointer "libSDL2" "SDL_DestroyWindow"))

(define sdl-render-clear(foreign-library-pointer "libSDL2" "SDL_RenderClear"))
(define sdl-render-copy(foreign-library-pointer "libSDL2" "SDL_RenderCopy"))
(define sdl-render-present(foreign-library-pointer "libSDL2" "SDL_RenderPresent"))

(define sdl-poll-event(foreign-library-pointer "libSDL2" "SDL_PollEvent"))


;; sdl2-image library foreign functions
(define sdl-img-load(foreign-library-pointer "libSDL2_image" "IMG_Load"))
(define sdl-img-init(foreign-library-pointer "libSDL2_image" "IMG_Init"))
(define sdl-img-quit(foreign-library-pointer "libSDL2_image" "IMG_Quit"))












