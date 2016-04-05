--DROP FUNCTION create_new_field(int);
 
 CREATE OR REPLACE FUNCTION create_new_field(id_new_game int) RETURNS void 
	AS $$
BEGIN
	INSERT INTO "state"(id_game, id_piece, cell_18, cell_ah) 
           VALUES 
               (id_new_game, 1, 1, 1),
               (id_new_game, 2, 1, 2),
			   (id_new_game, 3, 1, 3),
			   (id_new_game, 4, 1, 4),
			   (id_new_game, 5, 1, 5),
			   (id_new_game, 3, 1, 6),
			   (id_new_game, 2, 1, 7),
			   (id_new_game, 1, 1, 8), --WHITE
					   
			   (id_new_game, 7, 8, 1),
			   (id_new_game, 8, 8, 2),
			   (id_new_game, 9, 8, 3),
			   (id_new_game, 11, 8, 4),
			   (id_new_game, 10, 8, 5),
			   (id_new_game, 9, 8, 6),
			   (id_new_game, 8, 8, 7),
			   (id_new_game, 7, 8, 8), -- BLACK
				   
			   (id_new_game, 6, 2, 1),
			   (id_new_game, 6, 2, 2),
			   (id_new_game, 6, 2, 3),
			   (id_new_game, 6, 2, 4),
			   (id_new_game, 6, 2, 5),
			   (id_new_game, 6, 2, 6),
			   (id_new_game, 6, 2, 7),
			   (id_new_game, 6, 2, 8), --WHITE PAWN
						   
			   (id_new_game, 12, 7, 1),
			   (id_new_game, 12, 7, 2),
			   (id_new_game, 12, 7, 3),
			   (id_new_game, 12, 7, 4),
			   (id_new_game, 12, 7, 5),
			   (id_new_game, 12, 7, 6),
			   (id_new_game, 12, 7, 7),
			   (id_new_game, 12, 7, 8);
							   
END;
$$ LANGUAGE plpgsql;


-- CREATE TABLE "state" (
    -- "id_game" INTEGER NOT NULL ,
    -- "id_piece" INTEGER ,
    -- "cell_ah" SMALLINT NOT NULL ,
    -- "cell_18" INTEGER ,
    -- "isExist" BOOLEAN ,
        -- PRIMARY KEY ("id_game", "id_piece", "cell_18", "cell_ah")
-- );
