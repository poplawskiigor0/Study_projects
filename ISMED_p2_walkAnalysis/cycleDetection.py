import numpy as np
from scipy.signal import find_peaks


def moving_average(data, window_size):
    """
    Oblicza średnią kroczącą dla podanego zestawu danych.

    Parametry:
    data (pandas.Series): Dane wejściowe, na których będzie obliczana średnia krocząca.
    window_size (int): Rozmiar okna średniej kroczącej.

    Zwraca:
    pandas.Series: Średnia krocząca dla danych wejściowych.
    """
    return data.rolling(window=window_size, center=True).mean().bfill().ffill()


def detectXPeaks(data, window_size=50):
    """
    Wykrywa piki w serii danych 'ax_filtered' na podstawie średniej kroczącej.

    Parametry:
    data (pandas.DataFrame): Dane wejściowe zawierające kolumny 'time' i 'ax_filtered'.
    window_size (int, opcjonalnie): Rozmiar okna dla średniej kroczącej. Domyślnie 50.

    Zwraca:
    tuple:
        - pandas.Series: Punkty czasowe, w których wykryto piki w danych 'ax_filtered'.
        - pandas.Series: Wartości 'ax_filtered' w punktach, w których wykryto piki.
    """
    ax_mean = moving_average(data['ax_filtered'], window_size)

    xpluspeaks, _ = find_peaks(
        data['ax_filtered'],
        distance=20,
        height=ax_mean.values, #znajdujemy piki względem średniej kroczącej
        prominence=0.05
    )

    xminuspeaks, _ = find_peaks(
        -data['ax_filtered'],
        distance=20,
        height=ax_mean.values, #znajdujemy piki względem średniej kroczącej
        prominence=0.05
    )

    xpeaks = np.sort(np.concatenate((xminuspeaks, xpluspeaks)))
    time_peaks_x = data['time'].iloc[xpeaks].reset_index(drop=True)
    ax_peaks = data['ax_filtered'].iloc[xpeaks].reset_index(drop=True)

    return time_peaks_x, ax_peaks


def detectSingleStance(data, time_double_stance):
    """
    Wykrywa fazy pojedynczego podparcia na podstawie interwałów czasowych podwójnego podparcia.

    Parametry:
    data (pandas.DataFrame): Dane wejściowe zawierające kolumny 'time' i 'ax_filtered'.
    time_double_stance (list of lists): Lista interwałów czasowych dla faz podwójnego podparcia.

    Zwraca:
    list of lists: Zagnieżdżona lista, w której każda podlista odpowiada fazie pojedynczego podparcia,
                   pierwsza podlista to lewa noga, druga to prawa noga.
    """
    # Znajdowanie pików

    single_stance_array = [[] for _ in range(2)]  # Wymiar 1: która noga (na podstawie piku accx)
                              # Wymiar 2: która to z kolei faza single stance
                              # Wymiar 3: seria czasów dla danej fazy single stance

    x_times_peaks, ax_peaks = detectXPeaks(data)


    for i in range(len(time_double_stance) - 1):
        # Zbieramy czasy z dwóch kolejnych faz podwójnego podparcia
        start_time = time_double_stance[i][0]  # Początek pierwszej fazy podwójnego podparcia
        end_time = time_double_stance[i + 1][-1]  # Koniec drugiej fazy podwójnego podparcia

        # Filtrujemy czasy, które znajdują się w tym zakresie (single stance)
        single_stance_serie = data['time'][(data['time'] >= start_time) & (data['time'] <= end_time)].values
        nearest_x_time=min(x_times_peaks, key=lambda x: abs(x - np.mean(single_stance_serie)))
        current_index = x_times_peaks[x_times_peaks == nearest_x_time].index[0]
        prev_index = x_times_peaks.index[x_times_peaks.index.get_loc(current_index) - 1] if x_times_peaks.index.get_loc(current_index) > 0 else None
        next_index = x_times_peaks.index[x_times_peaks.index.get_loc(current_index) + 1] if x_times_peaks.index.get_loc(current_index) < len(x_times_peaks) - 1 else None
        leg_def_value=ax_peaks[current_index]
        next_x_peak_value=ax_peaks[next_index] if next_index is not None else 0
        prev_x_peak_value=ax_peaks[prev_index] if prev_index is not None else 0
        #mozna tez zastosowac tutaj porownanie wartosci do usrednionej wartosci calego ax_filtered
        if leg_def_value > np.mean([prev_x_peak_value, next_x_peak_value]):
            single_stance_array[0].append(single_stance_serie) #podpór lewej nogi
        else:
            single_stance_array[1].append(single_stance_serie) #podpór prawej nogi
    return single_stance_array


def detectDoubleStance(data):
    """
    Wykrywa fazy podwójnego podparcia na podstawie danych 'ay_filtered'.

    Parametry:
    data (pandas.DataFrame): Dane wejściowe zawierające kolumny 'time' i 'ay_filtered'.

    Zwraca:
    tuple:
        - list: Punkty czasowe, w których wykryto fazy podwójnego podparcia.
        - pandas.Series: Wartości 'ay_filtered' w punktach, w których wykryto fazy podwójnego podparcia.
    """
    # Znajdowanie pików
    ypluspeaks, _ = find_peaks(data['ay_filtered'], distance=20, height=np.mean(data['ay_filtered']), prominence=0.3)

    # Wyciągnięcie czasu i wartości pików
    time_peaks = data['time'].iloc[ypluspeaks]  # Czas odpowiadający pikom

    cycle_time = np.diff(data['time'].iloc[ypluspeaks])
    avg_cycle_time = np.mean(cycle_time)

    new_time_peaks=peaksWithWidth(time_peaks, avg_cycle_time*0.12, data)
    new_peaks=[]

    for series in new_time_peaks:
        indices = np.searchsorted(data['time'].values, series)
        new_peaks.extend(indices)

    return new_time_peaks, data['ay_filtered'].iloc[new_peaks]

def peaksWithWidth(time_peaks, width, data):
    """
    Dostosowuje wykryte piki na podstawie określonej szerokości i zwraca odpowiadające im interwały czasowe.

    Parametry:
    time_peaks (list): Lista punktów czasowych odpowiadających wykrytym pikiem.
    width (float): Szerokość, którą należy zastosować wokół każdego piku dla nowych pików.
    data (pandas.DataFrame): Dane wejściowe zawierające kolumnę 'time'.

    Zwraca:
    list: Lista interwałów czasowych odpowiadających dostosowanym pikom.
    """
    new_peaks = []
    for peak in time_peaks:
        start = peak - (width/2)
        end = peak + (width/2)
        values_in_window = data['time'][(data['time'] >= start) & (data['time'] <= end)]
        new_peaks.append(values_in_window.tolist())
    return new_peaks