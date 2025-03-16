from tkinter import Tk, Button, Frame
from walkData import WalkData


class Console:

    def __init__(self) -> None:
        """
        Inicjalizuje obiekt Console, tworząc interfejs użytkownika do analizy chodu człowieka.

        W tej metodzie inicjalizowane są wszystkie elementy GUI, w tym główne okno,
        ramka dla przycisków oraz obiekt WalkData do obsługi plików z danymi akcelometrycznymi.

        Tworzy również przycisk, który umożliwia użytkownikowi wybór pliku z danymi.
        """

        self.root = Tk()
        self.root.configure(bg="#283538")
        self.root.title("Analiza chodu człowieka")
        self.root.protocol("WM_DELETE_WINDOW", self.close)

        self.root.grid_rowconfigure(0, weight=1)  # Wykresy będą wypełniały całą przestrzeń
        self.root.grid_columnconfigure(0, weight=1)  # Kolumna 1 będzie dla wykresów
        self.root.grid_columnconfigure(1, weight=0)  # Kolumna 2 dla przycisku (nie rozciąga się)

        self.buttonframe = Frame(self.root, bg="#283538")

        self.walk_data = WalkData(self.root, self.buttonframe)

        self.select_file_button = Button(
            text="Select File",
            command=self.walk_data.selectFile,
            width=20,
            height=2,
            bg = "lightblue",
            master = self.buttonframe
        )
        self.select_file_button.grid(row=0, column=0, padx=5, pady=5)
        self.buttonframe.grid(row=0, column=1, padx=10, pady=10, sticky="n")
        self.root.mainloop()

    def close(self):
        """
        Zamyka aplikację, niszcząc główne okno.
        """
        self.root.destroy()











