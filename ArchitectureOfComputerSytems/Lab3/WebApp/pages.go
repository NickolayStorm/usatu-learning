package main

import (
	"github.com/go-martini/martini"
	"github.com/martini-contrib/sessions"
	"html/template"
	"log"
	"net/http"
	"strconv"
	"strings"
)

// PAGES:

var temp = "Templates/"
var templates = template.Must(
	template.ParseFiles(
		temp+"users.html",
		temp+"edit.html",
		temp+"create.html",
		temp+"autorization.html",
		temp+"registration.html",
		temp+"mainPage.html"))

type Post struct {
	Id      int
	Title   string
	Autor   string
	Text    string
	Image   string
	Time    string
	Editing bool
}

type Page struct {
	Title      string
	Username   string
	Error      string
	Posts      []Post
	Body       string
	permission string
	Id         int
	Image      string
}

type Users struct {
	Id []int
	Name []string
	Time []string
}

func renderTemplate(w http.ResponseWriter, tmpl string, p *Page) {
	err := templates.ExecuteTemplate(w, tmpl+".html", p)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

// HANDLERS:

func loginHandler(r *http.Request, db *Database, session sessions.Session, w http.ResponseWriter) {
	log.Println("Login Handler")
	name := r.FormValue("username")
	password := r.FormValue("password")
	is, id, permission := db.is_user_valid(name, password)
	if is {
		session.Set("id", id)
		session.Set("nick", name)
		session.Set("permission", permission)
		return
	}
	p := &Page{
		Title: "попробуйте снова",
		Error: "Oops! wrong username/password",
	}
	renderTemplate(w, "autorization", p)
}

func hiddenHandler(session sessions.Session) string {
	gid := session.Get("id")
	gnick := session.Get("nick")
	var (
		id   int
		nick string
	)
	if gid == nil {
		return "<iframe width=\"100%\" height=\"100%\"  src=\"https://www.youtube.com/embed/dQw4w9WgXcQ?autoplay=1&cc_load_policy=1\" frameborder=\"0\" allowfullscreen></iframe>"
	}
	id = gid.(int)
	nick = gnick.(string)
	return "Твое лицо, id = " + strconv.Itoa(id) + ", когда ты видишь скрытые страницы, " + nick + "."
}

func newPostHandler(session sessions.Session, w http.ResponseWriter) {
	gid := session.Get("id")
	if gid != nil {
		p := &Page{}
		renderTemplate(w, "create", p)
	}
}

func createPostHandler(r *http.Request, session sessions.Session, db *Database) {
	gid := session.Get("id")
	if gid != nil {
		id := gid.(int)
		title := r.FormValue("title")
		body := r.FormValue("body")
		image := r.FormValue("image")
		log.Println("Create post" + title)
		db.create_post(id, title, image, body)

	}
}

func logoutHandler(session sessions.Session) {
	log.Println("Logout")
	session.Clear()
}

func mainHandler(session sessions.Session, w http.ResponseWriter, db *Database) {
	gnick := session.Get("nick")
	gpremis := session.Get("permission")
	if gnick != nil {
		nick := gnick.(string)
		permission := gpremis.(string)
		posts, _ := db.get_posts()

		if permission == "admin     " {
			log.Println("permission is admin")
			for i, _ := range posts {
				log.Println(posts[i].Title)
				posts[i].Editing = true
			}
		} else {
			for i, _ := range posts {
				if strings.Compare(posts[i].Autor, nick) == 0 {
					posts[i].Editing = true
				}
			}
		}

		for _, p := range posts {
			log.Println(p.Editing)
		}

		p := &Page{
			Username:   nick,
			permission: permission,
			Posts:      posts,
		}
		renderTemplate(w, "mainPage", p)
	}
}

func editHandler(session sessions.Session, db *Database, params martini.Params, w http.ResponseWriter) {
	id, err := strconv.Atoi(params["id"])
	if err != nil {
		return
	}
	autor, title, image, body, err := db.get_post(id)

	if err == nil {
		gnick := session.Get("nick")
		gpremis := session.Get("permission")
		if gnick != nil {
			permission := gpremis.(string)
			nick := gnick.(string)
			log.Println([]byte(autor))
			log.Println([]byte(nick))
			if permission == "admin     " || nick == autor {
				log.Println("permission exists")
				p := &Page{
					Id:    id,
					Title: title,
					Body:  body,
					Image: image,
				}
				renderTemplate(w, "edit", p)
			}
		}
	} else {
		log.Println(err)
	}
}

func saveHandler(r *http.Request, session sessions.Session, params martini.Params, db *Database) {
	id, err := strconv.Atoi(params["id"])
	if err != nil {
		return
	}

	gnick := session.Get("nick")
	gpremis := session.Get("permission")
	if gpremis != nil {
		permission := gpremis.(string)
		nick := gnick.(string)
		autor, _ := db.get_post_autor(id)
		if permission == "admin     " || nick == autor {
			log.Println("permission exists")
			title := r.FormValue("title")
			body := r.FormValue("body")
			image := r.FormValue("image")
			db.update_post(id, title, image, body)
		}

	}

}

func autorizationHandler(session sessions.Session, w http.ResponseWriter) {
	gid := session.Get("id")
	if gid == nil {
		p := &Page{
			Title: "Hello!",
		}
		renderTemplate(w, "autorization", p)
	}
}

func registrationPageHandler(session sessions.Session, w http.ResponseWriter) {
	gnick := session.Get("nick")
	if gnick != nil {
		return
	}
	p := &Page{}
	renderTemplate(w, "registration", p)
}

func registrateHandler(r *http.Request, db *Database, w http.ResponseWriter, session sessions.Session) {
	gnick := session.Get("nick")
	if gnick != nil {
		return
	}

	log.Println("Registrate handler")
	nick := r.FormValue("email")
	password := r.FormValue("password")

	id, err := db.add_user(nick, password)

	if err != nil {
		p := &Page{
			Error: "Пользователь с таким именем уже существует!",
		}
		renderTemplate(w, "registration", p)
	} else {

		session.Set("id", id)
		session.Set("nick", nick)
		session.Set("permission", "user")
	}
}

func changeUserPageHandler(db *Database, w http.ResponseWriter, session sessions.Session) {
	gpremis := session.Get("permission")

	if gpremis == nil {
		return
	}

	permission := gpremis.(string)
	if permission == "admin     " {

		posts, err := db.get_users()

		if err != nil{
			return
		}

		p := &Page{
			Posts: posts,
		}
		renderTemplate(w, "users", p)
	}

}

func removeUserHandler(r *http.Request, db *Database,  params martini.Params, w http.ResponseWriter, session sessions.Session) {
	gpremis := session.Get("permission")

	if gpremis == nil {
		return
	}

	permission := gpremis.(string)
	if permission == "admin     " {

		id, err := strconv.Atoi(params["id"])
		if err != nil {
			return
		}
		db.remove_user(id)

		gid := session.Get("id")

		my_id := gid.(int)

		if id == my_id {
			log.Println("Самоудаление")
			session.Clear()
		}
	}

}
