from tkinter import filedialog, messagebox
import pandas as pd
import tkinter as tk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from scipy.signal import butter, filtfilt

import plots
from cycleDetection import detectSingleStance, detectDoubleStance, detectXPeaks


class WalkData:
    def __init__(self, root, buttonframe):
        """
        Inicjalizuje klasę WalkData, ustawiając główne elementy interfejsu i dane wejściowe.

        Parametry:
        root (tk.Tk): Główne okno aplikacji.
        buttonframe (tk.Frame): Frame, w którym znajdują się przyciski.
        """
        self.root = root
        self.data = []
        self.buttonframe = buttonframe
        self.plotframe = tk.Frame(self.root, bg="#283538")
        self.stepslabel = tk.Label(self.buttonframe)
        self.plotframe.grid(row=0, column=0, sticky="nsew")

    def clear_frame(self, frame):
        """
        Usuwa wszystkie widgety z podanego Frame.

        Parametry:
        frame (tk.Frame): Frame, z którego mają zostać usunięte widgety.
        """
        for widget in frame.winfo_children():
            widget.destroy()

    def clear_labels(self, frame):
        """
        Usuwa tylko widgety typu Label z podanego Frame, pozostawiając inne elementy.

        Parametry:
        frame (tk.Frame): Frame, z którego mają zostać usunięte widgety Label.
        """
        for widget in frame.winfo_children():
            if isinstance(widget, tk.Label):  # Sprawdzamy, czy widget jest instancją Label
                widget.destroy()


    def fileOperation(self, fname):
        """
        Wykonuje operacje na pliku, formatuje dane, filtruje je, a następnie rysuje wykresy.

        Parametry:
        fname (str): Ścieżka do pliku CSV, który ma zostać załadowany.
        """
        try:
            self.data = self.formatData(fname)
            self.clear_frame(self.plotframe)
            self.clear_labels(self.buttonframe)
            self.plotframe.config(bg="#283538")

            # Filtracja danych
            self.data['aT_filtered'] = self.apply_butterworth_filter(self.data, 'aT (m/s^2)', 0.02)
            self.data['az_filtered'] = self.apply_butterworth_filter(self.data, 'az (m/s^2)', 0.02)
            self.data['ay_filtered'] = self.apply_butterworth_filter(self.data, 'ay (m/s^2)', 0.02)
            self.data['ax_filtered'] = self.apply_butterworth_filter(self.data, 'ax (m/s^2)', 0.015)
            time_double_stance, acc_double_stance = detectDoubleStance(self.data)
            x_time_peaks, ax_peaks = detectXPeaks(self.data)
            single_stance_array = detectSingleStance(self.data, time_double_stance)

            steps=len(single_stance_array[0])+len(single_stance_array[1])

            figures = [
                plots.plotPhases(self.data, single_stance_array),
                plots.plotY(self.data, time_double_stance),
                plots.plotX(self.data, x_time_peaks),
                plots.plotZ(self.data),
                plots.plotT(self.data),
            ]

            # Dodawanie każdego wykresu do GUI
            for fig, ax in figures:
                fig.subplots_adjust(bottom = 0.2, top = 0.9)
                canvas = FigureCanvasTkAgg(fig, master=self.plotframe)
                canvas.draw()
                canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)


            self.stepslabel = tk.Label(master=self.buttonframe, text=f"Number of steps : {steps}", font=("Arial", 12), padx=5, pady=5, bg="#283538", fg="white")
            self.stepslabel.grid(row=1, column=0, padx=10, pady=10)
            self.plotframe.config(bg="#283538")

        except FileNotFoundError:
            print(f"The file {fname} was not found.")
            exit()
        except Exception as e:
            print(f"An error occurred while loading the file: {e}")
            exit()

    def selectFile(self):
        """
        Obsługuje wybór pliku i jego przetwarzanie.
        """
        # Open a file dialog
        fname = filedialog.askopenfilename(
            title="Select a CSV File",
            filetypes=[("CSV Files", "*.csv"), ("All Files", "*.*")]
        )

        if not fname:
            # Show a message if no file was selected
            messagebox.showinfo("No File Selected", "You did not select a file.")
            return

        try:
            # Process the selected file
            self.fileOperation(fname)
        except Exception as e:
            # Show error message in case of failure
            messagebox.showerror("Error", f"An error occurred: {e}")

    @staticmethod
    def apply_butterworth_filter(data, column, wn):
        """
        Zastosowuje filtr Butterwortha do danych w określonej kolumnie.

        Parametry:
        data (pandas.DataFrame): Dane wejściowe.
        column (str): Nazwa kolumny, do której ma zostać zastosowany filtr.
        wn (float): Częstotliwość odcięcia filtru.

        Zwraca:
        numpy.ndarray: Filtrowane dane.
        """
        b, a = butter(3, wn, btype='low', analog=False)
        filtered_data = filtfilt(b, a, data[column])
        return filtered_data

    @staticmethod
    def formatData(fname):
        """
        Formatuje dane z pliku CSV.

        Parametry:
        fname (str): Ścieżka do pliku CSV.

        Zwraca:
        pandas.DataFrame: Sformatowane dane.
        """
        # z- przód tył
        # y - góra dół
        # x - prawo lewo
        data = pd.read_csv(fname, sep=';')
        data = data.replace({',': '.'}, regex=True)
        data['time'] = pd.to_numeric(data['time'])
        data['ax (m/s^2)'] = pd.to_numeric(data['ax (m/s^2)'])
        data['ay (m/s^2)'] = pd.to_numeric(data['ay (m/s^2)'])
        data['az (m/s^2)'] = pd.to_numeric(data['az (m/s^2)'])
        data['aT (m/s^2)'] = pd.to_numeric(data['aT (m/s^2)'])
        #print(data)

        return data