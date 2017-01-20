package main

import (
	"github.com/go-martini/martini"
	"github.com/martini-contrib/sessions"
	"log"
)

// var db Database

func main() {

	// init
	m := martini.Classic()

	// DATABASE
	db := &Database{}
	db.init()
	m.Map(db)

	// SESSION
	store := sessions.NewCookieStore([]byte("myrealbigsecretkey"))
	m.Use(sessions.Sessions("my_session", store))

	//DIRS
	m.Use(martini.Static("StaticPages"))

	//REQUESTS
	m.Get("/", mainHandler, autorizationHandler)

	// Autorization
	m.Get("/registration", registrationPageHandler, mainHandler)
	m.Get("/autorization", autorizationHandler, mainHandler)

	m.Post("/registrate", registrateHandler, mainHandler)
	m.Post("/login", loginHandler, mainHandler)
	m.Post("/logout", logoutHandler, autorizationHandler)
	m.Get("/logout", logoutHandler, autorizationHandler)

	//Possibles
	m.Get("/hidden", hiddenHandler)
	m.Get("/edit/:id", editHandler, mainHandler)
	m.Post("/save/:id", saveHandler, mainHandler)
	m.Post("/create", createPostHandler, mainHandler)
	m.Get("/new", newPostHandler, mainHandler)

	// Administration
	m.Get("/changeusers", changeUserPageHandler, mainHandler)
	m.Get("/remove_user/:id", removeUserHandler, changeUserPageHandler, mainHandler)

	// m.Get("/hello/**", func(params martini.Params) string {
	// 	return "Hello " + params["_1"]
	// })

	// 404
	static := martini.Static("StaticPages", martini.StaticOptions{Fallback: "/404.html", Exclude: "/api/v"})
	m.NotFound(static)

	log.Println("Start Martini classic...")
	m.Run()

}
