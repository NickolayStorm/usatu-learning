CREATE TABLE "player" (
    "id"  SERIAL NOT NULL ,
    "nick" VARCHAR(20) UNIQUE NOT NULL ,
    "reg_date" TIMESTAMP DEFAULT NOW(),
    "pas_hash" VARCHAR(20) NOT NULL ,
    "online" BOOLEAN DEFAULT TRUE,
        PRIMARY KEY ("id")
);

CREATE TABLE "piece" (
    "id"  SERIAL NOT NULL ,
    "name" VARCHAR(20) NOT NULL ,
        PRIMARY KEY ("id")
);

CREATE TABLE "games" (
    "id"  SERIAL NOT NULL ,
    "player_1" INTEGER NOT NULL ,
    "player_2" INTEGER NOT NULL ,
    "move" BOOLEAN DEFAULT TRUE ,
    "complete" BOOLEAN DEFAULT FALSE ,
    "start_time" TIMESTAMP DEFAULT NOW(),
        PRIMARY KEY ("id")
);

CREATE TABLE "message" (
    "id_game" INTEGER NOT NULL ,
    "id_player" INTEGER NOT NULL ,
    "time" TIMESTAMP NOT NULL ,
    "text" CHAR(200) NOT NULL ,
        PRIMARY KEY ("id_game", "id_player", "time")
);

CREATE TABLE "piece_turn" (
    "id"  SERIAL ,
    "piece" INTEGER NOT NULL ,
    "a-h" SMALLINT NOT NULL ,
    "1_8" SMALLINT NOT NULL ,
    "move" BOOLEAN , -- ограничение на ход
    "chop" BOOLEAN, -- ограничение на срубание
        PRIMARY KEY ("id")
);

CREATE TABLE "game_turn" (
    "id_game" INTEGER NOT NULL ,
    "player_id" INTEGER NOT NULL, --НЕ СВЯЗААННО С PLAYER !!!! TODO
    "id_piece" INTEGER ,
	"prev_piece_position_ah" SMALLINT NOT NULL,
	"prev_piece_position_18" SMALLINT NOT NULL ,
    "id_turn" INTEGER ,
    "time" TIMESTAMP DEFAULT NOW(),
        PRIMARY KEY ("id_game", "time")
);

CREATE TABLE "state" (
	"id" SERIAL NOT NULL,
    "id_game" INTEGER NOT NULL ,
    "id_piece" INTEGER ,
    "cell_ah" SMALLINT NOT NULL ,
    "cell_18" SMALLINT NOT NULL ,
    "isExist" BOOLEAN DEFAULT TRUE ,
        PRIMARY KEY ("id")
);

ALTER TABLE "games" ADD FOREIGN KEY ("player_1") REFERENCES "player" ("id");
ALTER TABLE "games" ADD FOREIGN KEY ("player_2") REFERENCES "player" ("id");
ALTER TABLE "message" ADD FOREIGN KEY ("id_game") REFERENCES "games" ("id");
ALTER TABLE "piece_turn" ADD FOREIGN KEY ("piece") REFERENCES "piece" ("id");
ALTER TABLE "game_turn" ADD FOREIGN KEY ("id_game") REFERENCES "games" ("id");
ALTER TABLE "game_turn" ADD FOREIGN KEY ("id_turn") REFERENCES "piece_turn" ("id");
ALTER TABLE "game_turn" ADD FOREIGN KEY ("id_piece") REFERENCES "piece" ("id");
ALTER TABLE "state" ADD FOREIGN KEY ("id_game") REFERENCES "games" ("id");
ALTER TABLE "state" ADD FOREIGN KEY ("id_piece") REFERENCES "piece" ("id");
