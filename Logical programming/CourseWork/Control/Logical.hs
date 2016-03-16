
module Logical where

    -- Отсечение следующих, если ответ уже найден
    -- В логическом плане Noth -> False, Answer -> True
    data Logic a arg = Question arg | Answer a

    isAnswer :: Logic a b -> Bool
    isAnswer (Question _) = False
    isAnswer _ = True

    unpack :: Logic a b -> a
    unpack (Answer c) = c
    unpack _ = undefined

    -- Так есть ли решение?
    toMaybe :: Logic a b -> Maybe a
    toMaybe r = if isAnswer r
                    then Just (unpack r) 
                else Nothing

    -- Антимонада Maybe
    -- Всё ради этого байнда, чтобы писать пафосный код 
    -- типа как monad >>= первая дизьюнкция >>= вторая лел
    (<<=) :: Logic a h -> (h -> Logic a h) -> Logic a h
    (<<=) (Question h) f = f h
    (<<=) (Answer c) _ = Answer c