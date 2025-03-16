import numpy as np
from matplotlib.figure import Figure

def plotPhases(data, single_stance_array):
    """
    Tworzy wykres przedstawiający fazy chodu dla obu nóg.

    Funkcja ta generuje wykres, na którym dla obu nóg (prawej i lewej) pokazane są fazy
    chodu, takie jak fazy "swing" (unoszenia nogi) oraz "stand" (stania na nodze).

    Argumenty:
    data (DataFrame): Dane wejściowe, zawierające informacje o czasie i przyspieszeniach.
    single_stance_array (list): Lista zawierająca dane o fazach stania (lewa i prawa noga).

    Zwraca:
    fig (Figure): Obiekt wykresu.
    ax (Axes): Obiekt osi wykresu.
    """
    fig = Figure(figsize=(1, 1))
    fig.patch.set_facecolor("#283538")
    ax = fig.add_subplot(111)
    label_added=False

    ax.tick_params(axis="both", colors="white", labelsize=8)
    ax.set_ylim(0, 2)
    ax.set_xlim(0, data['time'].iloc[-1])
    ax.set_facecolor('#e6fff2')

    # Tworzenie paska faz dla prawej nogi
    maxtime=max(single_stance_array[1][-1][-1],single_stance_array[0][-1][-1])
    prev=min(single_stance_array[1][0][0],single_stance_array[0][0][0])
    for series in single_stance_array[1]:  # 1 => prawa noga
        if not label_added:
            ax.broken_barh([(prev, abs(prev - series[0]))], (0, 1), facecolors = '#00ff80', edgecolors = 'black', alpha = 0.6,label= 'swing state')
            prev = series[-1]
            ax.broken_barh([(series[0], abs(series[-1] - series[0]))], (0, 1), facecolors='#00994d', edgecolors='black',alpha=0.6,label= 'stand state')
            label_added = True
        else:
            ax.broken_barh([(prev, abs(prev - series[0]))], (0, 1), facecolors='#00ff80', edgecolors='black', alpha=0.6)
            prev = series[-1]
            ax.broken_barh([(series[0], abs(series[-1] - series[0]))], (0, 1), facecolors='#00994d', edgecolors='black',alpha=0.6)

    ax.broken_barh([(prev, abs(maxtime-prev))], (0, 1), facecolors='#00ff80', edgecolors='black',alpha=0.6)

    prev=min(single_stance_array[1][0][0],single_stance_array[0][0][0])
    # Tworzenie paska faz dla lewej nogi
    for series in single_stance_array[0]:  # 0 => lewa noga
        ax.broken_barh([(prev, abs(prev - series[0]))], (1, 1), facecolors='#00ff80', edgecolors='black', alpha=0.6,)
        prev = series[-1]
        ax.broken_barh([(series[0], abs(series[-1] - series[0]))], (1, 1), facecolors='#00994d', edgecolors='black',alpha=0.6)

    ax.broken_barh([(prev, abs(maxtime - prev))], (1, 1), facecolors='#00ff80', edgecolors='black', alpha=0.6)

    # Ustawienia osi i etykiet
    ax.set_yticks([0.5, 1.5])  # Pozycje dla etykiet
    ax.set_yticklabels(["Right Leg", "Left Leg"], color="white")
    ax.get_xaxis().tick_bottom()  # Tylko dolna oś X
    ax.get_yaxis().tick_left()  # Tylko lewa oś Y
    ax.legend(loc='upper left')

    ax.set_xlabel("Time(s)", color="white", fontsize=8, labelpad=1)
    ax.set_title("Gait phases for both legs", color="white", fontsize=8, pad=5)

    return fig, ax

def plotT(data):
    """
    Tworzy wykres przedstawiający przyspieszenie w kierunku całkowitym (aT).

    Wykres porównuje oryginalne dane aT oraz dane po filtracji.

    Argumenty:
    data (DataFrame): Dane wejściowe, zawierające czas oraz przyspieszenie w kierunku całkowitym.

    Zwraca:
    fig (Figure): Obiekt wykresu.
    ax (Axes): Obiekt osi wykresu.
    """
    fig = Figure(figsize=(1,1))
    fig.patch.set_facecolor("#283538")
    ax = fig.add_subplot(111)
    ax.tick_params(axis="both", colors="white", labelsize=8)
    ax.set_xlim(0, data['time'].iloc[-1])

    ax.plot(data['time'], data['aT (m/s^2)'], label='Original aT', alpha=0.5)
    ax.plot(data['time'], data['aT_filtered'], label='Filtered aT', linewidth=2)

    ax.set_title("Resultant Acceleration ", color="white", fontsize=8, pad=5)
    ax.set_xlabel("Time(s)", color="white", fontsize=8, labelpad=1)
    ax.set_ylabel("Total Acceleration (m/s^2)", color="white", fontsize=8, labelpad=5)
    ax.legend(loc='upper left')

    return fig, ax

