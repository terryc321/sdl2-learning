
;; can load this from the shell

;;(use-modules (ice-9 ...))

;; coop repl server vs scm_shell ??

(use-modules (system repl coop-server))
(define *server* #f)

;; call this first to spawn coop server
(define (coop-server-init)
  (set! *server* (spawn-coop-repl-server))
  (format #t "server started ~a ~%" *server*))

;; called from hello.c inside the c event loop to change system as it is running
(define (event-loop-server-poll)
  (poll-coop-repl-server *server*))

(define (get-title)
  "welcome title!")


;; startup
(define (startup)
  (coop-server-init) ;; start repl server  
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
(define (run)
  (startup)
  (shutdown))

(format #t "type (run) to start ball rolling~%")





 
