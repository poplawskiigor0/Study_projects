from meal import Meal
import product
from product import Product


class Menu:
    def __init__(self):
        """Inicjalizuje Menu z pustą listą na posiłki."""
        self.menu = []

    def countCalories(self) -> float:
        """Oblicza całkowitą liczbę kalorii dla wszystkich posiłków w menu.

        Zwraca:
            float: Całkowita liczba kalorii we wszystkich posiłkach.
        """
        return self.summarize(lambda p: p.calories)

    def countProtein(self) -> float:
        """Oblicza całkowitą ilość białka dla wszystkich posiłków w menu.

        Zwraca:
            float: Całkowita ilość białka (w gramach) we wszystkich posiłkach.
        """
        return self.summarize(lambda p: p.protein)

    def countFats(self) -> float:
        """Oblicza całkowitą ilość tłuszczów dla wszystkich posiłków w menu.

        Zwraca:
            float: Całkowita ilość tłuszczów (w gramach) we wszystkich posiłkach.
        """
        return self.summarize(lambda p: p.fats)

    def countCarbs(self) -> float:
        """Oblicza całkowitą ilość węglowodanów dla wszystkich posiłków w menu.

        Zwraca:
            float: Całkowita ilość węglowodanów (w gramach) we wszystkich posiłkach.
        """
        return self.summarize(lambda p: p.carbs)

    def summarize(self, option) -> float:
        """Sumuje dany składnik odżywczy dla wszystkich posiłków w menu.

        Argumenty:
            option (function): Funkcja lambda, która wybiera składnik odżywczy z produktu.

        Zwraca:
            float: Całkowita ilość wybranego składnika odżywczego (w gramach) we wszystkich posiłkach.
        """
        total = 0
        for m in self.menu:
            total += option(m) * m.weight * 0.01
        return total

    def deleteMeal(self):
        """Usuwa posiłek z menu na podstawie wyboru użytkownika.

        Pyta użytkownika o numer posiłku do usunięcia.
        """
        deletenr = 0
        if len(self.menu) == 0:
            print("Nie ma żadnych posiłków")
            return
        while deletenr <= 0 or deletenr > len(self.menu):
            try:
                deletenr = int(input("Podaj nr posiłku do usunięcia\n"))
            except ValueError:
                print("Błąd: Podaj wartość w zakresie listy\n")
        self.menu.pop(deletenr - 1)

    def addMeal(self, base:list[Product]):
        """Dodaje posiłek do menu poprzez wybór produktu i określenie jego wagi.

        Argumenty:
            base (list[Product]): Lista dostępnych produktów do wyboru.
        """
        adding = True
        while (adding):
            chosename = str(input("Podaj nazwe produktu(f by zakonczyć)\n"))
            if chosename == "f":
                adding = False
            else:
                chosenproduct = product.search(base, chosename)
                if chosenproduct:
                    pweight = 0
                    while pweight == 0:
                        try:
                            pweight = float(input("Podaj ilość (g)\n"))
                        except ValueError:
                            print("Błąd: Podaj wartość liczbową\n")
                    self.menu.append(Meal(chosenproduct, pweight))
                else:
                    print("Nie ma takiego produktu w bazie\n")

    def printMenu(self):
        """Wyświetla szczegóły wszystkich posiłków obecnych w menu."""
        print("\nLista posiłków:")
        for m in self.menu:
            print(m)




