from prompt_toolkit import prompt
from prompt_toolkit.formatted_text import HTML

# Simple prompt with >>> 
user_input = prompt('>>> ')

# For styled prompt
user_input = prompt(HTML('<ansigreen>>>> </ansigreen>'))
