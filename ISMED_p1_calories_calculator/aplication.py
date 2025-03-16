import product as product
from menu import Menu


class Console:

    def __init__(self, fname: str) -> None:
        """Inicjalizuje obiekt Console z plikiem zawierającym dane produktów.

        Argumenty:
            fname (str): Nazwa pliku z danymi produktów.
        """
        self.filename = fname
        self.products_list = []
        if self.readProducts():
            product.printProducts(self.products_list)
            self.goApp()

    def readProducts(self) -> bool:
        """Odczytuje listę produktów z pliku i zapisuje je w liście produktów.

        Zwraca:
            bool: True, jeśli odczyt się powiódł, w przeciwnym razie False.
         """

        result = False

        try:
            self.products_list = product.getData(self.filename)
            result = True
        except OSError as error:
            print(error)

        return result

    def goApp(self):
        """Uruchamia aplikację konsolową i obsługuje interakcje z użytkownikiem."""
        go = True
        mymenu = Menu()

        while go:
            try:
                choose = int(input("\nWybierz opcje:\n"
                                   "1- zamknij\n"
                                   "2- dodaj posiłek\n"
                                   "3- usuń posiłek\n"
                                   "4- wyswietl moje posiłki\n"
                                   "5- podaj kalorie w posiłkach\n"
                                   "6- podaj białko w posiłkach\n"
                                   "7- podaj tłuszcze w posiłkach\n"
                                   "8- podaj węglowodany w posiłkach\n"))
                if choose == 1:
                    go = False
                elif choose == 2:
                    mymenu.addMeal(self.products_list)
                elif choose == 3:
                    mymenu.deleteMeal()
                elif choose == 4:
                    mymenu.printMenu()
                elif choose == 5:
                    print(f"Kalorie w posiłkach: {mymenu.countCalories():.2f}")
                elif choose == 6:
                    print(f"Białko w posiłkach: {mymenu.countProtein():.2f}")
                elif choose == 7:
                    print(f"Tłuszcze w posiłkach: {mymenu.countFats():.2f}")
                elif choose == 8:
                    print(f"Węglowodany w posiłkach: {mymenu.countCarbs():.2f}")
                else:
                    print("Błędna opcja, podaj liczbe 1-8")
            except ValueError:
                print("Błąd: Podaj liczbę całkowitą od 1 do 8")