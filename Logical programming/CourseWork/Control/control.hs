

module Main where

    import Cards
    import Logical

-- костылинг для пафосного кода
    import Prelude hiding (return)

    import Data.Maybe()
    import Data.List
    import System.Environment
    import Debug.Trace()


    return :: a -> Logic Card a
    return = Question

    -- Отбиваемся как б-ги
    -- Рука, отбиваемая карта, ко33ырь -> вернем отбившую карту
    findFightBack :: Hand -> Card -> Suit -> Maybe Card
    findFightBack cards card trump = let
                    -- Лучшей картой будет та, 
                    -- которой отбиться меньшая стоимость ->
                    -- отсортируем по достоинству
                    sorts = sortBy ordCard cards

                    rez = return (sorts, card) <<= 
                        -- Пытаемся отбиться без козырей
                        (\(cds, c)
                             -> let 
                                    suitable = dropWhile (not . isFightBackNormal c) cds
                                in if null suitable
                                    then return (cds, c)
                                else Answer (head suitable)) <<=
                        -- Не отбились обычными, здесь уже нужен ко33ырь 
                        (\(cds, c)
                            -> let 
                                    trumps = filter (isTrump trump) cds
                                    suitable = dropWhile (not . isFightBackTrump c) trumps
                                in if null suitable
                                    then return (cds, c)
                                else Answer (head suitable))
                     in 
                        toMaybe rez
            where
                -- первая карта, которую надо отбить
                -- вторая отбивающая
                isFightBackNormal :: Card -> Card -> Bool
                isFightBackNormal (Card s a) (Card s2 a2) | s == s2 = a < a2
                                                          | otherwise = False
                --сюда гарантированно передается ко33ырь
                isFightBackTrump :: Card -> Card -> Bool
                isFightBackTrump (Card s a) (Card s2 a2) | s /= s2 = True -- Ко33ырь бьет всё, что угодно, если вторая карта не ко33ырь
                                                         -- ситуация козырь на козырь
                                                         | otherwise = isFightBackNormal (Card s a) (Card s2 a2)

    fightBack :: [String] -> String
    fightBack ss = let
                -- парсим имеющиеся карты до флага отбиваемой карты
                handCards = parseHand (takeWhile ( /= "--slugger") ss) 
                --затем идет флаг, затем отбиваемая карта, затем флаг, затем кто по масти
                --ещё бы обработку ошибок впилить для этого кортежа
                ( _ : sl1 : sl2 : sl3 : _ : strTrump :_) = dropWhile (/= "--slugger") ss
                slugger = parseCard (sl1 ++ " " ++ sl2 ++ " " ++ sl3)
                trump = parseSuit strTrump
                    in maybe "Not strayed" show (findFightBack handCards slugger trump)

    gradeHand :: Hand -> Suit -> Advantage
    gradeHand hand trump | length (filter (isTrump trump) hand) + 1 >= length (filter (not . isTrump trump) hand) = J
                            -- Пояснение: если козырей почти столько же, сколько обычных карт, рука сильная
                            -- И с J ходить норм
                         | otherwise = intToAdv (gradeHand' (map getAdv hand))
                            -- Иначе просто посчитаем среднюю стоимость карт
            where
                gradeHand' = foldr ((+) . gradeAdvantage) 0


    findMove :: Hand -> [(Card, Card)] -> Suit -> Bool -> Maybe Card
    -- карты кончились, хода не будет
    findMove [] _ _ _ = Nothing 
    --отсортируем карты
    -- преобразуем получившийся в findMove' Logic-ответ в Maybe
    findMove h p s b = findMove' (sortBy ordCard h) p s b
            where 
        findMove':: Hand -> [(Card, Card)] -> Suit -> Bool -> Maybe Card
        --если просто ходим, а не подкидываем
            -- агрессивный режим
            -- оценим нашу руку с помощью gradeHand
        findMove' hand [] trump True = toMaybe (return (hand, trump, gradeHand hand trump) <<= 
                                            --в конце играем агрессивно
                                            --пробуем ходить парой, ограниченной оценкой
                                            --без козырей
                                        movePairWithoutTrump <<=
                                            -- не вышло? можно и козырную комбинацию
                                        movePair <<=
                                            -- если пары нет, то просто сходим минимальным не козырем
                                        minimalCost <<=
                                            -- если нет, минимальным козырем
                                        minimalTrump)
            -- не агрессивный
        findMove' hand [] trump False = toMaybe (return (hand, trump, Nine) <<= 
                                            --иначе считаем карты выше 9 слишком сильными для создания пары
                                        movePairWithoutTrump <<=
                                        minimalCost <<=
                                        minimalTrump)
        -- Теперь если мы подкидываем
            -- Агрессивный режим
        findMove' hand thrownrepul t True = toMaybe (return (hand, thrownrepul, t, gradeHand hand t) <<=
                                        moveAlreadyThrown <<=
                                        moveAlreadyThrownTrump <<=
                                        moveSlugger <<=
                                        moveSluggerTrump)

            -- Не агрессивный
        findMove' hand thrownrepul t False = toMaybe (return (hand, thrownrepul, t, gradeHand hand t) <<=
                                        moveAlreadyThrown <<=
                                        moveSlugger)


        moveAlreadyThrown (hand, pairs, t, a) = let
                                --берем карты, которые подкинули мы
                            alreadyThrowned = map fst pairs
                            cards = withoutTrump t hand
                            pair = findPair (sortBy ordCard (alreadyThrowned ++ cards))
                                -- Нашли -> ответ, нет -> следующий предикат
                                in case pair of
                                    Just c -> Answer c
                                    Nothing -> Question (hand, pairs, t, a)

        moveAlreadyThrownTrump (hand, pairs, t, a) = let
                                -- берем карты, которые подкинули мы
                            alreadyThrowned = map fst pairs
                                -- не будем выкидывать слишком дорогие козыри
                                -- ??????????????????????????????? косяк в логике, 
                                -- например, хотели выкинуть высокую пару, 
                                -- а теперь рука стала слабее и зажали
                                -- наплевать
                            cards = filter (\x -> not (isTrump t x) || (getAdv x < a)) hand
                            pair = findPair (sortBy ordCard (alreadyThrowned ++ cards))
                                -- Нашли -> ответ, нет -> следующий предикат
                                in case pair of
                                    Just c -> Answer c
                                    Nothing -> Question (hand, pairs, t, a)

        moveSlugger (hand, pairs, t, a) = let
                            lessThen = takeWhile ((<) a . getAdv) hand
                            cards = withoutTrump t lessThen
                            slugger = map snd pairs
                            pair = findPair (sortBy ordCard (slugger ++ cards))
                                in case pair of
                                    Just c -> Answer c
                                    Nothing -> Question (hand, pairs, t, a)

        moveSluggerTrump (hand, pairs, t, a) = let
                            cards = takeWhile ((<) a . getAdv) hand
                            slugger = map snd pairs
                            pair = findPair (sortBy ordCard (slugger ++ cards))
                                in case pair of
                                    Just c -> Answer c
                                    Nothing -> Question (hand, pairs, t, a)

        movePairWithoutTrump (hand, t, maxAdv) = let
                                -- Возьмем подходящие по крупности
                            lessThen = takeWhile ((<) maxAdv . getAdv) hand
                                -- Выкинем ко33ыри и
                                -- найдем минимальную пару
                            pair = findPair (withoutTrump t lessThen)
                                -- Нашли -> ответ, нет -> следующий предикат
                                in case pair of
                                    Just a -> Answer a
                                    Nothing -> Question (hand, t, maxAdv)

        movePair (hand, t, maxAdv) = let
                                -- Возьмем подходящие по крупности
                            lessThen = takeWhile ((<) maxAdv . getAdv) hand
                                -- найдем минимальную пару
                            pair = findPair lessThen
                                -- Нашли -> ответ, нет -> следующий предикат
                                in case pair of
                                    Just a -> Answer a
                                    Nothing -> Question (hand, t, maxAdv)

        minimalCost (hand, t, maxAdv) = let
                            cards = withoutTrump t hand
                                in case cards of 
                                (c:_) -> Answer c
                                _ -> Question (hand, t, maxAdv)

        minimalTrump (t:_, _, _) = Answer t
        minimalTrump _ = error "(findMove.minimalTrump): Видимо, рука пуста"

        withoutTrump t = filter (not . isTrump t)

        findPair :: Hand -> Maybe Card
        findPair [] = Nothing
        findPair [_] = Nothing
        findPair (c1:c2:residue) | getAdv c1 == getAdv c2 = Just c1
                                 | otherwise = findPair (c2:residue)


    move :: [String] -> String
    move args = let
            handStr = takeWhile ( /= "--thrownrepulsed") args -- флаг кинутых-отбитых карт
            hand = parseHand handStr
            ( _ : afterHand ) = dropWhile (/= "--thrownrepulsed") args --флаг обязателен
            thrownRepulsedStr = takeWhile (/= "--trump") afterHand -- пары карт кинул-отбил
            thrownReplused = parseHand thrownRepulsedStr -- парсим как набор карт
            --тепрь нужно составить из них пары
            thrownReplusedPairs = makePair thrownReplused
            ( _ : strTrump : flags) = dropWhile (/= "--trump") args --козырь
            -- флаг того, что игра на финишной, ещё флаги?
            endMode = flags == ["--endmode"]
            trump = parseSuit strTrump
                in maybe "Bat" show (findMove hand thrownReplusedPairs trump endMode)
        where
            makePair [] = []
            makePair [_] = error "Карта не побита алё"
            makePair (f:s:cards) = (f, s) : makePair cards

    main :: IO()
    main = do
        arguments <- getArgs
        case arguments of
            (mode:args) -> putStr $ case mode of  
                            "--fight_back" -> fightBack args
                            "--move"       -> move args
                            "--help"       -> concat help
                            _              -> "undefined mode"
            _ -> error "No args."


    help :: [String]
    help = ["\nИскуственный интеллект для игры в русского дурака\n",
            "Использование:\n",
            "    --fight_back Флаг отбития карты.\n",
            "        Синтаксис команды: --fight_back набор карт в руке ",
            "--sluger карта, которую нужно отбить --trump козырная масть\n",
            "    --move Флаг хода ИИ\n",
            "        Синтаксис команды: --move набор карт в руке ",
            "--thrownrepulsed пары карта-отбившая карта --trump козырь [--endmode]\n",
            "    --endmode Флаг, означающий, что игра подоходит к концу ",
            "и что пора действовать агрессивней\n\n",
            "Карта задается в виде: Card Hearts J\n",
            "Козырь в виде: Clubs\n",
            "Ответ получается в виде карты, например: Card Spades Seven\n",
            "Если ход окончен, ответом будет Bat\n\n"
        ]

        -- ./control --fight_back Card Hearts Seven Card Hearts Six --slugger Card Hearts J --trump Hearts
        -- ./control --move Card Heartpulsed Card Hearts J Card Hearts K --trump Hearts

