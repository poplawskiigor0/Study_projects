from product import Product


class Meal(Product):
    def __init__(self, p: Product, weight: float) -> None:
        """Inicjalizuje obiekt Meal (posiłki) na podstawie produktu i wagi.

        Argumenty:
            p (Product): Produkt bazowy, z którego powstaje posiłek.
            weight (float): Waga posiłku w gramach.
        """
        super().__init__(p.name, p.calories, p.protein, p.fats, p.carbs)
        self.weight = weight
        self.wcalories = self.calories * weight * 0.01
        self.wprotein = self.protein * weight * 0.01
        self.wfats = self.fats * weight * 0.01
        self.wcarbs = self.carbs * weight * 0.01

    def __str__(self) -> str:
        """Zwraca tekstową reprezentację posiłku, z uwzględnieniem wartości odżywczych i wagi.

        Zwraca:
            str: Nazwa posiłku oraz wartości odżywcze (kalorie, białko, tłuszcze, węglowodany) oraz wagę.
        """
        return f"{self.name} kalorie-{self.wcalories:.2f} białko(g)-{self.wprotein:.2f} tłuszcze(g)-{self.wfats:.2f} węglowodany(g)-{self.wcarbs:.2f} waga(g)-{self.weight}"



