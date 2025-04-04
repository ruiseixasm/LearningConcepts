import matplotlib.pyplot as plt
from matplotlib.widgets import Button
from fractions import Fraction
import random

# Dummy Note class
class Note:
    def __init__(self, position_beats, duration_notevalue, pitch, quantization):
        self.position_beats = Fraction(position_beats)
        self.duration_notevalue = Fraction(duration_notevalue)
        self.pitch = pitch
        self.quantization = Fraction(quantization)

# Generate dummy note data
def generate_notes(seed):
    random.seed(seed)
    notes = []
    for i in range(10):
        pos = Fraction(i, 2)
        dur = Fraction(1, 4)
        pitch = random.randint(50, 80)
        quant = Fraction(1, 16)
        notes.append(Note(pos, dur, pitch, quant))
    return notes

# Store history of plotted note sets
history = [(generate_notes(i), f"Plot #{i+1}") for i in range(5)]
current_index = [0]  # Use a mutable object to keep it updated in callbacks

# Plotting function
def plot_notes(notes, title):
    ax.clear()

    min_pitch = min(note.pitch for note in notes) // 12 * 12
    max_pitch = max(note.pitch for note in notes) // 12 * 12 + 12

    for note in notes:
        ax.barh(note.pitch, float(note.duration_notevalue), left=float(note.position_beats), height=0.5, color='green', edgecolor='black')

    ax.set_title(title)
    ax.set_xlabel("Beats")
    ax.set_ylabel("Pitch")

    ax.set_yticks(range(min_pitch, max_pitch + 1))
    y_labels = [f"**{p}**" if p == 60 else str(p) for p in range(min_pitch, max_pitch + 1)]
    ax.set_yticklabels(y_labels)

    ax.set_ylim(min_pitch - 0.5, max_pitch + 0.5)
    ax.set_xlim(0, 8)
    fig.canvas.draw_idle()

# Button callbacks
def next_plot(event):
    if current_index[0] < len(history) - 1:
        current_index[0] += 1
        notes, title = history[current_index[0]]
        plot_notes(notes, title)

def prev_plot(event):
    if current_index[0] > 0:
        current_index[0] -= 1
        notes, title = history[current_index[0]]
        plot_notes(notes, title)

# Setup figure and axes
fig, ax = plt.subplots(figsize=(10, 6))
plt.subplots_adjust(bottom=0.2)

# Add buttons
axprev = plt.axes([0.3, 0.05, 0.1, 0.075])
axnext = plt.axes([0.6, 0.05, 0.1, 0.075])
bnext = Button(axnext, 'Next')
bprev = Button(axprev, 'Previous')
bnext.on_clicked(next_plot)
bprev.on_clicked(prev_plot)

# Initial plot
plot_notes(*history[0])

plt.show()
