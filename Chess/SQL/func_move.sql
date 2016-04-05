CREATE OR REPLACE FUNCTION move(
				_player_id INT, _id_game INT, _id_piece INT, 
				_prev_18 INT, _prev_ah INT, 
				_curr_18 INT, _curr_ah INT
				) 
		RETURNS BOOLEAN 
AS $$
DECLARE
_curr_move BOOLEAN; 
_is_somth_exist_on_a_new_cell BOOLEAN;
BEGIN
		IF NOT is_can_move(_player_id, _id_game, _id_piece, _prev_18, _prev_ah, _curr_18, _curr_ah) THEN
			RETURN FALSE;
		END IF;
		
	-- SELECT "isExist" INTO 
			-- _is_somth_exist_on_a_new_cell
		-- FROM "state" 
	-- WHERE id_game = _id_game AND 
			 -- "1_8" = _new_18 AND 
			 -- "a-h" = _new_ah AND 
			 -- "isExist" = TRUE;
	
	--IF _is_somth_exist_on_a_new_cell = TRUE THEN
	--удоляем предыдущую фигуру
			UPDATE "state"
					SET "isExist" = FALSE
				WHERE
					"id_game" = _id_game AND
					"cell_ah" = _curr_ah AND
					"cell_18" = _curr_18;
	--END IF;
	--RAISE NOTICE 'count = %', _count;
--обновление текущего хода	
	SELECT "move" INTO _curr_move FROM "games" WHERE id = _id_game;
	
	UPDATE "games"
			SET "move" = NOT _curr_move
			WHERE id = _id_game;
--конец

--обновление состояния				
	UPDATE "state"
			SET "cell_ah" = _curr_ah,
				"cell_18" = _curr_18
		WHERE 
				"id_game" = _id_game AND
				"id_piece" = _id_piece AND
				"cell_ah" = _prev_ah AND
		   	    "cell_18" = _prev_18;
--конец				
		
--запись хода в историю		
	INSERT INTO game_turn VALUES(_id_game, _player_id, _id_piece, 
								_prev_ah, _prev_18, 
								1,--id_turn, высчитанный и няшный
								NOW()
								);
								
--конец
	RETURN TRUE;
END;
$$ LANGUAGE plpgsql;
--select move(1,1,1,1,1,1,1);
-- CREATE TABLE "state" (
    -- "id_game" INTEGER NOT NULL ,
    -- "id_piece" INTEGER ,
    -- "cell_ah" SMALLINT NOT NULL ,
    -- "cell_18" INTEGER ,
    -- "isExist" BOOLEAN DEFAULT TRUE ,
        -- PRIMARY KEY ("id_game", "id_piece", "cell_18", "cell_ah")
-- );
-- CREATE TABLE "game_turn" (
    -- "id_game" INTEGER NOT NULL ,
    -- "player_id" INTEGER NOT NULL, --НЕ СВЯЗААННО С PLAYER !!!! TODO
    -- "id_piece" INTEGER ,
	-- "prev_piece_position_ah" SMALLINT NOT NULL,
	-- "prev_piece_position_18" SMALLINT NOT NULL ,
    -- "id_turn" INTEGER ,
    -- "time" TIMESTAMP DEFAULT NOW(),
        -- PRIMARY KEY ("id_game", "time")
-- );
