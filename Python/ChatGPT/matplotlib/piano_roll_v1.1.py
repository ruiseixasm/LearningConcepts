import matplotlib.pyplot as plt
import numpy as np
from fractions import Fraction

class Note:
    def __init__(self, position_beats: Fraction, duration_notevalue: Fraction, pitch: int, quantization: Fraction):
        self.position_beats: Fraction = position_beats 
        self.duration_notevalue: Fraction = duration_notevalue 
        self.pitch: int = pitch 
        self.quantization: Fraction = quantization 

def plot_piano_roll(notes):
    """
    Plot a piano roll for a list of Note objects with a quantization grid.
    
    :param notes: List of Note objects.
    """
    fig, ax = plt.subplots(figsize=(12, 6))

    # Find min quantization step (smallest fraction in all notes)
    min_quantization = min(note.quantization for note in notes)

    # Determine the max beat position for grid
    max_position = max(note.position_beats + note.duration_notevalue for note in notes)

    # Get pitch range
    min_pitch = min(note.pitch for note in notes)
    max_pitch = max(note.pitch for note in notes)

    # Draw vertical grid lines based on quantization
    grid_positions = np.arange(0, float(max_position) + float(min_quantization), float(min_quantization))
    for grid_pos in grid_positions:
        ax.axvline(grid_pos, color='gray', linestyle='dotted', alpha=0.5)

    # Draw horizontal line for Middle C (MIDI 60)
    if 60 in range(min_pitch, max_pitch + 1):
        ax.axhline(y=60, color='red', linestyle='dashed', linewidth=1, label="Middle C (C4)")

    # Plot notes
    for note in notes:
        ax.barh(y=note.pitch, width=float(note.duration_notevalue), left=float(note.position_beats), 
                height=0.8, color='blue', edgecolor='black')

    ax.set_xlabel("Time (beats)")
    ax.set_ylabel("MIDI Note Number")
    ax.set_title("Piano Roll with Quantization Grid")

    # Set MIDI note ticks and ensure increasing pitch order
    ax.set_yticks(range(min_pitch, max_pitch + 1))
    ax.invert_yaxis()  # Ensures MIDI 0 is at the bottom
    ax.legend()

    plt.show()

# Example Notes
notes = [
    Note(Fraction(0), Fraction(1, 4), 60, Fraction(1, 16)),  # C4
    Note(Fraction(1, 4), Fraction(1, 8), 62, Fraction(1, 16)),  # D4
    Note(Fraction(1, 2), Fraction(3, 16), 64, Fraction(1, 16)),  # E4
    Note(Fraction(3, 4), Fraction(1, 4), 65, Fraction(1, 16)),  # F4
    Note(Fraction(1), Fraction(1, 8), 67, Fraction(1, 16)),  # G4
    Note(Fraction(5, 4), Fraction(1, 16), 69, Fraction(1, 16)),  # A4
    Note(Fraction(6, 4), Fraction(1, 4), 71, Fraction(1, 16)),  # B4
    Note(Fraction(2), Fraction(1, 2), 72, Fraction(1, 16))   # C5
]

plot_piano_roll(notes)
