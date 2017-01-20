package main

import (
	"crypto/sha1"
	"database/sql"
	"encoding/hex"
	"encoding/json"
	"errors"
	_ "github.com/lib/pq"
	"io/ioutil"
	"log"
	"strconv"
	"time"
)

type Database struct {
	name string
	db   *sql.DB
}

type Config struct {
	Database struct {
		Name     string `json:"name"`
		Address  string `json:"address"`
		Password string `json:"password"`
		Port     string `json:"port"`
		User     string `json:"user"`
	} `json:"Database"`
}

func make_db_conf() string {

	config, err := ioutil.ReadFile("config.json")
	if err != nil {
		panic(err)
	}

	conf := Config{}
	err = json.Unmarshal(config, &conf)
	if err != nil {
		panic(err)
	}

	connOptions := "user=" + conf.Database.User +
		" password=" + conf.Database.Password +
		" host=" + conf.Database.Address +
		" port=" + conf.Database.Port +
		" dbname=" + conf.Database.Name +
		" sslmode=disable"

	return connOptions
}

func (d *Database) init() {

	d.name = "postgres"

	conf := make_db_conf()
	db, err := sql.Open(d.name, conf)
	log.Print("Open database " + d.name)
	if err != nil {
		log.Fatal(err)
	}

	err = db.Ping()
	log.Print("Conn params: " + conf)
	if err != nil {
		log.Fatal(err)
	}

	d.db = db
}

func (db *Database) user_info(nick string, key string) (int, string, error) {
	rows, err := db.db.Query(
		"SELECT id, premmision FROM users WHERE nick = $1 AND pas_hash = $2",
		nick, key)
	defer rows.Close()

	if err != nil {
		log.Println("Select неверный")
		log.Fatal(err)
		return 0, string(""), err
	}

	var id int
	var premission string

	for rows.Next() {
		err = rows.Scan(&id, &premission)
		if err != nil {
			log.Println("Rows не rows")
			log.Println(err)
			return 0, string(""), err
		}
		log.Println([]byte(premission))
		return id, premission, nil
	}

	return 0, string(""), errors.New("Unexist")
}

func (db *Database) get_posts() ([]Post, error) {
	rows, err := db.db.Query(
		"SELECT posts.id, nick, title, text, image, time FROM posts INNER JOIN \"users\" ON posts.user_id = users.id ORDER BY posts.id DESC")
	defer rows.Close()

	var posts []Post

	n := 0

	for rows.Next() {
		var id int
		var name string
		var title string
		var text string
		var image string
		var date time.Time

		err = rows.Scan(&id, &name, &title, &text, &image, &date)
		if err != nil {
			log.Println("Rows не rows")
			log.Println(err)
			break
		}

		var post Post
		post.Id = id
		post.Autor = name
		post.Text = text
		post.Title = title
		post.Editing = false
		post.Image = image

		y, m, d := date.Date()

		myDate := strconv.Itoa(d) + " " + m.String() + " " + strconv.Itoa(y)

		post.Time = myDate

		newPosts := make([]Post, n+1)
		copy(newPosts, posts)

		posts = newPosts
		posts[n] = post

		n = n + 1
	}
	return posts, err

}

func (db Database) get_post_autor(id int) (string, error) {
	rows, err := db.db.Query(
		"SELECT nick FROM posts INNER JOIN \"users\" ON posts.user_id = users.id WHERE posts.id = $1", id)
	defer rows.Close()
	if err != nil {
		return "", err
	}
	var autor string
	for rows.Next() {
		err = rows.Scan(&autor)
		if err != nil {
			return "", err
		}
	}
	return autor, err
}

func (db Database) create_post(id int, title string, image string, body string) {
	_, err := db.db.Exec(
		"INSERT INTO \"posts\" (\"user_id\", \"title\", image, \"text\") values ($1, $2, $3, $4)",
		id, title, image, body)
	if err != nil {
		log.Println(err)
	}
}

func (db *Database) get_post(id int) (autor string, title string, image string, body string, err error) {
	rows, err := db.db.Query(
		"SELECT nick, title, image, text FROM posts INNER JOIN \"users\" ON posts.user_id = users.id WHERE posts.id = $1", id)
	defer rows.Close()

	if err != nil {
		log.Println(err)
	} else {
		for rows.Next() {
			err = rows.Scan(&autor, &title, &image, &body)
			if err != nil {
				log.Println(err)
			}
		}
	}
	return
}

func (db *Database) update_post(id int, title string, image string, body string) {

	db.db.Exec("UPDATE posts SET title = $1, image = $2, text = $3 WHERE id = $4", title, image, body, id)
}

func (db *Database) is_user_valid(nick string, pass string) (bool, int, string) {
	key := sha1.Sum([]byte(pass))
	strKey := hex.EncodeToString(key[:])
	id, premission, err := db.user_info(nick, strKey)
	if err != nil {
		return false, id, string("")
	}
	return true, id, premission
}

func (db *Database) get_users() ([]Post, error){

	log.Println("get_users()")
	rows, err := db.db.Query(
		"SELECT * FROM \"users\"")
	defer rows.Close()

	if err != nil {
		log.Println(err)
	}

	var posts []Post

	n := 0
	for rows.Next() {
		var id int
		var name string
		var permission string
		var key string
		var date time.Time

		err = rows.Scan(&id, &name, &permission, &key, &date)
		if err != nil {
			log.Println("Rows не rows")
			log.Println(err)
			break
		}

		var post Post
		post.Id = id
		post.Autor = name
		post.Text = key
		post.Title = permission

		y, m, d := date.Date()

		myDate := strconv.Itoa(d) + " " + m.String() + " " + strconv.Itoa(y)

		post.Time = myDate

		newPosts := make([]Post, n+1)
		copy(newPosts, posts)

		posts = newPosts
		posts[n] = post

		n = n + 1
	}

	return posts, err


}

func (db *Database) remove_user(id int){
	log.Println("remove_user()")
	_, err := db.db.Exec(
		"DELETE FROM \"posts\" * WHERE user_id = $1", id)
	if err != nil {
		log.Println("Ops in add_user()")
		log.Println(err)
		return
	}
	_, err = db.db.Exec(
		"DELETE FROM \"users\" * WHERE id = $1", id)
	if err != nil {
		log.Println("Ops in add_user()")
		log.Println(err)
		return
	}

}

func (db *Database) add_user(nick string, pass string) (int, error) {
	log.Println("add_user()")
	key := sha1.Sum([]byte(pass))
	strKey := hex.EncodeToString(key[:])
	_, err := db.db.Exec(
		"INSERT INTO \"users\" (\"nick\", \"premmision\", \"pas_hash\") VALUES ($1, $2, $3)",
		nick, "user", strKey)

	if err != nil {
		log.Println("Ops in add_user()")
		log.Println(err)
		return 0, err
	}

	id, _, err := db.user_info(nick, strKey)

	return id, err
}
