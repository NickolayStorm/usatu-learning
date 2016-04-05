SELECT DISTINCT "a-h" FROM cell; --убирает повторяющиеся
SELECT * FROM message WHERE text LIKE 'Hell%';
SELECT * FROM message WHERE text LIKE 'Hell__';


SELECT * FROM piece ORDER BY name DESC; -- сортировка в обратную сторону
SELECT * FROM player ORDER BY id ASC; -- сортировка напрямую

SELECT COUNT(*) FROM piece WHERE id != 1;

LAB3=# SELECT name, COUNT(*) FROM piece GROUP BY name HAVING COUNT(*) = 1; --имеется

SELECT * FROM state, piece WHERE state.id_piece = piece.id;
SELECT * FROM state JOIN piece ON state.id_piece = piece.id;
SELECT * FROM state, piece, cell WHERE state.id_piece = piece.id AND state.id_cell = cell.id;
SELECT *, ("a-h" + "1_8") AS SUM FROM cell; 
-- view

CREATE VIEW myview AS SELECT player.nick, games.id, games.player_2  FROM player, games WHERE player.id = games.player_1;


CREATE VIEW myview AS SELECT *, ("a-h" + "1_8") AS SUM FROM cell; 
 UPDATE myview SET "a-h" = 10  WHERE "a-h" = 8;
DELETE FROM myview WHERE "a-h" = 10;
INSERT INTO myview ("a-h", "1_8") VALUES (8,3);
