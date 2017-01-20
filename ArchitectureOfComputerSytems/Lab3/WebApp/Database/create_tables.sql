CREATE TABLE "users" (
	"id" SERIAL NOT NULL,
	"nick" VARCHAR(20) UNIQUE NOT NULL,
	"premmision" CHAR(10),
	"pas_hash" CHAR(40) NOT NULL,
	"registration" TIMESTAMP DEFAULT NOW(),
		PRIMARY KEY ("id")
);

CREATE TABLE "info" (
	"user_id" INTEGER NOT NULL,
	"data" TEXT
);

ALTER TABLE "info" ADD FOREIGN KEY ("user_id") REFERENCES "users" ("id");

CREATE TABLE "posts" (
	"id" SERIAL NOT NULL,
	"user_id" INTEGER NOT NULL,
	"title" VARCHAR(200),
	"text" TEXT,
	"image" VARCHAR(200) DEFAULT 'images/pic01.jpg',
	"time" DATE DEFAULT NOW()
);

ALTER TABLE "posts" ADD FOREIGN KEY ("user_id") REFERENCES "users" ("id");
