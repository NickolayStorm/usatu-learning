import sys
import random

from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.uic import loadUi
import string
import subprocess
import queue

int_to_suit = {6: "Six",
7: "Seven",
8: "Eight",
9: "Nine",
10: "Ten",
11: "J",
12: "Q",
13: "K",
14: "A"}

suit_to_int = {"Six": 6, "Seven": 7, "Eight": 8, "Nine": 9, "Ten": 10, "J": 11, "Q": 12, "K": 13, "A": 14}

class Card(QGraphicsPixmapItem):
    def __init__(self, picture, suit, adv):
        super(Card, self).__init__(picture)
        self.suit = suit
        self.adv = adv
        self.isTrump = False

    def __str__(self):
        return "Card {} {}".format(self.adv, int_to_suit[self.suit])

def generate_cards():
    paths = ["./cards/6d.png",
    "./cards/6h.png",
    "./cards/6c.png",
    "./cards/6s.png",
    "./cards/7d.png",
    "./cards/7h.png",
    "./cards/7c.png",
    "./cards/7s.png",
    "./cards/8d.png",
    "./cards/8h.png",
    "./cards/8c.png",
    "./cards/8s.png",
    "./cards/9d.png",
    "./cards/9h.png",
    "./cards/9c.png",
    "./cards/9s.png",
    "./cards/10d.png",
    "./cards/10h.png",
    "./cards/10c.png",
    "./cards/10s.png",
    "./cards/11d.png",
    "./cards/11h.png",
    "./cards/11c.png",
    "./cards/11s.png",
    "./cards/12d.png",
    "./cards/12h.png",
    "./cards/12c.png",
    "./cards/12s.png",
    "./cards/13d.png",
    "./cards/13h.png",
    "./cards/13c.png",
    "./cards/13s.png",
    "./cards/14d.png",
    "./cards/14h.png",
    "./cards/14c.png",
    "./cards/14s.png"]

    pictures = list(map(QPixmap, paths))

    suit = [6, 7, 8, 9, 10, 11, 12, 13, 14]
    adv = ["Diamonds", "Hearts", "Clubs", "Spades"]

    i = 0
    cards = []
    for s in suit:
        for a in adv:
            cards.append(Card(pictures[i], s, a))
            i += 1
    return cards

indent_ii = QPoint(10, 10)
indent_card = 5
indent_player = QPoint(10, 410)
indent_table = QPoint(10, 165)

deck_pos = QPoint(780, 190)