def plotY(data, time_peaks):
    """
    Tworzy wykres przedstawiający przyspieszenie w kierunku Y (ay).

    Wykres porównuje oryginalne dane ay oraz dane po filtracji, a także zaznacza punkty podwójnego wsparcia.

    Argumenty:
    data (DataFrame): Dane wejściowe, zawierające czas oraz przyspieszenie w kierunku Y.
    time_peaks (list): Lista punktów czasowych, które reprezentują fazy podwójnego wsparcia.

    Zwraca:
    fig (Figure): Obiekt wykresu.
    ax (Axes): Obiekt osi wykresu.
    """
    fig = Figure(figsize=(1,1))
    fig.patch.set_facecolor("#283538")
    ax = fig.add_subplot(111)
    ax.tick_params(axis="both", colors="white", labelsize=8)
    ax.plot(data['time'], data['ay (m/s^2)'], label='Original ay', alpha=0.5)
    ax.plot(data['time'], data['ay_filtered'], label='Filtered ay', linewidth=2)
    ax.set_xlim(0, data['time'].iloc[-1])
    y_peaks=[]
    time1d_peaks=[]
    for series in time_peaks:
        # Dla każdej serii czasów
        indices = np.searchsorted(data['time'].values, series)
        y_peaks.extend(indices)
        time1d_peaks.extend(data['time'].iloc[indices])
    ax.scatter(time1d_peaks, data['ay_filtered'].iloc[y_peaks], color='red', label="Double support phases")

    ax.legend(loc='upper left')
    ax.set_title("Acceleration Y", color="white", fontsize=8, pad=5)
    ax.set_xlabel("Time(s)", color="white", fontsize=8, labelpad=1)
    ax.set_ylabel("Total Acceleration (m/s^2)", color="white", fontsize=8, labelpad=5)
    return fig, ax

def plotX(data,time_peaks):
    """
    Tworzy wykres przedstawiający przyspieszenie w kierunku X (ax).

    Wykres porównuje oryginalne dane ax oraz dane po filtracji, a także zaznacza punkty,
    które mogą wskazywać na obciążenie jednej nogi.

    Argumenty:
    data (DataFrame): Dane wejściowe, zawierające czas oraz przyspieszenie w kierunku X.
    time_peaks (list): Lista punktów czasowych, które mogą wskazywać na obciążenie jednej nogi.

    Zwraca:
    fig (Figure): Obiekt wykresu.
    ax (Axes): Obiekt osi wykresu.
    """
    fig = Figure(figsize=(1,1))
    fig.patch.set_facecolor("#283538")
    ax = fig.add_subplot(111)
    ax.tick_params(axis="both", colors="white", labelsize=8)
    ax.plot(data['time'], data['ax (m/s^2)'], label='Original ax', alpha=0.5)
    ax.plot(data['time'], data['ax_filtered'], label='Filtered ax', linewidth=2)
    ax.set_xlim(0, data['time'].iloc[-1])
    ax.scatter(time_peaks, data['ax_filtered'].iloc[np.searchsorted(data['time'],time_peaks)], color='red', label="Potential weight bearing on one leg")

    ax.legend(loc='upper left')
    ax.set_title("Acceleration X", color="white", fontsize=8, pad=5)
    ax.set_xlabel("Time(s)", color="white", fontsize=8, labelpad=1)
    ax.set_ylabel("Total Acceleration (m/s^2)", color="white", fontsize=8, labelpad=5)
    return fig, ax

def plotZ(data):
    """
    Tworzy wykres przedstawiający przyspieszenie w kierunku Z (az).

    Wykres porównuje oryginalne dane az oraz dane po filtracji.

    Argumenty:
    data (DataFrame): Dane wejściowe, zawierające czas oraz przyspieszenie w kierunku Z.

    Zwraca:
    fig (Figure): Obiekt wykresu.
    ax (Axes): Obiekt osi wykresu.
    """
    fig = Figure(figsize=(1,1))
    fig.patch.set_facecolor("#283538")
    ax = fig.add_subplot(111)
    ax.tick_params(axis="both", colors="white", labelsize=8)
    ax.plot(data['time'], data['az (m/s^2)'], label='Original az', alpha=0.5)
    ax.plot(data['time'], data['az_filtered'], label='Filtered az', linewidth=2)
    ax.set_xlim(0, data['time'].iloc[-1])
    ax.legend(loc='upper left')

    ax.set_title("Acceleration Z", color="white", fontsize=8, pad=5)
    ax.set_xlabel("Time(s)", color="white", fontsize=8, labelpad=1)
    ax.set_ylabel("Total Acceleration (m/s^2)", color="white", fontsize=8, labelpad=5)
    return fig, ax