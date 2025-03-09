import pandas as pd


class Product:
    product_counter=0

    def __init__(self, n:str, cal: float ,p:float , f:float , car:float) -> None:
        """Inicjalizuje obiekt Produkt z podaną nazwą, kaloriami, białkiem, tłuszczem i węglowodanami.

        Argumenty:
            n (str): Nazwa produktu.
            cal (float): Ilość kalorii w 100g produktu.
            p (float): Ilość białka w 100g produktu.
            f (float): Ilość tłuszczu w 100g produktu.
            car (float): Ilość węglowodanów w 100g produktu.
        """
        self.name = n
        self.calories = cal
        self.protein = p
        self.fats = f
        self.carbs = car
        Product.product_counter+=1

    def __str__(self) -> str:
        """Zwraca tekstową reprezentację produktu.

        Zwraca:
            str: Nazwa produktu oraz jego wartości odżywcze na 100g (kalorie, białko, tłuszcze, węglowodany).
        """
        return f"{self.name} {self.calories} {self.protein} {self.fats} {self.carbs}"

def getData(file: str) -> list[Product]:
    """Wczytuje dane produktów z pliku Excel i zwraca listę obiektów Product.

    Argumenty:
        file (str): Ścieżka do pliku Excel z danymi produktów.

    Zwraca:
        list[Product]: Lista produktów wczytanych z pliku.
    """
    products = []

    df = pd.read_excel(file, engine='openpyxl', header=2)

    for _, row in df.iterrows():
        try:
            product = Product(
                str(row['Name']),
                float(row['Energy, kilocalories (kcal)']),
                float(row['Fat, total (g)']),
                float(row['Protein (g)']),
                float(row['Carbohydrates, available (g)'])
            )
            products.append(product)
        except KeyError as e:
            print(f"Brak kluczowej kolumny: {e}")
        except ValueError:
            print("Błąd konwersji wartości na liczbę - może występować brak danych.")

    return products

    # def getData(file: str) -> list[Product]:
    # """Wczytuje dane produktów z pliku CSV i zwraca listę obiektów Product.
    #
    #     Argumenty:
    #         file (str): Ścieżka do pliku CSV z danymi produktów.
    #
    #     Zwraca:
    #             list[Product]: Lista produktów wczytanych z pliku.
    #     """
    # #     products = []
    #     with open(file, newline="", encoding="utf-8") as file:
    #         reader = csv.reader(file, delimiter=",")
    #
    #         next(reader)
    #         for row in reader:
    #             products.append(Product(str(row[0]), float(row[1]), float(row[2]), float(row[3]), float(row[4])))
    #     return products

def printProducts(products: list[Product]) -> None:
    """Wypisuje na ekranie wszystkie produkty z listy.

    Argumenty:
        products (list[Product]): Lista obiektów Product do wyświetlenia.
    """
    print("\nProducts in base:")
    for p in products:
        print(p)

def search(products: list[Product], pname: str) -> Product:
    """Wyszukuje produkt w liście produktów na podstawie jego nazwy.

    Argumenty:
        products (list[Product]): Lista produktów, w której należy szukać.
        pname (str): Nazwa produktu do wyszukania.

    Zwraca:
        Product: Znaleziony produkt, jeśli istnieje, inaczej None.
    """
    for p in products:
        if p.name == pname:
            return p