CREATE OR REPLACE FUNCTION is_can_move(

				_player_id INT, _id_game INT, _id_piece INT, 
				_prev_18 INT, _prev_ah INT, 
				_curr_18 INT, _curr_ah INT
				) RETURNS BOOLEAN 
AS $$
DECLARE 
_curr_move BOOLEAN;
_vec_18 INT;
_vec_ah INT;
_count INT;
_diff_move BOOLEAN;
_diff_chop BOOLEAN;
_is_somth_exist_on_a_new_cell BOOLEAN;
_id_turn INT;


BEGIN 
	--проверка, а затем:
	-- есть ли доп условия, 
	-- проверить, не срублена ли другая фигура
	-- прогнать на условия
	-- и "срубить" другую фигуру, если нужно
	-- кстати, и проверки на существование игры тоже бы не помешали

-- проверка на выход за границы
	
	IF _curr_18 < 1 OR _curr_18 > 8 OR _curr_ah < 1 OR _curr_18 > 8 THEN
		RETURN FALSE;
	END IF;

--поиск нужного хода	
	_vec_18 = _curr_18 - _prev_18;
	_vec_ah = _curr_ah - _prev_ah;
	
	SELECT COUNT(*), "move", "chop", "id" INTO
		   _count, _diff_move, _diff_chop, _id_turn 
		FROM "piece_turn" 
	WHERE "piece" = _id_piece AND
		  "a-h" = _vec_ah AND
		  "1_8" = _vec_18
	GROUP BY id;
		  
--если такого хода нет, сразу зарубаем		  
	IF _count is NULL THEN 
		RETURN FALSE;
	END IF;
	
	-- коллижен ТМ
	IF 	check_collision(_id_turn, _id_game, _id_piece,
						 _prev_ah, _prev_18, 
						 _curr_ah, _curr_18
						) 
			= FALSE 
	THEN 
		RETURN FALSE;
	END IF;

	SELECT "isExist" INTO 
			_is_somth_exist_on_a_new_cell
		FROM "state" 
	WHERE id_game = _id_game AND 
			 "cell_18" = _curr_18 AND 
			 "cell_ah" = _curr_ah AND 
			 "isExist" = TRUE;

	RETURN TRUE;
END;
$$ LANGUAGE plpgsql;
