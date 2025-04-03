import matplotlib.pyplot as plt
import numpy as np
from fractions import Fraction

class Note:
    def __init__(self, position_beats: Fraction, duration_notevalue: Fraction, pitch: int, quantization: Fraction):
        self.position_beats: Fraction = position_beats 
        self.duration_notevalue: Fraction = duration_notevalue 
        self.pitch: int = pitch 
        self.quantization: Fraction = quantization 

def is_black_key(midi_note):
    """Returns True if the given MIDI note is a black key."""
    black_keys = {1, 3, 6, 8, 10}  # C#, D#, F#, G#, A#
    return (midi_note % 12) in black_keys

def plot_piano_roll(notes):
    """
    Plot a piano roll for a list of Note objects with a quantization grid.
    Black key rows are shaded to simulate a piano keyboard.
    
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

    # Shade black keys
    for pitch in range(min_pitch, max_pitch + 1):
        if is_black_key(pitch):
            ax.axhspan(pitch - 0.5, pitch + 0.5, color='lightgray', alpha=0.5)

    # Plot notes
    for note in notes:
        ax.barh(y=note.pitch, width=float(note.duration_notevalue), left=float(note.position_beats), 
                height=0.8, color='blue', edgecolor='black')

    ax.set_xlabel("Time (beats)")
    ax.set_ylabel("MIDI Note Number")
    ax.set_title("Piano Roll with Simulated Black Keys")

    # Set MIDI note ticks
    ax.set_yticks(range(min_pitch, max_pitch + 1))
    y_labels = [f"**{p}**" if p == 60 else str(p) for p in range(min_pitch, max_pitch + 1)]  # Bold Middle C
    ax.set_yticklabels(y_labels, fontsize=10, fontweight='bold' if 60 in range(min_pitch, max_pitch + 1) else 'normal')

    ax.set_ylim(min_pitch - 0.5, max_pitch + 0.5)  # Ensure all notes fit
    ax.invert_yaxis()  # This keeps pitch increasing from bottom to top

    plt.show()

# Example Notes
notes = [
    Note(Fraction(0), Fraction(1, 4), 60, Fraction(1, 16)),  # C4
    Note(Fraction(1, 4), Fraction(1, 8), 61, Fraction(1, 16)),  # C#4
    Note(Fraction(1, 2), Fraction(3, 16), 63, Fraction(1, 16)),  # D#4
    Note(Fraction(3, 4), Fraction(1, 4), 65, Fraction(1, 16)),  # F4
    Note(Fraction(1), Fraction(1, 8), 66, Fraction(1, 16)),  # F#4
    Note(Fraction(5, 4), Fraction(1, 16), 68, Fraction(1, 16)),  # G#4
    Note(Fraction(6, 4), Fraction(1, 4), 70, Fraction(1, 16)),  # A#4
    Note(Fraction(2), Fraction(1, 2), 72, Fraction(1, 16))   # C5
]

plot_piano_roll(notes)