class Game(QMainWindow):
    def __init__(self):
        super(Game, self).__init__()
        loadUi("view.ui", self)
        self.show()
        self.deck = None

        self.field = QGraphicsScene(0, 0, self.field_view.width(), self.field_view.height())
        self.field.setBackgroundBrush(QColor(42, 89, 57, 255))
        self.field_view.setScene(self.field)

        self.player_hand = []
        self.ii_hand = []
        self.table = []

        self.is_ii_move = True
        self.trump_card = None
        self.trump = None

        self.is_trow_up = False

        self.b_new_game.clicked.connect(self.new_game)
        self.b_bito.clicked.connect(self.press_bito)
        self.b_take.clicked.connect(self.press_take)

    def maybe_new_card(self):
        if self.deck.empty():
            self.field.removeItem(self.picture_deck)

            if self.trump_card:
                self.field.removeItem(self.trump_card)
                card = self.trump_card
                card.setRotation(-90)
                self.trump_card = None
                return card

            return None

        return self.deck.get()

    #109x161
    def add_cards(self):

        first_hand = None
        second_hand = None
        first_indent = None
        second_indent = None

        if self.is_ii_move:
            first_hand = self.ii_hand
            second_hand = self.player_hand
            first_indent = indent_ii
            second_indent = indent_player
        else:
            print("first_hand is player hand")
            second_hand = self.ii_hand
            first_hand = self.player_hand
            second_indent = indent_ii
            first_indent = indent_player

        while len(first_hand) < 6:
            card = self.maybe_new_card()
            if not card:
                return
            self.add_card(card, first_hand, first_indent)

        while len(second_hand) < 6:
            card = self.maybe_new_card()
            if not card:
                return
            card = self.deck.get()
            self.add_card(card, second_hand, second_indent)

    def add_card(self, card, hand, indent):
        place = 0
        while True:
            print(place)
            position = QPoint(place * (109 + indent_card + 20), 10) + indent
            c = self.field.itemAt(position, QTransform())
            if not c:
                break
            print(c)
            place += 1
        pos_x = place * (109 + indent_card)
        self.field.addItem(card)
        card.setPos(QPoint(pos_x, 0) + indent)
        hand.append(card)



    def new_game(self):
        print("New game")
        self.field.clear()
        self.deck = queue.Queue()

        deck_list = generate_cards()
        random.shuffle(deck_list)

        # self.player_hand = deck_list[0:5]
        # self.ii_hand = deck_list[6:11]
        self.trump_card = deck_list[0]
        deck_list = deck_list[1:]

        for c in deck_list:
            self.deck.put(c)

        self.add_cards()

        self.trump = self.trump_card.adv
        foo = lambda x: x.suit if x.adv == self.trump else 999
        ii_min = min(map(foo, self.ii_hand))
        player_min = min(map(foo, self.player_hand))

        # Раздать карты

        if ii_min < player_min:
            if ii_min == 999:
                return new_game()
            self.is_ii_move = True
            self.ii_attack()
        else:
            self.is_ii_move = False
        print("Trump: {}".format(self.trump))

        self.picture_deck = QGraphicsPixmapItem(QPixmap("./cards/r.png"))
        self.field.addItem(self.picture_deck)
        self.picture_deck.setPos(deck_pos)

        self.field.addItem(self.trump_card)
        self.trump_card.setPos(deck_pos + QPoint(50, 25))
        self.trump_card.setRotation(90)
        self.trump_card.setZValue(-1)



    def mousePressEvent(self, event):
        print("mousePressEvent: {}".format(event.pos()))
        print("ii_move: {}, is_trow_up: {}".format(self.is_ii_move, self.is_trow_up))
        if self.is_ii_move:
            if not self.is_trow_up:
                return
        click = event.pos()
        card = self.field.itemAt(click, QTransform())
        if card and card in self.player_hand:
            print(card)
            self.player_move(card)


    def player_move(self, card):
        # проверка, если можно ХХХХХХХ
        self.add_to_table(card)
        if not self.is_ii_move:
            self.ii_defense()
            return
        if self.is_trow_up:
            self.ii_attack()



    def add_to_table(self, card):

        print("add_to_table()")

        try:
            self.player_hand.remove(card)
        except:
            self.ii_hand.remove(card)

        count = len(self.table)
        pos_x = (count // 2) * (109 + indent_card)
        if count % 2 == 0:
            card.setPos(QPoint(pos_x, 0) + indent_table)
        else:
            card.setPos(QPoint(pos_x, 50) + indent_table)
            card.setZValue(999)
        self.table.append(card)


    def press_bito(self):
        if self.is_ii_move:
            return
        self.bito()


    def bito(self):
        if len(self.table) % 2 != 0:
            return

        for c in self.table:
            self.field.removeItem(c)

        self.add_cards()
        self.move_ends(False)


    def move_ends(self, is_take):
        self.table = []
        if not is_take:
            self.is_ii_move = not self.is_ii_move
        self.is_trow_up = False
        if self.is_ii_move:
            self.ii_attack()


    def press_take(self):
        if self.is_ii_move:
            if not self.is_trow_up:
                return
        self.take(self.player_hand, indent_player)


    def take(self, hand, indent):
        for c in self.table:
            self.add_card(c, hand, indent)
            c.setZValue(0)
        self.table = []
        self.add_cards()
        self.move_ends(True)



    def ii_attack(self):
        print("Atake")
        s = "--move "
        s += " ".join(list(map(str, self.ii_hand)))
        if self.table != []:
            s += " --thrownrepulsed "
            s += " ".join(list(map(str, self.table)))
            s += " --trump "
        else:
            s += " --thrownrepulsed"
            s += " --trump "
        s += self.trump
        if self.deck.qsize() <= 4:
            s += " --endmode"
        print(s)
        s = s.split(" ")
        rez = subprocess.check_output(["./control"] + s, universal_newlines=True)
        print(rez)
        if rez == "Bat":
            self.bito()
            return

        rez = rez.split(" ")

        for c in self.ii_hand:
            #print("Card {} {} Card {} {}".format(c.adv, c.suit, rez[1], int_to_suit[rez[2]]))
            if c.adv == rez[1] and c.suit == suit_to_int[rez[2]]:
                self.add_to_table(c)
                break

        self.is_trow_up = True

    def ii_defense(self):
        print("Defense")
        s = "--fight_back "
        s += " ".join(list(map(str, self.ii_hand)))
        s += " --slugger "
        s += str(self.table[-1])
        s += " --trump "
        s += str(self.trump)
        print(s)
        s = s.split(" ")
        rez = subprocess.check_output(["./control"] + s, universal_newlines=True)
        print(rez)
        if rez == "Not strayed":
            self.take(self.ii_hand, indent_ii)
            return

        rez = rez.split(" ")
        rez = rez[1:]
        for c in self.ii_hand:
            if c.adv == rez[0] and c.suit == suit_to_int[rez[1]]:
                self.add_to_table(c)
                break


if __name__ == "__main__":
    app = QApplication(sys.argv)
    game = Game()
    app.exec_()