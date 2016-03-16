module Cards where

    data Suit = Hearts | Diamonds | Clubs | Spades deriving (Show, Read, Eq)
    
    data Advantage = Six | Seven | Eight | Nine | Ten | J | Q | K | A deriving (Show, Read, Eq, Ord)
    
    data Card = Card Suit Advantage deriving (Show, Read)

    type Hand = [Card]

    --Для сортировки карт по стоимости
    ordCard :: Card -> Card -> Ordering
    ordCard (Card _ a) (Card _ a2) = compare a a2 

    parseCard :: String -> Card
    parseCard = read

    parseSuit :: String -> Suit
    parseSuit = read
 
    parseHand :: [String] -> [Card]
    parseHand [] = []
    parseHand (c:h:a:strs) = parseCard (c ++ " " ++ h ++ " " ++ a) : parseHand strs
    parseHand _ = error "Parse error"


    getAdv :: Card -> Advantage
    getAdv (Card _ a) = a

    isTrump :: Suit -> Card -> Bool
    isTrump t (Card s _) = s == t

    gradeAdvantage :: Advantage -> Int
    gradeAdvantage Six = -4
    gradeAdvantage Seven = -3
    gradeAdvantage Eight = -2
    gradeAdvantage Nine = -1
    gradeAdvantage Ten = 0
    gradeAdvantage J = 1
    gradeAdvantage Q = 2
    gradeAdvantage K = 3
    gradeAdvantage A = 4

    intToAdv :: Int -> Advantage
    intToAdv (-4) = Six
    intToAdv (-3) = Seven
    intToAdv (-2) = Eight
    intToAdv (-1) = Nine
    intToAdv 0 = Ten
    intToAdv 1 = J
    intToAdv 2 = Q
    intToAdv 3 = K
    intToAdv 4 = A
    intToAdv _ = error "Undefined Advantage (intToAdv)"