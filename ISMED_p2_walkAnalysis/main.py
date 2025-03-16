import aplication as app


def main():
    """
    Główna funkcja aplikacji.

    Funkcja ta uruchamia konsolę aplikacji poprzez wywołanie metody `Console` z modułu `aplication`.
    Jest to punkt startowy programu, który wywołuje główną funkcjonalność.

    Zwraca:
        None
    """
    app.Console()


if __name__ == "__main__":
    """
    Sprawdza, czy skrypt jest uruchamiany bezpośrednio, a nie importowany jako moduł.

    Jeśli skrypt jest uruchamiany bezpośrednio, wywołuje funkcję `main`, aby rozpocząć działanie aplikacji.

    Zwraca:
        None
    """
    main()