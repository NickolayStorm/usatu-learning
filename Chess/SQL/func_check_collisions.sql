CREATE OR REPLACE 
	FUNCTION check_collision(_id_turn INT, _id_game INT, _id_piece INT,
							 _prev_ah INT, _prev_18 INT, 
							 _curr_ah INT, _curr_18 INT
							) 
			RETURNS BOOLEAN
AS $$
DECLARE
_curr_cell_x INT;
_curr_cell_y INT;
_step_x INT; 
_step_y INT;
_count INT;
_piece_on_a_curr_pos INT;
BEGIN
	SELECT "a-h", "1_8" INTO 
		   _step_x, _step_y 
	FROM "piece_turn" 
			WHERE id = _id_turn;
	--почему так? все фигуры ходят либо прямо либо наискосок, кроме коней, но у коней не нужно проверять коллизию
	IF _step_x < 0 THEN
		_step_x = -1;
	END IF;
	
	IF _step_x > 0 THEN
		_step_x = 1;
	END IF;
	
	IF _step_y < 0 THEN
		_step_y = -1;
	END IF;
	
	IF _step_y > 0 THEN
		_step_y = 1;
	END IF;
	
	_curr_cell_x = _prev_ah;
	_curr_cell_y = _prev_18;
	
	--короче, последнюю клетку нельзя проверять, так как, возможно, мы рубим (поэтому, -1) !!!
	WHILE 
		  _curr_cell_x < _curr_ah - 1 OR 
		  _curr_cell_y < _curr_18 - 1
	LOOP
			_curr_cell_x = _curr_cell_x + _step_x;
			_curr_cell_y = _curr_cell_y + _step_y;
		
			SELECT COUNT(*) INTO _count 
				FROM "state" 
			WHERE 
				"id_game" = _id_game AND 
				"cell_ah" = _curr_cell_x AND 
				"cell_18" = _curr_cell_y AND 
				"isExist" = TRUE;
			--RAISE NOTICE 'count = %', _count;
			IF NOT _count = 0 THEN
				RETURN FALSE;
			END IF;
		
	END LOOP;
	
	--если на этой клетке стоит фигура того же цвета
	
	SELECT "id_piece" INTO _piece_on_a_curr_pos 
		FROM "state"
	WHERE
		"id_game" = _id_game AND 
		"cell_ah" = _curr_ah AND 
		"cell_18" = _curr_18 AND 
		"isExist" = TRUE;
	IF NOT _piece_on_a_curr_pos is NULL THEN
	
		IF _id_piece < 7 AND _piece_on_a_curr_pos < 7 THEN 
			RETURN FALSE;
		END IF;
		
		IF _id_piece > 6 AND _piece_on_a_curr_pos > 7 THEN 
			RETURN FALSE;
		END IF;
	END IF;
	
	RETURN TRUE;
END;
$$ LANGUAGE plpgsql;
