
;; can load this from the shell

;;(use-modules (ice-9 ...))

;; startup
(define (startup)
  (sdl-init)
  (sdl-image-init)
  (sdl-make-window)
  (sdl-make-renderer)
  (sdl-make-lettuce-surface)
  (sdl-make-lettuce-texture)
  (sdl-event-loop)  
  )

;; shutdown
(define (shutdown)
  (sdl-destroy-lettuce-tex)
  (sdl-destroy-renderer)
  (sdl-destroy-window)
  (sdl-image-quit)
  (sdl-quit)
  (format #t "bye!~%")
  )


;; entry here
(startup)
(shutdown)


 
